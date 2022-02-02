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
    bool isHlt() const;

protected:
    Instruction::type iType;

    virtual void decode(Decoder&) = 0;
    virtual void execute(Registers&, Memory&) = 0;
    virtual void printExpression() const = 0;

    void printName() const;
    void printInstructionCounter(Registers&) const;
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

class Hlt : public Instruction
{
public:
    Hlt() { iType = Instruction::hlt; };
private:
    virtual void decode(Decoder&) {};
    virtual void execute(Registers&, Memory&) {};
    virtual void printExpression() const {};
};

class ConsoleWrite : public Instruction
{
public:
    ConsoleWrite();
private:
    Argument arg1;

    virtual void decode(Decoder&);
    virtual void execute(Registers&, Memory&);
    virtual void printExpression() const {};
};

class ConsoleRead : public Instruction
{
public:
    ConsoleRead();
private:
    Argument arg1;
    VM_DWORD value;

    virtual void decode(Decoder&);
    virtual void execute(Registers&, Memory&);
    virtual void printExpression() const;
};

class Alu : public Instruction
{
public:
    Alu();

protected:
    Argument arg1;
    Argument arg2;
    Argument arg3;

    virtual void decode(Decoder&);
    virtual void execute(Registers&, Memory&) = 0;
    virtual void printExpression() const;
};

class Add : public Alu
{
public:
    Add();

private:
    virtual void execute(Registers&, Memory&);
};

class Sub : public Alu
{
public:
    Sub();

private:
    virtual void execute(Registers&, Memory&);
};

class Div : public Alu
{
public:
    Div();

private:
    virtual void execute(Registers&, Memory&);
};

class Mod : public Alu
{
public:
    Mod();

private:
    virtual void execute(Registers&, Memory&);
};

class Mul : public Alu
{
public:
    Mul();

private:
    virtual void execute(Registers&, Memory&);
};

class Compare : public Alu
{
public:
    Compare();

private:
    int result;

    virtual void execute(Registers&, Memory&);
    int getCompareResult(Registers&, Memory&);
    void printExpression() const;
};

class Mov : public Instruction
{
public:
    Mov();

private:
    Argument arg1;
    Argument arg2;

    virtual void decode(Decoder&);
    virtual void execute(Registers&, Memory&);
    virtual void printExpression() const;
};

class Jump : public Instruction
{
public:
    Jump();

private:
    VM_DWORD address;

    virtual void decode(Decoder&);
    virtual void execute(Registers&, Memory&);
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
    bool jumping;

    virtual void decode(Decoder&);
    virtual void execute(Registers&, Memory&);
    virtual void printExpression() const;
};

class Call : public Instruction
{
public:
    Call();

private:
    VM_DWORD address;

    virtual void decode(Decoder&);
    virtual void execute(Registers&, Memory&);
    virtual void printExpression() const;
};

class Ret : public Instruction
{
public:
    Ret();

private:
    VM_DWORD returnAddress;
    virtual void decode(Decoder&) {};
    virtual void execute(Registers&, Memory&);
    virtual void printExpression() const;
};

class Read : public Instruction
{
public:
    Read();

private:
    Argument arg1;
    Argument arg2;
    Argument arg3;
    Argument arg4;

    std::string filename;

    virtual void decode(Decoder&);
    virtual void execute(Registers&, Memory&);
    virtual void printExpression() const;
};

#endif // INSTRUCTION_H
