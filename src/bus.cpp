#include "ram.hpp"
#include "bitw.hpp"
#include "bus.hpp"

Byte Bus::read_memory(Short address){
    return ram.read(address);

}

void Bus::write_memory(Short address, Byte value){
    ram.write(value, address);
}