//
// Created by Hank Stennes on 1/24/23.
//

#ifndef GATEWAYENGINE_UTILS_H
#define GATEWAYENGINE_UTILS_H

#include <string>

namespace Gateway {

    namespace Utils {
        std::string CTYPE_STRS[] = {"AND", "OR", "XOR", "NOT", "NAND", "NOR", "XNOR",
                                    "SWITCH", "LIGHT", "CHIP", "SPLITTER"};

        std::array<int, 2> numInputsOutputs(CompType type) {
            switch(type) {
                case AND: case OR: case XOR: case NAND: case NOR: case XNOR:
                    return {2, 1};
                case NOT:
                    return {1, 1};
                case SWITCH:
                    return {0, 1};
                case LIGHT:
                    return {1, 0};
                case CHIP: case SPLITTER:
                    return {-1, -1};
            }
        }
    }
}

#endif //GATEWAYENGINE_UTILS_H
