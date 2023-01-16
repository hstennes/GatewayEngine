#include <iostream>

#include "../circuit/Component.h"
#include "../circuit/Circuit.h"
#include "../chip/ChipTemplate.h"

int main() {
    using namespace Gateway;

    auto* circuit = new Circuit();
    int first = circuit->addComp(CompType::AND, 0, 0);
    int second = circuit->addComp(CompType::OR, 50, 50);
    int light = circuit->addComp(CompType::LIGHT, 100, 100);
    circuit->connect(first, 0, second, 0);
    circuit->connect(second, 0, light, 0);

    std::vector<int> ids;
    ids.push_back(1);
    ids.push_back(2);

    ChipTemplate temp = ChipTemplate(circuit, ids);
    std::cout << "absolutely froggers" << std::endl;

//    Component& comp = circuit->getComp(first);
//    if(circuit->getComp(comp.outputs[0].connect[0]).type == CompType::OR) {
//        std::cout << "Cool" << std::endl;
//    }
//    else {
//        std::cout << "not cool" << std::endl;
//    }

    return 0;

//    std::cout << "hello" << std::endl;
//    return 0;
}
