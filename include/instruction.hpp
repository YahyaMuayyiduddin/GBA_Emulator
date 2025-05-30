#include "cpu.hpp"
#include "gb_program.hpp"
#include "bitw.hpp"


//Block 0, 7th, 6th bits are 00

int clock_cycles;
Ram ram{8000};
CPU cpu;
GB_Program program{cpu,ram};


void execute_block_0(Byte opcode){
    Byte low_3_nibble = 0x00;
    low_3_nibble = opcode & 0x07;
    switch(low_3_nibble){
        case 0x01:
        case 0x07:
    }


}

void ld_r16_imm16(Byte opcode);