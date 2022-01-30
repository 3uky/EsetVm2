#include <map>
#include <string>
#include <iostream>
#include <iomanip>

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
    auto value = 0;

    if(arg1.isRegister())
        value = reg[arg1.index];
    else if(arg1.isMemory())
        value = memory.data[arg1.address];

    cout << setfill('0') << setw(16) << right << hex << value << endl;
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

    if(DEBUG)
    {
        cout << "Expression : ";
        arg1.print();
        cout << " = ";
        arg2.print();
        cout << operand[iType];
        arg3.print();
        cout << endl;
    }
}

Add::Add()
{
    iType = Instruction::type::add;
}

void Add::execute(Registers& reg, Memory& memory)
{
    if(arg3.isRegister())
        reg[arg3.index] = getValue(arg1, reg, memory) + getValue(arg2, reg, memory);
    else
        ; //tbd
}

Sub::Sub()
{
    iType = Instruction::type::sub;
}

void Sub::execute(Registers& reg, Memory& memory)
{
    if(arg3.isRegister())
        reg[arg3.index] = getValue(arg1, reg, memory) - getValue(arg2, reg, memory);
    else
        ; //tbd
}

Div::Div()
{
    iType = Instruction::type::div;
}

void Div::execute(Registers& reg, Memory& memory)
{
    if(arg3.isRegister())
        reg[arg3.index] = getValue(arg1, reg, memory) / getValue(arg2, reg, memory);
    else
        ; //tbd
}

Mod::Mod()
{
    iType = Instruction::type::mod;
}

void Mod::execute(Registers& reg, Memory& memory)
{
    if(arg3.isRegister())
        reg[arg3.index] = getValue(arg1, reg, memory) % getValue(arg2, reg, memory);
    else
        ; //tbd
}

Mul::Mul()
{
    iType = Instruction::type::mul;
}

void Mul::execute(Registers& reg, Memory& memory)
{
    if(arg3.isRegister())
        reg[arg3.index] = getValue(arg1, reg, memory) * getValue(arg2, reg, memory);
    else
        ; //tbd
}

Compare::Compare()
{
    iType = Instruction::type::compare;
}

void Compare::execute(Registers& reg, Memory& memory)
{
    if(arg3.isRegister())
        reg[arg3.index] = getCompareResult(reg, memory);
    else
        ; //tbd
}

int Compare::getCompareResult(Registers& reg, Memory& memory) const
{
    auto arg1Val = getValue(arg1, reg, memory);
    auto arg2Val = getValue(arg2, reg, memory);
    auto result = 0;

    if(arg1Val == arg2Val)
        result = 0;
    else if(arg1Val < arg2Val)
        result = -1;
    else if(arg1Val > arg2Val)
        result = 1;

    return result;
}





