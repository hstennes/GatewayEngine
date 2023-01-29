//
// Created by Hank Stennes on 1/24/23.
//

#ifndef GATEWAYENGINE_INPIN_H
#define GATEWAYENGINE_INPIN_H

#include "array"
#include "unordered_map"

namespace Gateway {

    class InPin {

    private:
        std::array<int, 2> connection {-1, -1};

    public:
        void connect(int id, int otherIdx);

        void disconnect();

        void updateIds(std::unordered_map<int, int>& idMap);

        [[nodiscard]] bool isConnected();

        [[nodiscard]] const std::array<int, 2> &getConnection() const;

    };

} // Gateway

#endif //GATEWAYENGINE_INPIN_H
