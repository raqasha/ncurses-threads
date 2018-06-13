#include "Barrier.hpp"

//Bariera ma po 10 krokach ślimaków ustawic czekanie na resztę wątków
//Musi wiedzieć ile jest wątków ogólnie i na ile ślimaków jeszcze musi czekać

Barrier::Barrier(int numberOfSnailThreads)
    : counter(0), numberOfSnailThreads(numberOfSnailThreads)
{
}

void Barrier::wait()
{
    unique_lock<std::mutex> lock(_mutex);
    counter++;

    if (counter == numberOfSnailThreads)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _cv.notify_all();
    }
    else
    {
        _cv.wait(lock, [this] { return numberOfSnailThreads == counter; });
    }
}

