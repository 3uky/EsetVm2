#ifndef DECODER_H
#define DECODER_H

#include "global.h"
#include "memory.h"
#include "argument.h"

class Decoder
{
public:
    Memory& memory;
    VM_DWORD& ip;

public:
    Decoder(Memory&, VM_DWORD&);

    HEADER decodeHeader();
    VM_BYTE decodeInstructionCode();
    Argument decodeArg();
    VM_BYTE decodeRegIndex();
    VM_BYTE decodeMemSize();
    VM_QWORD decodeConstant();
    VM_DWORD decodeAddress();

    void printBits(VM_DWORD);

private:
    void setIp(VM_DWORD);

    VM_BYTE getBitFromCodeMemory();
    VM_QWORD getBitsFromCodeMemory(int);
    VM_QWORD getBitsFromCodeMemory_BigEndianOrder(int);

    bool isInstructionValid(VM_BYTE) const;

    VM_BYTE convertEndian(VM_BYTE);
    VM_BYTE convertEndian(VM_BYTE, int);

    VM_WORD swapWord(VM_WORD);
    VM_DWORD swapDword(VM_DWORD);
    VM_QWORD swapQword(VM_QWORD);
};

#endif // DECODER_H
