project(NeoZEmu)
add_executable(neoz-emu
    src/main.cpp
)
target_include_directories(neoz-emu PRIVATE include)

# Z80 emulator library
target_include_directories(neoz-emu PRIVATE 3rd/z80)

# Argparse
add_subdirectory(3rd/argparse)
target_link_libraries(neoz-emu PRIVATE argparse)

# Raylib
add_subdirectory(3rd/raylib)
target_link_libraries(neoz-emu PRIVATE raylib)
