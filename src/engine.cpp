#include "engine.h"
#include "vm.h"

#include <set>

using namespace std;

Engine::Engine(Decoder& dec, IO& io, Memory& memory, ThreadingModel& tm) : decoder(dec),
    read(io, memory), write(io, memory), createThread(tm), joinThread(tm), lock(tm), unlock(tm)
{
    initialize();
}

Instruction::Type Engine::executeNextInstruction(Registers& reg)
{
    auto type = decoder.decodeInstructionCode(reg);

    if(DEBUG)
        instructions[type]->printName();

    if(isInstructionMemoryRelated(type))
        mtx.lock();

    instructions[type]->decode(reg, decoder);
    instructions[type]->execute(reg);

    if(isInstructionMemoryRelated(type))
        mtx.unlock();

    if(DEBUG)
        instructions[type]->printExpression();

    return type;
}

bool Engine::isInstructionMemoryRelated(Instruction::Type type) const
{
    static std::set<Instruction::Type> memoryRelated = {
        { Instruction::Type::mov},
        { Instruction::Type::loadConstant},
        { Instruction::Type::add},
        { Instruction::Type::sub},
        { Instruction::Type::div},
        { Instruction::Type::mod},
        { Instruction::Type::mul},
        { Instruction::Type::compare},
        { Instruction::Type::jump},
        { Instruction::Type::jumpEqual},
        { Instruction::Type::read},
        { Instruction::Type::write},
        //{ Instruction::Type::consoleRead}, // peudorandom
        //{ Instruction::Type::consoleWrite}, // philosophers
        { Instruction::Type::createThread},
        //{ Instruction::Type::joinThread},
        //{ Instruction::Type::hlt},
        //{ Instruction::Type::sleep},
        //{ Instruction::Type::call},
        //{ Instruction::Type::ret},
        //{ Instruction::Type::lock}
        //{ Instruction::Type::unlock}
    };

    return memoryRelated.find(type) != memoryRelated.end();
}

void Engine::initialize()
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
        { Instruction::Type::write, &write},
        { Instruction::Type::consoleRead, &consoleRead},
        { Instruction::Type::consoleWrite, &consoleWrite},
        { Instruction::Type::createThread, &createThread},
        { Instruction::Type::joinThread, &joinThread},
        { Instruction::Type::hlt, &hlt},
        { Instruction::Type::sleep, &sleep},
        { Instruction::Type::call, &call},
        { Instruction::Type::ret, &ret},
        { Instruction::Type::lock, &lock},
        { Instruction::Type::unlock, &unlock}
    };
}
