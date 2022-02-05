#ifndef INSTRUCTIONS_ALU_H
#define INSTRUCTIONS_ALU_H

#include "instruction.h"
#include "argument.h"
#include "registers.h"
#include "decoder.h"

class Math : public Instruction
{
public:
    Math();

protected:
    Argument arg1;
    Argument arg2;
    Argument arg3;

    virtual void decode(Registers&, Decoder&);
    virtual void execute(Registers&) = 0;
    virtual void printExpression() const;
};

class Add : public Math
{
public:
    Add();

private:
    virtual void execute(Registers&);
};

class Sub : public Math
{
public:
    Sub();

private:
    virtual void execute(Registers&);
};

class Div : public Math
{
public:
    Div();

private:
    virtual void execute(Registers&);
};

class Mod : public Math
{
public:
    Mod();

private:
    virtual void execute(Registers&);
};

class Mul : public Math
{
public:
    Mul();

private:
    virtual void execute(Registers&);
};

class Compare : public Math
{
public:
    Compare();

private:
    int result;

    virtual void execute(Registers&);
    int getCompareResult(Registers&);
    void printExpression() const;
};

class Mov : public Instruction
{
public:
    Mov();

private:
    Argument arg1;
    Argument arg2;

    virtual void decode(Registers&, Decoder&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

class LoadConstant : public Instruction
{
public:
    LoadConstant();

private:
    VM_QWORD constant;
    Argument arg1;

    virtual void decode(Registers&, Decoder&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
};


#endif // INSTRUCTIONS_ALU_H
