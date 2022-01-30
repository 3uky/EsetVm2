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
    {
        memory.print();
        reg.print();
    }
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
    if(arg1.isRegister())
        reg[arg1.index] = constant;
    else if(arg1.isMemory())
        throw runtime_error(std::string("NOT IMPLEMENTED!")); //tbd

}

void LoadConstant::printExpression() const
{
    if(DEBUG)
    {
        if(arg1.isRegister())
            cout << "Expression : reg[" << arg1.index << "] = 0x" << std::hex << constant << endl;
        else if(arg1.isMemory())
            throw runtime_error(std::string("NOT IMPLEMENTED!")); // tbd cout << "Expression : memory.data[" << arg1.address << "] = 0x" << std::hex << constant << endl;
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
        reg[arg3.index] = arg1.getValue(reg, memory) + arg1.getValue(reg, memory);
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
        reg[arg3.index] = arg1.getValue(reg, memory) - arg2.getValue(reg, memory);
    else
        throw runtime_error(std::string("NOT IMPLEMENTED!")); //tbd
}

Div::Div()
{
    iType = Instruction::type::div;
}

void Div::execute(Registers& reg, Memory& memory)
{
    if(arg3.isRegister())
        reg[arg3.index] = arg1.getValue(reg, memory) / arg2.getValue(reg, memory);
    else
        throw runtime_error(std::string("NOT IMPLEMENTED!")); //tbd
}

Mod::Mod()
{
    iType = Instruction::type::mod;
}

void Mod::execute(Registers& reg, Memory& memory)
{
    if(arg3.isRegister())
        reg[arg3.index] = arg1.getValue(reg, memory) % arg2.getValue(reg, memory);
    else
        throw runtime_error(std::string("NOT IMPLEMENTED!")); //tbd
}

Mul::Mul()
{
    iType = Instruction::type::mul;
}

void Mul::execute(Registers& reg, Memory& memory)
{
    if(arg3.isRegister())
        reg[arg3.index] = arg1.getValue(reg, memory) * arg2.getValue(reg, memory);
    else
        throw runtime_error(std::string("NOT IMPLEMENTED!")); //tbd
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
        throw runtime_error(std::string("NOT IMPLEMENTED!")); //tbd
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
    VM_QWORD value = arg1.getValue(reg, memory);

    if(arg2.isRegister())
        reg[arg2.index] = value;
    else if(arg2.isMemory())
        memory.write(arg2.getAddress(reg), arg2.msize, value);
}

void Mov::printExpression() const
{
    std::map<Memory::msize, std::string> sizeTable = {
        {Memory::msize::byte, "byte"},
        {Memory::msize::word, "word"},
        {Memory::msize::dword, "dword"},
        {Memory::msize::qword, "qword"}
    };

    if(DEBUG) {
        if(arg2.isRegister())
            cout << "Expression : reg[" << arg2.index << "] = 0x" << arg1.value << " arg1.msize= " << sizeTable[arg1.msize] << endl;
        else
            cout << "Expression : "<< sizeTable[arg2.msize] << "[" << arg2.address << "] = 0x" << arg1.value << endl;
    }
}



