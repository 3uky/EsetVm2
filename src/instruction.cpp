#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "../include/instruction.h"
#include "../include/decoder.h"

using namespace std;

Instruction::Instruction()
{
}

void Instruction::run(Decoder& decoder, Registers& reg, Memory& memory)
{
    if(DEBUG) {
        printInstructionCounter(reg);
        printName();
    }

    decode(decoder);
    execute(reg, memory);

    if(DEBUG) {
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

void Instruction::printInstructionCounter(Registers& reg) const
{
    reg.printInstCounter();
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
    cout << "Expression : " << arg1.getStr() << " = 0x" << hex << constant << endl;
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

ConsoleRead::ConsoleRead()
{
    iType = Instruction::type::consoleRead;
}

void ConsoleRead::decode(Decoder& decoder)
{
    arg1 = decoder.decodeArg();
}

void ConsoleRead::execute(Registers& reg, Memory& memory)
{
    cin >> value;
    arg1.storeResult(value, reg, memory);
}

void ConsoleRead::printExpression() const
{
    cout << "Expression : " << arg1.getStr() << " = " << dec << value << " (0x" << hex << value << ")" << endl;
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
        { Instruction::type::compare, " compare " }
    };

    std::cout << "Expression : " << arg3.getStr() << " = " << arg1.getStr() << operand[iType] << arg2.getStr() << std::endl;
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
    int64_t arg1Val = arg1.getValue(reg, memory);
    int64_t arg2Val = arg2.getValue(reg, memory);

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

Jump::Jump()
{
    iType = Instruction::type::jump;
}

void Jump::decode(Decoder& decoder)
{
    address = decoder.decodeAddress();
}

void Jump::execute(Registers& reg, Memory& memory)
{
    reg.ip = address;
}

void Jump::printExpression() const
{
    cout << "Expression : jump to address " << address << endl;
}

JumpEqual::JumpEqual() : jumping(false)
{
    iType = Instruction::type::jump;
}

void JumpEqual::decode(Decoder& decoder)
{
    address = decoder.decodeAddress();
    arg1 = decoder.decodeArg();
    arg2 = decoder.decodeArg();
}

void JumpEqual::execute(Registers& reg, Memory& memory)
{
    if (arg1.getValue(reg, memory) == arg2.getValue(reg, memory)) {
        jumping = true;
        reg.ip = address;
    }
    else
        jumping = false;
}

void JumpEqual::printExpression() const
{
    if (jumping)
        cout << "Expression : jump to address " << address << endl;
    else
        cout << "Expression : values are not equal NOP" << endl;
}


Call::Call()
{
    iType = Instruction::type::call;
}

void Call::decode(Decoder& decoder)
{
    address = decoder.decodeAddress();
}

void Call::execute(Registers& reg, Memory& memory)
{
    reg.sp.push(reg.ip);
    reg.ip = address;
}

void Call::printExpression() const
{
    cout << "Expression : call -> " << address << endl;
}

Ret::Ret()
{
    iType = Instruction::type::ret;
}

void Ret::execute(Registers& reg, Memory& memory)
{
     returnAddress = reg.sp.top();
     reg.sp.pop();
     reg.ip = returnAddress;
}

void Ret::printExpression() const
{
    cout << "Expression : return -> " << returnAddress << endl;
}

Read::Read()
{
    iType = Instruction::type::read;
}

void Read::decode(Decoder& decoder)
{
    arg1 = decoder.decodeArg();
    arg2 = decoder.decodeArg();
    arg3 = decoder.decodeArg();
    arg4 = decoder.decodeArg();
}

void Read::execute(Registers& reg, Memory& memory)
{
    auto fileOffset = arg1.getValue(reg, memory);
    auto noBytes = arg2.getValue(reg, memory);
    auto storageOffset = arg3.getValue(reg, memory);

    std::vector<VM_BYTE> readed;
    auto readedNoBytes = memory.io.read(fileOffset, noBytes, readed);

    for (size_t i = 0; i < readed.size(); i++)
        memory.write(storageOffset+i, Memory::msize::byte, readed[i]);

    arg4.storeResult(readedNoBytes, reg, memory);
}

void Read::printExpression() const
{
    cout << "Expression : read " << arg1.getStr() << ", " << arg2.getStr() << ", " << arg3.getStr() << ", " << arg4.getStr() << "  file=" << filename << endl;
}
