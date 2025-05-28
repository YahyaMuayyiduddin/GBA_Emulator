#include "cpu.hpp"
#include "ram.hpp"
#include "gb_program.hpp"

GB_Program::GB_Program(CPU& cpu_ref, Ram& ram_ref):
    cpu(cpu_ref), ram(ram_ref){}

void GB_Program::write_r8(Byte reg, Byte data){
    if(reg == 0x06){
        ram.write(data, cpu.get_16bitreg(Reg16::HL));
    }
    else{
        cpu.set_8bitreg(reg, data);
    }
    
}
void GB_Program::write_r16(Byte reg, Short data){
    switch(reg){
        case 0x00:
            cpu.set_16bitreg(Reg16::BC, data);
            break;
        case 0x01:
            cpu.set_16bitreg(Reg16::DE, data);
            break;
        case 0x02:
            cpu.set_16bitreg(Reg16::HL, data);
            break;
        case 0x03:
            cpu.SP = data;
            break;
    }
}
void GB_Program::write_r16_stk(Byte reg, Short data){
  

}


void GB_Program::write_r16_mem(Byte reg, Byte data){
    Short memory_addr;
    switch (reg){
        case 0x00:
            memory_addr = cpu.get_16bitreg(Reg16::BC);
            ram.write(data, memory_addr);
            break;
        case 0x01:
            memory_addr = cpu.get_16bitreg(Reg16::DE);
            ram.write(data, memory_addr);
            break;
        case 0x02:
            memory_addr = cpu.get_16bitreg(Reg16::HL);
            ram.write(data, memory_addr);
            cpu.set_16bitreg(Reg16::HL, cpu.get_16bitreg(Reg16::HL) + 1);
            break;
        case 0x03:    
            memory_addr = cpu.get_16bitreg(Reg16::HL);
            ram.write(data, memory_addr);
            cpu.set_16bitreg(Reg16::HL, cpu.get_16bitreg(Reg16::HL) - 1);
            break;
    }
 
}
