#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <iostream>
#include <string.h>
#include <stdexcept>
#include <vector>
#include <array>

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

/*
std::list<Instruction> instructions = {
    Instruction(0b000,    3, "mov"),
    Instruction(0b001,    3, "loadConst"),
    Instruction(0b010001, 6, "add"),
    Instruction(0b010010, 6, "sub"),
    Instruction(0b010011, 6, "div"),
    Instruction(0b010100, 6, "mod"),
    Instruction(0b010101, 6, "mul"),
    Instruction(0b01100,  5, "compare"),
    Instruction(0b01101,  5, "jump"),
    Instruction(0b01110,  5, "jumpEqual"),
    Instruction(0b10000,  5, "read"),
    Instruction(0b10001,  5, "write"),
    Instructistr[i]on(0b10001,  5, "consoleRead"),
    Instruction(0b10011,  5, "consoleWrite"),
    Instruction(0b10100,  5, "createThread"),
    Instruction(0b10101,  5, "joinThread"),
    Instruction(0b10110,  5, "hlt"),
    Instruction(0b10111,  5, "sleep"),
    Instruction(0b1100,   5, "call"),
    Instruction(0b1101,   5, "ret"),
    Instruction(0b1110,   5, "lock"),
    Instruction(0b1111,   5, "unlock")
};*/

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

    INSTRUCTION decodeIns();
    ARGUMENT decodeArg();
    VM_BYTE decodeRegIndex();
    VM_BYTE decodeMemSize();
    VM_QWORD decodeConstant();
    VM_DWORD decodeAddress();

    void setIp(VM_DWORD);
    void printBits(VM_DWORD);
};

#endif // VIRTUALMACHINE_H
