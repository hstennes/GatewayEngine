//
// Created by Hank Stennes on 2/4/23.
//

#include "TemplateList.h"

namespace Gateway {

    int TemplateList::createTemplate(Circuit& circuit) {
        int id = (int) templates.size();
        templates.emplace_back(circuit, id);
        return id;
    }

    ChipTemplate &TemplateList::getTemplate(int id) {
        return templates[id];
    }
}