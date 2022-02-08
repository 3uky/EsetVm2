#include "instructions_io.h"

#include <vector>

using namespace std;

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
