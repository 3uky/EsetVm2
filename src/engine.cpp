#include "engine.h"

#include <string>

using namespace std;

Engine::Engine(Memory& mem, Decoder& dec, IO& iio) : memory(mem), decoder(dec), io(iio), read(io, memory)
{
    instructions = {
        { Instruction::Type::mov, &mov},
        { Instruction::Type::add, &add},
        { Instruction::Type::sub, &sub},
        { Instruction::Type::div, &div},
        { Instruction::Type::mod, &mod},
        { Instruction::Type::mul, &mul},
        { Instruction::Type::compare, &compare},
        { Instruction::Type::jump, &jump},
        { Instruction::Type::jumpEqual, &jumpEqual},
        { Instruction::Type::call, &call},
        { Instruction::Type::ret, &ret},
        { Instruction::Type::read, &read},
        { Instruction::Type::consoleWrite, &consoleWrite},
        { Instruction::Type::consoleRead, &consoleRead},
        { Instruction::Type::loadConstant, &loadConstant},
        { Instruction::Type::hlt, &hlt}
    };
}

Instruction::Type Engine::executeNextInstruction(Registers& reg)
{
    reg.instcount++;
    auto type = decoder.decodeInstructionCode(reg);
    if(instructions[type] == nullptr)
        throw std::runtime_error(std::string("Engine tried access uninitialized instruction pointer!"));

    if(DEBUG) {
        cout << "thread id : " << reg.tId << endl;
        reg.printInstCounter();
        instructions[type]->printName();
    }

    instructions[type]->decode(reg, decoder);
    instructions[type]->execute(reg);

    if(DEBUG) {
        instructions[type]->printExpression();
        memory.printData();
        reg.print();
    }

    return type;
}

