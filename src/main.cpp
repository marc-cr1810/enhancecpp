#include <iostream>

#include "enhance/bitset.hpp"

int main (int argc, char *argv[])
{
    enhance::bitset<uint8_t> bits("00001010_00001010_00001010_00001010");

    std::cout << bits.to_string() << std::endl;
}
