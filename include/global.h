#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <iostream>

const int REGS_COUNT=16;

typedef uint8_t VM_BYTE;
typedef uint16_t VM_WORD;
typedef uint32_t VM_DWORD;
typedef uint64_t VM_QWORD;

namespace instruction {
    enum type { mov, loadConstant, add, sub, div, mod, mul, compare, jump, jumpEqual, read, write, consoleRead, consoleWrite, createThread, joinThread, hlt, sleep, call, ret, lock, unlock};
}

#endif // GLOBAL_H_INCLUDED
