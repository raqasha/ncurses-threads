#include "Random.hpp"

mutex container_mtx;

Random::Random(pair<int, int> windowSize, vector<pair<int, int>> &coordinates, vector<bool> &terminationThreads)
{
   while(true)
   {
       container_mtx.lock();
       if(coordinates.empty())
       {
        random_device rd; //to init seed engine
        mt19937 randomGenerator(rd());
        uniform_int_distribution<int> uni_x(1, windowSize.first - 1);
        uniform_int_distribution<int> uni_y(1, windowSize.second - 1);
        auto random_x = uni_x(randomGenerator);
        auto random_y = uni_y(randomGenerator);

        coordinates.push_back({random_x, random_y});
        container_mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
       }

       if(!terminationThreads.empty())
       {
           container_mtx.unlock();
           return;
       }
       container_mtx.unlock();
    }
}
