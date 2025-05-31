#pragma once // This is an alternative to the traditional include guard, but I'll keep it here as well.

#include <iostream>
#include "bitw.hpp"
#include "bus.hpp"

using Short = uint16_t;
using Byte = uint8_t;
using Signed_Byte = int8_t;


enum class Reg16
{
    AF,
    BC,
    DE,
    HL,
};

class SharpSM83
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
    Bus &bus;

    SharpSM83(Bus &bus_ref);

public:
bool get_cond(Byte cond);
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
    void set_16bitreg_direct(Reg16 reg, Short data);

    /**
     *
     * Gets the value at the specified 16-bit register pair, MN.
     *
     * @param reg The specified register pair

     *
     */
    Short get_16bitreg_direct(Reg16 reg);

    /**
     *
     * Gets the value at the specified 8-bit register pair. If the specified argument is 0x06, gets the value stored at memory address HL
     *
     * @param reg The specified register pair

     *
     */
    Byte get_8bitreg(Byte reg);

    void set_zero();
    bool get_zero();
    void reset_zero();

    void set_subtract();
    bool get_subtract();
    void reset_subtract();

    void set_h_carry();
    bool get_h_carry();
    void reset_h_carry();

    void set_carry();
    bool get_carry();
    void reset_carry();

    // void write_r8(Byte reg, Byte data);
    void write_r16(Byte reg, Short data);
    void write_r16_stk(Byte reg);
    void write_r16_mem(Byte reg, Byte data);
    // Byte read_r8(Byte reg);
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

    void execute_block_0(Byte opcode);
  

    void ld_r16_imm16(Byte opcode);


    void ld_r16mem_a(Byte opcode);

    void ld_a_r16mem(Byte opcode);
    void ld_imm16_sp(Byte opcode);

    void inc_r16(Byte opcode);

    void dec_r16(Byte opcode);
    void add_hl_r16(Byte opcode);
    void inc_r8(Byte opcode);
    void dec_r8(Byte opcode);
    void ld_r8_imm8(Byte opcode);
    void jr_s_imm8(Byte opcode);
    void jr_cc_s_imm8(Byte opcode);
    void rlca(Byte opcode);
    void rrca(Byte opcode);
    void rla(Byte opcode);
    void rra(Byte opcode);
    void daa(Byte opcode);
    void cpl(Byte opcode);
    void scf(Byte opcode);
    void ccf(Byte opcode);








private:
    Short _merge_registers(Byte reg_A, Byte reg_B);

    // Instructions
};
