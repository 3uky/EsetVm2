#ifndef REGISTERS_H
#define REGISTERS_H

#include <array>

#include "global.h"

const int REGS_COUNT=16;

class Registers
{
public:
    /* Here will be stored all registers */
    std::array<int64_t, REGS_COUNT> reg;
    /* Instruction Pointer / Bit Pointer */
    VM_DWORD ip;
    /* Stack Pointer */
    VM_QWORD sp;

    int64_t& operator[](int index) {
        return reg[index];
    }

    void print() const {
        std::cout << "ip = " << std::dec << ip << std::endl;
        for (int i=0; i<REGS_COUNT; i++)
            std::cout << "reg[" << std::dec << i << "] = 0x" << std::hex << reg[i] << std::endl;
        std::cout << std::endl;
    }
};

#endif // REGISTERS_H
