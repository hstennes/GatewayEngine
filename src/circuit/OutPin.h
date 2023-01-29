//
// Created by Hank Stennes on 1/15/23.
//

#ifndef GATEWAYENGINE_OUTPIN_H
#define GATEWAYENGINE_OUTPIN_H

#include <vector>
#include <array>
#include <unordered_map>

namespace Gateway {

    class OutPin {

    private:
        std::vector<std::array<int, 2>> connections;

        int signal;

    public:
        void connect(int id, int otherIdx);

        void disconnect(int id);

        void updateIds(std::unordered_map<int, int>& idMap);

        [[nodiscard]] int getSignal() const;

        [[nodiscard]] int getNumConnections() const;

        [[nodiscard]] const std::array<int, 2> &getConnection(int i) const;
    };
}

#endif //GATEWAYENGINE_OUTPIN_H
