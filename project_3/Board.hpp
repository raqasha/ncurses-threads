#ifndef BOARD_HPP
#define BOARD_HPP
#include "Random.hpp"
#include "Grass.hpp"
#include "Trap.hpp"
#include <mutex>
#include <vector>
#include <thread>
#include <memory>
#include <cstdlib>
#include <condition_variable>

using namespace std;

class Board
{
    public:
        Board(vector<pair<int, int>> &coordinates, vector<vector<bool>> &grass,
              vector<vector<bool>> &trap, vector<bool> &terminationThreads);
};

#endif // BOARD_HPP
