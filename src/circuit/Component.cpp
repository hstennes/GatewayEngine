//
// Created by Hank Stennes on 1/15/23.
//

#include "Component.h"

namespace Gateway {

    Component::Component(CompType type, int id, int x, int y) : type(type), id(id), x(x), y(y), data(nullptr) {
        //TODO make util methods
        inputs.resize(2);
        outputs.resize(2);
    }

    void Component::connectInput(int index, int id, int otherIdx) {
        //TODO check that input has max one connection
        inputs[index].connect(id, otherIdx);
    }

    void Component::disconnectInput(int index) {
        inputs[index].disconnect();
    }

    void Component::connectOutput(int index, int id, int otherIdx) {
        outputs[index].connect(id, otherIdx);
    }

    void Component::disconnectOutput(int index, int id) {
        outputs[index].disconnect(id);
    }

    int Component::getNumInputs() const {
        return (int) inputs.size();
    }

    int Component::getNumOutputs() const {
        return (int) outputs.size();
    }

    void Component::updateIds(std::unordered_map<int, int> &idMap) {
        id = idMap[id];
        for(InPin& input : inputs) input.updateIds(idMap);
        for(OutPin& output : outputs) output.updateIds(idMap);
    }

    int Component::getId() const {
        return id;
    }

    void Component::setId(int id) {
        Component::id = id;
    }

    int Component::getX() const {
        return x;
    }

    void Component::setX(int x) {
        Component::x = x;
    }

    int Component::getY() const {
        return y;
    }

    void Component::setY(int y) {
        Component::y = y;
    }

    const CompType &Component::getType() const {
        return type;
    }

    const InPin &Component::getInputPin(int i) const {
        return inputs[i];
    }

    const OutPin &Component::getOutputPin(int i) const {
        return outputs[i];
    }

    CompData *Component::getData() const {
        return data;
    }

} // Gateway