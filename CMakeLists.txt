cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GB)
 
# set(SRCS cpu.cpp main.cpp bitw.cpp)
set(SOURCES main.cpp cpu.cpp bitw.cpp ram.cpp gb_program.cpp)

# set(HEADERS ${CMAKE_SOURCE_DIR}/include/Headers/bitw.hpp ${CMAKE_SOURCE_DIR}/include/Headers/cpu.hpp)

include_directories(${CMAKE_SOURCE_DIR}/include/Headers)

# link_directories(${CMAKE_SOURCE_DIR}/include/Headers)

add_executable(Gameboy ${SOURCES})