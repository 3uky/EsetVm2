#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <vector>
#include <map>

#include "global.h"
#include "registers.h"
#include "memory.h"
#include "decoder.h"

class VirtualMachine
{
public:
    VirtualMachine(std::vector<char>& programBytes);

    void run();

private:
    Registers reg;
    Memory memory;
    Decoder decoder;

    Mov iMov;
    Add iAdd;
    Sub iSub;
    Div iDiv;
    Mod iMod;
    Mul iMul;
    Compare iCompare;
    LoadConstant iLoadConstant;
    ConsoleWrite iConsoleWrite;
    Hlt iHlt;

    std::map<Instruction::type, Instruction*> initializeEngine();
};

#endif // VIRTUALMACHINE_H
