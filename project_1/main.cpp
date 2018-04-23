#include "Snake.hpp"
#include "Window.hpp"
#include <ncurses.h>

void addThread(int coordinateX, int coordinateY, std::pair<int, int> dimensions)
{
  Window window(coordinateX, coordinateY, dimensions);
  Snake snake(coordinateX, coordinateY, dimensions);
  snake.init();
}

int main()
{
  std::pair<int, int> size;
  std::pair<int, int> half_size;
  std::vector<std::thread> threads;

  initscr();
  curs_set(0);  
     
  //pobranie i obliczenie wymiarów okien
  getmaxyx(stdscr, size.second, size.first);
  half_size.first = size.first / 2;
  half_size.second = size.second / 2;                   
      
  threads.push_back(std::thread(addThread, 0, 0, half_size));
  threads.push_back(std::thread(addThread, half_size.first, 0, half_size));
  threads.push_back(std::thread(addThread, 0, half_size.second, half_size));
  threads.push_back(std::thread(addThread, half_size.first, half_size.second, half_size));
    
  for (std::thread &thread : threads)
  {
    thread.join();
  }

  getch();
  endwin();
  return 0;
}
