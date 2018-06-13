#include "Board.hpp"

extern mutex print_mtx;
extern mutex container_mtx;

Board::Board(vector<pair<int, int>> &coordinates, vector<vector<bool>> &grassMatrix,
             vector<vector<bool>> &trapMatrix, vector<bool> &terminationThreads)
{
    int counter = 0;
    while(true)
    {
        //container_mtx.lock();
        if(coordinates.size() > 0)
        {
            container_mtx.lock();
            auto position = coordinates.back();
            coordinates.pop_back();
            container_mtx.unlock();
            counter++;

            if(counter % 10)
            {
                Grass grass;
                container_mtx.lock();
                grassMatrix[position.first][position.second] = true;
                container_mtx.unlock();
                print_mtx.lock();
                grass.print(position.first, position.second);
                print_mtx.unlock();
            }
            else
            {
                Trap trap;
                container_mtx.lock();
                trapMatrix[position.first][position.second] = true;
                container_mtx.unlock();
                print_mtx.lock();
                trap.print(position.first, position.second);
                print_mtx.unlock();
            }
        }
        //container_mtx.unlock();

        container_mtx.lock();
        if(!terminationThreads.empty())
        {
            container_mtx.unlock();
            return;
        }
        container_mtx.unlock();

    }
}
