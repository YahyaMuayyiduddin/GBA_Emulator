#pragma once

using namespace std;

using Byte = uint8_t;
using Short = uint16_t;

/**
 * Extracts the most significant nibble from a byte
 * 
 * @param opcode The 8-bit value to extract from
 * 
 * @return The most significant nibble, bits 7-4
 */
Byte extract_high_nibble(Byte opcode);

/**
 * Extracts the lest significant nibble from a byte
 * 
 * @param opcode The 8-bit value to extract from
 * 
 * @return The lest significant nibble, bits 3-0
 */
Byte extract_low_nibble(Byte opcode);

/**
 * Extracts the least significant byte from a 16-bit value
 * 
 * @param opcode The 16-bit value to extract from
 * 
 * @return The least significant byte, bits 7-0
 */
Byte extract_low_byte(Short opcode);

/**
 * Extracts the most significant byte from a 16-bit value
 * 
 * @param opcode The 16-bit value to extract from
 * 
 * @return The most significant byte, bits 15-8
 */
Byte extract_high_byte(Short opcode);

/**
 * Merges two 1-byte (8-bit) values into a single 16-bit value.
 * 
 * Shifts the higher byte 8 bits to the left, and ORs it with the lower byte
 * 
 * @param higher_byte The significant byte
 * @param lower_byte The least-significant byte
 * 
 * @return The combined 16-bit value
 */
Short merge_bytes(Byte higher_byte, Byte lower_byte);

/**
 * Extracts the bit value at a given position from a given byte
 * 
 * Bit positions start from 0
 * 
 * @param byte The byte to extract the bit value from
 * @param position The bit position to extract
 * 
 */
Byte extract_bit(Byte byte, int position);

