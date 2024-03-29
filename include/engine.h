#ifndef ENGINE_H
#define ENGINE_H

#include <map>

#include "instruction.h"
#include "instructions_alu.h" // mov, loadConstant, add, sub, div, mod, mul, compare
#include "instructions_io.h" // read, write
#include "instructions_thread.h" // createThread, joinThread, sleep, lock, unlock
#include "instructions_console.h" // consoleRead, consoleWrite
#include "instructions_jump.h" // jump, jumpEqual, call, ret, hlt

class VirtualMachine;

class Engine
{
public:
    Engine(Decoder&, IO&, Memory&, ThreadingModel&);

    Instruction::Type executeNextInstruction(Registers&);

private:
    Decoder& decoder;
    ThreadingModel& threadingModel;

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
    Write write;
    ConsoleRead consoleRead;
    ConsoleWrite consoleWrite;
    CreateThread createThread;
    JoinThread joinThread;
    Hlt hlt;
    Sleep sleep;
    Call call;
    Ret ret;
    Lock lock;
    Unlock unlock;

    void initialize();
    bool isInstructionMemoryRelated(Instruction::Type) const;
};

#endif // ENGINE_H
