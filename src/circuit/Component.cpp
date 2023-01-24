//
// Created by Hank Stennes on 1/15/23.
//

#include "Component.h"

namespace Gateway {

    Component::Component(CompType type, int id, int x, int y) : type(type), id(id), x(x), y(y), data(nullptr) {
        inputs.resize(type.defInputs);
        outputs.resize(type.defOutputs);
    }

    void Component::connectInput(int index, int id) {
        //TODO check that input has max one connection
        inputs[index].connect(id);
    }

    void Component::disconnectInput(int index, int id) {
        inputs[index].disconnect(id);
    }

    void Component::connectOutput(int index, int id) {
        outputs[index].connect(id);
    }

    void Component::disconnectOutput(int index, int id) {
        outputs[index].disconnect(id);
    }

    int Component::getNumInputs() {
        return (int) inputs.size();
    }

    int Component::getNumOutputs() {
        return (int) outputs.size();
    }

    void Component::updateIds(std::unordered_map<int, int> &idMap) {
        id = idMap[id];
        for(Pin& input : inputs) input.updateIds(idMap);
        for(Pin& output : outputs) output.updateIds(idMap);
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

    const std::vector<Pin> &Component::getInputs() const {
        return inputs;
    }

    const std::vector<Pin> &Component::getOutputs() const {
        return outputs;
    }

    CompData *Component::getData() const {
        return data;
    }

} // Gateway