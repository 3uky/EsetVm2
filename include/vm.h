#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <string>

#include "global.h"
#include "registers.h"
#include "io.h"
#include "memory.h"
#include "decoder.h"
#include "engine.h"
#include "threading_model.h"

class VirtualMachine
{
public:
    VirtualMachine(std::string&);

    void run();
    void execute(Registers);

    Registers reg;
    IO io;
    Memory memory;
    Decoder decoder;
    ThreadingModel tm;
    Engine engine;
};

#endif // VIRTUALMACHINE_H
