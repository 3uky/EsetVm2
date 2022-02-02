#include <map>

#include "../include/decoder.h"
#include "../include/decoding_tables.h"

using namespace std;

Decoder::Decoder(Memory& mem, Registers& reg) : memory(mem), ip(reg.ip)
{
}

VM_BYTE Decoder::getBitFromMemory()
{
    auto currentByte = memory.code[ip / 8];
    auto mask = 0b10000000 >> (ip % 8);
    auto bit = (currentByte & mask) >> (7 - (ip % 8));
    ip++;
    return bit;
}

VM_QWORD Decoder::getBitsFromMemory(int noBits, endian order=endian::little)
{
    VM_QWORD bits = 0;

    if(order == endian::little)   // 010001 -> 10001
    {
        for (int i=0; i < noBits; i++)
            bits |= (VM_QWORD(getBitFromMemory()) << i);
    }
    else if(order == endian::big) // 010001 -> 010001
    {
        for (int i=0; i < noBits; i++)
            bits = (bits << 1) | VM_QWORD(getBitFromMemory());
    }

    return bits;
}

// first check 3 bits long opcode then 4 bits, 5 bits, 6 bits long opcodes, throw if not found
Instruction::Type Decoder::decodeInstructionCode()
{
    VM_BYTE iCode = getBitsFromMemory(3, endian::big);

    for(int iSize = 3; iSize < 7; iSize++)
    {
        if(isInstructionValid(iCode, iSize))
            return getInstruction(iCode, iSize);
        iCode = (iCode << 1) | getBitFromMemory();
    }

    throw runtime_error(string("Cannot decode instruction!"));
}

bool Decoder::isInstructionValid(VM_BYTE iCode, int iSize) const
{
    return instruction::table.find(std::make_pair(iCode, iSize)) != instruction::table.end();
}

Instruction::Type Decoder::getInstruction(VM_BYTE iCode, int iSize)
{
    return instruction::table[{iCode, iSize}];
}

Argument Decoder::decodeArg()
{
    auto argType = argument::typeTable[getBitFromMemory()];

    if(argType == Argument::Type::reg) {
        auto regIndex = decodeRegIndex();
        return Argument(argType, regIndex);
    }
    else { // argType == Argument::type::mem
        auto memSize = argument::sizeTable[decodeMemSize()];
        auto regIndex = decodeRegIndex();
        return Argument(argType, regIndex, memSize);
    }
}

VM_BYTE Decoder::decodeRegIndex()
{
    return getBitsFromMemory(4);
}

VM_BYTE Decoder::decodeMemSize()
{
    return getBitsFromMemory(2);
}

VM_DWORD Decoder::decodeAddress()
{
    return getBitsFromMemory(32);
}

VM_QWORD Decoder::decodeConstant()
{
    return getBitsFromMemory(64);
}
