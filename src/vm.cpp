#include <string>
#include <map>

#include "../include/vm.h"
#include "../include/instruction.h"

using namespace std;

VirtualMachine::VirtualMachine(std::string& filename) : reg(), io(filename), memory(io), decoder(memory, reg)
{
}

// tbd: engine.instructions[type]->run() move engine to separate class
std::map<Instruction::Type, Instruction*> VirtualMachine::initializeEngine()
{
    std::map<Instruction::Type, Instruction*> instructions = {
        { Instruction::Type::mov, &iMov},
        { Instruction::Type::add, &iAdd },
        { Instruction::Type::sub, &iSub},
        { Instruction::Type::div, &iDiv},
        { Instruction::Type::mod, &iMod},
        { Instruction::Type::mul, &iMul},
        { Instruction::Type::compare, &iCompare},
        { Instruction::Type::jump, &iJump},
        { Instruction::Type::jumpEqual, &iJumpEqual},
        { Instruction::Type::call, &iCall},
        { Instruction::Type::ret, &iRet},
        { Instruction::Type::read, &iRead},
        { Instruction::Type::consoleWrite, &iConsoleWrite},
        { Instruction::Type::consoleRead, &iConsoleRead},
        { Instruction::Type::loadConstant, &iLoadConstant},
        { Instruction::Type::hlt, &iHlt}
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
