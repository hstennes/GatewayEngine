//
// Created by Hank Stennes on 1/15/23.
//

#ifndef GATEWAYENGINE_COMPTYPE_H
#define GATEWAYENGINE_COMPTYPE_H

#include <ostream>

namespace Gateway {

    class CompType {
    public:
        static const CompType AND;
        static const CompType OR;
        static const CompType XOR;
        static const CompType NOT;
        static const CompType NAND;
        static const CompType NOR;
        static const CompType XNOR;
        static const CompType SWITCH;
        static const CompType LIGHT;
        static const CompType CHIP;

    public:
        const int id;
        const int defInputs;
        const int defOutputs;

        bool operator==(const CompType& other) const {
            return other.id == id;
        }

    private:
        CompType(int id, int defInputs, int defOutputs) : id(id), defInputs(defInputs), defOutputs(defOutputs) {};
    };

    std::ostream& operator<<(std::ostream &strm, const CompType &a);
} // Gateway

#endif //GATEWAYENGINE_COMPTYPE_H
