#ifndef GRASS_HPP
#define GRASS_HPP
#include <set>
#include <utility>
#include <ncurses.h>

using namespace std;

class Grass
{
    public:
        Grass();//set<pair<int, int>> area);
        void print(int x, int y);
        void clear(int x, int y);
};

#endif // GRASS_HPP
