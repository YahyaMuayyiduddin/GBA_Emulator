#pragma once
#include <iostream>


using namespace std;

using Short = uint16_t;
using Byte = uint8_t;


class Ram
{
public:
    Byte *internal_array = nullptr;
    int max_size;

    Ram(int size)
    {
        internal_array = (Byte *)malloc(size * sizeof(Byte));
        max_size = size;
    };

    ~Ram()
    {
        free(internal_array);
    }

    void write(Byte data, Short address)
    {
        *(internal_array + address) = data;
    }
    
    Byte& operator[](size_t index) {
        // Optionally check index here
        return *(internal_array + index);
    }


    Byte read(Short address)
    {
        if ((unsigned int)address >= max_size)
        {
            throw std::out_of_range("Received address bigger than memory");
        }
        return *(internal_array + address);
    }
};