#include "../include/argument.h"
#include "../include/global.h"

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

/*
void Argument::print() const
{
    if(arg.type == argument::type::reg)
        cout << "reg[" << arg.index << "]: " << reg[arg.index] << endl;
    else if(arg.type == argument::type::mem)
        cout << "mem[" << arg.address << "]: " << endl; //tbd
}
*/
