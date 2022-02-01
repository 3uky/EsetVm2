#ifndef REGISTERS_H
#define REGISTERS_H

#include <array>
#include <stack>

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
    std::stack<VM_DWORD> sp;

    int64_t& operator[](int index) {
        return reg[index];
    }

    uint64_t instcount;

    void print() const {
        std::cout << "ip = " << std::dec << ip << std::endl;
        if(!sp.empty())
            std::cout << "sp = " << std::dec << sp.top() << std::endl;
        for (int i=0; i<REGS_COUNT; i++)
            std::cout << "r[" << std::dec << i << "] = 0x" << std::hex << reg[i] << std::endl;
        std::cout << std::endl;
    }
    void printInstCounter() const {
        std::cout << std::dec << instcount << ": ";
    }
};

#endif // REGISTERS_H
