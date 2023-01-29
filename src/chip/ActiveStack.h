//
// Created by Hank Stennes on 1/15/23.
//

#ifndef GATEWAYENGINE_ACTIVESTACK_H
#define GATEWAYENGINE_ACTIVESTACK_H

#include <stack>

namespace Gateway {

    class ActiveStack {

    private:
        struct LevelData {
            LevelData(int m, int r, bool f) : markCount(m), remainCount(r), flip(f) {}

            int markCount;
            int remainCount;
            bool flip;
        };

        std::stack<int> activeA;
        std::stack<int> activeB;
        std::stack<LevelData> levels;
        std::stack<int>* markStack = &activeA;
        std::stack<int>* remainStack = &activeB;

        bool flipState = false;
        int markCount = 0;
        int remainCount = 0;

    public:
        int next();

        bool hasNext();

        void mark(std::vector<int>& items);

        void mark(int item);

        void startInner();

        void finishInner();

    private:
        void flip();

        void updatePtrs();
    };

} // Gateway

#endif //GATEWAYENGINE_ACTIVESTACK_H
