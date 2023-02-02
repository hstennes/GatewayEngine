#include <iostream>

#include "../circuit/Component.h"
#include "../circuit/Circuit.h"
#include "../chip/ChipSim.h"

int main() {
    using namespace Gateway;

//    Circuit circuit;
//    int sw = circuit.addComp(CompType::SWITCH, 0, 0);
//    int nt = circuit.addComp(CompType::NOT, 50, 50);
//    int lt = circuit.addComp(CompType::LIGHT, 100, 100);
//
//    circuit.connect(sw, 0, nt, 0);
//    circuit.connect(nt, 0, lt, 0);
//
//    ChipSim sim(circuit);
//    std::cout << "Done compiling" << std::endl;

//    Circuit circuit;
//    int sw1 = circuit.addComp(CompType::SWITCH, 0, 0);
//    int sw2 = circuit.addComp(CompType::SWITCH, 0, 0);
//    int and1 = circuit.addComp(CompType::AND, 50, 50);
//    int xor1 = circuit.addComp(CompType::XOR, 50, 50);
//    int lt1 = circuit.addComp(CompType::LIGHT, 100, 100);
//    int lt2 = circuit.addComp(CompType::LIGHT, 100, 100);
//
//    circuit.connect(sw1, 0, and1, 0);
//    circuit.connect(sw2, 0, and1, 1);
//    circuit.connect(sw1, 0, xor1, 0);
//    circuit.connect(sw2, 0, xor1, 1);
//    circuit.connect(and1, 0, lt1, 0);
//    circuit.connect(xor1, 0, lt2, 0);
//
//    ChipSim sim(circuit);
//    std::cout << "Done compiling" << std::endl;
}
