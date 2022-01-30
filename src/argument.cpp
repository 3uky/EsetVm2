#include "../include/argument.h"

Argument::Argument() : argType(type::reg), index(0)
{
}

Argument::Argument(type iType, int iIndex) : argType(iType), index(iIndex)
{
}

Argument::Argument(type iType, int iIndex, Memory::msize iMemSize) : argType(iType), msize(iMemSize), index(iIndex)
{
}

bool Argument::isRegister() const
{
    return (argType == type::reg);
}

bool Argument::isMemory() const
{
    return (argType == type::mem);
}

void Argument::print() const
{
    if(isRegister())
        std::cout << "reg[" << index << "]";
    else if(isMemory())
        std::cout << "memory.data[" << "reg[" << index << "]]";
}


VM_QWORD Argument::getValue(Registers& reg, Memory& memory)
{
    if(isRegister())
        value = reg[index];
    else
        value = memory.read(index, msize);

    return value;
}

int64_t Argument::getAddress(Registers& reg)
{
    address = reg[index];
    return address;
}
