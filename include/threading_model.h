#ifndef THREADING_MODEL_H_INCLUDED
#define THREADING_MODEL_H_INCLUDED

#include <vector>
#include <map>
#include <thread>
#include <mutex>

#include "global.h"

class ThreadingModel
{
public:
    std::vector<std::thread> threads;
    std::map<VM_QWORD, std::mutex> mtxs;
    //std::mutex mtx;

    void lock(VM_QWORD index) {
        //mtx.lock();
        mtxs.emplace(std::piecewise_construct, std::make_tuple(index), std::make_tuple());
        mtxs[index].lock();
    };

    void unlock(VM_QWORD index) {
        //mtx.unlock();
        mtxs[index].unlock(); // tbd: check if exists
    };
};

#endif // THREADING_MODEL_H_INCLUDED
