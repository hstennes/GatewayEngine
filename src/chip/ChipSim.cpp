//
// Created by Hank Stennes on 1/16/23.
//

#include "ChipSim.h"
#include "ChipTemplate.h"

namespace Gateway {

    ChipSim::ChipSim(Circuit &circuit) {
        numInputs = (int) circuit.getSwitches().size();
        compile(circuit);
    }

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
                                   comp.getNumInputs(), comp.getNumOutputs(), 0);

        compToNode[comp.getId()] = nodeIdx;
        nodeIdx += 1;

        compToSig[comp.getId()] = sigIdx;
        sigIdx += (int) comp.getNumOutputs();
        if(comp.getType() == CompType::CHIP)
            sigIdx += (int) comp.getData()->chipTemplate->getDefSignals().size();

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
            InPin pin = comp.getInputPin(i);
            connect[connectItr1] = compToSig[pin.getConnection()[0]] + pin.getConnection()[1];
            connectItr1++;
        }

        int connectItr2 = connectItr1 + comp.getNumOutputs();
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
            connect[connectItr1] = connectItr2 - connectIdx;
        }
        //TODO copy inner chip signals

        if(comp.getType() == CompType::SPLITTER){
            int* connectPtr = connect.data() + connectItr2;
            std::vector<int>& split = comp.getData()->split;
            memcpy(connectPtr, split.data(), split.size() * sizeof(int));
        }
    }

    int ChipSim::calcConnectDataSize(Circuit& circuit, Component& comp) {
        int size = comp.getNumInputs() + comp.getNumOutputs();
        for(int i = 0; i < comp.getNumOutputs(); i++) {
            const OutPin& pin = comp.getOutputPin(i);
            for(int j = 0; j < pin.getNumConnections(); j++) {
                if(circuit.getComp(pin.getConnection(j)[0]).getType() != CompType::LIGHT) size++;
            }
        }
        if(comp.getType() == CompType::SPLITTER) size += (int) comp.getData()->split.size();
        return size;
    }

    const std::vector<int> &ChipSim::getDefSignals() const {
        return defSignals;
    }

    void ChipSim::update(int* signals, ActiveStack &active, Circuit& circuit, int compId) {
        prepareInput(signals, active, circuit, compId);
    }

    void ChipSim::update(int* signals, int* outerSignals, ActiveStack &active, ChipSim &sim, int nodeId) {
        prepareInput(signals, outerSignals, active, sim, nodeId);
    }

    void ChipSim::prepareInput(int* signals, ActiveStack& active, Circuit& circuit, int compId) const {
        for(int i = 0; i < numInputs; i++) {
            int& currentSignal = signals[i + 1];
            int newSignal = circuit.getCompInputSignal(compId, i);
            if(newSignal != currentSignal) {
                //TODO mark stuff
                currentSignal = newSignal;
            }
        }
    }

    void ChipSim::prepareInput(int* signals, int* outerSignals, ActiveStack& active, ChipSim &sim, int nodeId) {
        for(int i = 0; i < numInputs; i++) {
            int& currentSignal = signals[i + 1];
            int newSignal = getNodeInputSignal(outerSignals, nodeId, i);
            if(newSignal != currentSignal) {
                //TODO mark stuff
                currentSignal = newSignal;
            }
        }
    }

    void ChipSim::doMark(Node& node, int outputIdx, ActiveStack active) {
        int connectAddr = node.connectAddr + node.numInputs;

    }

    int ChipSim::getNodeInputSignal(int* signals, int id, int idx) {
        return signals[connect[nodes[id].connectAddr + idx]];
    }

} // Gateway