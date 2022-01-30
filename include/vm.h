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

    Add iAdd;
    LoadConstant iLoadConstant;

    std::map<Instruction::type, Instruction*> initializeEngine();
};

#endif // VIRTUALMACHINE_H
