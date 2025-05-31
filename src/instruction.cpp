#include "cpu.hpp"
#include "gb_program.hpp"
#include "bitw.hpp"


//Block 0, 7th, 6th bits are 00

int clock_cycles;
Ram ram{8000};
SharpSM83 cpu;
GB_Program program{cpu,ram};


void execute_block_0(Byte opcode){
    Byte low_3_nibble = 0x00;
    low_3_nibble = opcode & 0x07;
    switch(low_3_nibble){
        case 0x01:
    }
}

void ld_r16_imm16(Byte opcode){
    Byte destination = (opcode >> 4) & 0x03;
    Short data = program.read_imm8() | (program.read_imm8() << 8);
    program.write_r16(destination, data);
}

void ld_r16mem_a(Byte opcode){
    Byte destination = (opcode >> 4) & 0x03;
    program.write_r16_mem(destination, program.cpu.A);
}

void ld_a_r16mem(Byte opcode){
    Byte destination = (opcode >> 4) & 0x03;
    Byte value = program.read_r16_mem(destination);
    cpu.A = value;
}

void ld_imm16_sp(Byte opcode){
    Short address = program.read_imm8() | (program.read_imm8() << 8);
    Byte low = extract_low_byte(cpu.SP);
    Byte high = extract_high_byte(cpu.SP);
    program.ram.write(low, address);
    program.ram.write(high, address+1);
}

void inc_r16(Byte opcode){
    Byte destination = (opcode >> 4) & 0x03;
    Short value = program.read_r16(destination) + 1;
    program.write_r16(destination, value);
}

void dec_r16(Byte opcode){
    Byte destination = (opcode >> 4) & 0x03;
    Short value = program.read_r16(destination) - 1;
    program.write_r16(destination, value);
}




int main(){
    cpu.PC = 0x00FF;
    ram.write(0x88, 0x0100);
    program.ram.write(0x13, 0x0101);
    program.inc_pc();
    ld_r16_imm16(0x21);
    std::cout << program.read_r16(0x02) << std::endl;
    program.cpu.A = 0xFF;
    ld_r16mem_a(0x21);
    std::cout << (int)program.ram.read(0x1388) << endl;



}