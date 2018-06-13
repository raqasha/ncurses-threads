#include "Window.hpp"
#include "Random.hpp"
#include "Board.hpp"
#include "Barrier.hpp"
#include "Snail.hpp"
#include "SnailMovement.hpp"
#include <ncurses.h>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

std::condition_variable cv;
std::atomic<int> amountOfGrass{0};
extern mutex container_mtx;

void windowThread(int coordinateX, int coordinateY, std::pair<int, int> dimensions)
{
  Window window(coordinateX, coordinateY, dimensions);
}

void randomCoordinates(std::pair<int, int> size,  std::vector<std::pair<int,int>> &coordinates,
                       vector<bool> &terminationThreads)
{
  Random random(size, coordinates, terminationThreads);
}

void fillBoard(vector<pair<int, int>> &coordinates, vector<vector<bool>> &grass, vector<vector<bool>> &trap,
               vector<bool> &terminationThreads)
{
  Board board(coordinates, grass, trap, terminationThreads);
}

void moveSnail(vector<Snail> &snailTab, int coordinateX, int coordinateY, pair<int, int> dimensions,
               vector<vector<bool>> &grass, vector<vector<bool>> &trap, int id, condition_variable &cv,
               vector<bool> &terminationThreads, atomic<int> &amountOfGrass, Barrier &barrier)
{
   SnailMovement snailMovement (snailTab, coordinateX, coordinateY, dimensions, grass, trap, id,
                                cv, terminationThreads, amountOfGrass, barrier);
}

void initialize_colors()
{
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  init_pair(4, COLOR_CYAN, COLOR_BLACK);
  init_pair(5, COLOR_YELLOW, COLOR_BLACK);
  init_pair(6, COLOR_BLUE, COLOR_BLACK);
}

int main()
{
  std::pair<int, int> size;
  std::vector<std::thread> threads;

  std::vector<std::pair<int, int>> coordinates;
  std::vector<Snail> snailTab;
  std::vector<bool> terminationThreads;

  int numberOfSnailThreads = 48;
  Barrier barrier(numberOfSnailThreads);

  initscr();
  curs_set(0);

  //pobranie i obliczenie wymiarów okien
  getmaxyx(stdscr, size.second, size.first);
  start_color();
  initialize_colors();

  std::vector<std::vector<bool>> grass(size.first, std::vector<bool>(size.second));
  std::vector<std::vector<bool>> trap(size.first, std::vector<bool>(size.second));

  threads.push_back(std::thread(windowThread, 0, 0, size ));
  threads.push_back(std::thread(randomCoordinates, size, std::ref(coordinates), std::ref(terminationThreads)));
  threads.push_back(std::thread(fillBoard, std::ref(coordinates), std::ref(grass), std::ref(trap),
                                std::ref(terminationThreads)));

  for(int i = 0; i < numberOfSnailThreads; i++)
    threads.push_back(std::thread(moveSnail, std::ref(snailTab), 0, 0, size, std::ref(grass),
                                  std::ref(trap), i, std::ref(cv), std::ref(terminationThreads),
                                  std::ref(amountOfGrass), std::ref(barrier)));

  std::unique_lock<std::mutex> lck(container_mtx);
  cv.wait(lck);
  lck.unlock();

  for (std::thread &thread : threads)
    thread.join();

  //getch();
  endwin();
  return 0;
}
