//
// Created by Hank Stennes on 1/15/23.
//

#include "Pin.h"

namespace Gateway {

    Pin::Pin(Pin::Type type) : type(type), signal(0) {}

    void Pin::connect(int id, int otherIdx) {
        connections.push_back({id, otherIdx});
    }

    void Pin::disconnect(int id) {
        for(auto it = connections.begin(); it < connections.end(); it++) {
            if((*it)[0] == id) connections.erase(it);
        }
    }

    void Pin::updateIds(std::unordered_map<int, int> &idMap) {
        for(std::array<int, 2>& connect : connections) {
            connect[0] = idMap[connect[0]];
        }
    }

    Pin::Type Pin::getType() const {
        return type;
    }

    int Pin::getSignal() const {
        return signal;
    }

    int Pin::getNumConnections() const {
        return (int) connections.size();
    }

    const std::array<int, 2> &Pin::getConnection(int i) const {
        return connections[i];
    }
}
