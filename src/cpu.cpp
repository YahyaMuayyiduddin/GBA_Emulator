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

CPU::CPU(Bus& bus_ref):bus(bus_ref)
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

Byte CPU::get_8bitreg(Byte reg){
    Byte value;
     switch(reg){
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
            throw(reg);
            break;
        case 0x7:
            value = A;
            break;
    }
    return value;
}

Short CPU::get_16bitreg(Reg16 reg){
    Short value = 0x0000;
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

void CPU::reset_zero()
{
    F = F & 0x7F;
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

void CPU::reset_subtract()
{
    F = F & 0xBF;
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

void CPU::reset_h_carry()
{
    F = F & 0xDF;
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

void CPU::reset_carry(){
    F = F & 0xEF;
}


void CPU::write_r8(Byte reg, Byte data){
    if(reg == 0x06){
        bus.write_memory(data, get_16bitreg(Reg16::HL));
    }
    else{
        set_8bitreg(reg, data);
    }
    
}

void CPU::write_r16(Byte reg, Short data){
    switch(reg){
        case 0x00:
            set_16bitreg(Reg16::BC, data);
            break;
        case 0x01:
            set_16bitreg(Reg16::DE, data);
            break;
        case 0x02:
            set_16bitreg(Reg16::HL, data);
            break;
        case 0x03:
            SP = data;
            break;
    }
}

void CPU::write_r16_stk(Byte reg){
    Short data = 0x0000;
    data |= bus.read_memory(SP);
    SP++;
    data |= bus.read_memory(SP) << 8;
    SP++;

    switch(reg){
        case 0x00:
            set_16bitreg(Reg16::BC, data);
            break;
        case 0x01:
            set_16bitreg(Reg16::DE, data);
            break;
        case 0x02:
            set_16bitreg(Reg16::HL, data);
            break;
        case 0x03:
            set_16bitreg(Reg16::AF, data);
            break;
    }
  
}


void CPU::write_r16_mem(Byte reg, Byte data){
    Short memory_addr;
    switch (reg){
        case 0x00:
            memory_addr = get_16bitreg(Reg16::BC);
            bus.write_memory(memory_addr, data);
            break;
        case 0x01:
            memory_addr = get_16bitreg(Reg16::DE);
            bus.write_memory(memory_addr, data);
            break;
        case 0x02:
            memory_addr = get_16bitreg(Reg16::HL);
            bus.write_memory(memory_addr, data);
            set_16bitreg(Reg16::HL, get_16bitreg(Reg16::HL) + 1);
            break;
        case 0x03:    
            memory_addr = get_16bitreg(Reg16::HL);
            bus.write_memory(memory_addr, data);
            set_16bitreg(Reg16::HL, get_16bitreg(Reg16::HL) - 1);
            break;
    }
 
}



Byte CPU::read_r8(Byte reg){
    if(reg == 0x06){
        return bus.read_memory(get_16bitreg(Reg16::HL));
    }
    else{
        return get_8bitreg(reg);
    }

}


Short CPU::read_r16(Byte reg){
    Short value;
    switch(reg){
        case 0x00:
            value = get_16bitreg(Reg16::BC);
            break;
        case 0x01:
            value = get_16bitreg(Reg16::DE);
            break;
        case 0x02:
            value = get_16bitreg(Reg16::HL);
            break;
        case 0x03:
            value = SP;
            break;
    }
    return value;

}


Short CPU::read_r16_stk(Byte reg){
    Short value_16;
    switch(reg){
        case 0x00:
            value_16 = get_16bitreg(Reg16::BC);
            break;
        case 0x01:
            value_16 = get_16bitreg(Reg16::DE);
            break;
        case 0x02:
            value_16 = get_16bitreg(Reg16::HL);
            break;
        case 0x03:
            value_16 = get_16bitreg(Reg16::AF);
            break;
    }
    Byte high_byte = (value_16 >>8 ) & 0xFF;
    Byte low_byte = (value_16) & 0xFF;
    bus.write_memory(SP, high_byte);
    SP--;
    bus.write_memory(SP, high_byte);
    SP--;
    return value_16;
}


Byte CPU::read_r16_mem(Byte reg){
    Short memory_addr;
    Byte value;
    switch (reg){
        case 0x00:
            memory_addr = get_16bitreg(Reg16::BC);
            value = bus.read_memory(memory_addr);
            break;
        case 0x01:
            memory_addr = get_16bitreg(Reg16::DE);
            value = bus.read_memory(memory_addr);
            break;
        case 0x02:
            memory_addr = get_16bitreg(Reg16::HL);
            value = bus.read_memory(memory_addr);
            set_16bitreg(Reg16::HL, get_16bitreg(Reg16::HL) + 1);
            break;
        case 0x03:    
            memory_addr = get_16bitreg(Reg16::HL);
            value = bus.read_memory(memory_addr);
            set_16bitreg(Reg16::HL, get_16bitreg(Reg16::HL) - 1);
            break;
    }
    return value;

}

void CPU::inc_pc(){
    PC ++;
}

Byte CPU::read_imm8(){
    Byte value = bus.read_memory(PC);
    inc_pc();
    return value;
}