#include <thread>
#include <mutex>
#include <ncurses.h>
#include <vector>
#include <chrono>

struct PartOfSnake
{
    int x;
    int y;
    PartOfSnake(int x, int y);
};

class Snake
{
private:
    int startX;
    int startY;
    int endX;
    int endY;
 
    char symbolOfSnake;
    int lengthOfSnake ;
    int prevDirection;
    std::vector<PartOfSnake> snake;
    
    bool dead();
    void moveSnake();
    
public:
    Snake(int coordinateX, int coordinateY, std::pair<int, int> dimensions);
    void init();
};

