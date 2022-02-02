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

public:
    Decoder(Memory&);

    Instruction::Type decodeInstructionCode(Registers&);
    Argument decodeArg(Registers&);
    VM_QWORD decodeConstant(Registers&);
    VM_DWORD decodeAddress(Registers&);

private:
    enum endian { little, big };
    VM_BYTE getBitFromMemory(Registers&);
    VM_QWORD getBitsFromMemory(Registers&, int, endian);

    VM_BYTE decodeRegIndex(Registers&);
    VM_BYTE decodeMemSize(Registers&);

    bool isInstructionValid(VM_BYTE, int) const;
    Instruction::Type getInstruction(VM_BYTE, int);
};

#endif // DECODER_H
