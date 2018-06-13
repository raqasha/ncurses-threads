#ifndef SNAILMOVEMENT_HPP
#define SNAILMOVEMENT_HPP
#include "Snail.hpp"
#include "Barrier.hpp"
#include <mutex>
#include <vector>
#include <thread>
#include <memory>
#include <cstdlib>
#include <condition_variable>
#include <algorithm>
#include <atomic>

using namespace std;

class SnailMovement
{
    public:
        int numberOfSteps = 0;
        SnailMovement(vector<Snail> &snailTab, int coordinateX, int coordinateY,
                      pair<int, int> dimensions, vector<vector<bool>> &grassMatrix,
                      vector<vector<bool>> &trapMatrix, int id, condition_variable &cv,
                      vector<bool> &terminationThreads, atomic<int> &amountOfGrass, Barrier &barrier);
        void move(vector<Snail> &snailTab, int index, int i, int y, Barrier &barrier);
        void step(int x, int y, vector<Snail> &snailTab, int index);
        bool collision(vector<Snail> &snailTab, vector<vector<bool>> &grassMatrix,
                       vector<vector<bool>> &trapMatrix, int index, atomic<int> &amountOfGrass);
};

#endif // SNAILMOVEMENT_HPP
