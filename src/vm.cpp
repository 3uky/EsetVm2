#include <string>
#include <iostream>
#include <map>

#include "../include/vm.h"
#include "../include/instruction.h"

using namespace std;

VirtualMachine::VirtualMachine(std::vector<char>& programMemory) : reg(), memory(programMemory), decoder(memory, reg)
{
}

// tbd: engine.instructions[type]->run() move engine to separate class
std::map<Instruction::type, Instruction*> VirtualMachine::initializeEngine()
{
    std::map<Instruction::type, Instruction*> instructions = {
        { Instruction::type::add, &iAdd },
        { Instruction::type::sub, &iSub},
        { Instruction::type::div, &iDiv},
        { Instruction::type::mod, &iMod},
        { Instruction::type::mul, &iMul},
        { Instruction::type::compare, &iCompare},
        { Instruction::type::consoleWrite, &iConsoleWrite},
        { Instruction::type::loadConstant, &iLoadConstant},
        { Instruction::type::hlt, &iHlt}
    };

    // check if is init

    return instructions;
}

void VirtualMachine::run()
{
    auto instructions = initializeEngine();

    //for (int i=0; i < 4; i++)
    while(1)
    {
        auto iType = decoder.decodeInstructionCode();
        //cout << "Instruction: " << int(iType) << endl;
        instructions[iType]->run(decoder, reg, memory);
    }
}
