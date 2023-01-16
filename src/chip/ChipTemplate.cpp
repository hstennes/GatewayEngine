//
// Created by Hank Stennes on 1/15/23.
//

#include "ChipTemplate.h"

namespace Gateway {

    ChipTemplate::ChipTemplate(Circuit* fullCircuit, std::vector<int>& subset) {
        fullCircuit->subset(&circuit, subset);
    }



} // Gateway