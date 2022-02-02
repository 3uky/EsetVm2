#ifndef DECODER_H
#define DECODER_H

#include "global.h"
#include "memory.h"
#include "argument.h"
#include "registers.h"
#include "instruction.h"

class Decoder
{
public:
    Memory& memory;
    VM_DWORD& ip;

public:
    Decoder(Memory&, Registers&);

    Instruction::Type decodeInstructionCode();
    Argument decodeArg();
    VM_QWORD decodeConstant();
    VM_DWORD decodeAddress();

private:
    enum endian { little, big };
    VM_BYTE getBitFromMemory();
    VM_QWORD getBitsFromMemory(int, endian);

    VM_BYTE decodeRegIndex();
    VM_BYTE decodeMemSize();

    bool isInstructionValid(VM_BYTE, int) const;
    Instruction::Type getInstruction(VM_BYTE, int);
};

#endif // DECODER_H
