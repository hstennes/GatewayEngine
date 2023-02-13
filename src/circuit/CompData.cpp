//
// Created by Hank Stennes on 2/4/23.
//

#include "CompData.h"

namespace Gateway {

    int CompData::getTemplateId() const {
        return templateId;
    }

    void CompData::setTemplateId(int templateId) {
        CompData::templateId = templateId;
    }

    const std::vector<int> &CompData::getSplit() const {
        return split;
    }

    void CompData::setSplit(const std::vector<int> &split) {
        CompData::split = split;
    }
}