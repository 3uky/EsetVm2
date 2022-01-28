#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <vector>
#include <array>

#include "global.h"
#include "memory.h"
#include "decoder.h"

typedef struct {
    /* Here will be stored a data, that program is needed */
    VM_BYTE *dataArray;
    /* Here will be stack */
    //VM_QWORD stackArray[STACK_SIZE];
    /* Here will be stored a program's code */
    VM_BYTE *codeArray;
} ADDRESS_SPACE, *PADDRESS_SPACE;

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

private:
    // new
    bool isVMwork;
    bool isMainThread;

    // MEMORY CONTROLLERS
    REGISTERS registers;
    std::array<int64_t, REGS_COUNT> reg;
    VM_DWORD ip;

    Memory memory;
    Decoder decoder;

    void setIp(VM_DWORD);
    void initializeMemory();
};

#endif // VIRTUALMACHINE_H
