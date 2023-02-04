//
// Created by Hank Stennes on 1/16/23.
//

#ifndef GATEWAYENGINE_CHIPSIM_H
#define GATEWAYENGINE_CHIPSIM_H

#include <vector>
#include "Node.h"
#include "../circuit/Circuit.h"
#include "ActiveStack.h"

namespace Gateway {

    class ChipSim {
    private:
        std::vector<Node> nodes;

        std::vector<int> connect;

        std::vector<int> outputAddrs;

        std::vector<int> defSignals;

        int numInputs;

    public:
        explicit ChipSim(Circuit& circuit);

    private:
        //COMPILATION METHODS
        void compile(Circuit& circuit);

        void populateDataArrays(Component &comp, std::unordered_map<int, int> &compToSig,
                                std::unordered_map<int, int> &compToConnect,
                                std::unordered_map<int, int> &compToNode, std::unordered_map<int, int> &lightToOutput);

        static int calcConnectDataSize(Circuit& circuit, Component& comp);

        void createNode(Circuit& circuit, Component &comp, int &nodeIdx, int &sigIdx, int &connectIdx,
                        std::unordered_map<int, int> &compToSig,
                        std::unordered_map<int, int> &compToConnect, std::unordered_map<int, int> &compToNode);

        //SIMULATION METHODS
        void updateEventDriven(int* signals, ActiveStack& active);

        void updateNodeEventDriven(int nodeId, int* signals, ActiveStack& active);

        bool prepareInput(int* signals, ActiveStack& active, Circuit& circuit, int chipId);

        bool prepareInput(int* signals, const int* outerSignals, ActiveStack& active, ChipSim& sim, int nodeId);

        bool setOutputAndMark(Node& node, int* signals, int newSignal, int outputIdx, ActiveStack& active);

        void markConnectedComps(Node& node, int outputIdx, ActiveStack active);

    public:
        void update(int* signals, ActiveStack& active, Circuit& circuit, int compId);

        void update(int* signals, int* outerSignals, ActiveStack& active, ChipSim& sim, int nodeId);

        [[nodiscard]] const std::vector<int> &getDefSignals() const;

        [[nodiscard]] int getOutput(int* signals, int idx);
    };

} // Gateway

#endif //GATEWAYENGINE_CHIPSIM_H
