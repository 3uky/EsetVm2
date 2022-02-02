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
    Argument(Type, int, Memory*);
    Argument(Type, int, Memory::Size, Memory*);

    VM_QWORD getValue(Registers&);
    void storeResult(VM_QWORD value, Registers&);
    const std::string getStr() const;

    bool isRegister() const;
    bool isMemory() const;

private:
    Memory* memory;
    void checkInit(void*);
};

#endif // ARGUMENT_H
