//
// Created by Hank Stennes on 1/15/23.
//

#include "Circuit.h"
#include <unordered_map>

namespace Gateway {

    int Circuit::addComp(CompType type, int x, int y) {
        int id = nextId();
        components.emplace_back(type, id, x, y);
        usedIds.push_back(id);
        return id;
    }

    void Circuit::removeComp(int id) {
        freeIds.push_back(id);
        auto it = std::find(usedIds.begin(), usedIds.end(), id);
        if (it != usedIds.end()) {
            usedIds.erase(it);
        }
    }

    Component& Circuit::getComp(int id) {
        return components[id];
    }

    void Circuit::connect(int source, int sourcePinIdx, int dest, int destPinIdx) {
        components[source].connectOutput(sourcePinIdx, dest);
        components[dest].connectInput(destPinIdx, source);
        //TODO add a wire
    }

    int Circuit::nextId() {
        if(freeIds.empty()) return ++maxId;
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
        newCircuit->maxId = (int) ids.size();
    }
} // Gateway