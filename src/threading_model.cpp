#include "../include/threading_model.h"
#include "../include/vm.h"
#include "../include/registers.h"

#include <thread>
#include <mutex>

using namespace std;

ThreadingModel::ThreadingModel(VirtualMachine* ivm) : vm(ivm)
{
    noThreads = 0;
}

void ThreadingModel::createThread(unsigned int index, Registers& regCopy)
{
    threads.emplace(threads.begin() + index, std::thread(&VirtualMachine::executeLoop, vm, regCopy));
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
