#include "Consumer.hpp"

extern mutex print_mtx;
extern mutex list_mtx;

Consumer::Consumer(std::vector<Block> &sharedList, Window &window, std::condition_variable &cv)
{
    while(true)
    {
        std::unique_lock<std::mutex> lck(list_mtx);
        cv.wait(lck);
        if(sharedList.size() > 0) {

            Block block = sharedList.front();
            sharedList.pop_back();

            int x = (std::rand() % (window.dimensions.first - 4)) + 1;
            int y = (std::rand() % (window.dimensions.second - 4)) + 1;

            std::lock_guard<std::mutex> guard(print_mtx);
            block.print(x + window.coordinateX, y + window.coordinateY);
        }
    }
}
