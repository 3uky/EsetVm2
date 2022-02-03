#include <string>
#include <map>
#include <thread>

#include "../include/vm.h"
#include "../include/instruction.h"

using namespace std;

VirtualMachine::VirtualMachine(string& filename) : io(filename), memory(io), decoder(memory), engine(this)
{
}

void VirtualMachine::run()
{
    execute(reg);
}

void VirtualMachine::execute(Registers reg)
{
    while(1)
    {
        if(engine.executeNextInstruction(reg) == Instruction::Type::hlt)
            break;
    }
}
