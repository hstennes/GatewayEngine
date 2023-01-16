//
// Created by Hank Stennes on 1/15/23.
//

#include "ChipTemplate.h"

namespace Gateway {

    ChipTemplate::ChipTemplate(Circuit* fullCircuit, std::vector<int>& subset) {
        fullCircuit->subset(&circuit, subset);
    }

    void ChipTemplate::compile() {
        std::unordered_map<int, int> compToSig;


    }

} // Gateway