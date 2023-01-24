//
// Created by Hank Stennes on 1/16/23.
//

#ifndef GATEWAYENGINE_CHIPSIM_H
#define GATEWAYENGINE_CHIPSIM_H

#include <vector>
#include "Node.h"
#include "../circuit/Circuit.h"

namespace Gateway {

    class ChipSim {
    public:
        std::vector<Node> nodes;
        std::vector<int> connect;
        std::vector<int> outputAddrs;

    public:
        ChipSim(Circuit& circuit);

    private:
        void compile(Circuit& circuit);

        int calcConnectDataSize(Component& comp);
    };

} // Gateway

#endif //GATEWAYENGINE_CHIPSIM_H
