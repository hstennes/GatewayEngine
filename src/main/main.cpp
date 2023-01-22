#include <iostream>

#include "../circuit/Component.h"
#include "../circuit/Circuit.h"
#include "../chip/ChipTemplate.h"
#include "../chip/ActiveStack.h"
#include <stack>
#include <array>
#include <unordered_set>
#include <chrono>

int main() {
    using namespace Gateway;

    auto* circuit = new Circuit();
    int first = circuit->addComp(CompType::AND, 0, 0);
    int second = circuit->addComp(CompType::OR, 50, 50);
    int light = circuit->addComp(CompType::LIGHT, 100, 100);

    for(Component& comp : *circuit) {
        std::cout << comp.x << std::endl;
    }
}
