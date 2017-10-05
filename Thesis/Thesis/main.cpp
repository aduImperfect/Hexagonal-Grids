#include <cstdio>
#include <queue>
#include <iostream>
#include <iomanip>
#include <sstream>


#include "MainMap.h"

int main(int argc, char** argv)
{
  bool newRun = false;
  do
  {
    int nGridSpace = 0;
    printf("GridSpace size is 20x20\n\n");
    printf("GridSpace (Square: 1, Hex: 2):\n");
    std::cin >> nGridSpace;

    int nAlgoType = 0;
    printf("Algorithm Type (BFS: 1, DIJKSTRA: 2, GREEDY: 3, ASTAR: 4, BLOCKASTAR: 5, JPS: 6):\n");
    std::cin >> nAlgoType;

    Position posStart;
    Position posGoal;

    printf("Starting positions (x y):\n");
    std::cin >> posStart.p_x >> posStart.p_y;

    printf("Goal positions (x y):\n");
    std::cin >> posGoal.p_x >> posGoal.p_y;

    printf("\nMap Compute:\n\n");
    double goalCost = Map(nGridSpace, nAlgoType, posStart, posGoal);
    
    printf("\nGoal cost (-1 = goal not reachable or not found!):\n%f", goalCost);

    printf("\n\nNew Run (0 - No, 1 - Yes):\n");
    std::cin >> newRun;
  } while (newRun);
  
  return 0;
}
