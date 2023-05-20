#pragma once
#include <cstdint>
#include <z80.hpp>

class Machine
{
public:
    Machine(uint8_t bank_count);
    ~Machine();

    Z80 *cpu;
    uint8_t *ram[16] = {nullptr};
    uint8_t bankmap[16] = {0};
};
