//
// Created by Hank Stennes on 1/15/23.
//

#ifndef GATEWAYENGINE_COMPTYPE_H
#define GATEWAYENGINE_COMPTYPE_H

#include <ostream>

namespace Gateway {

    enum CompType {
        AND = 0,
        OR,
        XOR,
        NOT,
        NAND,
        NOR,
        XNOR,
        SWITCH,
        LIGHT,
        CHIP,
        SPLITTER,
    };

} // Gateway

#endif //GATEWAYENGINE_COMPTYPE_H
