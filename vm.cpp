#include "vm.h"
#include <bitset>

//enum InsType { mov, loadConst, add, sub, div, mod, mul, compare, jump, jumpEqual, read, write, consoleRead, consoleWrite, createThread, }

std::unordered_set<VM_BYTE> validInstructions = {
    {0b000},    // mov
    {0b001},    // loadConst
    {0b010001}, // add
    {0b010010}, // sub
    {0b010011}, // div
    {0b010100}, // mod
    {0b010101}, // mul
    {0b01100},  // compare
    {0b01101},  // jump
    {0b01110},  // jumpEqual
    {0b10000},  // read
    {0b10001},  // write
    {0b10001},  // consoleRead
    {0b10011},  // consoleWrite
    {0b10100},  // createThread
    {0b10101},  // joinThread
    {0b10110},  // hlt
    {0b10111},  // sleep
    {0b1100},   // call
    {0b1101},   // ret
    {0b1110},   // lock
    {0b1111}    // unlock
};

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

ARGUMENT VirtualMachine::decodeArg()
{
    ARGUMENT arg = {0,};

    arg.type = getBitFromCodeMemory();
    if(arg.type == RegType::reg)
        arg.index = decodeRegIndex();
    else if(arg.type == RegType::mem) {
        arg.memSize = decodeMemSize();
        arg.index = decodeRegIndex();
    }

    return arg;
}

VM_BYTE VirtualMachine::decodeRegIndex()
{
    return getBitsFromCodeMemory(4);
}

VM_BYTE VirtualMachine::decodeMemSize()
{
    return getBitsFromCodeMemory(2);
}

VM_DWORD VirtualMachine::decodeAddress()
{
    return getBitsFromCodeMemory(32);
}

VM_QWORD VirtualMachine::decodeConstant()
{
    return getBitsFromCodeMemory(64);
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
