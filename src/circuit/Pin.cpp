//
// Created by Hank Stennes on 1/15/23.
//

#include "Pin.h"

namespace Gateway {

    Pin::Pin(Pin::Type type) : type(type), signal(0) {}

    Pin::Type Pin::getType() const {
        return type;
    }

    int Pin::getSignal() const {
        return signal;
    }

    void Pin::connect(int id) {
        connections.push_back(id);
    }

    void Pin::disconnect(int id) {
        auto it = std::find(connections.begin(), connections.end(), id);
        if (it != connections.end()) {
            connections.erase(it);
        }
    }

    void Pin::updateIds(std::unordered_map<int, int> &idMap) {
        for(int& i : connections) {
            i = idMap[i];
        }
    }
}
