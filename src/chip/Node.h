//
// Created by Hank Stennes on 1/16/23.
//

#ifndef GATEWAYENGINE_NODE_H
#define GATEWAYENGINE_NODE_H

#include <vector>
#include "../circuit/CompType.h"
#include "ActiveStack.h"

namespace Gateway {

    struct Node {

        CompType type;

        /*
         * Start index for this component's signal data in the signal array. The data starts with output signals,
         * followed by all nested signals if this node represents a chip.
         */
        int sigAddr;

        /*
         * Start index of connection data for this node in the connect array
         * Format {in1, in2, out1start, out2start, out2end, out1a, out1b..., out2a, out2b..., split1, split2}
         */
        int connectAddr;

        /*
         * Number of input connections
         */
        uint8_t numInputs;

        /**
         * Number of output connections
         */
        uint8_t numOutputs;

        /*
         * General purpose data, depends on type of component
         */
        int data;

        Node() = default;

        Node(CompType type, int sigAddr, int connectAddr, uint8_t numInputs, uint8_t numOutputs);
    };

} // Gateway

#endif //GATEWAYENGINE_NODE_H
