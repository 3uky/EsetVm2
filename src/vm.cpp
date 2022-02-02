#include <string>
#include <map>

#include "../include/vm.h"
#include "../include/instruction.h"

using namespace std;

VirtualMachine::VirtualMachine(std::string& filename) : reg(), io(filename), memory(io), decoder(memory, reg), engine(memory, decoder, io)
{
}

void VirtualMachine::run()
{
    while(1)
    {
        if(engine.executeNextInstruction(reg) == Instruction::Type::hlt)
            break;
    }
}
