#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <thread>
#include <chrono>

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
    isEqual = false;
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
        isEqual = true;
        reg.ip = address;
    }
    else
        isEqual = false;
}

void JumpEqual::printExpression() const
{
    if (isEqual)
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
    cout << "Expression : read " << arg1.getStr() << ", " << arg2.getStr() << ", " << arg3.getStr() << ", " << arg4.getStr() << endl;
}

Write::Write(IO& iio, Memory& mem) : io(iio), memory(mem)
{
    iType = Instruction::Type::write;
}

void Write::decode(Registers& reg, Decoder& decoder)
{
    arg1 = decoder.decodeArg(reg);
    arg2 = decoder.decodeArg(reg);
    arg3 = decoder.decodeArg(reg);
}

void Write::execute(Registers& reg)
{
    auto fileOffset = arg1.getValue(reg);
    auto noBytes = arg2.getValue(reg);
    auto memoryOffset = arg3.getValue(reg);

    std::vector<VM_BYTE> toWrite;

    // read data from memory
    for(size_t i=0; i < noBytes; i++)
        toWrite.push_back(memory.read(memoryOffset + i, Memory::Size::byte));

    // write data to file
    io.write(fileOffset, noBytes, toWrite);
}

void Write::printExpression() const
{
    cout << "Expression : write " << arg1.getStr() << ", " << arg2.getStr() << ", " << arg3.getStr() << endl;
}

CreateThread::CreateThread(ThreadingModel& itm) : tm(itm)
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
    // prepare new registers copy parent registers
    Registers regCopy = reg;
    // empty stack
    regCopy.emptyStack();
    // set starting address for new thread
    regCopy.ip = address;
    // start new thread
    auto index = tm.createThread(regCopy);
    // store child identifier in parent thread
    arg1.storeResult(index, reg);
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

Sleep::Sleep()
{
    iType = Instruction::Type::sleep;
}

void Sleep::decode(Registers& reg, Decoder& decoder)
{
    arg1 = decoder.decodeArg(reg);
}

void Sleep::execute(Registers& reg)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(arg1.getValue(reg)));
}

void Sleep::printExpression() const
{
    cout << "Expression : sleep " << arg1.getStr() << " (wake up from sleep)" << endl;
}

Lock::Lock(ThreadingModel& itm) : tm(itm)
{
    iType = Instruction::Type::lock;
}

void Lock::decode(Registers& reg, Decoder& decoder)
{
    arg1 = decoder.decodeArg(reg);
}

void Lock::execute(Registers& reg)
{
    tm.lock(arg1.getValue(reg));
}

void Lock::printExpression() const
{
    cout << "Expression : lock " << arg1.getStr() << endl;
}

Unlock::Unlock(ThreadingModel& itm) : tm(itm)
{
    iType = Instruction::Type::unlock;
}

void Unlock::decode(Registers& reg, Decoder& decoder)
{
    arg1 = decoder.decodeArg(reg);
}

void Unlock::execute(Registers& reg)
{
    tm.unlock(arg1.getValue(reg));
}

void Unlock::printExpression() const
{
    cout << "Expression : unlock " << arg1.getStr() << endl;
}
