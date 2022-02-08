#include "vm.h"
#include "instruction.h"

#include <string>

using namespace std;

VirtualMachine::VirtualMachine(string& filename) : reg(), io(filename), memory(io), decoder(memory), tm(this), engine(decoder, io, memory, tm)
{
}

// only main thread
void VirtualMachine::run()
{
    executeLoop(reg);

    tm.joinStillRunningThreads();
}

void VirtualMachine::executeLoop(Registers reg)
{
    while(1)
    {
        if(engine.executeNextInstruction(reg) == Instruction::Type::hlt)
            break;

        if(DEBUG) {
            memory.printData();
            reg.print();
        }
    }
}
