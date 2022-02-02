#ifndef ARGUMENT_H
#define ARGUMENT_H

#include "global.h"
#include "registers.h"
#include "memory.h"

class Argument // data access argument type
{
public:
    enum Type { mem, reg } argType;
    enum Memory::Size msize;
    int index;

    Argument();
    Argument(Type, int);
    Argument(Type, int, Memory::Size);

    VM_QWORD getValue(Registers&, Memory&);
    void storeResult(VM_QWORD value, Registers&, Memory&);
    const std::string getStr() const;

    bool isRegister() const;
    bool isMemory() const;
};

#endif // ARGUMENT_H
