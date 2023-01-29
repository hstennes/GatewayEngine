//
// Created by Hank Stennes on 1/16/23.
//

#include "ChipSim.h"
#include "ChipTemplate.h"

namespace Gateway {

    ChipSim::ChipSim(Circuit &circuit) {

    }

    void ChipSim::compile(Circuit& circuit) {
        nodes.resize(circuit.size());
        std::unordered_map<int, int> compToSig;
        std::unordered_map<int, int> compToConnect;
        std::unordered_map<int, int> compToNode;

        /*
         * Signal address starts as 1 because the first index is reserved for a hardcoded 0. Components with empty input
         * connections are pointed to this address.
         */
        int nodeIdx = 0, sigIdx = 1, connectIdx = 0;

        for(int id : circuit.getSwitches()) {
            compToNode.insert({id, nodeIdx});
            nodeIdx += 1;
            compToSig.insert({id, sigIdx});
            sigIdx += 1;
            compToConnect.insert({id, connectIdx});
            connectIdx += 1;
        }

        for(Component& comp : circuit) {
            if(comp.getType() == CompType::SWITCH) continue;

            compToNode.insert({comp.getId(), nodeIdx});
            nodeIdx += 1;

            compToSig.insert({comp.getId(), sigIdx});
            sigIdx += (int) comp.getNumInputs();
            if(comp.getType() == CompType::CHIP)
                sigIdx += (int) comp.getData()->chipTemplate->getDefSignals().size();

            compToConnect.insert({comp.getId(), connectIdx});
            connectIdx += calcConnectDataSize(comp);
        }
        connect.resize(connectIdx);

        for(Component& comp : circuit) {
            int id = comp.getId();
            connectIdx = compToConnect[id];

            for(int i = 0; i < comp.getNumInputs(); i++) {
                InPin pin = comp.getInputPin(i);
                connect[connectIdx] = compToSig[pin.getConnection()[0]] + pin.getConnection()[1];
                connectIdx++;
            }

            int totalWires = 0;
            for(int i = 0; i < comp.getNumOutputs(); i++) {
//                OutPin outPin = comp.getOutputPin(i);
//                for(int j = 0; j < outPin.getNumConnections(); j++) {
//
//                }
//
//                outputEnd += outPin.getNumConnections();
//                connect[connectIdx] = outputEnd;
//                connectIdx++;
            }
        }
    }

    int ChipSim::calcConnectDataSize(Component &comp) {
        int result = maxOutputWires(comp) + comp.getNumInputs();
        if(comp.getType() == CompType::SPLITTER) result += (int) comp.getData()->split.size();
        return result;
    }

    int ChipSim::maxOutputWires(Component &comp) {
        int maxWires = 0;
        for(int i = 0; i < comp.getNumOutputs(); i++) {
            int wires = comp.getOutputPin(i).getNumConnections();
            if(wires > maxWires) maxWires = wires;
        }
        return maxWires;
    }

} // Gateway