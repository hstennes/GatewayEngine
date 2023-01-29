//
// Created by Hank Stennes on 1/24/23.
//

#include "InPin.h"

namespace Gateway {

    void InPin::connect(int id, int otherIdx) {
        connection[0] = id;
        connection[1] = otherIdx;
    }

    void InPin::disconnect() {
        connection[0] = -1;
        connection[1] = -1;
    }

    void InPin::updateIds(std::unordered_map<int, int> &idMap) {
        connection[0] = idMap[connection[0]];
    }

    bool InPin::isConnected() {
        return connection[0] == -1;
    }

    const std::array<int, 2> &InPin::getConnection() const {
        return connection;
    }
} // Gateway