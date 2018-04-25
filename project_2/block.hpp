#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
#include <string>
#include <ncurses.h>

using namespace std;

class Block
{
    vector<string> tab;

    public:
        int height;
        Block(vector<string> tab);
        Block(initializer_list<string> tab);
        void print(int x, int y);
        void clear(int x, int y);
};

#endif // BLOCK_H
