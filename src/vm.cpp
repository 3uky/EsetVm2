#include <string>
#include <iostream>

#include "../include/vm.h"
#include "../include/argument.h"

using namespace std;

VirtualMachine::VirtualMachine(std::vector<char>& programMemory) : reg({0,}), ip(0), memory(programMemory), decoder(memory, ip)
{
    initializeMemory();
    //initializeRegisters();
}

void VirtualMachine::setIp(VM_DWORD newIp)
{
    ip = newIp;
}

void VirtualMachine::initializeMemory()
{
    memory.setHeader(decoder.decodeHeader());
    if(!memory.isHeaderValid()) {
        memory.printSizes();
        throw runtime_error(std::string("Memory validation failed"));
    }
}

int64_t VirtualMachine::getValue(Argument arg) const
{
    if(arg.isRegister())
        return reg[arg.index];
    else
        return 0; //return memory.data[arg.address];
}

void VirtualMachine::run()
{
    setIp(20*8); // tbd improve code mem and get rid of it

    for (int i=0; i < 3; i++) // while(1)
    {
        auto inst = decoder.decodeInstructionCode();
        cout << "Instruction: " << int(inst) << endl;
        switch(inst)
        {
            case instruction::type::loadConstant:
            {
                auto constant = decoder.decodeConstant();
                auto arg1 = decoder.decodeArg();

                if(arg1.isRegister())
                    reg[arg1.index] = constant;
                else if(arg1.isMemory())
                    ;//tbd

                break;
            }
            case instruction::type::add:
            {
                Argument arg1 = decoder.decodeArg();
                Argument arg2 = decoder.decodeArg();
                Argument arg3 = decoder.decodeArg();

                if(arg3.isRegister())
                    reg[arg2.index] = getValue(arg1) + getValue(arg2);
                else
                    ; //tbd

                break;
            }
            case instruction::type::sub:
            {
            }
            case instruction::type::div:
            {
                break;
            }
            case instruction::type::mod:
            {
                break;
            }
            case instruction::type::mul:
            {
                break;
            }
            /*
            case instruction::type::consoleWrite:
            {
            }
            */
            case instruction::type::htl:
                return;

            default:
                throw runtime_error(std::string("Unknown instruction\nopcode: " + inst));
        }
    }
}
