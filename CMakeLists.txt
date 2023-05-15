project(NeoZEmu)
add_executable(neoz-emu
    src/main.cpp
)
target_include_directories(neoz-emu PRIVATE include)

# Z80 emulator library
target_include_directories(neoz-emu PRIVATE 3rd/z80)
