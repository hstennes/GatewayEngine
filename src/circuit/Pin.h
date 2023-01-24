//
// Created by Hank Stennes on 1/15/23.
//

#ifndef GATEWAYENGINE_PIN_H
#define GATEWAYENGINE_PIN_H

#include <vector>
#include <array>
#include <unordered_map>

namespace Gateway {

    class Pin {

    public:
        enum class Type {
            Input, Output
        };

    private:
        const Type type = Type::Input;

        std::vector<std::array<int, 2>> connections;

        int signal;

    public:
        Pin() = default;

        explicit Pin(Type type);

        void connect(int id, int otherIdx);

        void disconnect(int id);

        void updateIds(std::unordered_map<int, int>& idMap);

        [[nodiscard]] Type getType() const;

        [[nodiscard]] int getSignal() const;

        [[nodiscard]] int getNumConnections() const;

        [[nodiscard]] const std::array<int, 2> &getConnection(int i) const;
    };
}

#endif //GATEWAYENGINE_PIN_H
