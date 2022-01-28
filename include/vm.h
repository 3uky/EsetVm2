#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <iostream>
#include <string.h>
#include <stdexcept>
#include <vector>
#include <array>

#include "global.h"
#include "memory.h"

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

// tbd: decoder
enum RegType { mem=1, reg=0 };
enum MemSize { byte=0b00, word=0b01, dword=0b10, qword=0b11 };

class VirtualMachine
{
private:
    // new
    bool isVMwork;
    bool isMainThread;

    REGISTERS registers;
    std::array<int64_t, REGS_COUNT> reg;

    Memory memory;

    // MEMORY CONTROLLERS
    VM_DWORD ip;

public:
    VirtualMachine(std::vector<char>& programBytes);

public:
    void setIp(VM_DWORD);

    // decoder
    VM_BYTE getBitFromCodeMemory();
    VM_QWORD getBitsFromCodeMemory(int);
    VM_QWORD getBitsFromCodeMemory_BigEndianOrder(int);

    HEADER decodeHeader();
    VM_BYTE decodeInstructionCode();
    ARGUMENT decodeArg();
    VM_BYTE decodeRegIndex();
    VM_BYTE decodeMemSize();
    VM_QWORD decodeConstant();
    VM_DWORD decodeAddress();

    bool isInstructionValid(VM_BYTE) const;

    VM_BYTE convertEndian(VM_BYTE);
    VM_BYTE convertEndian(VM_BYTE, int);

    VM_WORD swapWord(VM_WORD);
    VM_DWORD swapDword(VM_DWORD);
    VM_QWORD swapQword(VM_QWORD);

    // others
    void printBits(VM_DWORD);
};

#endif // VIRTUALMACHINE_H
