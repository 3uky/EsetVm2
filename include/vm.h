#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <iostream>
#include <string.h>
#include <stdexcept>
#include <vector>
#include <array>
#include <unordered_set>

typedef uint8_t VM_BYTE;
typedef uint16_t VM_WORD;
typedef uint32_t VM_DWORD;
typedef uint64_t VM_QWORD;

const int REGS_COUNT=16;

typedef struct {
    /* Here will be stored a data, that program is needed */
    VM_BYTE *dataArray;
    /* Here will be stack */
    //VM_QWORD stackArray[STACK_SIZE];
    /* Here will be stored a program's code */
    VM_BYTE *codeArray;
} ADDRESS_SPACE, *PADDRESS_SPACE;

typedef struct {
    /* Here will be stored all registers */
    VM_QWORD regArray[REGS_COUNT];
    /* Program Counter */
    VM_QWORD pc;
    /* Instruction Pointer / Bit Pointer */
    /* Stack Pointer */
    //VM_QWORD sp;
} REGISTERS, *PREGISTERS;




enum RegType { mem=1, reg=0 };
enum MemSize { byte=0b00, word=0b01, dword=0b10, qword=0b11 };

typedef struct {
    VM_BYTE index;
    VM_BYTE type;
    VM_BYTE memSize;
    VM_DWORD address;
} ARGUMENT;

typedef struct {
    VM_BYTE index;
} INSTRUCTION;

class VirtualMachine
{
private:
    // new
    bool isVMwork;
    bool isMainThread;

    REGISTERS registers;
    //ADDRESS_SPACE memory;
    //HEADER header;

    std::vector<char> memory;
    std::array<int64_t, REGS_COUNT> reg;

    // MEMORY CONTROLLERS
    VM_DWORD ip;

public:
    VirtualMachine(std::vector<char>& programBytes);

public:
    VM_BYTE getBitFromCodeMemory();
    VM_QWORD getBitsFromCodeMemory(int);

    VM_BYTE decodeInstructionCode();
    bool isInstructionValid(VM_BYTE) const;
    ARGUMENT decodeArg();
    VM_BYTE decodeRegIndex();
    VM_BYTE decodeMemSize();
    VM_QWORD decodeConstant();
    VM_DWORD decodeAddress();
    VM_BYTE convertEndian(VM_BYTE);
    VM_BYTE convertEndian(VM_BYTE, int);

    void setIp(VM_DWORD);
    void printBits(VM_DWORD);
};

#endif // VIRTUALMACHINE_H
