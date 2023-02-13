//
// Created by Hank Stennes on 1/16/23.
//

#include "Node.h"

namespace Gateway {

    Node::Node(CompType type, int sigAddr, int connectAddr, uint8_t numInputs, uint8_t numOutputs)
        :type(type), sigAddr(sigAddr), connectAddr(connectAddr), numInputs(numInputs), numOutputs(numOutputs), data(0){}

} // Gateway