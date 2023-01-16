cmake_minimum_required(VERSION 3.24)
project(GatewayEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(GatewayEngine src/main/main.cpp src/circuit/Component.cpp src/circuit/Component.h src/circuit/Pin.cpp src/circuit/Pin.h src/circuit/Wire.cpp src/circuit/Wire.h src/circuit/Circuit.cpp src/circuit/Circuit.h src/chip/ChipTemplate.cpp src/chip/ChipTemplate.h src/circuit/CompType.h src/circuit/CompType.cpp src/chip/NodeBox.cpp src/chip/NodeBox.h src/chip/ActiveStack.cpp src/chip/ActiveStack.h)
