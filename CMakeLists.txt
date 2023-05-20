project(Neo80Emu)
add_executable(neo80-emu
    src/main.cpp
    src/machine.cpp
)
target_include_directories(neo80-emu PRIVATE include)

# Z80 emulator library
target_include_directories(neo80-emu PRIVATE 3rd/z80)

# Argparse
add_subdirectory(3rd/argparse)
target_link_libraries(neo80-emu PRIVATE argparse)

# Raylib
add_subdirectory(3rd/raylib)
target_link_libraries(neo80-emu PRIVATE raylib)
