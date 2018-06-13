#ifndef BARRIER_HPP
#define BARRIER_HPP
#include <condition_variable>
#include <atomic>
#include <thread>

using namespace std;

class Barrier
{
    mutex _mutex;
    condition_variable _cv;

    public:
        atomic<int> counter;
        int numberOfSnailThreads;
        Barrier(int numberOfSnailThreads);
        void wait();

};

#endif // BARRIER_HPP
