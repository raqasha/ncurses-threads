#include "SnailMovement.hpp"

extern mutex print_mtx;
extern mutex container_mtx;

SnailMovement::SnailMovement(vector<Snail> &snailTab, int coordinateX, int coordinateY,
                             pair<int, int> dimensions, vector<vector<bool>> &grassMatrix,
                             vector<vector<bool>> &trapMatrix, int id, condition_variable &cv,
                             vector<bool> &terminationThreads, atomic<int> &amountOfGrass, Barrier &barrier)
{
    while(true)
    {
        vector<Snail> allSnails = {{{"@s"}, 5}, {{"l@"}, 1}};
        int maxEatenGrass = 10;

        container_mtx.lock();
        snailTab.push_back(allSnails[rand() % allSnails.size()]);
        int index = snailTab.size() - 1;
        snailTab[index].id = id;
        container_mtx.unlock();

        int y = rand () % dimensions.second + coordinateY;

        if(snailTab[index].color == 5) {
            for(int i = coordinateX + snailTab[index].height; i + snailTab[index].height < coordinateX + dimensions.first - 1; i++)
            {
                move(snailTab, index, i, y, barrier);
                if(!collision(snailTab, grassMatrix, trapMatrix, index, amountOfGrass))
                    break;
            }
        }
        else
        {
            for(int i = coordinateX + dimensions.first - 3; i > coordinateX + snailTab[index].height; i--)
            {
                move(snailTab, index, i, y, barrier);
                if(!collision(snailTab, grassMatrix, trapMatrix, index, amountOfGrass))
                    break;
            }
        }

        if(amountOfGrass >= maxEatenGrass)
        {
            container_mtx.lock();
            terminationThreads.push_back(true);
            container_mtx.unlock();
            cv.notify_all();
            return;
        }
//        snailTab.erase(snailTab.begin() + index);
    }
}

void SnailMovement::move(vector<Snail> &snailTab, int index, int i, int y, Barrier &barrier)
{
    snailTab[index].coordinates = {i, y};
    step(i, y, snailTab, index);
    numberOfSteps++;
    if(numberOfSteps == 10)
    {
        barrier.wait();
        //jeśli ślimak wykona 10 kroków wywołane jest wait bariery
    }
}

void SnailMovement::step(int x, int y, vector<Snail> &snailTab, int index)
{
    int speed = rand () % 200 + 100;

    {
        std::lock_guard<std::mutex> lock(print_mtx);
        snailTab[index].print(x, y, snailTab[index].color);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(speed));

    {
        std::lock_guard<std::mutex> lock(print_mtx);
        snailTab[index].clear(x, y);
    }

}

bool SnailMovement::collision(vector<Snail> &snailTab, vector<vector<bool>> &grassMatrix,
                              vector<vector<bool>> &trapMatrix, int index, atomic<int> &amountOfGrass)
{
    container_mtx.lock();
    if(grassMatrix[snailTab[index].coordinates.first][snailTab[index].coordinates.second])
    {
        snailTab[index].grassEaten++;
        grassMatrix[snailTab[index].coordinates.first][snailTab[index].coordinates.second] = false;
        //amountOfGrass++;
        amountOfGrass.fetch_add(1, std::memory_order_release); // Atomic

    }
    else if(trapMatrix[snailTab[index].coordinates.first][snailTab[index].coordinates.second])
    {
        snailTab[index].clear(snailTab[index].coordinates.first, snailTab[index].coordinates.second);
        trapMatrix[snailTab[index].coordinates.first][snailTab[index].coordinates.second] = false;
        //snailTab.erase(snailTab.begin() + index);
        container_mtx.unlock();
        return false;
    }
    container_mtx.unlock();
    return true;
}
