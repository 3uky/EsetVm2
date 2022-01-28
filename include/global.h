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
    VM_BYTE index;
    VM_BYTE type;
    VM_BYTE memSize;
    VM_DWORD address;
} ARGUMENT;

typedef struct {
    VM_BYTE index;
} INSTRUCTION;

#endif // GLOBAL_H_INCLUDED
