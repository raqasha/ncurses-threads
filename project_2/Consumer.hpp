#ifndef CONSUMER_H
#define CONSUMER_H
#include "Window.hpp"
#include "block.hpp"
#include <mutex>
#include <vector>
#include <ncurses.h>
#include <condition_variable>
#include <cstdlib>

class Consumer
{
    public:
        Consumer(std::vector<Block> &sharedList, Window &window, std::condition_variable &cv);
};
#endif
