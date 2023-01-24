//
// Created by Hank Stennes on 1/15/23.
//

#ifndef GATEWAYENGINE_PIN_H
#define GATEWAYENGINE_PIN_H

#include <vector>
#include <unordered_map>

namespace Gateway {
    class Pin {

    public:
        enum class Type {
            Input, Output
        };

    private:
        const Type type = Type::Input;

        std::vector<int> connections;

        int signal;

    public:
        Pin() = default;

        explicit Pin(Type type);

        [[nodiscard]] Type getType() const;

        [[nodiscard]] int getSignal() const;

        void connect(int id);

        void disconnect(int id);

        void updateIds(std::unordered_map<int, int>& idMap);
    };
}

#endif //GATEWAYENGINE_PIN_H
