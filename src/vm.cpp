#include <string>
#include <iostream>

#include "../include/vm.h"
#include "../include/instruction.h"

using namespace std;

VirtualMachine::VirtualMachine(std::vector<char>& programMemory) : reg(), memory(programMemory), decoder(memory, reg)
{
}

void VirtualMachine::run()
{
    for (int i=0; i < 3; i++) // while(1)
    {
        auto inst = decoder.decodeInstructionCode();
        cout << "Instruction: " << int(inst) << endl;
        switch(inst)
        {
            case Instruction::type::mov:
                break;
            case Instruction::type::loadConstant:
            {
                LoadConstant test;
                test.run(decoder, reg, memory);
                break;
            }
            case Instruction::type::add:
            {
                Add iAdd;
                iAdd.run(decoder, reg, memory);
                break;
            }
            case Instruction::type::sub:
            case Instruction::type::div:
            case Instruction::type::mod:
            case Instruction::type::mul:
            case Instruction::type::compare:
            case Instruction::type::jump:
            case Instruction::type::jumpEqual:
            case Instruction::type::read:
            case Instruction::type::write:
            case Instruction::type::consoleRead:
            case Instruction::type::consoleWrite:
            case Instruction::type::createThread:
            case Instruction::type::joinThread:
            case Instruction::type::sleep:
            case Instruction::type::call:
            case Instruction::type::ret:
            case Instruction::type::lock:
            case Instruction::type::unlock:
                break;
            case Instruction::type::hlt:
                return;

            default:
                throw runtime_error(std::string("Unknown instruction"));
        }
    }
}
