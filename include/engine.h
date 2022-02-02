#ifndef ENGINE_H
#define ENGINE_H

#include <map>

#include "instruction.h"
#include "memory.h"
#include "decoder.h"
#include "io.h"
#include "registers.h"

class Engine
{
public:
    Engine(Memory&, Decoder&, IO&);

    Memory& memory;
    Decoder& decoder;
    IO& io;

    Instruction::Type executeNextInstruction(Registers&);

private:
    std::map<Instruction::Type, Instruction*> instructions;

    Mov mov;
    LoadConstant loadConstant;
    Add add;
    Sub sub;
    Div div;
    Mod mod;
    Mul mul;
    Compare compare;
    Jump jump;
    JumpEqual jumpEqual;
    Read read;
    ConsoleWrite consoleWrite;
    ConsoleRead consoleRead;
    Call call;
    Ret ret;
    Hlt hlt;
};

#endif // ENGINE_H
