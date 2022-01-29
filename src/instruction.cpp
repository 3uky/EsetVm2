#include <map>
#include <string>
#include <iostream>

#include "../include/instruction.h"
#include "../include/decoder.h"

using namespace std;

std::map<Instruction::type, string> name = {
    {Instruction::type::mov, "mov"},
    {Instruction::type::loadConstant, "loadConstant"},
    {Instruction::type::add, "add"},
    {Instruction::type::sub, "sub"},
    {Instruction::type::div, "div"},
    {Instruction::type::mod, "mod"},
    {Instruction::type::mul, "mul"},
    {Instruction::type::compare, "compare"},
    {Instruction::type::jump, "jump"},
    {Instruction::type::jumpEqual, "jumpEqual"},
    {Instruction::type::read, "read"},
    {Instruction::type::write, "write"},
    {Instruction::type::consoleRead, "consoleRead"},
    {Instruction::type::consoleWrite, "cosnoleWrite"},
    {Instruction::type::createThread, "createThread"},
    {Instruction::type::joinThread, "joinThread"},
    {Instruction::type::hlt, "hlt"},
    {Instruction::type::sleep, "sleep"},
    {Instruction::type::call, "call"},
    {Instruction::type::ret, "ret"},
    {Instruction::type::lock, "lock"},
    {Instruction::type::unlock, "unlock"}
};

Instruction::Instruction()
{
}

void Instruction::run(Decoder& decoder, Registers& reg, Memory& memory)
{
    printName();
    decode(decoder);
    execute(reg, memory);
    printExpression();
    printResult(reg, memory);
}

void Instruction::printName() const
{
    if(DEBUG)
        cout << "Instruction: " << name[iType] << endl;
}

void Instruction::printResult(Registers& reg, Memory& memory) const
{
    if(DEBUG)
        reg.print();
}

int64_t Instruction::getValue(Argument arg, Registers& reg, Memory& memory) const
{
    if(arg.isRegister())
        return reg[arg.index];
    else
        return memory.data[arg.address];
}



LoadConstant::LoadConstant()
{
    iType = Instruction::type::loadConstant;
}

void LoadConstant::decode(Decoder& decoder)
{
    constant = decoder.decodeConstant();
    arg1 = decoder.decodeArg();
}

void LoadConstant::execute(Registers& reg, Memory& memory)
{
    if(arg1.isRegister())
        reg[arg1.index] = constant;
    else if(arg1.isMemory())
        memory.data[arg1.address] = constant;

}

void LoadConstant::printExpression() const
{
    if(DEBUG)
    {
        if(arg1.isRegister())
            cout << "Expression : reg[" << arg1.index << "] = 0x" << std::hex << constant << endl;
        else if(arg1.isMemory())
            cout << "Expression : memory.data[" << arg1.address << "] = 0x" << std::hex << constant << endl;
    }
}


Add::Add()
{
    iType = Instruction::type::add;
}

void Add::decode(Decoder& decoder)
{
    arg1 = decoder.decodeArg();
    arg2 = decoder.decodeArg();
    arg3 = decoder.decodeArg();
}

void Add::execute(Registers& reg, Memory& memory)
{
    if(arg3.isRegister())
        reg[arg3.index] = getValue(arg1, reg, memory) + getValue(arg2, reg, memory);
    else
        ; //tbd
}

void Add::printExpression() const
{
    if(DEBUG)
    {
        cout << "Expression : ";
        arg1.print();
        cout << " = ";
        arg2.print();
        cout << " + ";
        arg3.print();
        cout << endl;
    }
}
