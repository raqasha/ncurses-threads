
#include "Snake.hpp"
#define DELAY 100

extern std::mutex mtx;

PartOfSnake::PartOfSnake(int x, int y)
{
    this->x = x;
    this->y = y;
}

Snake::Snake(int coordinateX, int coordinateY, std::pair<int, int> dimensions)
{
    std::lock_guard<std::mutex> guard(mtx);

    symbolOfSnake = 'o';
    lengthOfSnake = 7;   

    startX = coordinateX;
    startY = coordinateY;
    endX = dimensions.first + coordinateX;
    endY = dimensions.second + coordinateY;                                 

    for(int i = 0; i < lengthOfSnake; i++) 
    {
        snake.push_back(PartOfSnake(startX + i + 5, startY + 5));
    }
    refresh();
}

enum Directions
{
    up,
    down,
    left,
    right
};

void Snake::moveSnake()
{
    std::lock_guard<std::mutex> guard(mtx);

    Directions direction = Directions(rand() % 4);

    switch (direction) {
        case up:
            if (prevDirection != down)
            {
                prevDirection = up;
                snake.insert(snake.begin(), PartOfSnake(snake[0].x, snake[0].y - 1));
            }
            break;
        case down:
            if (prevDirection != up)
            {
                prevDirection = down;
                snake.insert(snake.begin(), PartOfSnake(snake[0].x, snake[0].y + 1));
            }
            break;
        case left:
            if (prevDirection != right)
            {
                prevDirection = left;
                snake.insert(snake.begin(), PartOfSnake(snake[0].x - 1, snake[0].y));
            }
            break;
        case right:
            if (prevDirection != left)
            {
                prevDirection = right;
                snake.insert(snake.begin(), PartOfSnake(snake[0].x + 1, snake[0].y));
            }
            break;
        default:
            break;
    }

    mvaddch(snake[lengthOfSnake - 1].y, snake[lengthOfSnake - 1].x, ' ');
    refresh();
    mvaddch(snake[0].y, snake[0].x, symbolOfSnake);
    refresh();
}

bool Snake::dead()
{
    return (snake[0].x == this->startX || snake[0].x == this->endX 
    || snake[0].y == this->startY || snake[0].y == this->endY) ? true : false;
}

void Snake::init()
{
    while (!dead()) 
    {
        moveSnake();
        std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
    }
}
