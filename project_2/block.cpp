#include "block.hpp"

Block::Block(vector<string> tab) : tab(tab)
{
    height = tab.size();
}

Block::Block(initializer_list<string> tab) : tab(tab)
{
    height = tab.size();
}

void Block::print(int x, int y)
{
    for(int i = 0; i < height; i++)
    {
        mvaddstr(y + i, x, tab[i].c_str());
    }
    refresh();
}

void Block::clear(int x, int y)
{
    for(int i = 0; i < height; i++)
    {
        mvaddstr(y + i, x, string(tab[i].size(),  ' ').c_str());
    }
    refresh();
}
