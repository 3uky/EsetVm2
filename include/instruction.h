#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <array>
#include <iostream>

#include "global.h"
#include "registers.h"
#include "memory.h"
#include "argument.h"

class Decoder;

class Instruction
{
public:
    enum type { mov, loadConstant, add, sub, div, mod, mul, compare, jump, jumpEqual, read, write, consoleRead, consoleWrite, createThread, joinThread, hlt, sleep, call, ret, lock, unlock};

    Instruction();

    void run(Decoder&, Registers&, Memory&);

protected:
    Instruction::type iType;

    virtual void decode(Decoder&) = 0;
    virtual void execute(Registers&, Memory&) = 0;

    int64_t getValue(Argument, Registers& reg, Memory& memory) const;

    void printName() const;
    virtual void printExpression() const = 0;
    void printResult(Registers&, Memory&) const;
};

class LoadConstant : public Instruction
{
public:
    LoadConstant();

private:
    VM_QWORD constant;
    Argument arg1;

    virtual void decode(Decoder&);
    virtual void execute(Registers&, Memory&);
    virtual void printExpression() const;
};

class Add : public Instruction
{
public:
    Add();

private:
    Argument arg1;
    Argument arg2;
    Argument arg3;

    virtual void decode(Decoder&);
    virtual void execute(Registers&, Memory&);
    virtual void printExpression() const;
};

#endif // INSTRUCTION_H
