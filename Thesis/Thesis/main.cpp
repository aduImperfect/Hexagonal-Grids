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

/*
Main function of the project.
Parameters to the function:
argc : int - the number of arguments.
argv : char** - the value of each argument taken as a string of characters.
Returns from the function:
success : int - the value for when the function returns a success (0) or not.
This function is the very first function called by the project. It handles the main game loop and calls the required functionalities to run the project based on the user inputs.
*/
int /*success*/ main(int argc, char** argv)
{
	//NewRun is a boolean that takes into consideration based on user input if there should be a new run of the project once everything finishes.
	bool newRun = false;

	//The main game loop that restarts every time the user wants to run the project again.
	do
	{
		int nGridSpace = 0;
		printf("GridSpace size is %d X %d. \n\n", SIZE - 1, SIZE - 1);
		printf("GridSpace (Square: 1, Hex: 2):\n");
		std::cin >> nGridSpace;

		int nAlgoType = 0;
		printf("Algorithm Type (BFS: 1, DIJKSTRA: 2, GREEDY: 3, ASTAR: 4, BLOCKASTAR: 5, JPS: 6):\n");
		std::cin >> nAlgoType;

		//The two positions entered by the user: start and goal.
		Position posStart;
		Position posGoal;

		printf("Starting positions (x y):\n");
		std::cin >> posStart.p_x >> posStart.p_y;

		printf("Goal positions (x y):\n");
		std::cin >> posGoal.p_x >> posGoal.p_y;

		int showMap = 0;
		printf("Show Printed Map (0 - No, 1 - Yes):\n");
		std::cin >> showMap;

		//Initialize and generate the map elements.
		printf("\nPre-Compute (initialize and generate) Map!!\n\n");
		Map(nGridSpace, nAlgoType, posStart, posGoal, showMap);

		//The Goal cost calculated from running the path-finding algorithm.
		printf("\nRun Path-finding!!\n\n");
		double goalCost = RunPathfinding(nGridSpace, nAlgoType, posStart, posGoal, showMap);
		
		printf("\nGoal cost (-1 = goal not reachable or not found!):\n%f", goalCost);

		printf("\n\nNew Run (0 - No, 1 - Yes):\n");
		std::cin >> newRun;
	} while (newRun);
	
	//Successfully exit out of the main loop.
	return 0;
}
