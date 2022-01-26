#include <array>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>
//#include <boost/dynamic_bitset.hpp>

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
// class cpu
// registry + call stack

// instruction memory
// data memory
std::array<int64_t, 16> reg;

std::vector<char> loadBinary(std::string filename)
{
	std::ifstream input(filename, std::ios::in | std::ios::binary);
    // get length of file:
    //input.seekg (0, input.end);
    //int fileLength = input.tellg();
    //input.seekg (0, input.beg);

    // print content in ASCII
    //std::cout << input.rdbuf() << std::endl;
    //std::cout << "length is " << fileLength << std::endl;
    //std::string str(std::istreambuf_iterator<char>(input), (std::istreambuf_iterator<char>()));
	std::vector<char> program(std::istreambuf_iterator<char>(input), (std::istreambuf_iterator<char>()));
	input.close();

	return program;
}

void printAsXxd(std::vector<char>& bytes) {
    // print vector loaded from binary file as xxd -b {file}
    for (size_t i = 0; i < bytes.size(); ++i) {
        std::bitset<8> bs(bytes[i]);
        std::cout << bs << " ";

        if ((i+1) % 6 == 0 && i != 0)
            std::cout << std::endl;
    }
}

std::string generateBitstring(std::vector<char>& bytes) {
    std::string bitString;
    for (size_t i = 0; i < bytes.size(); ++i) {
        std::bitset<8> bs(bytes[i]);
        bitString += bs.to_string();
    }

    return bitString;
}

/*
boost::dynamic_bitset<> generateDynamicBitset(std::string& bitString) {
    return boost::dynamic_bitset<>(bitString);
}*/



int main()
{
    auto filename = "/home/buky/eset/samples/precompiled/math.evm";
    auto program = loadBinary(filename);
    //printAsXxd(bytes);
    //auto bitString = generateBitstring(program);
    //auto dBitSet = generateDynamicBitset(bitString);

    VirtualMachine vm(program);

    vm.printBits(24);
    vm.setIp(1);
    vm.printBits(24);


    return 0;
}
