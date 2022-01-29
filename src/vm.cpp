#include <string>
#include <iostream>

#include "../include/vm.h"
#include "../include/instruction.h"

using namespace std;

VirtualMachine::VirtualMachine(std::vector<char>& programMemory) : reg(), memory(programMemory), decoder(memory, reg)
{
    initializeMemory();
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
    for (int i=0; i < 3; i++) // while(1)
    {
        auto inst = decoder.decodeInstructionCode();
        cout << "Instruction: " << int(inst) << endl;
        switch(inst)
        {
            case instruction::type::mov:
                break;
            case instruction::type::loadConstant:
            {
                LoadConstant test;
                test.run(decoder, reg, memory);
                break;
            }
            case instruction::type::add:
            {
                Add iAdd;
                iAdd.run(decoder, reg, memory);
                break;
            }
            case instruction::type::sub:
            case instruction::type::div:
            case instruction::type::mod:
            case instruction::type::mul:
            case instruction::type::compare:
            case instruction::type::jump:
            case instruction::type::jumpEqual:
            case instruction::type::read:
            case instruction::type::write:
            case instruction::type::consoleRead:
            case instruction::type::consoleWrite:
            case instruction::type::createThread:
            case instruction::type::joinThread:
            case instruction::type::sleep:
            case instruction::type::call:
            case instruction::type::ret:
            case instruction::type::lock:
            case instruction::type::unlock:
                break;
            case instruction::type::hlt:
                return;

            default:
                throw runtime_error(std::string("Unknown instruction"));
        }
    }
}
