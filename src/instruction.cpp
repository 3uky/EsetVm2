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

void Instruction::run(Decoder& decoder, std::array<int64_t, REGS_COUNT>& reg, Memory& memory)
{
    printName();
    decode(decoder);
    execute(reg, memory);
    printExpression();
}

void Instruction::printName() const
{
    if(DEBUG)
        cout << "Instruction: " << name[iType] << endl;
}

int64_t Instruction::getValue(Argument arg, std::array<int64_t, REGS_COUNT>& reg, Memory& memory) const
{
    if(arg.isRegister())
        return reg[arg.index];
    else
        return memory.data[arg.address];
}



LoadConstant::LoadConstant()
{
    iType = instruction::type::loadConstant;
}

void LoadConstant::decode(Decoder& decoder)
{
    constant = decoder.decodeConstant();
    arg1 = decoder.decodeArg();
}

void LoadConstant::execute(std::array<int64_t, REGS_COUNT>& reg, Memory& memory)
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
            cout << "Expression:  reg[" << arg1.index << "] = 0x" << std::hex << constant << endl;
        else if(arg1.isMemory())
            cout << "Expression:  memory.data[" << arg1.address << "] = 0x" << std::hex << constant << endl;
    }
}


Add::Add()
{
    iType = instruction::type::add;
}

void Add::decode(Decoder& decoder)
{
    arg1 = decoder.decodeArg();
    arg2 = decoder.decodeArg();
    arg3 = decoder.decodeArg();
}

void Add::execute(std::array<int64_t, REGS_COUNT>& reg, Memory& memory)
{
    if(arg3.isRegister())
        reg[arg2.index] = getValue(arg1, reg, memory) + getValue(arg2, reg, memory);
    else
        ; //tbd
}

void Add::printExpression() const
{
    if(DEBUG)
    {
        cout << "Expression: ";
        arg1.print();
        cout << " = ";
        arg2.print();
        cout << " + ";
        arg3.print();
        cout << endl;
    }
}
