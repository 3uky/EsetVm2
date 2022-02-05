#include <map>
#include <string>

#include <iomanip>



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



