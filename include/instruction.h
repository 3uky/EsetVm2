#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <array>
#include <iostream>

#include "global.h"
#include "registers.h"
#include "memory.h"
#include "argument.h"

class Engine;
class Decoder;

class Instruction
{
public:
    enum Type { mov, loadConstant, add, sub, div, mod, mul, compare, jump, jumpEqual, read, write, consoleRead, consoleWrite, createThread, joinThread, hlt, sleep, call, ret, lock, unlock};

    Instruction(Engine&);

    virtual void decode(Registers&) = 0;
    virtual void execute(Registers&) = 0;
    virtual void printExpression() const = 0;

    void printName() const;
    bool isHlt() const;

protected:
    Instruction::Type iType;
    Engine& engine;
};

class LoadConstant : public Instruction
{
public:
    LoadConstant(Engine&);

private:
    VM_QWORD constant;
    Argument arg1;

    virtual void decode(Registers&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

class Hlt : public Instruction
{
public:
    Hlt(Engine& eng) : Instruction(eng) { iType = Instruction::hlt; };
private:
    virtual void decode(Registers&) {};
    virtual void execute(Registers&) {};
    virtual void printExpression() const {};
};

class ConsoleWrite : public Instruction
{
public:
    ConsoleWrite(Engine&);
private:
    Argument arg1;

    virtual void decode(Registers&);
    virtual void execute(Registers&);
    virtual void printExpression() const {};
};

class ConsoleRead : public Instruction
{
public:
    ConsoleRead(Engine&);
private:
    Argument arg1;
    VM_DWORD value;

    virtual void decode(Registers&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

class Alu : public Instruction
{
public:
    Alu(Engine&);

protected:
    Argument arg1;
    Argument arg2;
    Argument arg3;

    virtual void decode(Registers&);
    virtual void execute(Registers&) = 0;
    virtual void printExpression() const;
};

class Add : public Alu
{
public:
    Add(Engine&);

private:
    virtual void execute(Registers&);
};

class Sub : public Alu
{
public:
    Sub(Engine&);

private:
    virtual void execute(Registers&);
};

class Div : public Alu
{
public:
    Div(Engine&);

private:
    virtual void execute(Registers&);
};

class Mod : public Alu
{
public:
    Mod(Engine&);

private:
    virtual void execute(Registers&);
};

class Mul : public Alu
{
public:
    Mul(Engine&);

private:
    virtual void execute(Registers&);
};

class Compare : public Alu
{
public:
    Compare(Engine&);

private:
    int result;

    virtual void execute(Registers&);
    int getCompareResult(Registers&);
    void printExpression() const;
};

class Mov : public Instruction
{
public:
    Mov(Engine&);

private:
    Argument arg1;
    Argument arg2;

    virtual void decode(Registers&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

class Jump : public Instruction
{
public:
    Jump(Engine&);

private:
    VM_DWORD address;

    virtual void decode(Registers&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

class JumpEqual : public Instruction
{
public:
    JumpEqual(Engine&);

private:
    VM_DWORD address;
    Argument arg1;
    Argument arg2;
    bool jumping;

    virtual void decode(Registers&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

class Call : public Instruction
{
public:
    Call(Engine&);

private:
    VM_DWORD address;

    virtual void decode(Registers&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

class Ret : public Instruction
{
public:
    Ret(Engine&);

private:
    VM_DWORD returnAddress;
    virtual void decode(Registers&) {};
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

class Read : public Instruction
{
public:
    Read(Engine&);

private:
    Argument arg1;
    Argument arg2;
    Argument arg3;
    Argument arg4;

    std::string filename;

    virtual void decode(Registers&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

#endif // INSTRUCTION_H
