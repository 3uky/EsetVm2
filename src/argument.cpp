#include "../include/argument.h"

Argument::Argument() : argType(type::reg), index(0)
{
}

Argument::Argument(type iType, int iIndex) : argType(iType), index(iIndex)
{
}

Argument::Argument(type iType, int iIndex, memSize iMemSize) : argType(iType), argMemSize(iMemSize), index(iIndex)
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
        std::cout << "memory.data[" << address << "]";
}
