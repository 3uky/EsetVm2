#include <array>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>

#include "../include/vm.h"

using namespace std;

vector<char> loadBinary(string filename)
{
	ifstream f(filename, ios::in | ios::binary);
    if (!f.is_open()) {
        throw;
    }
	vector<char> binary(istreambuf_iterator<char>(f), (istreambuf_iterator<char>()));
	f.close();

	return binary;
}

int main()
{
    auto filename = "./task/samples/precompiled/math.evm";
    auto binary = loadBinary(filename);

    VirtualMachine vm(binary);

    return 0;
}
