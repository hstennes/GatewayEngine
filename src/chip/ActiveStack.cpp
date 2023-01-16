//
// Created by Hank Stennes on 1/15/23.
//

#include "ActiveStack.h"
#include <vector>

namespace Gateway {

    int ActiveStack::next() {
        if(remainCount == 0) flip();
        int top = remainStack->top();
        remainStack->pop();
        remainCount--;
        return top;
    }

    bool ActiveStack::hasNext() {
        return !(remainCount == 0 && markCount == 0);
    }

    void ActiveStack::mark(std::vector<int>& items) {
        markCount += (int) items.size();
        for(int i : items) markStack->push(i);
    }

    void ActiveStack::startInner() {
        levels.emplace(markCount, remainCount, flipState);
        markCount = 0;
        remainCount = 0;
        flipState = false;
        markStack = &activeA;
        remainStack = &activeB;
    }

    void ActiveStack::finishInner() {
        LevelData& ld = levels.top();
        markCount = ld.markCount;
        remainCount = ld.remainCount;
        flipState = ld.flip;
        updatePtrs();
    }

    void ActiveStack::flip() {
        remainCount = markCount;
        markCount = 0;
        flipState = !flipState;
        updatePtrs();
    }

    void ActiveStack::updatePtrs() {
        markStack = flipState ? &activeB : &activeA;
        remainStack = flipState ? &activeA : &activeB;
    }

} // Gateway