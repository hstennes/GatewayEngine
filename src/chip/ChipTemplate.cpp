//
// Created by Hank Stennes on 1/15/23.
//

#include "ChipTemplate.h"

namespace Gateway {

    ChipTemplate::ChipTemplate(Circuit& circuit, int id) : sim(ChipSim(circuit)), id(id) { }

    const std::vector<int> &ChipTemplate::getDefSignals() const {
        return sim.getDefSignals();
    }

    int ChipTemplate::getId() const {
        return id;
    }

    ChipSim &ChipTemplate::getSim() {
        return sim;
    }

} // Gateway