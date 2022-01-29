#ifndef ARGUMENT_H
#define ARGUMENT_H

#include "global.h"

class Argument
{
public:
    enum type { mem, reg } argType;
    enum memSize { byte, word, dword, qword } argMemSize;
    int index;
    VM_DWORD address;

    Argument();
    Argument(type, int);
    Argument(type, int, memSize);

    bool isRegister() const;
    bool isMemory() const;

    void print() const;
};

#endif // ARGUMENT_H
