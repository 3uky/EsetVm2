#ifndef INSTRUCTIONS_THREAD_H
#define INSTRUCTIONS_THREAD_H

#include "instruction.h"
#include "registers.h"
#include "decoder.h"
#include "threading_model.h"

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

#endif // INSTRUCTIONS_THREAD_H
