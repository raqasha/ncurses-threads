#include <cstdlib>
#include <mutex>
#include <ncurses.h>

class Window
{     
public:
    Window(int coordinateX, int coordinateY, std::pair<int, int> dimensions);
};