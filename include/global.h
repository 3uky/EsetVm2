#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <iostream>

const int REGS_COUNT=16;

typedef uint8_t VM_BYTE;
typedef uint16_t VM_WORD;
typedef uint32_t VM_DWORD;
typedef uint64_t VM_QWORD;

typedef struct {
    VM_DWORD codeSize;
    VM_DWORD dataSize;
    VM_DWORD initialDataSize;
} HEADER;

typedef struct {
    int index;
    VM_BYTE type;
    VM_BYTE memSize;
    VM_DWORD address;
} ARGUMENT;

namespace argument {
    enum type {
        mem = 1,
        reg = 0
    };

    enum memSize {
        byte = 0b00,
        word = 0b01,
        dword = 0b10,
        qword = 0b11
    };
}

namespace instruction {
    enum type { // tbd Instruction class
        mov = 0b000,
        loadConstant = 0b001,
        add = 0b010001,
        sub = 0b010010,
        div = 0b010011,
        mod = 0b010100,
        mul = 0b010101,
        compare = 0b01100,
        jump = 0b01101,
        jumpEqual = 0b01110,
        read = 0b10000,
        write = 0b10001,
        consoleRead = 0b10010,
        consoleWrite = 0b10011,
        createThread = 0b10100,
        joinThread = 0b10101,
        htl = 0b10110,
        sleep = 0b10111,
        call = 0b1100,
        ret = 0b1101,
        lock = 0b1110,
        unlock = 0b1111
    };
}

#endif // GLOBAL_H_INCLUDED
