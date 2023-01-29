//
// Created by Hank Stennes on 1/16/23.
//

#ifndef GATEWAYENGINE_NODE_H
#define GATEWAYENGINE_NODE_H

#include <vector>

namespace Gateway {

    class Node {
    public:

        /*
         * Start index for this component's signal data in the signal array. The data starts with output signals,
         * followed by all nested signals if this node represents a chip.
         */
        int sigAddr;

        /*
         * Start index of connection data for this node in the connect array
         * Format {in1, in2, out1end, out2end, out1a, out1b..., out2a, out2b..., split1, split2}
         */
        int connectAddr;

        /*
         * Number of input connections
         */
        int numInputs;

        /**
         * Number of output connections
         */
        int numOutputs;

        /*
         * General purpose data, depends on type of component
         */
        uint64_t data;
    };

} // Gateway

#endif //GATEWAYENGINE_NODE_H
