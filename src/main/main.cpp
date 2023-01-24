#include <iostream>

#include "../circuit/Component.h"
#include "../circuit/Circuit.h"
#include "Utils.h"
#include <array>

int main() {
    using namespace Gateway;

    auto* circuit = new Circuit();
    int first = circuit->addComp(CompType::AND, 0, 0);
    int second = circuit->addComp(CompType::OR, 50, 50);
    int light = circuit->addComp(CompType::LIGHT, 100, 100);

    for(Component& comp : *circuit) {
        std::cout << Gateway::Utils::CTYPE_STRS[comp.getType()] << std::endl;
    }
}
