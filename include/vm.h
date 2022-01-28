#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <vector>
#include <array>

#include "global.h"
#include "memory.h"
#include "decoder.h"
#include "argument.h"

typedef struct { // tbd
    /* Here will be stored all registers */
    VM_QWORD regArray[REGS_COUNT];
    /* Program Counter */
    VM_QWORD pc;
    /* Instruction Pointer / Bit Pointer */
    /* Stack Pointer */
    //VM_QWORD sp;
} REGISTERS, *PREGISTERS;

class VirtualMachine
{
public:
    VirtualMachine(std::vector<char>& programBytes);

    void run();

private:
    std::array<int64_t, REGS_COUNT> reg;
    VM_DWORD ip;

    Memory memory;
    Decoder decoder;

    void setIp(VM_DWORD);
    void initializeMemory();
    void initializeRegisters();

    int64_t getValue(Argument) const;
};

#endif // VIRTUALMACHINE_H
