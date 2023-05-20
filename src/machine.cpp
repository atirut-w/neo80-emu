#include <machine.hpp>
#include <iostream>

uint8_t get_real_bank(uint8_t bankmap[16], uint16_t address)
{
    return bankmap[address >> 12];
}

uint8_t read(void *context, uint16_t address)
{
    Machine *machine = (Machine *)context;
    if (machine->ram[get_real_bank(machine->bankmap, address)] != nullptr)
    {
        return machine->ram[get_real_bank(machine->bankmap, address)][address & 0xFFF];
    }
    else
    {
        return 0;
    }
}

void write(void *context, uint16_t address, uint8_t value)
{
    Machine *machine = (Machine *)context;
    if (machine->ram[get_real_bank(machine->bankmap, address)] != nullptr)
    {
        machine->ram[get_real_bank(machine->bankmap, address)][address & 0xFFF] = value;
    }
}

uint8_t in(void *context, uint16_t address)
{
    return 0;
}

void out(void *context, uint16_t address, uint8_t value)
{
    switch (address & 0xFF)
    {
    case 0:
        std::cout << value << std::flush;
        break;
    }
}

Machine::Machine(uint8_t bank_count)
{
    cpu = new Z80(read, write, in, out, this, true);
    
    for (uint8_t i = 0; i < bank_count; i++)
    {
        ram[i] = new uint8_t[4096];
    }
}

Machine::~Machine()
{
    delete cpu;
    
    for (uint8_t i = 0; i < 16; i++)
    {
        if (ram[i] != nullptr)
        {
            delete[] ram[i];
        }
    }
}
