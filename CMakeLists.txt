cmake_minimum_required(VERSION 3.24)
project(GatewayEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(GatewayEngine src/main/main.cpp src/circuit/Component.cpp src/circuit/Component.h src/circuit/OutPin.cpp src/circuit/OutPin.h src/circuit/Wire.cpp src/circuit/Wire.h src/circuit/Circuit.cpp src/circuit/Circuit.h src/chip/ChipTemplate.cpp src/chip/ChipTemplate.h src/circuit/CompType.h src/chip/ActiveStack.cpp src/chip/ActiveStack.h src/chip/ChipSim.cpp src/chip/ChipSim.h src/chip/Node.cpp src/chip/Node.h src/circuit/CompData.h src/main/Utils.h src/circuit/InPin.cpp src/circuit/InPin.h src/chip/TemplateList.cpp src/chip/TemplateList.h)
