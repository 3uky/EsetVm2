#include "decoder.h"

#include <unordered_set>

Decoder::Decoder(Memory& mem, VM_DWORD &inputIp) : memory(mem), ip(inputIp)
{
}

void Decoder::setIp(VM_DWORD newIp)
{
    ip = newIp;
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

HEADER Decoder::decodeHeader()
{
    // set bit pointer after magic value (8B=64b)
    setIp(64);
    HEADER header = {0,};
    header.dataSize = swapDword(getBitsFromCodeMemory_BigEndianOrder(32));
    header.codeSize = swapDword(getBitsFromCodeMemory_BigEndianOrder(32));
    header.initialDataSize = swapDword(getBitsFromCodeMemory_BigEndianOrder(32));
    return header;
}

// first check 3 bits long opcode then 4 bits, 5 bits, 6 bits long opcodes, throw if not found
VM_BYTE Decoder::decodeInstructionCode()
{
    VM_BYTE inst = getBitsFromCodeMemory_BigEndianOrder(3);

    for(int i=0; i<4; i++)
    {
        if(isInstructionValid(inst))
            return inst;
        inst = (inst << 1) | getBitsFromCodeMemory_BigEndianOrder(1);
    }

    throw;
}

bool Decoder::isInstructionValid(VM_BYTE instructionCode) const
{
    static const std::unordered_set<VM_BYTE> validInstructions = {
        {0b000},    // mov
        {0b001},    // loadConst
        {0b010001}, // add
        {0b010010}, // sub
        {0b010011}, // div
        {0b010100}, // mod
        {0b010101}, // mul
        {0b01100},  // compare
        {0b01101},  // jump
        {0b01110},  // jumpEqual
        {0b10000},  // read
        {0b10001},  // write
        {0b10010},  // consoleRead
        {0b10011},  // consoleWrite
        {0b10100},  // createThread
        {0b10101},  // joinThread
        {0b10110},  // hlt
        {0b10111},  // sleep
        {0b1100},   // call
        {0b1101},   // ret
        {0b1110},   // lock
        {0b1111}    // unlock
    };

    return validInstructions.find(instructionCode) != validInstructions.end();
}

ARGUMENT Decoder::decodeArg()
{
    ARGUMENT arg = {0,};

    arg.type = getBitFromCodeMemory();
    if(arg.type == argument::type::reg)
        arg.index = decodeRegIndex();
    else if(arg.type == argument::type::mem) {
        arg.memSize = decodeMemSize();
        arg.index = decodeRegIndex();
    }

    return arg;
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
