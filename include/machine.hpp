#pragma once
#include <cstdint>
#include <z80.hpp>

class Machine
{
public:
    Machine(uint8_t bank_count);
    ~Machine();

    Z80 *cpu;
    uint8_t *ram;
    uint8_t bank_count;
    int address_limit;
    uint8_t bankmap[16] = {0};
};
