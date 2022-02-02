#include <string>
#include <map>

#include "../include/vm.h"
#include "../include/instruction.h"

using namespace std;

VirtualMachine::VirtualMachine(std::string& filename) : reg(), io(filename), memory(io), decoder(memory, reg)
{
}

// tbd: engine.instructions[type]->run() move engine to separate class
std::map<Instruction::type, Instruction*> VirtualMachine::initializeEngine()
{
    std::map<Instruction::type, Instruction*> instructions = {
        { Instruction::type::mov, &iMov},
        { Instruction::type::add, &iAdd },
        { Instruction::type::sub, &iSub},
        { Instruction::type::div, &iDiv},
        { Instruction::type::mod, &iMod},
        { Instruction::type::mul, &iMul},
        { Instruction::type::compare, &iCompare},
        { Instruction::type::jump, &iJump},
        { Instruction::type::jumpEqual, &iJumpEqual},
        { Instruction::type::call, &iCall},
        { Instruction::type::ret, &iRet},
        { Instruction::type::read, &iRead},
        { Instruction::type::consoleWrite, &iConsoleWrite},
        { Instruction::type::consoleRead, &iConsoleRead},
        { Instruction::type::loadConstant, &iLoadConstant},
        { Instruction::type::hlt, &iHlt}
    };

    return instructions;
}

void VirtualMachine::run()
{
    auto instructions = initializeEngine();

    while(1)
    {
        reg.instcount++;
        auto iType = decoder.decodeInstructionCode();
        instructions[iType]->run(decoder, reg, memory);
        if(instructions[iType]->isHlt())
            break;
    }
}
