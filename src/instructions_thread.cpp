#include "instructions_thread.h"

#include <thread>
#include <chrono>

using namespace std;

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
