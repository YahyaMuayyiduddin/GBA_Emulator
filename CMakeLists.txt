cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GB)

set(SOURCES main.cpp cpu.cpp bitw.cpp ram.cpp gb_program.cpp instruction.cpp)
set(SOURCES2 main.cpp cpu.cpp bitw.cpp ram.cpp gb_program.cpp instruction.cpp)


add_executable(Gameboy ${SOURCES})

find_package(SDL3 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include/Headers)
include_directories(${CMAKE_SOURCE_DIR}/libraries/SDL3.framework/Headers)

target_link_libraries(Gameboy SDL3::SDL3)


