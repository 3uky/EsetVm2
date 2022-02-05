#ifndef INSTRUCTIONS_JUMP_H
#define INSTRUCTIONS_JUMP_H

#include "global.h"
#include "instruction.h"
#include "argument.h"
#include "registers.h"
#include "decoder.h"

class Jump : public Instruction
{
public:
    Jump();

private:
    VM_DWORD address;

    virtual void decode(Registers&, Decoder&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

class JumpEqual : public Instruction
{
public:
    JumpEqual();

private:
    VM_DWORD address;
    Argument arg1;
    Argument arg2;
    bool isEqual;

    virtual void decode(Registers&, Decoder&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

class Call : public Instruction
{
public:
    Call();

private:
    VM_DWORD address;

    virtual void decode(Registers&, Decoder&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

class Ret : public Instruction
{
public:
    Ret();

private:
    VM_DWORD address;

    virtual void decode(Registers&, Decoder&) {};
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

class Hlt : public Instruction
{
public:
    Hlt() { iType = Instruction::hlt; };
private:
    virtual void decode(Registers&, Decoder&) {};
    virtual void execute(Registers&) {};
    virtual void printExpression() const {};
};

#endif // INSTRUCTIONS_JUMP_H
