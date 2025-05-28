#include <iostream>
#include "bitw.hpp"
#include "cpu.hpp"
#include "gb_program.hpp"




using namespace std;

using Short = uint16_t;
using Byte = uint8_t;


int main(){
    Ram ram{8000};
    CPU cpu;
    GB_Program program{cpu,ram};
    program.write_r16(0x00, 0x1F3F);
    program.write_r16_mem(0x00, 0xFF);
    std::cout << (int)program.ram.read(0x1F3F) << endl;



}