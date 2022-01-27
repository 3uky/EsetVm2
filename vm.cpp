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

VM_BYTE VirtualMachine::decodeReg()
{
    return getBitFromCodeMemory() | (getBitFromCodeMemory() << 1) | (getBitFromCodeMemory() << 2) | (getBitFromCodeMemory() << 3);
}

ARGUMENT VirtualMachine::decodeArg()
{
    ARGUMENT arg = {0,};
    arg.type = getBitFromCodeMemory();

    if(arg.type == RegType::reg)
        arg.index = decodeReg();
    else if(arg.type == RegType::mem) {
        VM_BYTE memSize = 0;
        memSize |= getBitFromCodeMemory() | (getBitFromCodeMemory() << 1);
        arg.memSize = memSize;
        arg.index = decodeReg();
    }

    return arg;
}

VM_DWORD VirtualMachine::decodeAddress()
{
    VM_DWORD address = 0;
    for (int i=0; i < 32; i++) {
        address |= (VM_QWORD(getBitFromCodeMemory()) << i);
    }
    return address;
}

VM_QWORD VirtualMachine::decodeConstant()
{
    VM_QWORD constant = 0;
    for (int i=0; i < 64; i++) {   // https://stackoverflow.com/questions/9290823/bitwise-shift-operation-in-c-on-uint64-t-variable
        constant |= (VM_QWORD(getBitFromCodeMemory()) << i);
    }
    return constant;
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
