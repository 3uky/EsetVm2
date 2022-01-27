#include <array>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>

#include "vm.h"

using namespace std;

vector<char> loadBinary(string filename)
{
	ifstream input(filename, ios::in | ios::binary);
    if (!input.is_open()) {
        throw;
    }
	vector<char> program(istreambuf_iterator<char>(input), (istreambuf_iterator<char>()));
	input.close();

	return program;
}

int main()
{
    auto filename = "./task/samples/precompiled/math.evm";
    auto program = loadBinary(filename);

    VirtualMachine vm(program);

    return 0;
}
