#include <iostream>
#include <fstream>
#include <argparse/argparse.hpp>
#include <machine.hpp>

using namespace argparse;

uint8_t initrom[39] = {
    0x31, 0xFF, 0x1F, 0x01, 0x18, 0x00, 0xC5, 0xCD, 0x0B, 0x00, 0x76, 0xE1, 0xE3, 0xEB, 0x1A, 0xFE, 
    0x00, 0xC8, 0xD3, 0x00, 0x13, 0xC3, 0x0E, 0x00, 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x2C, 0x20, 0x77, 
    0x6F, 0x72, 0x6C, 0x64, 0x21, 0x0A, 0x00
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
        memcpy(machine.rom, initrom, sizeof(initrom));
    }

    while (1)
    {
        machine.cpu->execute(1);
    }

    return 0;
}
