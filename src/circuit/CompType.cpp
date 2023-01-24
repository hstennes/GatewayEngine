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
    const CompType CompType::CHIP = CompType(9, -1, -1);

    std::ostream& operator<<(std::ostream &strm, const CompType &a) {
        if(a == CompType::AND) return strm << "AND";
        else if(a == CompType::OR) return strm << "OR";
        else if(a == CompType::XOR) return strm << "XOR";
        else if(a == CompType::NOT) return strm << "NOT";
        else if(a == CompType::NAND) return strm << "NAND";
        else if(a == CompType::NOR) return strm << "NOR";
        else if(a == CompType::XNOR) return strm << "XNOR";
        else if(a == CompType::SWITCH) return strm << "SWITCH";
        else if(a == CompType::LIGHT) return strm << "LIGHT";
        else if(a == CompType::CHIP) return strm << "CHIP";
        return strm << "Unknown";
    }
}