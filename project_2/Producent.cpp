#include "Producent.hpp"
mutex print_mtx;
mutex list_mtx;

Producent::Producent(std::vector<Block> &sharedList, Window &window, std::condition_variable &cv)
{
    while(true)
    {
        std::vector<Block> allBlocks = {{" x ","xxx"}, {"xx "," xx"},
                                        {" xx","xx "}, {"x  ","xxx"},
                                        {"  x","xxx"}, {"xx ","xx "},
                                        {"xxxx"}, {"x", "x", "x", "x"}};
        Block block(allBlocks[rand() % allBlocks.size()]);

        for(int i = window.coordinateY + 1; i + block.height <= window.coordinateY + window.dimensions.second; i++ )
        {
            step(window.coordinateX + window.dimensions.first/2, i, block);
            
            //kiedy kolizja - trafienie do wspólnej kolekcji
            if(i + block.height == window.coordinateY + window.dimensions.second - 1)
            {
               std::lock_guard<std::mutex> guard(list_mtx);
               sharedList.push_back(block);
               cv.notify_one(); //wszyscy konsumenci zostaną powiadomieni
            }
        }
    }
}

void Producent::step(int x, int y, Block block)
{
    std::lock_guard<std::mutex> guard(print_mtx);
    block.print(x, y);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    block.clear(x, y);
}
