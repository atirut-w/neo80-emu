#include <machine.hpp>

int get_real_address(uint8_t bankmap[16], uint16_t address)
{
    uint8_t bank = bankmap[address >> 12];
    return (bank * 4096) + (address & 0xFFF);
}

uint8_t read(void *context, uint16_t address)
{
    Machine *machine = (Machine *)context;
    if (get_real_address(machine->bankmap, address) < 4096 * machine->bank_count)
    {
        return machine->ram[get_real_address(machine->bankmap, address)];
    }
    else
    {
        return 0;
    }
}

void write(void *context, uint16_t address, uint8_t value)
{
    Machine *machine = (Machine *)context;
    if (get_real_address(machine->bankmap, address) < 4096 * machine->bank_count)
    {
        machine->ram[get_real_address(machine->bankmap, address)] = value;
    }
}

uint8_t in(void *context, uint16_t address)
{
    return 0;
}

void out(void *context, uint16_t address, uint8_t value)
{
    
}

Machine::Machine(uint8_t bank_count)
{
    cpu = new Z80(read, write, in, out, this);
    ram = new uint8_t[4096 * bank_count];
    this->bank_count = bank_count;
}

Machine::~Machine()
{
    delete cpu;
    delete[] ram;
}
