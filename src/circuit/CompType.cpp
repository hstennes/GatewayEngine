//
// Created by Hank Stennes on 1/15/23.
//

#include "CompType.h"

namespace Gateway {

    const CompType CompType::AND = CompType(0, 2, 1);
    const CompType CompType::OR = CompType(1, 2, 1);
    const CompType CompType::XOR = CompType(2, 2, 1);
    const CompType CompType::NOT = CompType(3, 1, 1);
    const CompType CompType::NAND = CompType(4, 2, 1);
    const CompType CompType::NOR = CompType(5, 2, 1);
    const CompType CompType::XNOR = CompType(6, 2, 1);
    const CompType CompType::SWITCH = CompType(7, 0, 1);
    const CompType CompType::LIGHT = CompType(8, 1, 0);

}