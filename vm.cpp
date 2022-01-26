#include "vm.h"

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

VM_BYTE VirtualMachine::decodeArg()
{
    return getBitFromCodeMemory() | (getBitFromCodeMemory() << 1) | (getBitFromCodeMemory() << 2) | (getBitFromCodeMemory() << 3);
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
