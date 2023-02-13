//
// Created by Hank Stennes on 1/23/23.
//

#ifndef GATEWAYENGINE_COMPDATA_H
#define GATEWAYENGINE_COMPDATA_H

#include <vector>

namespace Gateway {

    class CompData {

    private:
        int templateId;
        std::vector<int> split;

    public:
        [[nodiscard]] int getTemplateId() const;

        void setTemplateId(int templateId);

        [[nodiscard]] const std::vector<int> &getSplit() const;

        void setSplit(const std::vector<int> &split);

    };

}

#endif //GATEWAYENGINE_COMPDATA_H
