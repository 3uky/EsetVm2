#include <array>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>

#include "vm.h"

using namespace std;
/*
std::list<Instruction> instructions = {
    Instruction(0b000,    3, "mov"),
    Instruction(0b001,    3, "loadConst"),
    Instruction(0b010001, 6, "add"),
    Instruction(0b010010, 6, "sub"),
    Instruction(0b010011, 6, "div"),
    Instruction(0b010100, 6, "mod"),
    Instruction(0b010101, 6, "mul"),
    Instruction(0b01100,  5, "compare"),
    Instruction(0b01101,  5, "jump"),
    Instruction(0b01110,  5, "jumpEqual"),
    Instruction(0b10000,  5, "read"),
    Instruction(0b10001,  5, "write"),
    Instructistr[i]on(0b10001,  5, "consoleRead"),
    Instruction(0b10011,  5, "consoleWrite"),
    Instruction(0b10100,  5, "createThread"),
    Instruction(0b10101,  5, "joinThread"),
    Instruction(0b10110,  5, "hlt"),
    Instruction(0b10111,  5, "sleep"),
    Instruction(0b1100,   5, "call"),
    Instruction(0b1101,   5, "ret"),
    Instruction(0b1110,   5, "lock"),
    Instruction(0b1111,   5, "unlock")
};*/

std::vector<char> loadBinary(std::string filename)
{
	std::ifstream input(filename, std::ios::in | std::ios::binary);
    if (!input.is_open()) {
        throw;
    }
	std::vector<char> program(std::istreambuf_iterator<char>(input), (std::istreambuf_iterator<char>()));
	input.close();

	return program;
}

int main()
{
    auto filename = "./task/samples/precompiled/math.evm";
    auto program = loadBinary(filename);

    VirtualMachine vm(program);

    vm.setIp(304);
    vm.printBits(24);
    vm.setIp(310);
    auto arg1 = vm.decodeArg();
    auto arg2 = vm.decodeArg();
    auto arg3 = vm.decodeArg();

    return 0;
}
