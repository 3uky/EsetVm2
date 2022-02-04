#ifndef THREADING_MODEL_H_INCLUDED
#define THREADING_MODEL_H_INCLUDED

#include <vector>
#include <map>
#include <thread>
#include <mutex>

#include "global.h"
#include "registers.h"

class VirtualMachine;
class ThreadingModel
{
public:
    std::vector<std::thread> threads;
    std::map<VM_QWORD, std::mutex> mtxs;    // used by evm programs
    std::recursive_mutex mtx;               // used for mutual exclusion to critical sections

    unsigned int noThreads;

    VirtualMachine* vm;
    ThreadingModel(VirtualMachine*);

    void createThread(unsigned int, Registers&);
    void joinStillRunningThreads();

    void lock(VM_QWORD);
    void unlock(VM_QWORD);
};

#endif // THREADING_MODEL_H_INCLUDED
