#ifndef SNAIL_HPP
#define SNAIL_HPP
#include <ncurses.h>
#include <string>
#include <vector>
#include <utility>

using namespace std;

class Snail
{
    vector<string> tab;

    public:
        int color;
        int height;
        int grassEaten;
        int id;
        pair<int, int> coordinates;
        Snail(vector<string> tab, int color);
        Snail(initializer_list<string> tab, int color);
        void print(int x, int y, int color);
        void clear(int x, int y);
        bool operator == (const Snail& snail);
};

#endif // SNAIL_HPP
