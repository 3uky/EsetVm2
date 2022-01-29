#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <vector>

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
};

#endif // VIRTUALMACHINE_H
