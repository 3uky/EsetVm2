#ifndef DECODING_TABLES_H_INCLUDED
#define DECODING_TABLES_H_INCLUDED

#include "global.h"
#include "instruction.h"
#include "argument.h"
#include "memory"

#include <map>

namespace instruction {
    std::map<std::pair<VM_BYTE, int>, Instruction::Type> table = {
        { {0b000, 3}, Instruction::Type::mov },
        { {0b001, 3}, Instruction::Type::loadConstant },
        { {0b010001, 6}, Instruction::Type::add },
        { {0b010010, 6}, Instruction::Type::sub },
        { {0b010011, 6}, Instruction::Type::div },
        { {0b010100, 6}, Instruction::Type::mod },
        { {0b010101, 6}, Instruction::Type::mul },
        { {0b01100, 5}, Instruction::Type::compare },
        { {0b01101, 5}, Instruction::Type::jump },
        { {0b01110, 5}, Instruction::Type::jumpEqual },
        { {0b10000, 5}, Instruction::Type::read },
        { {0b10001, 5}, Instruction::Type::write },
        { {0b10010, 5}, Instruction::Type::consoleRead },
        { {0b10011, 5}, Instruction::Type::consoleWrite },
        { {0b10100, 5}, Instruction::Type::createThread },
        { {0b10101, 5}, Instruction::Type::joinThread },
        { {0b10110, 5}, Instruction::Type::hlt },
        { {0b10111, 5}, Instruction::Type::sleep },
        { {0b1100, 4}, Instruction::Type::call },
        { {0b1101, 4}, Instruction::Type::ret },
        { {0b1110, 4}, Instruction::Type::lock },
        { {0b1111, 4}, Instruction::Type::unlock}
    };
}

namespace argument {
    std::map<VM_BYTE, Memory::Size> sizeTable = {
        { 0b00, Memory::Size::byte },
        { 0b01, Memory::Size::word },
        { 0b10, Memory::Size::dword },
        { 0b11, Memory::Size::qword }
    };
    std::map<VM_BYTE, Argument::Type> typeTable = {
        { 1, Argument::Type::mem },
        { 0, Argument::Type::reg }
    };
}

#endif // DECODING_TABLES_H_INCLUDED
