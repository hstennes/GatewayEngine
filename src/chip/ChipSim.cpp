//
// Created by Hank Stennes on 1/16/23.
//

#include "ChipSim.h"
#include "ChipTemplate.h"
#include "TemplateList.h"

namespace Gateway {

    ChipSim::ChipSim(Circuit &circuit) {
        numInputs = (int) circuit.getSwitches().size();
        compile(circuit);
    }

    //COMPILATION METHODS

    void ChipSim::compile(Circuit& circuit) {
        nodes.resize(circuit.size());
        std::unordered_map<int, int> compToSig;
        std::unordered_map<int, int> compToConnect;
        std::unordered_map<int, int> compToNode;
        std::unordered_map<int, int> lightToOutput;

        /*
         * Signal address starts as 1 because the first index is reserved for a hardcoded 0. Components with empty input
         * connections are pointed to this address.
         */
        int nodeIdx = 0, sigIdx = 1, connectIdx = 0, lightIdx = 0;
        compToSig[-1] = 0;

        /*
         * Create node objects and populate component allocation maps. Create switches first so that the first n Nodes
         * correspond to chip inputs in the same order. This also means that indices 1 to n+1 in the signals array
         * correspond to chip input signals.
         */
        for(int id : circuit.getSwitches()) {
            createNode(circuit, circuit.getComp(id), nodeIdx, sigIdx, connectIdx,
                       compToSig, compToConnect, compToNode);
        }
        for(Component& comp : circuit) {
            if(comp.getType() != CompType::SWITCH)
                createNode(circuit, comp, nodeIdx, sigIdx, connectIdx,
                           compToSig, compToConnect, compToNode);
        }
        connect.resize(connectIdx);
        defSignals.resize(sigIdx);

        //Map light IDs to chip output indices
        for(int id : circuit.getLights()) {
            lightToOutput[id] = lightIdx;
            lightIdx++;
        }
        outputAddrs.resize(lightIdx);

        //Populate connect, defSignals and outputAddrs based on allocation maps
        for(Component& comp : circuit) {
            populateDataArrays(comp, compToSig, compToConnect, compToNode, lightToOutput);
        }
    }

    void ChipSim::createNode(Circuit& circuit, Component& comp, int& nodeIdx, int& sigIdx, int& connectIdx,
                             std::unordered_map<int, int>& compToSig,
                             std::unordered_map<int, int>& compToConnect,
                             std::unordered_map<int, int>& compToNode) {
        new (&nodes[nodeIdx]) Node(comp.getType(), sigIdx, connectIdx,
                                   comp.getNumInputs(), comp.getNumOutputs());

        compToSig[comp.getId()] = sigIdx;
        sigIdx += (int) comp.getNumOutputs();
        if(comp.getType() == CompType::CHIP) {
            ChipTemplate& chipTemplate = TEMPLATE_LIST.getTemplate(comp.getData()->getTemplateId());
            sigIdx += (int) chipTemplate.getDefSignals().size();
            nodes[nodeIdx].data = chipTemplate.getId();
        }

        compToNode[comp.getId()] = nodeIdx;
        nodeIdx += 1;
        compToConnect[comp.getId()] = connectIdx;
        connectIdx += calcConnectDataSize(circuit, comp);
    }

    void ChipSim::populateDataArrays(Component& comp, std::unordered_map<int, int>& compToSig,
                                     std::unordered_map<int, int>& compToConnect,
                                     std::unordered_map<int, int>& compToNode,
                                     std::unordered_map<int, int>& lightToOutput) {
        int id = comp.getId();
        int connectIdx = compToConnect[id];
        int connectItr1 = connectIdx;
        int sigIdx = compToSig[id];

        for(int i = 0; i < comp.getNumInputs(); i++) {
            const std::array<int, 2>& connection = comp.getInputPin(i).getConnection();
            connect[connectItr1] = compToSig[connection[0]] + connection[1];
            connectItr1++;
        }

        int connectItr2 = connectItr1;
        if(comp.getNumOutputs() > 0) {
            connectItr2 += comp.getNumOutputs() + 1;
            connect[connectItr1] = connectItr2 - connectIdx;
        }
        for(int i = 0; i < comp.getNumOutputs(); i++) {
            const OutPin& outPin = comp.getOutputPin(i);
            defSignals[sigIdx + i] = outPin.getSignal();
            for(int j = 0; j < outPin.getNumConnections(); j++) {
                int otherId = outPin.getConnection(j)[0];
                if(lightToOutput.find(otherId) == compToNode.end()) {
                    connect[connectItr2] = compToNode[otherId];
                    connectItr2++;
                }
                else outputAddrs[lightToOutput[otherId]] = compToSig[id] + j;
            }
            connectItr1++;
            connect[connectItr1] = connectItr2 - connectIdx;
        }

        if(comp.getType() == CompType::SPLITTER) {
            int* connectPtr = connect.data() + connectItr2;
            const std::vector<int>& split = comp.getData()->getSplit();
            memcpy(connectPtr, split.data(), split.size() * sizeof(int));
        }
        else if(comp.getType() == CompType::CHIP) {
            int* connectPtr = connect.data() + connectItr2;
            const std::vector<int>& innerDefSignals =
                    TEMPLATE_LIST.getTemplate(comp.getData()->getTemplateId()).getDefSignals();
            memcpy(connectPtr, innerDefSignals.data(), innerDefSignals.size() * sizeof(int));
        }
    }

    int ChipSim::calcConnectDataSize(Circuit& circuit, Component& comp) {
        int size = comp.getNumInputs();
        if(comp.getNumOutputs() > 0) size += comp.getNumOutputs() + 1;

        for(int i = 0; i < comp.getNumOutputs(); i++) {
            const OutPin& pin = comp.getOutputPin(i);
            for(int j = 0; j < pin.getNumConnections(); j++) {
                if(circuit.getComp(pin.getConnection(j)[0]).getType() != CompType::LIGHT) size++;
            }
        }
        if(comp.getType() == CompType::SPLITTER) size += (int) comp.getData()->getSplit().size();
        return size;
    }

    //SIMULATION METHODS

    void ChipSim::updateEventDriven(int *signals, ActiveStack &active) {
        while(active.hasNext()) {
            updateNodeEventDriven(active.next(), signals, active);
        }
    }

    void ChipSim::updateNodeEventDriven(int nodeId, int *signals, ActiveStack &active) {
        Node& node = nodes[nodeId];
        switch(node.type) {
            case AND: {
                int newSignal = signals[connect[node.connectAddr]];
                for (int i = 1; i < numInputs; i++) newSignal &= signals[connect[node.connectAddr + i]];
                setOutputAndMark(node, signals, newSignal, 0, active);
                break;
            }
            case OR: {
                int newSignal = signals[connect[node.connectAddr]];
                for (int i = 1; i < numInputs; i++) newSignal |= signals[connect[node.connectAddr + i]];
                setOutputAndMark(node, signals, newSignal, 0, active);
                break;
            }
            case XOR: {
                int newSignal = signals[connect[node.connectAddr]];
                for (int i = 1; i < numInputs; i++) newSignal ^= signals[connect[node.connectAddr + i]];
                setOutputAndMark(node, signals, newSignal, 0, active);
                break;
            }
            case NAND: {
                int newSignal = signals[connect[node.connectAddr]];
                for (int i = 1; i < numInputs; i++) newSignal = ~(newSignal & signals[connect[node.connectAddr + i]]);
                setOutputAndMark(node, signals, newSignal, 0, active);
                break;
            }
            case NOR: {
                int newSignal = signals[connect[node.connectAddr]];
                for (int i = 1; i < numInputs; i++) newSignal = ~(newSignal | signals[connect[node.connectAddr + i]]);
                setOutputAndMark(node, signals, newSignal, 0, active);
                break;
            }
            case XNOR: {
                int newSignal = signals[connect[node.connectAddr]];
                for (int i = 1; i < numInputs; i++) newSignal = ~(newSignal ^ signals[connect[node.connectAddr + i]]);
                setOutputAndMark(node, signals, newSignal, 0, active);
                break;
            }
            case NOT: {
                int newSignal = ~signals[connect[node.connectAddr]];
                setOutputAndMark(node, signals, newSignal, 0, active);
                break;
            }
            case CHIP: {
                ChipSim& innerSim = TEMPLATE_LIST.getTemplate(node.data).getSim();
                int* innerSignals = signals + node.sigAddr + node.numOutputs;
                active.startInner();
                innerSim.update(innerSignals, signals,active,
                                *this, nodeId);
                active.finishInner();
                for(int i = 0; i < node.numOutputs; i++)
                    setOutputAndMark(node, signals, innerSim.getOutput(innerSignals, i),
                                     i, active);
            }
        }
    }

    bool ChipSim::prepareInput(int* signals, ActiveStack& active, Circuit& circuit, int compId) {
        bool change = false;
        for(int i = 0; i < numInputs; i++) {
            int& currentSignal = signals[i + 1];
            int newSignal = circuit.getCompInputSignal(compId, i);
            if(newSignal != currentSignal) {
                change = true;
                markConnectedComps(nodes[i], 0, active);
                currentSignal = newSignal;
            }
        }
        return change;
    }

    bool ChipSim::prepareInput(int* signals, const int* outerSignals, ActiveStack& active, ChipSim &sim, int nodeId) {
        bool change = false;
        int connectAddr = sim.nodes[nodeId].connectAddr;
        for(int i = 0; i < numInputs; i++) {
            int newSignal = outerSignals[sim.connect[connectAddr + i]];
            if(setOutputAndMark(nodes[i], signals, newSignal, 0, active))
                change = true;
        }
        return change;
    }

    bool ChipSim::setOutputAndMark(Node &node, int* signals, int newSignal, int outputIdx, ActiveStack &active) {
        int& currentSignal = signals[node.sigAddr + outputIdx];
        if(newSignal != currentSignal) {
            currentSignal = newSignal;
            markConnectedComps(node, outputIdx, active);
            return true;
        }
        return false;
    }

    void ChipSim::markConnectedComps(Node& node, int outputIdx, ActiveStack active) {
        int connectAddr = node.connectAddr + node.numInputs + outputIdx;
        for(int i = connect[connectAddr]; i < connect[connectAddr + 1]; i++) {
            active.mark(connect[i]);
        }
    }

    //PUBLIC METHODS

    void ChipSim::update(int* signals, ActiveStack &active, Circuit& circuit, int compId) {
        bool change = prepareInput(signals, active, circuit, compId);
        if(change) updateEventDriven(signals, active);
    }

    void ChipSim::update(int* signals, int* outerSignals, ActiveStack &active, ChipSim &sim, int nodeId) {
        bool change = prepareInput(signals, outerSignals, active, sim, nodeId);
        if(change) updateEventDriven(signals, active);
    }

    const std::vector<int> &ChipSim::getDefSignals() const {
        return defSignals;
    }

    int ChipSim::getOutput(int* signals, int idx) {
        return signals[outputAddrs[idx]];
    }

} // Gateway