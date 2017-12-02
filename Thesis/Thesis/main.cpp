///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: main.cpp
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

//Including the required standard libraries.
#include <cstdio>
#include <queue>
#include <iostream>
#include <iomanip>
#include <sstream>

//Including the MainMap header file.
#include "MainMap.h"

//The main function that gets called to execute the project.
int main(int argc, char** argv)
{
	//NewRun is a boolean that takes into consideration based on user input if there should be a new run of the project once everything finishes.
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
