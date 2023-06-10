//
// Created by Hank Stennes on 2/4/23.
//

#ifndef GATEWAYENGINE_TEMPLATELIST_H
#define GATEWAYENGINE_TEMPLATELIST_H

#include "ChipTemplate.h"
#include <vector>

namespace Gateway {

    class TemplateList {

    private:
        std::vector<ChipTemplate> templates;

    public:
        int createTemplate(Circuit& circuit);

        ChipTemplate& getTemplate(int id);
    };

    inline TemplateList TEMPLATE_LIST;

}

#endif //GATEWAYENGINE_TEMPLATELIST_H
