#include "Grass.hpp"

Grass::Grass()
{
}

void Grass::print(int x, int y)
{
    attron(COLOR_PAIR(3));
    mvaddstr(y, x, "w");
    attroff(COLOR_PAIR(3));
    refresh();
}

void Grass::clear(int x, int y)
{
    mvaddstr(y, x, " ");
    refresh();
}
