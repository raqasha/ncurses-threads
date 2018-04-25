#include "Window.hpp"
#include "Producent.hpp"
#include "Consumer.hpp"
#include "block.hpp"
#include <ncurses.h>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <memory>
#include <condition_variable>

std::condition_variable cv;

void addProducentThread(int coordinateX, int coordinateY, std::pair<int, int> dimensions, std::vector<Block> &sharedList, condition_variable &cv)
{
  Window window(coordinateX, coordinateY, dimensions);
  Producent producent(sharedList, window, cv);
}

void addCustomerThread(int coordinateX, int coordinateY, std::pair<int, int> dimensions, std::vector<Block> &sharedList, condition_variable &cv)
{
  Window window(coordinateX, coordinateY, dimensions);
  Consumer consumer(sharedList, window, cv);
}

int main()
{
  std::pair<int, int> size;
  std::pair<int, int> half_size;
  std::vector<std::thread> threads;

  std::vector<Block> sharedList;

  initscr();
  curs_set(0);  
     
  //pobranie i obliczenie wymiarów okien
  getmaxyx(stdscr, size.second, size.first);
  half_size = { size.first / 2, size.second / 2 };                   
      
  threads.push_back(std::thread(addProducentThread, 0, 0, half_size, std::ref(sharedList), std::ref(cv)));
  threads.push_back(std::thread(addCustomerThread, half_size.first, 0, half_size, std::ref(sharedList), std::ref(cv)));
  threads.push_back(std::thread(addCustomerThread, 0, half_size.second, half_size, std::ref(sharedList), std::ref(cv)));
  threads.push_back(std::thread(addCustomerThread, half_size.first, half_size.second, half_size, std::ref(sharedList), std::ref(cv)));
    
  for (std::thread &thread : threads)
  {
    thread.join();
  }

  getch();
  endwin();
  return 0;
}
