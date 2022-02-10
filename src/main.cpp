#include <string>

#include "vm.h"

using namespace std;

void checkUserInput(int argc)
{
    if(argc != 2) {
        throw runtime_error(string("Wrong number of input arguments\nUsage: esetvm2 {filename.evm}"));
    }
}

int main(int argc,char* argv[])
{
    try {
        checkUserInput(argc);
        string filename = argv[1];
        VirtualMachine vm(filename);
        vm.run();
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
