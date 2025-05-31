#include "cpu.hpp"
#include "ram.hpp"
#include "gb_program.hpp"

GB_Program::GB_Program(SharpSM83& cpu_ref, Ram& ram_ref):
    cpu(cpu_ref), ram(ram_ref){}

void GB_Program::write_r8(Byte reg, Byte data){
    if(reg == 0x06){
        ram.write(data, cpu.get_16bitreg_direct(Reg16::HL));
    }
    else{
        cpu.set_8bitreg(reg, data);
    }
    
}

void GB_Program::write_r16(Byte reg, Short data){
    switch(reg){
        case 0x00:
            cpu.set_16bitreg_direct(Reg16::BC, data);
            break;
        case 0x01:
            cpu.set_16bitreg_direct(Reg16::DE, data);
            break;
        case 0x02:
            cpu.set_16bitreg_direct(Reg16::HL, data);
            break;
        case 0x03:
            cpu.SP = data;
            break;
    }
}

void GB_Program::write_r16_stk(Byte reg){
    Short data = 0x0000;
    data |= ram.read(cpu.SP);
    cpu.SP++;
    data |= ram.read(cpu.SP) << 8;
    cpu.SP++;

    switch(reg){
        case 0x00:
            cpu.set_16bitreg_direct(Reg16::BC, data);
            break;
        case 0x01:
            cpu.set_16bitreg_direct(Reg16::DE, data);
            break;
        case 0x02:
            cpu.set_16bitreg_direct(Reg16::HL, data);
            break;
        case 0x03:
            cpu.set_16bitreg_direct(Reg16::AF, data);
            break;
    }
  
}


void GB_Program::write_r16_mem(Byte reg, Byte data){
    Short memory_addr;
    switch (reg){
        case 0x00:
            memory_addr = cpu.get_16bitreg_direct(Reg16::BC);
            ram.write(data, memory_addr);
            break;
        case 0x01:
            memory_addr = cpu.get_16bitreg_direct(Reg16::DE);
            ram.write(data, memory_addr);
            break;
        case 0x02:
            memory_addr = cpu.get_16bitreg_direct(Reg16::HL);
            ram.write(data, memory_addr);
            cpu.set_16bitreg_direct(Reg16::HL, cpu.get_16bitreg_direct(Reg16::HL) + 1);
            break;
        case 0x03:    
            memory_addr = cpu.get_16bitreg_direct(Reg16::HL);
            ram.write(data, memory_addr);
            cpu.set_16bitreg_direct(Reg16::HL, cpu.get_16bitreg_direct(Reg16::HL) - 1);
            break;
    }
 
}



Byte GB_Program::read_r8(Byte reg){
    if(reg == 0x06){
        return ram.read(cpu.get_16bitreg_direct(Reg16::HL));
    }
    else{
        return cpu.get_8bitreg(reg);
    }

}


Short GB_Program::read_r16(Byte reg){
    Short value;
    switch(reg){
        case 0x00:
            value = cpu.get_16bitreg_direct(Reg16::BC);
            break;
        case 0x01:
            value = cpu.get_16bitreg_direct(Reg16::DE);
            break;
        case 0x02:
            value = cpu.get_16bitreg_direct(Reg16::HL);
            break;
        case 0x03:
            value = cpu.SP;
            break;
    }
    return value;

}


Short GB_Program::read_r16_stk(Byte reg){
    Short value_16;
    switch(reg){
        case 0x00:
            value_16 = cpu.get_16bitreg_direct(Reg16::BC);
            break;
        case 0x01:
            value_16 = cpu.get_16bitreg_direct(Reg16::DE);
            break;
        case 0x02:
            value_16 = cpu.get_16bitreg_direct(Reg16::HL);
            break;
        case 0x03:
            value_16 = cpu.get_16bitreg_direct(Reg16::AF);
            break;
    }
    Byte high_byte = (value_16 >>8 ) & 0xFF;
    Byte low_byte = (value_16) & 0xFF;
    ram.write(high_byte, cpu.SP);
    cpu.SP--;
    ram.write(high_byte, cpu.SP);
    cpu.SP--;
    return value_16;
}


Byte GB_Program::read_r16_mem(Byte reg){
    Short memory_addr;
    Byte value;
    switch (reg){
        case 0x00:
            memory_addr = cpu.get_16bitreg_direct(Reg16::BC);
            value = ram.read(memory_addr);
            break;
        case 0x01:
            memory_addr = cpu.get_16bitreg_direct(Reg16::DE);
            value = ram.read(memory_addr);
            break;
        case 0x02:
            memory_addr = cpu.get_16bitreg_direct(Reg16::HL);
            value = ram.read(memory_addr);
            cpu.set_16bitreg_direct(Reg16::HL, cpu.get_16bitreg_direct(Reg16::HL) + 1);
            break;
        case 0x03:    
            memory_addr = cpu.get_16bitreg_direct(Reg16::HL);
            value = ram.read(memory_addr);
            cpu.set_16bitreg_direct(Reg16::HL, cpu.get_16bitreg_direct(Reg16::HL) - 1);
            break;
    }
    return value;

}

void GB_Program::inc_pc(){
    cpu.PC ++;
}

Byte GB_Program::read_imm8(){
    Byte value = ram.read(cpu.PC);
    inc_pc();
    return value;
}