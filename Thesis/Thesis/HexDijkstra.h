///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: HexDijkstra.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef HEX_DIJKSTRA_H
#define HEX_DIJKSTRA_H
//Including the base header for different hex operations and parsing the hex neighbors, along with the search loop and pre and post search functionalities.
#include "BaseHexOperations.h"
#include "ParseHexNeighbors.h"
#include "SearchLoop.h"
#include "PrePostSearch.h"

/*
Calculates the cost from start to goal using DIJKSTRA.
Parameters to the function:
npStart : Position - the starting position.
npGoal : Position - the goal position.
autoCompute : bool - compute the DIJKSTRA node expansion until it finishes searching for the goal or goal is not found. If false, we get step by step results of the DIJKSTRA nodes expansion.
center : Position - the center position of the hex grid.
perimeter : int - the perimeter of the hex grid.
showMap : int - this numeric value is used to check against if the user wants to view the printed maps or not.
goalPath : std::vector<Position> - the goal path vector that contains the position list from where the goal came from by starting at the start position.
Returns from the function:
startToGoalCost : double - return the calculated start to goal cost.
This function takes in the start and goal positions input by the user (or by other mechanisms) and takes in the center and perimeter points of the hex grid along with the check to see if the result needs to be given step by step or auto computed and if the hex grid maps be printed or not.
*/
double /*startToGoalCost*/ HexDijkstra(Position npStart, Position npGoal, bool autoCompute, Position center, int perimeter, const int showMap, std::vector<Position> & goalPath)
{
	if (!HexPreSearch(priorityFrontier, npStart, npGoal, center, perimeter, COST_MAX))
		return -1;

	bool generateInstantaneous = false;

	//If autoCompute is not set to run (meaning we are going to get step by step results of the DIJKSTRA).
	//Then give the user the option to change it to make it compute automatically, if needed.
	if (!autoCompute)
	{
		printf("\nCompute Dijkstra Immediate!? (0 - no/1 - yes):\n");
		std::cin >> generateInstantaneous;
	}

	HexSearchLoop(true, priorityFrontier, PathfindingAlgo::ALGO_DIJKSTRA, npStart, npGoal, center, perimeter, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, generateInstantaneous, autoCompute, showMap);

	if (!HexPostSearch(PathfindingAlgo::ALGO_DIJKSTRA, COST_MAX_TERM, npStart, npGoal, goalPath, generateInstantaneous, autoCompute, showMap))
	return -1;

	//Return the goal cost stored in the cost_so_far(goal).
	return cost_so_far[npGoal.p_x][npGoal.p_y];
}
#endif