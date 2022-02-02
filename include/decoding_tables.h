#ifndef DECODING_TABLES_H_INCLUDED
#define DECODING_TABLES_H_INCLUDED

#include "instruction.h"
#include "argument.h"
#include "memory"

namespace instruction {
    std::map<std::pair<VM_BYTE, int>, Instruction::type> table = {
        { {0b000, 3}, Instruction::type::mov },
        { {0b001, 3}, Instruction::type::loadConstant },
        { {0b010001, 6}, Instruction::type::add },
        { {0b010010, 6}, Instruction::type::sub },
        { {0b010011, 6}, Instruction::type::div },
        { {0b010100, 6}, Instruction::type::mod },
        { {0b010101, 6}, Instruction::type::mul },
        { {0b01100, 5}, Instruction::type::compare },
        { {0b01101, 5}, Instruction::type::jump },
        { {0b01110, 5}, Instruction::type::jumpEqual },
        { {0b10000, 5}, Instruction::type::read },
        { {0b10001, 5}, Instruction::type::write },
        { {0b10010, 5}, Instruction::type::consoleRead },
        { {0b10011, 5}, Instruction::type::consoleWrite },
        { {0b10100, 5}, Instruction::type::createThread },
        { {0b10101, 5}, Instruction::type::joinThread },
        { {0b10110, 5}, Instruction::type::hlt },
        { {0b10111, 5}, Instruction::type::sleep },
        { {0b1100, 4}, Instruction::type::call },
        { {0b1101, 4}, Instruction::type::ret },
        { {0b1110, 4}, Instruction::type::lock },
        { {0b1111, 4}, Instruction::type::unlock}
    };
}

namespace argument {
    std::map<VM_BYTE, Memory::Size> sizeTable = {
        { 0b00, Memory::Size::byte },
        { 0b01, Memory::Size::word },
        { 0b10, Memory::Size::dword },
        { 0b11, Memory::Size::qword }
    };
    std::map<VM_BYTE, Argument::type> typeTable = {
        { 1, Argument::type::mem },
        { 0, Argument::type::reg }
    };
}

#endif // DECODING_TABLES_H_INCLUDED
