//
// Created by Hank Stennes on 1/15/23.
//

#pragma once

#include <vector>
#include <unordered_map>
#include "OutPin.h"
#include "CompType.h"
#include "CompData.h"
#include "InPin.h"

namespace Gateway {

    class Component {

    private:
        int id;

        int x, y;

        CompType type;

        std::vector<InPin> inputs;

        std::vector<OutPin> outputs;

        CompData* data;

    public:
        Component(CompType type, int id, int x, int y);

        void initChip(int templateId);

        void initSplitter(std::vector<int>& split);

        void connectInput(int index, int id, int otherIdx);

        void disconnectInput(int index);

        void connectOutput(int index, int id, int otherIdx);

        void disconnectOutput(int index, int id);

        [[nodiscard]] int getNumInputs() const;

        [[nodiscard]] int getNumOutputs() const;

        void updateIds(std::unordered_map<int, int>& idMap);

        [[nodiscard]] int getId() const;

        void setId(int id);

        [[nodiscard]] int getX() const;

        void setX(int x);

        [[nodiscard]] int getY() const;

        void setY(int y);

        [[nodiscard]] const CompType &getType() const;

        [[nodiscard]] const InPin &getInputPin(int i) const;

        [[nodiscard]] const OutPin &getOutputPin(int i) const;

        [[nodiscard]] CompData *getData() const;
    };

} // Gateway
