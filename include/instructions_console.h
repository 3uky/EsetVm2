#ifndef INSTRUCTIONS_CONSOLE_H
#define INSTRUCTIONS_CONSOLE_H

#include "global.h"
#include "argument.h"
#include "registers.h"
#include "decoder.h"

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

#endif // INSTRUCTIONS_CONSOLE_H
