#include <map>
#include <string>
#include <iostream>
#include <iomanip>

#include "../include/instruction.h"
#include "../include/decoder.h"

using namespace std;

Instruction::Instruction()
{
}

void Instruction::run(Decoder& decoder, Registers& reg, Memory& memory)
{
    decode(decoder);
    execute(reg, memory);

    if(DEBUG)
    {
        printName();
        printExpression();
        printResult(reg, memory);
    }
}

void Instruction::printName() const
{
    static std::map<Instruction::type, string> name = {
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
        {Instruction::type::consoleWrite, "consoleWrite"},
        {Instruction::type::createThread, "createThread"},
        {Instruction::type::joinThread, "joinThread"},
        {Instruction::type::hlt, "hlt"},
        {Instruction::type::sleep, "sleep"},
        {Instruction::type::call, "call"},
        {Instruction::type::ret, "ret"},
        {Instruction::type::lock, "lock"},
        {Instruction::type::unlock, "unlock"}
    };

    cout << "Instruction: " << name[iType] << endl;
}

void Instruction::printResult(Registers& reg, Memory& memory) const
{
    memory.printData();
    reg.print();
}

bool Instruction::isHlt() const
{
    return iType == Instruction::type::hlt;
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
    arg1.storeResult(constant, reg, memory);
}

void LoadConstant::printExpression() const
{
    cout << "Expression : " << arg1.getStr() << std::hex << constant << endl;
}

ConsoleWrite::ConsoleWrite()
{
    iType = Instruction::type::consoleWrite;
}

void ConsoleWrite::decode(Decoder& decoder)
{
    arg1 = decoder.decodeArg();
}

void ConsoleWrite::execute(Registers& reg, Memory& memory)
{
    cout << setfill('0') << setw(16) << right << hex << arg1.getValue(reg, memory) << endl;
}

Alu::Alu()
{
}

void Alu::decode(Decoder& decoder)
{
    arg1 = decoder.decodeArg();
    arg2 = decoder.decodeArg();
    arg3 = decoder.decodeArg();
}

void Alu::printExpression() const
{
    static map<Instruction::type, std::string> operand = {
        { Instruction::type::add, " + " },
        { Instruction::type::sub, " - " },
        { Instruction::type::mul, " * " },
        { Instruction::type::div, " / " },
        { Instruction::type::mod, " % " },
        { Instruction::type::compare, " == " }
    };

    std::cout << "Expression : " << arg1.getStr() << " = " << arg2.getStr() << operand[iType] << arg3.getStr() << std::endl;
}

Add::Add()
{
    iType = Instruction::type::add;
}

void Add::execute(Registers& reg, Memory& memory)
{
    arg3.storeResult(arg1.getValue(reg, memory) + arg2.getValue(reg, memory), reg, memory);
}

Sub::Sub()
{
    iType = Instruction::type::sub;
}

void Sub::execute(Registers& reg, Memory& memory)
{
    arg3.storeResult(arg1.getValue(reg, memory) - arg2.getValue(reg, memory), reg, memory);
}

Div::Div()
{
    iType = Instruction::type::div;
}

void Div::execute(Registers& reg, Memory& memory)
{
    arg3.storeResult(arg1.getValue(reg, memory) / arg2.getValue(reg, memory), reg, memory);
}

Mod::Mod()
{
    iType = Instruction::type::mod;
}

void Mod::execute(Registers& reg, Memory& memory)
{
    arg3.storeResult(arg1.getValue(reg, memory) % arg2.getValue(reg, memory), reg, memory);
}

Mul::Mul()
{
    iType = Instruction::type::mul;
}

void Mul::execute(Registers& reg, Memory& memory)
{
    arg3.storeResult(arg1.getValue(reg, memory) * arg2.getValue(reg, memory), reg, memory);
}

Compare::Compare()
{
    iType = Instruction::type::compare;
}

void Compare::execute(Registers& reg, Memory& memory)
{
    arg3.storeResult(getCompareResult(reg, memory), reg, memory);
}

int Compare::getCompareResult(Registers& reg, Memory& memory)
{
    auto arg1Val = arg1.getValue(reg, memory);
    auto arg2Val = arg2.getValue(reg, memory);
    auto result = 0;

    if(arg1Val == arg2Val)
        result = 0;
    else if(arg1Val < arg2Val)
        result = -1;
    else if(arg1Val > arg2Val)
        result = 1;

    return result;
}

Mov::Mov()
{
    iType = Instruction::type::mov;
}

void Mov::decode(Decoder& decoder)
{
    arg1 = decoder.decodeArg();
    arg2 = decoder.decodeArg();
}

void Mov::execute(Registers& reg, Memory& memory)
{
    arg2.storeResult(arg1.getValue(reg, memory), reg, memory);
}

void Mov::printExpression() const
{
    cout << "Expression : " << arg2.getStr() << " = " << arg1.getStr() << endl;
}
