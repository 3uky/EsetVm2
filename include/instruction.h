#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <array>
#include <iostream>

#include "global.h"
#include "decoder.h"
#include "registers.h"
#include "memory.h"
#include "argument.h"

class Instruction
{
public:
    instruction::type iType;

    Instruction();

    void run(Decoder&, Registers&, Memory&);
    virtual void decode(Decoder&) = 0;
    virtual void execute(Registers&, Memory&) = 0;

    int64_t getValue(Argument, Registers& reg, Memory& memory) const;

    void printName() const;
    virtual void printExpression() const = 0;
};

class LoadConstant : public Instruction
{
public:
    VM_QWORD constant;
    Argument arg1;

    LoadConstant();

    virtual void decode(Decoder&);
    virtual void execute(Registers&, Memory&);
    virtual void printExpression() const;
};

class Add : public Instruction
{
public:
    Argument arg1;
    Argument arg2;
    Argument arg3;

    Add();

    virtual void decode(Decoder&);
    virtual void execute(Registers&, Memory&);
    virtual void printExpression() const;
};

#endif // INSTRUCTION_H
