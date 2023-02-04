//
// Created by Hank Stennes on 2/4/23.
//

#include "TemplateList.h"

namespace Gateway {

    int TemplateList::createTemplate(Circuit &fullCircuit, std::vector<int> &subset) {
        templates.emplace_back(fullCircuit, subset);
        return (int) templates.size() - 1;
    }

    ChipTemplate &TemplateList::getTemplate(int id) {
        return templates[id];
    }
}