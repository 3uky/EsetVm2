#include "threading_model.h"
#include "vm.h"
#include "registers.h"

#include <thread>
#include <mutex>

using namespace std;

ThreadingModel::ThreadingModel(VirtualMachine* ivm) : vm(ivm)
{
    noThreads = 0;
}

unsigned int ThreadingModel::createThread(Registers& regCopy)
{
    auto index = noThreads++;
    regCopy.tId = noThreads;
    threads.emplace(threads.begin() + index, std::thread(&VirtualMachine::executeLoop, vm, regCopy));
    return index;
}

void ThreadingModel::lock(VM_QWORD index)
{
    mtxs.emplace(std::piecewise_construct, std::make_tuple(index), std::make_tuple());
    mtx.unlock();
    mtxs[index].lock();
}

void ThreadingModel::unlock(VM_QWORD index)
{
    mtx.unlock();
    mtxs[index].unlock();
}

void ThreadingModel::joinStillRunningThreads()
{
    for (auto& t: threads) {
        if(t.joinable())
            t.join();
    }
}
