#include "vm.h"
#include <bitset>

VirtualMachine::VirtualMachine(std::vector<char>& programMemory) : memory(programMemory), ip(0)
{
}

VM_BYTE VirtualMachine::getBitFromCodeMemory()
{
    auto currentByte = memory[ip / 8];
    auto mask = 0b10000000 >> (ip % 8);
    auto b = (currentByte & mask) >> (7 - (ip % 8));
    ip++;
    return b;
}

// https://stackoverflow.com/questions/9290823/bitwise-shift-operation-in-c-on-uint64-t-variable
VM_QWORD VirtualMachine::getBitsFromCodeMemory(int numberOfBits)
{
    VM_QWORD bits = 0;
    for (int i=0; i < numberOfBits; i++) {
        bits |= (VM_QWORD(getBitFromCodeMemory()) << i);
    }
    return bits;
}

VM_BYTE VirtualMachine::decodeReg()
{
    return getBitsFromCodeMemory(4);
}

VM_DWORD VirtualMachine::decodeAddress()
{
    return getBitsFromCodeMemory(32);
}

VM_QWORD VirtualMachine::decodeConstant()
{
    return getBitsFromCodeMemory(64);
}

VM_BYTE VirtualMachine::decodeMemSize()
{
    return getBitsFromCodeMemory(2);
}

ARGUMENT VirtualMachine::decodeArg()
{
    ARGUMENT arg = {0,};
    arg.type = getBitFromCodeMemory();

    if(arg.type == RegType::reg)
        arg.index = decodeReg();
    else if(arg.type == RegType::mem) {
        arg.memSize = decodeMemSize();
        arg.index = decodeReg();
    }

    return arg;
}

void VirtualMachine::setIp(VM_DWORD newIp)
{
    ip = newIp;
}

void VirtualMachine::printBits(VM_DWORD numberOfBits)
{
    for(VM_DWORD i=0; i < numberOfBits; i++) {
        bool a = getBitFromCodeMemory();

        if (i % (8*6) == 0 && i != 0)
            std::cout << std::endl;

        std::cout << a;

        if ((i+1) % 8 == 0 && i != 0)
            std::cout << " ";
    }
    std::cout << std::endl;
}
