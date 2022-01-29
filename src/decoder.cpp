#include <map>

#include "../include/decoder.h"
#include "../include/decoding_tables.h"

using namespace std;

Decoder::Decoder(Memory& mem, Registers& reg) : memory(mem), ip(reg.ip)
{
}

VM_BYTE Decoder::getBitFromCodeMemory()
{
    auto currentByte = memory.code[ip / 8];
    auto mask = 0b10000000 >> (ip % 8);
    auto b = (currentByte & mask) >> (7 - (ip % 8));
    ip++;
    return b;
}

// https://stackoverflow.com/questions/9290823/bitwise-shift-operation-in-c-on-uint64-t-variable
VM_QWORD Decoder::getBitsFromCodeMemory(int numberOfBits)
{
    VM_QWORD bits = 0;
    for (int i=0; i < numberOfBits; i++) {
        bits |= (VM_QWORD(getBitFromCodeMemory()) << i);
    }
    return bits;
}

VM_QWORD Decoder::getBitsFromCodeMemory_BigEndianOrder(int numberOfBits)
{
    VM_QWORD bits = 0;
    for (int i=0; i < numberOfBits; i++) {
        bits = (bits << 1) | VM_QWORD(getBitFromCodeMemory());
    }
    return bits;
}

VM_BYTE Decoder::getBitFromMemory() // tbd template or default argument with memory type...
{
    auto currentByte = memory.binary[ip / 8];
    auto mask = 0b10000000 >> (ip % 8);
    auto b = (currentByte & mask) >> (7 - (ip % 8));
    ip++;
    return b;
}

VM_QWORD Decoder::getBitsFromMemory_BigEndianOrder(int numberOfBits)
{
    VM_QWORD bits = 0;
    for (int i=0; i < numberOfBits; i++) {
        bits = (bits << 1) | VM_QWORD(getBitFromMemory());
    }
    return bits;
}

HEADER Decoder::decodeHeader()
{
    HEADER header = {0,};

    ip = 64; // set bit pointer after magic value (8B=64b)
    header.dataSize = swapDword(getBitsFromMemory_BigEndianOrder(32));
    header.codeSize = swapDword(getBitsFromMemory_BigEndianOrder(32));
    header.initialDataSize = swapDword(getBitsFromMemory_BigEndianOrder(32));
    ip = 0; // reset bit pointer for code memory decoding
    return header;
}

// first check 3 bits long opcode then 4 bits, 5 bits, 6 bits long opcodes, throw if not found
Instruction::type Decoder::decodeInstructionCode()
{
    VM_BYTE iCode = getBitsFromCodeMemory_BigEndianOrder(3);

    for(int iSize = 3; iSize < 7; iSize++)
    {
        if(isInstructionValid(iCode, iSize))
            return getInstruction(iCode, iSize);
        iCode = (iCode << 1) | getBitsFromCodeMemory_BigEndianOrder(1);
    }

    throw;
}

bool Decoder::isInstructionValid(VM_BYTE iCode, int iSize) const
{
    return instruction::table.find(std::make_pair(iCode, iSize)) != instruction::table.end();
}

Instruction::type Decoder::getInstruction(VM_BYTE iCode, int iSize)
{
    return instruction::table[{iCode, iSize}];
}

Argument Decoder::decodeArg()
{
    auto argType = argument::typeTable[getBitFromCodeMemory()];

    if(argType == Argument::type::reg) {
        auto regIndex = decodeRegIndex();
        return Argument(argType, regIndex);
    }
    else { // argType == Argument::type::mem
        auto memSize = argument::sizeTable[decodeMemSize()];
        VM_BYTE index = decodeRegIndex();
        return Argument(argType, index, memSize);
    }
}

VM_BYTE Decoder::decodeRegIndex()
{
    return getBitsFromCodeMemory(4);
}

VM_BYTE Decoder::decodeMemSize()
{
    return getBitsFromCodeMemory_BigEndianOrder(2);
}

VM_DWORD Decoder::decodeAddress()
{
    return getBitsFromCodeMemory(32);
}

VM_QWORD Decoder::decodeConstant()
{
    return getBitsFromCodeMemory(64);
}

VM_BYTE Decoder::convertEndian(VM_BYTE byte)
{
    return convertEndian(byte, 8);
}

VM_BYTE Decoder::convertEndian(VM_BYTE byte, int numberOfBits)
{
    VM_BYTE converted = 0;
    VM_BYTE mask = 0b10000000;
    mask >>= 8 - numberOfBits;

    for(int i = 1; i <= numberOfBits; i++)
    {
        VM_BYTE tmp = ((converted & mask) >> (numberOfBits - i));
        if(i != 1) tmp <<= (i - 1);
        converted |= tmp;
        mask >>= 1;
    }

    return converted;
}

VM_WORD Decoder::swapWord(VM_WORD a)
{
    a = ((a & 0x00FF) << 8) | ((a & 0xFF00) >> 8);
    return a;
}

VM_DWORD Decoder::swapDword(VM_DWORD a)
{
    a = ((a & 0x000000FF) << 24) |
        ((a & 0x0000FF00) <<  8) |
        ((a & 0x00FF0000) >>  8) |
        ((a & 0xFF000000) >> 24);
    return a;
}

VM_QWORD Decoder::swapQword(VM_QWORD a)
{
    a = ((a & 0x00000000000000FFULL) << 56) |
        ((a & 0x000000000000FF00ULL) << 40) |
        ((a & 0x0000000000FF0000ULL) << 24) |
        ((a & 0x00000000FF000000ULL) <<  8) |
        ((a & 0x000000FF00000000ULL) >>  8) |
        ((a & 0x0000FF0000000000ULL) >> 24) |
        ((a & 0x00FF000000000000ULL) >> 40) |
        ((a & 0xFF00000000000000ULL) >> 56);
    return a;
}

void Decoder::printBits(VM_DWORD numberOfBits)
{
    for(VM_DWORD i=0; i < numberOfBits; i++) {
        bool a = getBitFromCodeMemory();

        if (i % (8*6) == 0 && i != 0)
            std::cout << std::endl;

        std::cout << a;

        if ((i+1) % 8 == 0 && i != 0)
            std::cout << " ";
    }
    std::cout << std::endl;
}
