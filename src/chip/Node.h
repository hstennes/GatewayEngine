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
         * Format {in1, in2, out1a, out1b, undef, out2a, undef, undef, out3a, out3b, out3c, split1, split2}
         * In this example, there are 2 inputs and 3 outputs. The first output has 2 connected components, the second
         * has 1, and the third has 3. The in values refer to indices in the signals array, and the out values are
         * indices in the nodes array. If the component is a splitter, the split array is appended to the end of this
         * data.
         */
        int connectAddr;

        /*
         * Number of input connections
         */
        int numInputs;

        /*
         * Number of values corresponding to each connection in the mark data. This is equal to the greatest number of
         * wires on any output connection. In the example for connectAddr, this is 3, because the third connection has 3
         * wires.
         */
        int connectMarkSize;

        /*
         * General purpose data, depends on type of component
         */
        uint64_t data;
    };

} // Gateway

#endif //GATEWAYENGINE_NODE_H
