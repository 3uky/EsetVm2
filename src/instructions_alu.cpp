#include "instructions_alu.h"

#include <map>

using namespace std;

Alu::Alu()
{
}

void Alu::decode(Registers& reg, Decoder& decoder)
{
    arg1 = decoder.decodeArg(reg);
    arg2 = decoder.decodeArg(reg);
    arg3 = decoder.decodeArg(reg);
}

void Alu::printExpression() const
{
    static map<Instruction::Type, std::string> operand = {
        { Instruction::Type::add, " + " },
        { Instruction::Type::sub, " - " },
        { Instruction::Type::mul, " * " },
        { Instruction::Type::div, " / " },
        { Instruction::Type::mod, " % " },
        { Instruction::Type::compare, " compare " }
    };

    std::cout << "Expression : " << arg3.getStr() << " = " << arg1.getStr() << operand[iType] << arg2.getStr() << std::endl;
}

Add::Add()
{
    iType = Instruction::Type::add;
}

void Add::execute(Registers& reg)
{
    arg3.storeResult(arg1.getValue(reg) + arg2.getValue(reg), reg);
}

Sub::Sub()
{
    iType = Instruction::Type::sub;
}

void Sub::execute(Registers& reg)
{
    arg3.storeResult(arg1.getValue(reg) - arg2.getValue(reg), reg);
}

Div::Div()
{
    iType = Instruction::Type::div;
}

void Div::execute(Registers& reg)
{
    arg3.storeResult(arg1.getValue(reg) / arg2.getValue(reg), reg);
}

Mod::Mod()
{
    iType = Instruction::Type::mod;
}

void Mod::execute(Registers& reg)
{
    arg3.storeResult(arg1.getValue(reg) % arg2.getValue(reg), reg);
}

Mul::Mul()
{
    iType = Instruction::Type::mul;
}

void Mul::execute(Registers& reg)
{
    arg3.storeResult(arg1.getValue(reg) * arg2.getValue(reg), reg);
}

Compare::Compare()
{
    iType = Instruction::Type::compare;
}

void Compare::execute(Registers& reg)
{
    arg3.storeResult(getCompareResult(reg), reg);
}

int Compare::getCompareResult(Registers& reg)
{
    int64_t arg1Val = arg1.getValue(reg);
    int64_t arg2Val = arg2.getValue(reg);

    if(arg1Val == arg2Val)
        result = 0;
    else if(arg1Val < arg2Val)
        result = -1;
    else if(arg1Val > arg2Val)
        result = 1;

    return result;
}

void Compare::printExpression() const
{
    if(result == 0)
        cout << "Expression : " << arg1.getStr() << " == " << arg2.getStr() << " -> " << arg3.getStr() << " = 0" << endl;
    if(result == -1)
        cout << "Expression : " << arg1.getStr() << " < " << arg2.getStr() << " -> " << arg3.getStr() << " = -1" << endl;
    if(result == 1)
        cout << "Expression : " << arg1.getStr() << " > " << arg2.getStr() << " -> " << arg3.getStr() << " = 1" << endl;
}

Mov::Mov()
{
    iType = Instruction::Type::mov;
}

void Mov::decode(Registers& reg, Decoder& decoder)
{
    arg1 = decoder.decodeArg(reg);
    arg2 = decoder.decodeArg(reg);
}

void Mov::execute(Registers& reg)
{
    arg2.storeResult(arg1.getValue(reg), reg);
}

void Mov::printExpression() const
{
    cout << "Expression : " << arg2.getStr() << " = " << arg1.getStr() << endl;
}

LoadConstant::LoadConstant()
{
    iType = Instruction::Type::loadConstant;
}

void LoadConstant::decode(Registers& reg, Decoder& decoder)
{
    constant = decoder.decodeConstant(reg);
    arg1 = decoder.decodeArg(reg);
}

void LoadConstant::execute(Registers& reg)
{
    arg1.storeResult(constant, reg);
}

void LoadConstant::printExpression() const
{
    cout << "Expression : " << arg1.getStr() << " = 0x" << hex << constant << endl;
}
