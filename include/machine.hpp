#pragma once
#include <cstdint>
#include <z80.hpp>

class Machine
{
public:
    Machine(uint8_t bank_count);
    ~Machine();

    Z80 *cpu;
    uint8_t rom[4096] = {0};
    uint8_t *ram[16] = {nullptr};
    uint8_t bankmap[16] = {255, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
};
