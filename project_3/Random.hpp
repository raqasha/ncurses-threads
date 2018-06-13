#ifndef RANDOM_HPP
#define RANDOM_HPP
#include <vector>
#include <utility>
#include <random>
#include <mutex>
#include <thread>
#include <memory>
#include <cstdlib>

using namespace std;

class Random
{
    public:
        Random(pair<int, int> windowSize, vector<pair<int, int>> &coordinates, vector<bool> &terminationThreads);
};

#endif // RANDOM_HPP
