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
};

#endif // REGISTERS_H
