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
    void write_r16_stk(Byte reg);
    void write_r16_mem(Byte reg, Byte data);
    Byte read_r8(Byte reg);
    Short read_r16(Byte reg);
    Short read_r16_stk(Byte reg);
    Byte read_r16_mem(Byte reg);
    
    /**
     * Increments the CPU's PC by 1
     * 
     */
    void inc_pc();

    /**
     * Jumps to the specified address by setting the new address to the CPU's PC 
     *
     * @param address The address to jump to
     * 
     */
    void jump(Short address);

    /**
     * Read the next immediate 8-bit value, which is currently pointed to by CPU's PC. Increments PC after fetching
     * 
     * @return An 8-bit value from the address specified by PC
     */
    Byte read_imm8();
       

    


};