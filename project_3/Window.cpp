#include "Window.hpp"

std::mutex print_mtx;

//lista inicjalizacyjna
Window::Window(int startX, int startY, std::pair<int, int> dimensions)
    : coordinateX(startX), coordinateY(startY), dimensions(dimensions)
{
    std::lock_guard<std::mutex> guard(print_mtx);

    char verticalSymbol = '|';
    int endX = dimensions.first + startX;
    int endY = dimensions.second + startY;

    for(int i = startY; i < endY; i++)
    {
        mvaddch(i, startX, verticalSymbol);
        mvaddch(i, endX - 1, verticalSymbol);
    }

}
