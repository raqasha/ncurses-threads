#include "Snail.hpp"

Snail::Snail(vector<string> tab, int color)
    : tab(tab), color(color)
{
    height = tab.size();
    grassEaten = 0;
}

Snail::Snail(initializer_list<string> tab, int color)
    : tab(tab), color(color)
{
    height = tab.size();
    grassEaten = 0;
}

void Snail::print(int x, int y, int color)
{
    for(int i = 0; i < height; i++)
    {

        attron(COLOR_PAIR(color));
        mvaddstr(y + i, x, tab[i].c_str());
        attroff(COLOR_PAIR(color));

    }
    refresh();
}

void Snail::clear(int x, int y)
{
    mvaddstr(y, x, string("  ").c_str());

    //for(int i = 0; i < height; i++)
    //{
    //    mvaddstr(y + i, x, string(tab[i].size(),  ' ').c_str());
    //
    //}
    refresh();
}

bool Snail::operator == (const Snail& snail)
{
    return this->id == snail.id;
}
