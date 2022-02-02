#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <string>
#include <map>

#include "global.h"
#include "registers.h"
#include "io.h"
#include "memory.h"
#include "decoder.h"
#include "engine.h"

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
    Engine engine;
};

#endif // VIRTUALMACHINE_H
