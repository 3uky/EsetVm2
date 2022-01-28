#include <string>

#include "../include/vm.h"

#include <string>
#include <iostream>

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

void VirtualMachine::run()
{
    setIp(20*8); // tbd improve code mem and get rid of it

    auto noInst = 3;
    for (int i=0; i<noInst; i++)
    {
        auto inst = decoder.decodeInstructionCode();
        cout << "Instruction: " << int(inst) << endl;
        switch(inst)
        {
            case instruction::type::loadConstant:
            {
                auto constant = decoder.decodeConstant();
                ARGUMENT arg1 = decoder.decodeArg();

                //cout << "constant: " << constant << endl;
                // printArgument(arg1);

                if(arg1.type == argument::type::reg) {
                    reg[arg1.index] = constant;
                    cout << "reg[" << arg1.index << "]: " << reg[arg1.index] << endl;
                }
                if(arg1.type == argument::type::mem) {
                    //tbd
                }
                break;
            }
            case instruction::type::add:
            {
                std::array<ARGUMENT, 3> args;

                for(auto arg : args) {
                    arg = decoder.decodeArg();

                    if(arg.type == argument::type::reg) {
                        //arg11 = reg[arg1.index];
                        cout << "reg[" << arg.index << "]: " << reg[arg.index] << endl;
                    }
                    else if(arg.type == argument::type::mem) {
                    //tbd
                    }
                }
                break;






            }
            case instruction::type::sub:
            {
            }
            case instruction::type::div:
            {
            }
            case instruction::type::mod:
            {
            }
            case instruction::type::mul:
            {
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
