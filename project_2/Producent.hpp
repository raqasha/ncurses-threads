#ifndef PRODUCENT_H
#define PRODUCENT_H
#include "Window.hpp"
#include "block.hpp"
#include <vector>
#include <mutex>
#include <thread>
#include <memory>
#include <cstdlib>
#include <condition_variable>

class Producent
{
    public:
        Producent(std::vector<Block> &sharedList, Window &window, std::condition_variable& cv);
        void step(int x, int y, Block block);
};
#endif
