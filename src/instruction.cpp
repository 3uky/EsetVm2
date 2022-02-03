#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "../include/instruction.h"
#include "../include/decoder.h"
#include "../include/vm.h"

using namespace std;

Instruction::Instruction()
{
}

void Instruction::printName() const
{
    static map<Instruction::Type, string> name = {
        {Instruction::Type::mov, "mov"},
        {Instruction::Type::loadConstant, "loadConstant"},
        {Instruction::Type::add, "add"},
        {Instruction::Type::sub, "sub"},
        {Instruction::Type::div, "div"},
        {Instruction::Type::mod, "mod"},
        {Instruction::Type::mul, "mul"},
        {Instruction::Type::compare, "compare"},
        {Instruction::Type::jump, "jump"},
        {Instruction::Type::jumpEqual, "jumpEqual"},
        {Instruction::Type::read, "read"},
        {Instruction::Type::write, "write"},
        {Instruction::Type::consoleRead, "consoleRead"},
        {Instruction::Type::consoleWrite, "consoleWrite"},
        {Instruction::Type::createThread, "createThread"},
        {Instruction::Type::joinThread, "joinThread"},
        {Instruction::Type::hlt, "hlt"},
        {Instruction::Type::sleep, "sleep"},
        {Instruction::Type::call, "call"},
        {Instruction::Type::ret, "ret"},
        {Instruction::Type::lock, "lock"},
        {Instruction::Type::unlock, "unlock"}
    };

    cout << "Instruction: " << name[iType] << endl;
}

bool Instruction::isHlt() const
{
    return iType == Instruction::Type::hlt;
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

ConsoleWrite::ConsoleWrite()
{
    iType = Instruction::Type::consoleWrite;
}

void ConsoleWrite::decode(Registers& reg, Decoder& decoder)
{
    arg1 = decoder.decodeArg(reg);
}

void ConsoleWrite::execute(Registers& reg)
{
    cout << setfill('0') << setw(16) << right << hex << arg1.getValue(reg) << endl;
}

ConsoleRead::ConsoleRead()
{
    iType = Instruction::Type::consoleRead;
}

void ConsoleRead::decode(Registers& reg, Decoder& decoder)
{
    arg1 = decoder.decodeArg(reg);
}

void ConsoleRead::execute(Registers& reg)
{
    cin >> value;
    arg1.storeResult(value, reg);
}

void ConsoleRead::printExpression() const
{
    cout << "Expression : " << arg1.getStr() << " = " << dec << value << " (0x" << hex << value << ")" << endl;
}

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

Jump::Jump()
{
    iType = Instruction::Type::jump;
}

void Jump::decode(Registers& reg, Decoder& decoder)
{
    address = decoder.decodeAddress(reg);
}

void Jump::execute(Registers& reg)
{
    reg.ip = address;
}

void Jump::printExpression() const
{
    cout << "Expression : jump to address " << address << endl;
}

JumpEqual::JumpEqual()
{
    iType = Instruction::Type::jump;
    jumping = false;
}

void JumpEqual::decode(Registers& reg, Decoder& decoder)
{
    address = decoder.decodeAddress(reg);
    arg1 = decoder.decodeArg(reg);
    arg2 = decoder.decodeArg(reg);
}

void JumpEqual::execute(Registers& reg)
{
    if (arg1.getValue(reg) == arg2.getValue(reg)) {
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
    iType = Instruction::Type::call;
}

void Call::decode(Registers& reg, Decoder& decoder)
{
    address = decoder.decodeAddress(reg);
}

void Call::execute(Registers& reg)
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
    iType = Instruction::Type::ret;
}

void Ret::execute(Registers& reg)
{
     returnAddress = reg.sp.top();
     reg.sp.pop();
     reg.ip = returnAddress;
}

void Ret::printExpression() const
{
    cout << "Expression : return -> " << returnAddress << endl;
}

Read::Read(IO& iio, Memory& mem) : io(iio), memory(mem)
{
    iType = Instruction::Type::read;
}

void Read::decode(Registers& reg, Decoder& decoder)
{
    arg1 = decoder.decodeArg(reg);
    arg2 = decoder.decodeArg(reg);
    arg3 = decoder.decodeArg(reg);
    arg4 = decoder.decodeArg(reg);
}

void Read::execute(Registers& reg)
{
    auto fileOffset = arg1.getValue(reg);
    auto noBytes = arg2.getValue(reg);
    auto storageOffset = arg3.getValue(reg);

    std::vector<VM_BYTE> readed;
    auto readedNoBytes = io.read(fileOffset, noBytes, readed, IO::Filetype::bin);

    for (size_t i = 0; i < readed.size(); i++)
        memory.write(storageOffset+i, Memory::Size::byte, readed[i]);

    arg4.storeResult(readedNoBytes, reg);
}

void Read::printExpression() const
{
    cout << "Expression : read " << arg1.getStr() << ", " << arg2.getStr() << ", " << arg3.getStr() << ", " << arg4.getStr() << "  file=" << filename << endl;
}

CreateThread::CreateThread(ThreadingModel& itm, VirtualMachine* ivm) : tm(itm), vm(ivm)
{
    iType = Instruction::Type::createThread;
}

void CreateThread::decode(Registers& reg, Decoder& decoder)
{
    address = decoder.decodeAddress(reg);
    arg1 = decoder.decodeArg(reg);
}

void CreateThread::execute(Registers& reg)
{
    // prepare new registers copy (tbd copy constructor)
    Registers regCopy = reg;
    regCopy.tId = tm.threads.size();
    regCopy.emptyStack();
    // set ip
    regCopy.ip = address;
    // store identifier
    arg1.storeResult(regCopy.tId, reg);
    // start new thread
    tm.threads.push_back(thread(&VirtualMachine::execute, vm, regCopy));
}

void CreateThread::printExpression() const
{
    cout << "Expression : createThread " << address << ", " << arg1.getStr() << endl;
}

JoinThread::JoinThread(ThreadingModel& itm) : tm(itm)
{
    iType = Instruction::Type::joinThread;
}

void JoinThread::decode(Registers& reg, Decoder& decoder)
{
    arg1 = decoder.decodeArg(reg);
}

void JoinThread::execute(Registers& reg)
{
    tm.threads.at(arg1.getValue(reg)).join();
}

void JoinThread::printExpression() const
{
    cout << "Expression : joinThread " << arg1.getStr() << endl;
}
