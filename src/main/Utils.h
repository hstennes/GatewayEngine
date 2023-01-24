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
    }

}

#endif //GATEWAYENGINE_UTILS_H
