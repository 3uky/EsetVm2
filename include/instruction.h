#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "decoder.h"

class Decoder;

class Instruction
{
    public:
        instruction::type inst;

        Instruction();

        void run();

        virtual void decode() = 0;
        virtual void execute() = 0;

        void printInstruction() const;
        virtual void printExpression() const = 0;
};

class iLoadConstant : public Instruction
{
        VM_QWORD constant;
        Argument arg1;

        virtual void decode(Decoder&);
        virtual void execute();
        virtual void printExpression() const;
};

#endif // INSTRUCTION_H
