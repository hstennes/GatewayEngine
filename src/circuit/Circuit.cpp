//
// Created by Hank Stennes on 1/15/23.
//

#include "Circuit.h"
#include <unordered_map>

namespace Gateway {

    int Circuit::addComp(CompType type, int x, int y) {
        int id = nextId();
        usedIds.push_back(id);

        if(id == components.size()) components.emplace_back(type, id, x, y);
        else components.emplace(components.begin() + id, type, id, x, y);

        if(type == CompType::LIGHT) lights.push_back(id);
        else if(type == CompType::SWITCH) switches.push_back(id);

        return id;
    }

    void Circuit::removeComp(int id) {
        auto it = std::find(usedIds.begin(), usedIds.end(), id);
        if (it != usedIds.end()) {
            usedIds.erase(it);
            freeIds.push_back(id);

            CompType type = components[id].getType();
            if(type == CompType::LIGHT) {
                auto it2 = std::find(lights.begin(), lights.end(), id);
                if (it2 != lights.end()) lights.erase(it2);
            }
            else if(type == CompType::SWITCH) {
                auto it2 = std::find(switches.begin(), switches.end(), id);
                if (it2 != switches.end()) switches.erase(it2);
            }
        }
    }

    Component& Circuit::getComp(int id) {
        return components[id];
    }

    int Circuit::size() {
        return (int) components.size();
    }

    void Circuit::connect(int source, int sourcePinIdx, int dest, int destPinIdx) {
        components[source].connectOutput(sourcePinIdx, dest, destPinIdx);
        components[dest].connectInput(destPinIdx, source, sourcePinIdx);
        //TODO add a wire
    }

    int Circuit::nextId() {
        if(freeIds.empty()) return (int) components.size();
        else {
            int newId = *freeIds.end();
            freeIds.pop_back();
            return newId;
        }
    }

    void Circuit::subset(Circuit* newCircuit, std::vector<int>& ids) {
        std::unordered_map<int, int> idMap;
        idMap[-1] = -1;
        for(int i = 0; i < ids.size(); i++) {
            idMap[ids[i]] = i;
        }

        std::vector<Component> *newComps = &(newCircuit->components);
        newComps->reserve(ids.size());
        for(int id : ids) {
            newComps->emplace_back(components[id]);
            newComps->back().updateIds(idMap);
        }
    }

    const std::vector<int> &Circuit::getSwitches() const {
        return switches;
    }

    const std::vector<int> &Circuit::getLights() const {
        return lights;
    }
} // Gateway