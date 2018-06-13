#ifndef TRAP_HPP
#define TRAP_HPP
#include <ncurses.h>
#include <utility>

class Trap
{
    public:
        Trap();
        void print(int x, int y);
        void clear(int x, int y);
};

#endif // TRAP_HPP
