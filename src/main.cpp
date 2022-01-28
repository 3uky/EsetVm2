#include <array>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>

#include "../include/vm.h"

using namespace std;

void checkUserInput(int argc)
{
    if(argc != 2) {
        throw runtime_error(std::string("Wrong number of input arguments\nUsage: esetvm2 {filename.evm}"));
    }
}

vector<char> loadBinary(const string& filename)
{
	ifstream f(filename, ios::in | ios::binary);
    if (!f.is_open()) {
        throw runtime_error(std::string("Cannot open file: ") + filename);
    }
	vector<char> binary(istreambuf_iterator<char>(f), (istreambuf_iterator<char>()));
	f.close();

	return binary;
}

int main(int argc,char* argv[])
{

    try {
        //checkUserInput(argc);
        //auto filename = argv[1];
        const string filename = "./task/samples/precompiled/math.evm";
        auto programBytes = loadBinary(filename);
        VirtualMachine vm(programBytes);
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
