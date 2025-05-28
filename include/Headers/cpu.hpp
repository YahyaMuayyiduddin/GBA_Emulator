#pragma once  // This is an alternative to the traditional include guard, but I'll keep it here as well.



#include <iostream>
#include "bitw.hpp"

using Short = uint16_t;
using Byte = uint8_t;


enum class Reg16{
    AF,
    BC,
    DE,
    HL,
};


class CPU
{
public:
    Short SP;
    Short PC;

    Byte A;
    Byte B;
    Byte C;
    Byte D;
    Byte E;
    Byte F;
    Byte H;
    Byte L;

    int c_cycles;
    int m_cycles;

    CPU();
    public:
    /**
     * 
     * Sets the value at the specified 8-bit register
     * 
     * @param data The data to write to the register
     * 
     */
    void set_8bitreg(Byte reg, Byte data);

    /**
     * 
     * Sets the value at the specified 16-bit register pair, MN. The lower 8-bits go to register N, and the higher 8-bits go to M.
     * 
     * @param reg The specified register pair
     * @param data A 16-bit data to write
     * 
     */
    void set_16bitreg(Reg16 reg, Short data);

    /**
     * 
     * Gets the value at the specified 16-bit register pair, MN. 
     * 
     * @param reg The specified register pair

     *
     */
    Short get_16bitreg(Reg16 reg);



    void set_zero();
    bool get_zero();

    void set_subtract();
    bool get_subtract();

    void set_h_carry();
    bool get_h_carry();

    void set_carry();
    bool get_carry();
    private:
    Short _merge_registers(Byte reg_A, Byte reg_B);

};


