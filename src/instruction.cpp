#include <map>
#include <string>

#include <iostream>

#include "../include/instruction.h"
#include "../include/global.h"
#include "../include/decoder.h"

using namespace std;

std::map<instruction::type, string> name = {
    {instruction::type::mov, "mov"},
    {instruction::type::loadConstant, "loadConstant"},
    {instruction::type::add, "add"},
    {instruction::type::sub, "sub"},
    {instruction::type::div, "div"},
    {instruction::type::mod, "mod"},
    {instruction::type::mul, "mul"},
    {instruction::type::compare, "compare"},
    {instruction::type::jump, "jump"},
    {instruction::type::jumpEqual, "jumpEqual"},
    {instruction::type::read, "read"},
    {instruction::type::write, "write"},
    {instruction::type::consoleRead, "consoleRead"},
    {instruction::type::consoleWrite, "cosnoleWrite"},
    {instruction::type::createThread, "createThread"},
    {instruction::type::joinThread, "joinThread"},
    {instruction::type::hlt, "hlt"},
    {instruction::type::sleep, "sleep"},
    {instruction::type::call, "call"},
    {instruction::type::ret, "ret"},
    {instruction::type::lock, "lock"},
    {instruction::type::unlock, "unlock"}
};

Instruction::Instruction()
{
}

void Instruction::run()
{
    if(DEBUG)
        printInstruction();
    decode();
    if(DEBUG)
        printExpression();
    execute();
}

void Instruction::printInstruction() const
{
    cout << "Instruction: " << name[inst] << endl;
}


void iLoadConstant::decode(Decoder& decoder)
{
    constant = decoder.decodeConstant();
    arg1 = decoder.decodeArg();
}

void iLoadConstant::execute() // &Memory
{
    if(arg1.isRegister())
        ;//reg[arg1.index] = constant;
    else if(arg1.isMemory())
        ;//memory.data[arg1.address] = constant
}

void iLoadConstant::printExpression() const
{
    if(arg1.isRegister())
        cout << "reg[" << arg1.index << "] = " <<constant;
    else if(arg1.isMemory())
        ;//tbd
}
