#include "../include/registers.h"

using namespace std;

void Registers::print() const
{
    cout << "tid = " << dec << tId << endl;
    cout << "ip = " << dec << ip << endl;
    if(!sp.empty())
        cout << "sp = " << dec << sp.top() << endl;
    for (int i=0; i<REGS_COUNT; i++)
        cout << "r[" << dec << i << "] = 0x" << hex << reg[i] << endl;
    cout << endl;
}

void Registers::printInstCounter() const
{
    cout << "instruction no.: " << dec << instcount << endl;
}

void Registers::emptyStack()
{
    while (!sp.empty())
        sp.pop();
}
