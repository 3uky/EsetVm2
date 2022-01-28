#include <string>

#include "../include/vm.h"

using namespace std;

VirtualMachine::VirtualMachine(std::vector<char>& programMemory) : ip(0), memory(programMemory), decoder(memory, ip)
{
    initializeMemory();
}

void VirtualMachine::setIp(VM_DWORD newIp)
{
    ip = newIp;
}

void VirtualMachine::initializeMemory()
{
    memory.setHeader(decoder.decodeHeader());
    if(!memory.isHeaderValid()) {
        memory.printHeaderSize();
        throw runtime_error(std::string("Memory validation failed"));
    }
}
