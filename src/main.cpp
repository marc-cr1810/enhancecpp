#include <iostream>

#include "enhance/bitset.hpp"

int main (int argc, char *argv[])
{
    enhance::bitset<int> bits("1010010001");

    std::cout << bits.to_string() << std::endl;
}
