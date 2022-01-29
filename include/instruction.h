#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <array>

#include "decoder.h"
#include "memory.h"
#include "vm.h"

class Instruction
{
public:
    instruction::type iType;

    Instruction();

    void run(Decoder&, std::array<int64_t, REGS_COUNT>&, Memory&);

    virtual void decode(Decoder&) = 0;
    virtual void execute(std::array<int64_t, REGS_COUNT>&, Memory&) = 0;

    void printName() const;
    virtual void printExpression() const = 0;
};

class LoadConstant : public Instruction
{
public:
    VM_QWORD constant;
    Argument arg1;

    LoadConstant();

    virtual void decode(Decoder&);
    virtual void execute(std::array<int64_t, REGS_COUNT>&, Memory&);
    virtual void printExpression() const;
};

#endif // INSTRUCTION_H
