#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "global.h"
#include "registers.h"
#include "memory.h"
#include "argument.h"
#include "threading_model.h"

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

class ConsoleWrite : public Instruction
{
public:
    ConsoleWrite();
private:
    Argument arg1;

    virtual void decode(Registers&, Decoder&);
    virtual void execute(Registers&);
    virtual void printExpression() const {};
};

class ConsoleRead : public Instruction
{
public:
    ConsoleRead();
private:
    Argument arg1;
    VM_DWORD value;

    virtual void decode(Registers&, Decoder&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
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

class Read : public Instruction
{
public:
    Read(IO&, Memory&);

private:
    IO& io;
    Memory& memory;

    Argument arg1;
    Argument arg2;
    Argument arg3;
    Argument arg4;

    virtual void decode(Registers&, Decoder&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

class Write : public Instruction
{
public:
    Write(IO&, Memory&);

private:
    IO& io;
    Memory& memory;

    Argument arg1;
    Argument arg2;
    Argument arg3;

    virtual void decode(Registers&, Decoder&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

class CreateThread : public Instruction
{
public:
    CreateThread(ThreadingModel&);

private:
    ThreadingModel& tm;

    VM_DWORD address;
    Argument arg1;

    virtual void decode(Registers&, Decoder&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

class JoinThread : public Instruction
{
public:
    JoinThread(ThreadingModel&);

private:
    ThreadingModel& tm;

    Argument arg1;

    virtual void decode(Registers&, Decoder&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

class Sleep : public Instruction
{
public:
    Sleep();

private:
    Argument arg1;

    virtual void decode(Registers&, Decoder&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

class Lock : public Instruction
{
public:
    Lock(ThreadingModel&);

private:
    ThreadingModel& tm;

    Argument arg1;

    virtual void decode(Registers&, Decoder&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

class Unlock : public Instruction
{
public:
    Unlock(ThreadingModel&);

private:
    ThreadingModel& tm;

    Argument arg1;

    virtual void decode(Registers&, Decoder&);
    virtual void execute(Registers&);
    virtual void printExpression() const;
};

#endif // INSTRUCTION_H
