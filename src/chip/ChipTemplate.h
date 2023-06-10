//
// Created by Hank Stennes on 1/15/23.
//

#ifndef GATEWAYENGINE_CHIPTEMPLATE_H
#define GATEWAYENGINE_CHIPTEMPLATE_H

#include "../circuit/Circuit.h"
#include "ChipSim.h"
#include <vector>

namespace Gateway {

    class ChipTemplate {
    private:
        Circuit circuit;

        ChipSim sim;

        int id;

    public:
        ChipTemplate(Circuit& circuit, int id);

        [[nodiscard]] const std::vector<int> &getDefSignals() const;

        [[nodiscard]] ChipSim &getSim();

        [[nodiscard]] int getNumInputs();

        [[nodiscard]] int getNumOutputs();

        [[nodiscard]] int getId() const;
    };

} // Gateway

#endif //GATEWAYENGINE_CHIPTEMPLATE_H
