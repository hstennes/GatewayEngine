//
// Created by Hank Stennes on 1/15/23.
//

#include "OutPin.h"

namespace Gateway {

    void OutPin::connect(int id, int otherIdx) {
        connections.push_back({id, otherIdx});
    }

    void OutPin::disconnect(int id) {
        for(auto it = connections.begin(); it < connections.end(); it++) {
            if((*it)[0] == id) connections.erase(it);
        }
    }

    void OutPin::updateIds(std::unordered_map<int, int> &idMap) {
        for(std::array<int, 2>& connect : connections) {
            connect[0] = idMap[connect[0]];
        }
    }

    int OutPin::getSignal() const {
        return signal;
    }

    int OutPin::getNumConnections() const {
        return (int) connections.size();
    }

    const std::array<int, 2> &OutPin::getConnection(int i) const {
        return connections[i];
    }
}
