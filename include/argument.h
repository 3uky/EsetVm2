#ifndef ARGUMENT_H
#define ARGUMENT_H

#include "global.h"
#include "registers.h"
#include "memory.h"

class Argument
{
public:
    enum type { mem, reg } argType;
    enum Memory::msize msize;
    int index;
    VM_QWORD value;
    int64_t address;

    Argument();
    Argument(type, int);
    Argument(type, int, Memory::msize);

    VM_QWORD getValue(Registers&, Memory&);
    int64_t getAddress(Registers&);

    bool isRegister() const;
    bool isMemory() const;

    void print() const;
};

#endif // ARGUMENT_H
