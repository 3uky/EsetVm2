#include <string>

#include "../include/vm.h"

#include <unordered_set>

// global
//enum InsType { mov, loadConst, add, sub, div, mod, mul, compare, jump, jumpEqual, read, write, consoleRead, consoleWrite, createThread, }

VirtualMachine::VirtualMachine(std::vector<char>& programMemory) : memory(programMemory), decoder(memory, ip), ip(0)
{
        memory.setHeader(decoder.decodeHeader());
        memory.printHeaderSize();
        std::cout << memory.isHeaderValid() << std::endl;
}

void VirtualMachine::setIp(VM_DWORD newIp)
{
    ip = newIp;
}
