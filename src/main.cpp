#include <iostream>
#include <fstream>
#include <argparse/argparse.hpp>
#include <machine.hpp>

using namespace argparse;

uint8_t initram[] = {
    // LD A, 'a'
    0x3E, 0x61,
    // OUT (0), A
    0xD3, 0x00,
};

int main(int argc, char** argv)
{
    ArgumentParser program("neo80-emu");

    program.add_argument("-r", "--rom")
        .help("path to the ROM file")
        .default_value("");
    
    program.add_argument("-m", "--memory")
        .help("amount of memory available in units of 4KiB banks");
    
    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err)
    {
        std::cout << err.what() << std::endl;
        std::cout << program;
        exit(0);
    }

    if (program["--help"] == true)
    {
        std::cout << program;
        exit(0);
    }

    Machine machine(12);

    if (program.get<std::string>("--rom") != "")
    {
        std::ifstream rom(program.get<std::string>("--rom"), std::ios::binary);
        if (rom.is_open())
        {
            rom.read((char *)machine.rom, 4096);
            rom.close();
        }
        else
        {
            std::cout << "Failed to open ROM file" << std::endl;
            exit(1);
        }
    }
    else
    {
        memcpy(machine.rom, initram, sizeof(initram));
    }

    while (1)
    {
        machine.cpu->execute(1);
    }

    return 0;
}
