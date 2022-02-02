#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <string>
#include <map>

#include "global.h"
#include "registers.h"
#include "io.h"
#include "memory.h"
#include "decoder.h"

class VirtualMachine
{
public:
    VirtualMachine(std::string&);

    void run();

private:
    Registers reg;
    IO io;
    Memory memory;
    Decoder decoder;

    //Engine engine;

    Mov iMov;
    Add iAdd;
    Sub iSub;
    Div iDiv;
    Mod iMod;
    Mul iMul;
    Compare iCompare;
    Jump iJump;
    Call iCall;
    Ret iRet;
    JumpEqual iJumpEqual;
    LoadConstant iLoadConstant;
    Read iRead;
    ConsoleWrite iConsoleWrite;
    ConsoleRead iConsoleRead;
    Hlt iHlt;

    std::map<Instruction::type, Instruction*> initializeEngine();
};

#endif // VIRTUALMACHINE_H
