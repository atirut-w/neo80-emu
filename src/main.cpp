#include <iostream>
#include <fstream>
#include <argparse/argparse.hpp>
#include <machine.hpp>

using namespace argparse;

int main(int argc, char** argv)
{
    ArgumentParser program("neoz-emu");

    program.add_argument("-r", "--rom")
        .help("path to the ROM file");
    
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

    while (1)
    {
        machine.cpu->execute(1);
    }

    return 0;
}
