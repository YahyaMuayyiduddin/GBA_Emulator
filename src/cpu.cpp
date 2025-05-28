#include <iostream>
#include "bitw.hpp"
#include "cpu.hpp"
#include <stdlib.h>



using namespace std;

using Short = uint16_t;
using Byte = uint8_t;

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

CPU::CPU()
{
    PC = 0x100;

}

void CPU::set_8bitreg(Byte reg, Byte data){
    switch(reg){
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
            throw(reg);
            break;
        case 0x7:
            A = data;
            break;
    }

}

void CPU::set_16bitreg(Reg16 reg, Short data){
    Byte low_byte = extract_low_byte(data);
    Byte high_byte = extract_high_byte(data);
    switch(reg){
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

Short CPU::get_16bitreg(Reg16 reg){
    Short value = 0x00;
    switch(reg){
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


Short CPU::_merge_registers(Byte reg_A, Byte reg_B){
    Short merged = reg_A << 8;
    merged |= reg_B;
    return merged;
}


void CPU::set_zero()
{
    F = F | 128;
}


bool CPU::get_zero()
{
    bool zero_flag = extract_bit(F, 7);
    return zero_flag;
}

void CPU::set_subtract()
{
    F = F | 64;
}

bool CPU::get_subtract()
{
    bool zero_flag = extract_bit(F, 6);
    return zero_flag;
}

void CPU::set_h_carry()
{

    F = F | 32;
}

bool CPU::get_h_carry()
{
    bool zero_flag = extract_bit(F, 5);
    return zero_flag;
}

void CPU::set_carry()
{
    F = F | 16;
}

bool CPU::get_carry()
{
    bool zero_flag = extract_bit(F, 4);
    return zero_flag;
}

