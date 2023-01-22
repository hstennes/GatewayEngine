//
// Created by Hank Stennes on 1/15/23.
//

#ifndef GATEWAYENGINE_CIRCUIT_H
#define GATEWAYENGINE_CIRCUIT_H

#include <vector>
#include "Component.h"

namespace Gateway {

    class Circuit {
    public:
        struct Iterator
        {
            Iterator(Circuit* circuit, int index) : circuit(circuit), index(index) {}

            Component& operator*() const { return circuit->components[circuit->usedIds[index]];  }
            Iterator& operator++() { index++; return *this; }
            Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
            friend bool operator==(const Iterator& a, const Iterator& b) { return a.index == b.index; }
            friend bool operator!=(const Iterator& a, const Iterator& b) { return a.index != b.index; }

        private:
            Circuit* circuit;
            int index;
        };

        Iterator begin() { return {this, 0}; }
        Iterator end()   { return {this, (int) usedIds.size()}; }

    private:
        std::vector<Component> components;

        std::vector<int> freeIds;

        std::vector<int> usedIds;

        int maxId = -1;

    public:
        int addComp(CompType type, int x, int y);

        Component& getComp(int id);

        void removeComp(int id);

        void connect(int source, int sourcePinIdx, int dest, int destPinIdx);

        void subset(Circuit* newCircuit, std::vector<int>& ids);

    private:
        int nextId();
    };

} // Gateway

#endif //GATEWAYENGINE_CIRCUIT_H
