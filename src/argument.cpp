#include "../include/argument.h"

Argument::Argument() : index(0), type(0)
{
}

Argument::Argument(VM_BYTE iType, int iIndex) : index(iIndex), type(iType)
{
}

Argument::Argument(VM_BYTE iType, int iIndex, VM_BYTE iMemSize) : index(iIndex), type(iType), memSize(iMemSize)
{
}

bool Argument::isRegister() const
{
    return (type == type::reg);
}

bool Argument::isMemory() const
{
    return (type == type::mem);
}

void Argument::print() const
{
    if(isRegister())
        std::cout << "reg[" << index << "]";
    else if(isMemory())
        std::cout << "memory.data[" << address << "]";
}
