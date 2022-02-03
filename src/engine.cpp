#include "engine.h"
#include "vm.h"

#include <string>

using namespace std;

Engine::Engine(VirtualMachine* ivm) : vm(*ivm), read(vm.io, vm.memory), createThread(vm.tm, ivm), joinThread(vm.tm)
{
    instructions = {
        { Instruction::Type::mov, &mov},
        { Instruction::Type::loadConstant, &loadConstant},
        { Instruction::Type::add, &add},
        { Instruction::Type::sub, &sub},
        { Instruction::Type::div, &div},
        { Instruction::Type::mod, &mod},
        { Instruction::Type::mul, &mul},
        { Instruction::Type::compare, &compare},
        { Instruction::Type::jump, &jump},
        { Instruction::Type::jumpEqual, &jumpEqual},
        { Instruction::Type::read, &read},
        // write
        { Instruction::Type::consoleRead, &consoleRead},
        { Instruction::Type::consoleWrite, &consoleWrite},
        { Instruction::Type::createThread, &createThread},
        { Instruction::Type::joinThread, &joinThread},
        { Instruction::Type::hlt, &hlt},
        { Instruction::Type::sleep, &sleep},
        { Instruction::Type::call, &call},
        { Instruction::Type::ret, &ret}
        // lock
        // unlock
    };
}

Instruction::Type Engine::executeNextInstruction(Registers& reg)
{
    reg.instcount++;
    auto type = vm.decoder.decodeInstructionCode(reg);
    if(instructions[type] == nullptr)
        throw std::runtime_error(std::string("Engine tried access uninitialized instruction pointer!"));

    if(DEBUG) {
        cout << "thread id : " << reg.tId << endl;
        vm.reg.printInstCounter();
        instructions[type]->printName();
    }

    instructions[type]->decode(reg, vm.decoder);
    instructions[type]->execute(reg);

    if(DEBUG) {
        instructions[type]->printExpression();
        vm.memory.printData();
        reg.print();
    }

    return type;
}

