#include "../include/argument.h"

#include <sstream>
#include <map>

Argument::Argument() : argType(Type::reg), index(0)
{
}

Argument::Argument(Type iType, int iIndex) : argType(iType), index(iIndex)
{
}

Argument::Argument(Type iType, int iIndex, Memory::Size iMemSize) : argType(iType), msize(iMemSize), index(iIndex)
{
}

bool Argument::isRegister() const
{
    return (argType == Type::reg);
}

bool Argument::isMemory() const
{
    return (argType == Type::mem);
}

VM_QWORD Argument::getValue(Registers& reg, Memory& memory)
{
    if(isRegister())
        return reg[index];
    else
        return memory.read(reg[index], msize);
}

void Argument::storeResult(VM_QWORD value, Registers& reg, Memory& memory)
{
    if(isRegister())
        reg[index] = value;
    else if(isMemory())
        memory.write(reg[index], msize, value);
}

const std::string Argument::getStr() const
{
    std::stringstream ss;
    static std::map<Memory::Size, std::string> sizeTable = {
        {Memory::Size::byte, "byte"},
        {Memory::Size::word, "word"},
        {Memory::Size::dword, "dword"},
        {Memory::Size::qword, "qword"}
    };

    if(isRegister())
        ss << "r" << index;
    else if(isMemory())
        ss << sizeTable[msize] << "[r" << index << "]";

    return ss.str();
}
