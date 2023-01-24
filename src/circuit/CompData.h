//
// Created by Hank Stennes on 1/23/23.
//

#ifndef GATEWAYENGINE_COMPDATA_H
#define GATEWAYENGINE_COMPDATA_H

namespace Gateway {

    class ChipTemplate;

    struct CompData {

        ChipTemplate* chipTemplate;

        std::vector<int> split;
    };

}

#endif //GATEWAYENGINE_COMPDATA_H
