#include "bitw.hpp"
#include "ram.hpp"

class Bus{

    Ram& ram;
    public:

    Bus(Ram& ram_ref): ram(ram_ref){
        
    }

    void write_memory(Short address, Byte data);
    Byte read_memory(Short address);







};