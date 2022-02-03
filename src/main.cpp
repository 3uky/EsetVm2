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

int main(int argc,char* argv[])
{
    string filename;
    try {
        if(argc < 2) {
            //filename = "./task/samples/precompiled/math.evm";
            //filename = "./task/samples/precompiled/memory.evm";
            //filename = "./task/samples/precompiled/fibonacci_loop.evm";
            //filename = "./task/samples/precompiled/xor.evm";
            //filename = "./task/samples/precompiled/crc.evm";
            filename = "./task/samples/precompiled/threadingBase.evm";
            //filename = "./task/samples/precompiled/xor-with-stack-frame.evm";
            //filename = "./analysis/samples/precompiled/console_read.evm";
            //filename = "./analysis/samples/precompiled/my.evm";
            //filename = "./analysis/samples/precompiled/my_memory.evm";
            //filename = "./analysis/samples/precompiled/my_memory2.evm";
            //filename = "./analysis/samples/precompiled/mem_store.evm";
            cout << filename << endl;
        }
        else {
            checkUserInput(argc);
            filename = argv[1];
        }

        VirtualMachine vm(filename);
        vm.run();
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
