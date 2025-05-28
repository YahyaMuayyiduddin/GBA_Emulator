#pragma once

#include "cpu.hpp"
#include "ram.hpp"

using namespace std;

class GB_Program{
    public:
    CPU& cpu;
    Ram& ram;
   
    GB_Program(CPU& cpu_ref, Ram& ram_ref);
    void write_r8(Byte reg, Byte data);
    void write_r16(Byte reg, Short data);
    void write_r16_stk(Byte reg, Short data);
    void write_r16_mem(Byte reg, Byte data);
       

    


};