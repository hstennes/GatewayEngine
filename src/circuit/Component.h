//
// Created by Hank Stennes on 1/15/23.
//

#pragma once

#include <vector>
#include <unordered_map>
#include "Pin.h"
#include "CompType.h"

namespace Gateway {

    class Component {

    public:
        int id;

        int x, y;

        const CompType type;

        std::vector<Pin> inputs;

        std::vector<Pin> outputs;

        Component(CompType type, int id, int x, int y);

    public:
        void updateIds(std::unordered_map<int, int>& idMap);
    };

} // Gateway
