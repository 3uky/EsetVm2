#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "global.h"
#include "registers.h"
#include "argument.h"

class VirtualMachine;
class Decoder;

class Instruction
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



class Hlt : public Instruction
{
public:
    Hlt() { iType = Instruction::hlt; };
private:
    virtual void decode(Registers&, Decoder&) {};
    virtual void execute(Registers&) {};
    virtual void printExpression() const {};
};



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
    VM_DWORD returnAddress;
    virtual void decode(Registers&, Decoder&) {};
    virtual void execute(Registers&);
    virtual void printExpression() const;
};




#endif // INSTRUCTION_H
