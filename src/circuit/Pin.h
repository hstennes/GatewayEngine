//
// Created by Hank Stennes on 1/15/23.
//

#ifndef GATEWAYENGINE_PIN_H
#define GATEWAYENGINE_PIN_H

#include <vector>

namespace Gateway {
    class Pin {

    public:
        enum class Type {
            Input, Output
        };

        const Type type = Type::Input;

        std::vector<int> connect;

        int signal;

        Pin() = default;

        Pin(Type type);
    };
}

#endif //GATEWAYENGINE_PIN_H
