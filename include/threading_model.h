#ifndef THREADING_MODEL_H_INCLUDED
#define THREADING_MODEL_H_INCLUDED

#include <thread>

class ThreadingModel
{
public:
    std::vector<std::thread> threads;
    // tbd locks/mutexes
};

#endif // THREADING_MODEL_H_INCLUDED
