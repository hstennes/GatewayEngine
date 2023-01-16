//
// Created by Hank Stennes on 1/15/23.
//

#include "Component.h"

namespace Gateway {

    Component::Component(CompType type, int id, int x, int y) : type(type), id(id), x(x), y(y) {
        inputs.resize(type.defInputs);
        outputs.resize(type.defOutputs);
    }

    void Component::updateIds(std::unordered_map<int, int> &idMap) {
        id = idMap[id];
        for(Pin& input : inputs) {
            for(int& i : input.connect) {
                i = idMap[i];
            }
        }
        for(Pin& output : outputs) {
            for(int & i : output.connect) {
                i = idMap[i];
            }
        }
    }

} // Gateway