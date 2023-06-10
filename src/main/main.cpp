#include <iostream>

#include "../circuit/Component.h"
#include "../circuit/Circuit.h"
#include "../chip/ChipSim.h"
#include "../chip/TemplateList.h"

int main() {
    using namespace Gateway;

//    Circuit chipCirc;
//    int sw = chipCirc.addComp(CompType::SWITCH, 0, 0);
//    int nt = chipCirc.addComp(CompType::NOT, 50, 50);
//    int lt = chipCirc.addComp(CompType::LIGHT, 100, 100);
//
//    chipCirc.connect(sw, 0, nt, 0);
//    chipCirc.connect(nt, 0, lt, 0);
//
//    ChipSim sim(chipCirc);
//    std::cout << "Done compiling" << std::endl;

    Circuit chipCirc;
    int sw1 = chipCirc.addComp(CompType::SWITCH, 0, 0);
    int sw2 = chipCirc.addComp(CompType::SWITCH, 0, 0);
    int and1 = chipCirc.addComp(CompType::AND, 50, 50);
    int xor1 = chipCirc.addComp(CompType::XOR, 50, 50);
    int lt1 = chipCirc.addComp(CompType::LIGHT, 100, 100);
    int lt2 = chipCirc.addComp(CompType::LIGHT, 100, 100);

    chipCirc.connect(sw1, 0, and1, 0);
    chipCirc.connect(sw2, 0, and1, 1);
    chipCirc.connect(sw1, 0, xor1, 0);
    chipCirc.connect(sw2, 0, xor1, 1);
    chipCirc.connect(and1, 0, lt1, 0);
    chipCirc.connect(xor1, 0, lt2, 0);

    int chipTemplate = TEMPLATE_LIST.createTemplate(chipCirc);
    TemplateList stuff = TEMPLATE_LIST;

    Circuit mainCirc;
    int chip = mainCirc.addComp(CompType::CHIP, 0, 0);
    int sw1a = mainCirc.addComp(CompType::SWITCH, 0, 0);
    int sw2a = mainCirc.addComp(CompType::SWITCH, 0, 0);
    int lt1a = mainCirc.addComp(CompType::LIGHT, 0, 0);
    int lt2a = mainCirc.addComp(CompType::SWITCH, 0, 0);

    mainCirc.getComp(chip).initChip(chipTemplate);
    mainCirc.connect(sw1a, 0, chip, 0);
    mainCirc.connect(sw2a, 0, chip, 1);
    mainCirc.connect(chip, 0, lt1a, 0);
    mainCirc.connect(chip, 1, lt2a, 0);

    std::cout << "Done compiling" << std::endl;
}
