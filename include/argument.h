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

    Argument();
    Argument(type, int);
    Argument(type, int, Memory::msize);

    VM_QWORD getValue(Registers&, Memory&);
    void storeResult(VM_QWORD value, Registers&, Memory&);
    const std::string getStr() const;

    bool isRegister() const;
    bool isMemory() const;
};

#endif // ARGUMENT_H
