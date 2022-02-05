#include "instructions_console.h"

#include <iomanip>

using namespace std;

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
