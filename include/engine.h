#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include <mutex>

#include "instruction.h"
#include "instructions_alu.h" // mov, loadConstant, add, sub, div, mod, mul, compare
#include "instructions_io.h" // read, write
//#include "memory.h"
//#include "decoder.h"
//#include "io.h"
#include "registers.h"

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
