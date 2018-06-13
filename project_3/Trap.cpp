#include "Trap.hpp"

Trap::Trap()
{}

void Trap::print(int x, int y)
{
    attron(COLOR_PAIR(4));
    mvaddstr(y, x, "O");
    attron(COLOR_PAIR(4));
    refresh();
}

void Trap::clear(int x, int y)
{
    mvaddstr(y, x, " ");
    refresh();
}
