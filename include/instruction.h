#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "registers.h"

class VirtualMachine;
class Decoder;

class Instruction // base class for all instructions
{
public:
    enum Type { mov, loadConstant, add, sub, div, mod, mul, compare, jump, jumpEqual, read, write, consoleRead, consoleWrite, createThread, joinThread, hlt, sleep, call, ret, lock, unlock};

    Instruction();

    virtual void decode(Registers&, Decoder&) = 0;
    virtual void execute(Registers&) = 0;
    virtual void printExpression() const = 0;

    void printName() const;
    bool isHlt() const;

protected:
    Instruction::Type iType;
};

#endif // INSTRUCTION_H
