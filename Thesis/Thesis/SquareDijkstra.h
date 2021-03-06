///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017-2018 DigiPen Institute of Technology, all rights reserved
/// FILE: SquareDijkstra.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef SQUARE_DIJKSTRA_H
#define SQUARE_DIJKSTRA_H
//Including the base header for different square operations and parsing the square neighbors, along with the search loop and pre and post search functionalities.
#include "BaseSquareOperations.h"
#include "ParseSquareNeighbors.h"
#include "SearchLoop.h"
#include "SquarePrePostSearch.h"

/*
Calculates the cost from start to goal using DIJKSTRA.
Parameters to the function:
npStart : Position - the starting position.
npGoal : Position - the goal position.
autoCompute : bool - compute the DIJKSTRA node expansion until it finishes searching for the goal or goal is not found. If false, we get step by step results of the DIJKSTRA nodes expansion.
topLeft : Position - the top left position of the square grid.
bottomRight : Position - the bottom right position of the square grid.
showMap : int - this numeric value is used to check against if the user wants to view the printed maps or not.
goalPath : std::vector<Position> - the goal path vector that contains the position list from where the goal came from by starting at the start position.
Returns from the function:
startToGoalCost : double - return the calculated start to goal cost.
This function takes in the start and goal positions input by the user (or by other mechanisms) and takes in the boundary points of the square grid along with the check to see if the result needs to be given step by step or auto computed and if the square grid maps be printed or not.
*/
double /*startToGoalCost*/ SquareDijkstra(Position npStart, Position npGoal, bool autoCompute, Position topLeft, Position bottomRight, const int showMap, std::vector<Position> & goalPath)
{
	if (!SquarePreSearch(priorityFrontier, npStart, npGoal, topLeft, bottomRight, COST_MAX))
		return -1;

	bool generateInstantaneous = false;
	
	//If autoCompute is not set to run (meaning we are going to get step by step results of the DIJKSTRA).
	//Then give the user the option to change it to make it compute automatically, if needed.
	if (!autoCompute)
	{
		printf("\nCompute DIJKSTRA Immediate!? (0 - no/1 - yes):\n");
		std::cin >> generateInstantaneous;
	}

	SquareSearchLoop(true, priorityFrontier, PathfindingAlgo::ALGO_DIJKSTRA, npStart, npGoal, topLeft, bottomRight, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, generateInstantaneous, autoCompute, showMap);

	if (!SquarePostSearch(PathfindingAlgo::ALGO_DIJKSTRA, COST_MAX_TERM, npStart, npGoal, goalPath, generateInstantaneous, autoCompute, showMap))
		return -1;

	//Return the goal cost stored in the cost_so_far(goal).
	return cost_so_far[npGoal.p_x][npGoal.p_y];
}
#endif