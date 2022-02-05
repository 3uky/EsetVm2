#ifndef INSTRUCTIONS_IO_H
#define INSTRUCTIONS_IO_H

#include "instruction.h"
#include "registers.h"
#include "decoder.h"
#include "memory.h"

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

#endif // INSTRUCTIONS_IO_H
