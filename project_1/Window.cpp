#include "Window.hpp"

std::mutex mtx;

Window::Window(int startX, int startY, std::pair<int, int> dimensions)
{
    std::lock_guard<std::mutex> guard(mtx);

    char verticalSymbol = '|';
    char horizontalSymbol = '-';   
    int endX = dimensions.first + startX;
    int endY = dimensions.second + startY;                                 

    //dzielenie na 4 okna
    for(int i = startX; i < endX; i++)
    {
        mvaddch(startY, i, horizontalSymbol);
        mvaddch(endY, i - 1, horizontalSymbol);
    } 
    
    for(int i = startY; i < endY; i++)
    {
        mvaddch(i, startX, verticalSymbol);
        mvaddch(i, endX - 1, verticalSymbol);
    }
}