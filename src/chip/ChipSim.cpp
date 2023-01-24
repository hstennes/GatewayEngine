//
// Created by Hank Stennes on 1/16/23.
//

#include "ChipSim.h"
#include "ChipTemplate.h"

namespace Gateway {

    ChipSim::ChipSim(Circuit &circuit) {

    }

    void ChipSim::compile(Circuit& circuit) {

        /*
         * How it works in OG Gateway:
         *
         * nodeComps starts with all switches in the order that input connections are considered. These become StartNodes,
         * which do essentially nothing besides mark their outputs if update is called. This has the effect of making the first
         * few signals in the signals array the "input signals" to the circuit.
         *
         */

        std::unordered_map<int, int> compToSig;

        /*
         * Signal address starts as 1 because the first index is reserved for a hardcoded 0. Components with empty input
         * connections are pointed to this address.
         */
        int sigAddr = 1;

        for(Component& comp : circuit) {
            compToSig.insert({comp.getId(), sigAddr});
            sigAddr += (int) comp.getNumInputs();
            if(comp.getType() == CompType::CHIP) sigAddr += (int) comp.getData()->chipTemplate->getDefSignals().size();
        }

        //list of indices for output signals

        //list of indices of input nodes
    }

} // Gateway