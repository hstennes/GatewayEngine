//
// Created by Hank Stennes on 1/15/23.
//

#ifndef GATEWAYENGINE_CHIPTEMPLATE_H
#define GATEWAYENGINE_CHIPTEMPLATE_H

#include "../circuit/Circuit.h"
#include "ChipSim.h"

namespace Gateway {

    class ChipTemplate {
    public:
        Circuit circuit;
        ChipSim sim;

    public:
        ChipTemplate(Circuit& fullCircuit, std::vector<int>& subset);

        void compile();
    };

} // Gateway

#endif //GATEWAYENGINE_CHIPTEMPLATE_H
