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
        int nodeIndex = 0, sigAddr = 1, connectAddr = 0;

        for(int id : circuit.getSwitches()) {
            compToNode.insert({id, nodeIndex});
            nodeIndex += 1;
            compToSig.insert({id, sigAddr});
            sigAddr += 1;
            compToConnect.insert({id, connectAddr});
            connectAddr += 1;
        }

        for(Component& comp : circuit) {
            if(comp.getType() == CompType::SWITCH) continue;

            compToNode.insert({comp.getId(), nodeIndex});
            nodeIndex += 1;

            compToSig.insert({comp.getId(), sigAddr});
            sigAddr += (int) comp.getNumInputs();
            if(comp.getType() == CompType::CHIP)
                sigAddr += (int) comp.getData()->chipTemplate->getDefSignals().size();

            compToConnect.insert({comp.getId(), connectAddr});
            connectAddr += calcConnectDataSize(comp);
        }
        connect.resize(connectAddr);

        for(Component& comp : circuit) {
            int id = comp.getId();
            connectAddr = compToConnect[id];

            for(int i = 0; i < comp.getNumInputs(); i++) {
                Pin pin = comp.getInputPin(i);

            }
        }
    }

    int ChipSim::calcConnectDataSize(Component &comp) {

    }

} // Gateway