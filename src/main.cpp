#include <iostream>
#include <argparse/argparse.hpp>

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

    return 0;
}
