#include <iostream>
#include "bitw.hpp"
#include "cpu.hpp"
#include <stdlib.h>
#include "bus.hpp"

using namespace std;

using Short = uint16_t;
using Byte = uint8_t;
using Signed_Byte = int8_t;

SharpSM83::SharpSM83(Bus &bus_ref) : bus(bus_ref)
{
    PC = 0x100;
}

bool SharpSM83::get_cond(Byte cond)
{
    switch (cond)
    {
    case 0x00:
        return get_zero() == 0;
    case 0x01:
        return get_zero() == 1;
    case 0x02:
        return get_carry() == 0;
    case 0x03:
        return get_carry() == 1;
    }
}

void SharpSM83::set_8bitreg(Byte reg, Byte data)
{
    switch (reg)
    {
    case 0x0:
        B = data;
        break;
    case 0x1:
        C = data;
        break;
    case 0x2:
        D = data;
        break;
    case 0x3:
        E = data;
        break;
    case 0x4:
        H = data;
        break;
    case 0x5:
        L = data;
        break;
    case 0x6:
        bus.write_memory(get_16bitreg_direct(Reg16::HL), data);
        break;
    case 0x7:
        A = data;
        break;
    }
}

void SharpSM83::set_16bitreg_direct(Reg16 reg, Short data)
{
    Byte low_byte = extract_low_byte(data);
    Byte high_byte = extract_high_byte(data);
    switch (reg)
    {
    case Reg16::AF:
        A = high_byte;
        F = low_byte;
        F &= 0xF0;
        break;
    case Reg16::BC:
        B = high_byte;
        C = low_byte;
        break;
    case Reg16::DE:
        D = high_byte;
        E = low_byte;
        break;
    case Reg16::HL:
        H = high_byte;
        L = low_byte;
        break;
    }
}

Byte SharpSM83::get_8bitreg(Byte reg)
{
    Byte value;
    switch (reg)
    {
    case 0x0:
        value = B;
        break;
    case 0x1:
        value = C;
        break;
    case 0x2:
        value = D;
        break;
    case 0x3:
        value = E;
        break;
    case 0x4:
        value = H;
        break;
    case 0x5:
        value = L;
        break;
    case 0x6:
        value = bus.read_memory(get_16bitreg_direct(Reg16::HL));
        break;
    case 0x7:
        value = A;
        break;
    }
    return value;
}

Short SharpSM83::get_16bitreg_direct(Reg16 reg)
{
    Short value = 0x0000;
    switch (reg)
    {
    case Reg16::BC:
        value |= B;
        value = value << 8;
        value |= C;
        break;
    case Reg16::DE:
        value |= D;
        value = value << 8;
        value |= E;
        break;
    case Reg16::AF:
        value |= A;
        value = value << 8;
        value |= F;
        break;
    case Reg16::HL:
        value |= H;
        value = value << 8;
        value |= L;
        break;
    }
    return value;
}

Short SharpSM83::_merge_registers(Byte reg_A, Byte reg_B)
{
    Short merged = reg_A << 8;
    merged |= reg_B;
    return merged;
}

void SharpSM83::set_zero()
{
    F = F | 128;
}

bool SharpSM83::get_zero()
{
    bool zero_flag = extract_bit(F, 7);
    return zero_flag;
}

void SharpSM83::reset_zero()
{
    F = F & 0x7F;
}

void SharpSM83::set_subtract()
{
    F = F | 64;
}

bool SharpSM83::get_subtract()
{
    bool sub_flag = extract_bit(F, 6);
    return sub_flag;
}

void SharpSM83::reset_subtract()
{
    F = F & 0xBF;
}

void SharpSM83::set_h_carry()
{

    F = F | 32;
}

bool SharpSM83::get_h_carry()
{
    bool h_flag = extract_bit(F, 5);
    return h_flag;
}

void SharpSM83::reset_h_carry()
{
    F = F & 0xDF;
}

void SharpSM83::set_carry()
{
    F = F | 16;
}

bool SharpSM83::get_carry()
{
    bool c_flag = extract_bit(F, 4);
    return c_flag;
}

void SharpSM83::reset_carry()
{
    F = F & 0xEF;
}

void SharpSM83::write_r16(Byte reg, Short data)
{
    switch (reg)
    {
    case 0x00:
        set_16bitreg_direct(Reg16::BC, data);
        break;
    case 0x01:
        set_16bitreg_direct(Reg16::DE, data);
        break;
    case 0x02:
        set_16bitreg_direct(Reg16::HL, data);
        break;
    case 0x03:
        SP = data;
        break;
    }
}

void SharpSM83::write_r16_stk(Byte reg)
{
    Short data = 0x0000;
    data |= bus.read_memory(SP);
    SP++;
    data |= bus.read_memory(SP) << 8;
    SP++;

    switch (reg)
    {
    case 0x00:
        set_16bitreg_direct(Reg16::BC, data);
        break;
    case 0x01:
        set_16bitreg_direct(Reg16::DE, data);
        break;
    case 0x02:
        set_16bitreg_direct(Reg16::HL, data);
        break;
    case 0x03:
        set_16bitreg_direct(Reg16::AF, data);
        break;
    }
}

void SharpSM83::write_r16_mem(Byte reg, Byte data)
{
    Short memory_addr;
    switch (reg)
    {
    case 0x00:
        memory_addr = get_16bitreg_direct(Reg16::BC);
        bus.write_memory(memory_addr, data);
        break;
    case 0x01:
        memory_addr = get_16bitreg_direct(Reg16::DE);
        bus.write_memory(memory_addr, data);
        break;
    case 0x02:
        memory_addr = get_16bitreg_direct(Reg16::HL);
        bus.write_memory(memory_addr, data);
        set_16bitreg_direct(Reg16::HL, get_16bitreg_direct(Reg16::HL) + 1);
        break;
    case 0x03:
        memory_addr = get_16bitreg_direct(Reg16::HL);
        bus.write_memory(memory_addr, data);
        set_16bitreg_direct(Reg16::HL, get_16bitreg_direct(Reg16::HL) - 1);
        break;
    }
}

Short SharpSM83::read_r16(Byte reg)
{
    Short value;
    switch (reg)
    {
    case 0x00:
        value = get_16bitreg_direct(Reg16::BC);
        break;
    case 0x01:
        value = get_16bitreg_direct(Reg16::DE);
        break;
    case 0x02:
        value = get_16bitreg_direct(Reg16::HL);
        break;
    case 0x03:
        value = SP;
        break;
    }
    return value;
}

Short SharpSM83::read_r16_stk(Byte reg)
{
    Short value_16;
    switch (reg)
    {
    case 0x00:
        value_16 = get_16bitreg_direct(Reg16::BC);
        break;
    case 0x01:
        value_16 = get_16bitreg_direct(Reg16::DE);
        break;
    case 0x02:
        value_16 = get_16bitreg_direct(Reg16::HL);
        break;
    case 0x03:
        value_16 = get_16bitreg_direct(Reg16::AF);
        break;
    }
    Byte high_byte = (value_16 >> 8) & 0xFF;
    Byte low_byte = (value_16) & 0xFF;
    SP--;
    bus.write_memory(SP, high_byte);
    SP--;
    bus.write_memory(SP, low_byte);

    return value_16;
}

Byte SharpSM83::read_r16_mem(Byte reg)
{
    Short memory_addr;
    Byte value;
    switch (reg)
    {
    case 0x00:
        memory_addr = get_16bitreg_direct(Reg16::BC);
        value = bus.read_memory(memory_addr);
        break;
    case 0x01:
        memory_addr = get_16bitreg_direct(Reg16::DE);
        value = bus.read_memory(memory_addr);
        break;
    case 0x02:
        memory_addr = get_16bitreg_direct(Reg16::HL);
        value = bus.read_memory(memory_addr);
        set_16bitreg_direct(Reg16::HL, get_16bitreg_direct(Reg16::HL) + 1);
        break;
    case 0x03:
        memory_addr = get_16bitreg_direct(Reg16::HL);
        value = bus.read_memory(memory_addr);
        set_16bitreg_direct(Reg16::HL, get_16bitreg_direct(Reg16::HL) - 1);
        break;
    }
    return value;
}

void SharpSM83::inc_pc()
{
    PC++;
}

Byte SharpSM83::read_imm8()
{
    Byte value = bus.read_memory(PC);
    inc_pc();
    return value;
}

// Instructions //

// Block 0
void SharpSM83::execute_block_0(Byte opcode)
{
    Byte low_3_nibble = 0x00;
    low_3_nibble = opcode & 0x07;
    switch (low_3_nibble)
    {
    case 0x01:
    }
}

void SharpSM83::ld_r16_imm16(Byte opcode)
{
    Byte destination = (opcode >> 4) & 0x03;
    Short data = read_imm8() | (read_imm8() << 8);
    write_r16(destination, data);
}

void SharpSM83::ld_r16mem_a(Byte opcode)
{
    Byte destination = (opcode >> 4) & 0x03;
    write_r16_mem(destination, A);
}

void SharpSM83::ld_a_r16mem(Byte opcode)
{
    Byte destination = (opcode >> 4) & 0x03;
    Byte value = read_r16_mem(destination);
    A = value;
}

void SharpSM83::ld_imm16_sp(Byte opcode)
{
    Short address = read_imm8() | (read_imm8() << 8);
    Byte low = extract_low_byte(SP);
    Byte high = extract_high_byte(SP);
    bus.write_memory(address, low);
    bus.write_memory(address + 1, high);
}

void SharpSM83::inc_r16(Byte opcode)
{
    Byte destination = (opcode >> 4) & 0x03;
    Short value = read_r16(destination) + 1;
    write_r16(destination, value);
}

void SharpSM83::dec_r16(Byte opcode)
{
    Byte destination = (opcode >> 4) & 0x03;
    Short value = read_r16(destination) - 1;
    write_r16(destination, value);
}

void SharpSM83::add_hl_r16(Byte opcode)
{
    Byte destination = (opcode >> 4) & 0x03;
    Short hl_value = get_16bitreg_direct(Reg16::HL);
    Short r16_value = read_r16(destination);

    if ((((hl_value & 0xFFF) + (r16_value & 0xFFF)) & 0x1000) == 0x1000)
    {
        set_h_carry();
    }
    else
    {
        reset_h_carry();
    }
    if (((hl_value + r16_value) & 0x10000) == 0x10000)
    {
        set_carry();
    }
    else
    {
        reset_carry();
    }
    reset_subtract();
    set_16bitreg_direct(Reg16::HL, (hl_value + r16_value) & 0xFFFF);
}

void SharpSM83::inc_r8(Byte opcode)
{
    Byte destination = (opcode >> 3) & 0x07;
    Byte value = get_8bitreg(destination);
    if (((value + 1) & 0xFF) == 0)
    {
        set_zero();
    }
    else
    {
        reset_zero();
    }
    if ((((value & 0x0F) + (0x01 & 0x0F)) & 0x10) == 0x10)
    {
        set_h_carry();
    }
    else
    {
        reset_h_carry();
    }
    reset_subtract();

    set_8bitreg(destination, value + 1);
}

void SharpSM83::dec_r8(Byte opcode)
{
    Byte destination = (opcode >> 3) & 0x07;
    Byte value = get_8bitreg(destination);
    if (((value - 1) & 0xFF) == 0)
    {
        set_zero();
    }
    else
    {
        reset_zero();
    }
    if ((value & 0xF) == 0)
    {
        set_h_carry();
    }
    else
    {
        reset_h_carry();
    }
    set_subtract();

    set_8bitreg(destination, value - 1);
}

void SharpSM83::ld_r8_imm8(Byte opcode)
{
    Byte destination = (opcode >> 3) & 0x07;
    Byte value = read_imm8();
    set_8bitreg(destination, value);
}

void SharpSM83::jr_s_imm8(Byte opcode)
{
    Short jump_dest = PC + (Signed_Byte)read_imm8();
    PC = jump_dest;
}

void SharpSM83::jr_cc_s_imm8(Byte opcode)
{
    Byte cond = (opcode >> 3) & 0x03;
    Short jump_dest = PC + (Signed_Byte)read_imm8();
    if (get_cond(cond))
    {
        PC = jump_dest;
    }
}

void SharpSM83::rlca(Byte opcode){
    Byte bit_7 = extract_bit(A, 7);
    A = (A << 1) | bit_7;
    if(bit_7){
        set_carry();
    }else{
        reset_carry();
    }
    reset_subtract();
    reset_h_carry();
    reset_zero();
}

void SharpSM83::rrca(Byte opcode){
    Byte bit_0 = extract_bit(A, 0);
    A = (A >> 1) | (bit_0 << 7);
    if(bit_0){
        set_carry();
    }else{
        reset_carry();
    }
    reset_subtract();
    reset_h_carry();
    reset_zero();
}

void SharpSM83::rla(Byte opcode){
    Byte carry = get_carry();
    Byte bit_7 = extract_bit(A, 7);
    if(bit_7){
        set_carry();
    }else{
        reset_carry();
    }
    reset_subtract();
    reset_h_carry();
    reset_zero();
    A = (A << 1) | carry;
}

void SharpSM83::rra(Byte opcode){
    Byte carry = get_carry();
    Byte bit_0 = extract_bit(A, 0);
    if(bit_0){
        set_carry();
    }else{
        reset_carry();
    }
    reset_subtract();
    reset_h_carry();
    reset_zero();
    A = (A >> 1) | (carry << 7);

}

void SharpSM83::cpl(Byte opcode){
    A = ~A;
    set_h_carry();
    set_subtract();
}

void SharpSM83::ccf(Byte opcode){
    if(get_carry()){
        reset_carry();
    }else{
        set_carry();
    }
    reset_h_carry();
    reset_subtract();
}

void SharpSM83::scf(Byte opcode){
    set_carry();
    reset_h_carry();
    reset_subtract();
}

void SharpSM83::daa(Byte opcode){
    Byte adjustment = 0x00;
    bool set_c = false;
    if(get_subtract()){
        if(get_h_carry()){
            adjustment |= 0x6;
        }
        if(get_carry()){
            adjustment |= 0x60;
        }
        A -= adjustment;
    }else{
        if(get_h_carry() || (A & 0xF) > 0x9){
            adjustment |= 0x6;
        }
        if(get_carry() || A > 0x99){
            adjustment |= 0x60;
            set_c = true;
        }
        A += adjustment;
    }
    if(set_c){
        set_carry();
    }else{
        reset_carry();
    }

    reset_h_carry();
    if (A == 0) {
        set_zero();
    } else {
        reset_zero();  // Ensure it's reset if non-zero
    }

}