#include "argument.h"

#include <sstream>
#include <string>
#include <map>

using namespace std;

Argument::Argument() : argType(Type::reg), index(0)
{
}

Argument::Argument(Type iType, int iIndex, Memory* iMemory) : argType(iType), index(iIndex), memory(iMemory)
{
}

Argument::Argument(Type iType, int iIndex, Memory::Size iMemSize, Memory* iMemory) : argType(iType), msize(iMemSize), index(iIndex), memory(iMemory)
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

VM_QWORD Argument::getValue(Registers& reg)
{
    if(isRegister())
        return reg[index];
    else {
        checkInit(memory);
        return memory->read(reg[index], msize);
    }
}

void Argument::storeResult(VM_QWORD value, Registers& reg)
{
    if(isRegister())
        reg[index] = value;
    else if(isMemory()) {
        checkInit(memory);
        memory->write(reg[index], msize, value);
    }
}

void Argument::checkInit(void* ptr)
{
    if(ptr == nullptr)
        throw runtime_error(string("Argument tried access uninitialized memory pointer!"));
}

const string Argument::getStr() const
{
    stringstream ss;
    static map<Memory::Size, string> sizeTable = {
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
