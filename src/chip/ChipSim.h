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
        std::vector<int> defSignals;

    public:
        explicit ChipSim(Circuit& circuit);

    private:
        void compile(Circuit& circuit);

        void populateDataArrays(Component &comp, std::unordered_map<int, int> &compToSig,
                                std::unordered_map<int, int> &compToConnect,
                                std::unordered_map<int, int> &compToNode, std::unordered_map<int, int> &lightToOutput);

        static int calcConnectDataSize(Circuit& circuit, Component& comp);

        void createNode(Circuit& circuit, Component &comp, int &nodeIdx, int &sigIdx, int &connectIdx,
                        std::unordered_map<int, int> &compToSig,
                        std::unordered_map<int, int> &compToConnect, std::unordered_map<int, int> &compToNode);

    public:
        [[nodiscard]] const std::vector<int> &getDefSignals() const;
    };

} // Gateway

#endif //GATEWAYENGINE_CHIPSIM_H
