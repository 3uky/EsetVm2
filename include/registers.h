#ifndef REGISTERS_H
#define REGISTERS_H

#include <array>
#include <stack>

#include "global.h"

const int REGS_COUNT=16;

class Registers
{
public:
    // all registers
    std::array<int64_t, REGS_COUNT> reg;
    // Instruction Pointer / Bit Pointer
    VM_DWORD ip;
    // Stack Pointer
    std::stack<VM_DWORD> sp;

    uint64_t instcount;
    size_t tId;

    int64_t& operator[](int index) {
        return reg[index];
    }

    void print() const;
    void printInstCounter() const;
    void emptyStack();
};

#endif // REGISTERS_H
