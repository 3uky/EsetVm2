#include <map>

#include "decoder.h"
#include "decoding_tables.h"

using namespace std;

Decoder::Decoder(Memory& mem) : memory(mem)
{
}

VM_BYTE Decoder::getBitFromMemory(Registers& reg)
{
    auto currentByte = memory.code[reg.ip / 8];
    auto mask = 0b10000000 >> (reg.ip % 8);
    auto bit = (currentByte & mask) >> (7 - (reg.ip % 8));
    reg.ip++;
    return bit;
}

VM_QWORD Decoder::getBitsFromMemory(Registers& reg, int noBits, endian order=endian::little)
{
    VM_QWORD bits = 0;

    if(order == endian::little)   // 010001 -> 10001
    {
        for (int i=0; i < noBits; i++)
            bits |= (VM_QWORD(getBitFromMemory(reg)) << i);
    }
    else if(order == endian::big) // 010001 -> 010001
    {
        for (int i=0; i < noBits; i++)
            bits = (bits << 1) | VM_QWORD(getBitFromMemory(reg));
    }

    return bits;
}

// first check 3 bits long opcode then 4 bits, 5 bits, 6 bits long opcodes, throw if not found
Instruction::Type Decoder::decodeInstructionCode(Registers& reg)
{
    VM_BYTE iCode = getBitsFromMemory(reg, 3, endian::big);

    for(int iSize = 3; iSize < 7; iSize++)
    {
        if(isInstructionValid(iCode, iSize))
            return getInstruction(iCode, iSize);
        iCode = (iCode << 1) | getBitFromMemory(reg);
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

Argument Decoder::decodeArg(Registers& reg)
{
    auto argType = argument::typeTable[getBitFromMemory(reg)];

    if(argType == Argument::Type::reg) {
        auto regIndex = decodeRegIndex(reg);
        return Argument(argType, regIndex, &memory);
    }
    else { // argType == Argument::type::mem
        auto memSize = argument::sizeTable[decodeMemSize(reg)];
        auto regIndex = decodeRegIndex(reg);
        return Argument(argType, regIndex, memSize, &memory);
    }
}

VM_BYTE Decoder::decodeRegIndex(Registers& reg)
{
    return getBitsFromMemory(reg, 4);
}

VM_BYTE Decoder::decodeMemSize(Registers& reg)
{
    return getBitsFromMemory(reg, 2);
}

VM_DWORD Decoder::decodeAddress(Registers& reg)
{
    return getBitsFromMemory(reg, 32);
}

VM_QWORD Decoder::decodeConstant(Registers& reg)
{
    return getBitsFromMemory(reg, 64);
}
