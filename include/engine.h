#ifndef ENGINE_H
#define ENGINE_H

#include <map>

#include "instruction.h"
#include "memory.h"
#include "decoder.h"
#include "io.h"
#include "registers.h"
#include "threading_model.h"

class VirtualMachine;

class Engine
{
public:
    Engine(VirtualMachine*);

    VirtualMachine& vm;

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
    ConsoleRead consoleRead;
    ConsoleWrite consoleWrite;
    CreateThread createThread;
    JoinThread joinThread;
    Call call;
    Ret ret;
    Hlt hlt;
};

#endif // ENGINE_H
