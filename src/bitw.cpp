
#include <iostream>

using namespace std;

using Byte = uint8_t;
using Short = uint16_t;


Byte extract_high_nibble(Byte opcode)
{
    unsigned int first_four = (opcode >> 4) | 0;
    return first_four;
}

Byte extract_low_nibble(Byte opcode)
{
    unsigned int sec_four = opcode & 15;
    return sec_four;
}

Byte extract_low_byte(Short opcode)
{
    Byte sec_byte = opcode & 0xff;
    return sec_byte;    
}

Byte extract_high_byte(Short opcode)
{
    
    Byte first_byte = (opcode >> 8) & 0xFF;
    return first_byte;
}

Short merge_bytes(Byte higher_byte, Byte lower_byte){
    Short merged = higher_byte << 8;
    merged = merged | lower_byte;
    return merged;
    
}

Byte extract_bit(Byte byte, int position)
{
    unsigned int result = (byte >> position) & 1;
    return result;
}