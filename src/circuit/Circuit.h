//
// Created by Hank Stennes on 1/15/23.
//

#ifndef GATEWAYENGINE_CIRCUIT_H
#define GATEWAYENGINE_CIRCUIT_H

#include <vector>
#include "Component.h"

namespace Gateway {

    class Circuit {
    private:
        std::vector<Component> components;

        std::vector<int> freeIds;

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
