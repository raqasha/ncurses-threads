#ifndef WINDOW_H
#define WINDOW_H
#include <cstdlib>
#include <mutex>
#include <ncurses.h>
#include <utility>

class Window
{     
    public:
        int coordinateX;
        int coordinateY; 
        std::pair<int, int> dimensions;
        Window(int coordinateX, int coordinateY, std::pair<int, int> dimensions);
};

#endif