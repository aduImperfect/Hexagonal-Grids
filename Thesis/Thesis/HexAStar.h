///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: HexAStar.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef HEX_ASTAR_H
#define HEX_ASTAR_H
//Including the base header for different hex operations and parsing the hex neighbors, along with the search loop and pre and post search functionalities.
#include "BaseHexOperations.h"
#include "ParseHexNeighbors.h"
#include "SearchLoop.h"
#include "HexPrePostSearch.h"

/*
Calculates the cost from start to goal using ASTAR.
Parameters to the function:
npStart : Position - the starting position.
npGoal : Position - the goal position.
autoCompute : bool - compute the ASTAR node expansion until it finishes searching for the goal or goal is not found. If false, we get step by step results of the ASTAR nodes expansion.
center : Position - the center position of the hex grid.
perimeter : int - the perimeter of the hex grid.
showMap : int - this numeric value is used to check against if the user wants to view the printed maps or not.
goalPath : std::vector<Position> - the goal path vector that contains the position list from where the goal came from by starting at the start position.
Returns from the function:
startToGoalCost : double - return the calculated start to goal cost.
This function takes in the start and goal positions input by the user (or by other mechanisms) and takes in the center and perimeter points of the hex grid along with the check to see if the result needs to be given step by step or auto computed and if the hex grid maps be printed or not.
*/
double /*startToGoalCost*/ HexAStar(Position npStart, Position npGoal, bool autoCompute, Position center, int perimeter, const int showMap, std::vector<Position> & goalPath)
{
	if (!HexPreSearch(priorityFrontier, npStart, npGoal, center, perimeter, COST_MAX))
		return -1;

	//Default heuristic here is set to OCTILE.
	HeuristicType nheuristic = HeuristicType::HEURISTIC_OCTILE;
	int ntmpHeu = 4;
	bool generateInstantaneous = false;

	//If autoCompute is not set to run (meaning we are going to get step by step results of the ASTAR).
	//Then give the user the option to change it to make it compute automatically, if needed.
	if (!autoCompute)
	{
		printf("\nHeuristic Type (CHEBYSHEV: 1, MANHATTAN: 2, EUCLIDEAN: 3, OCTILE: 4):\n");
		std::cin >> ntmpHeu;
		nheuristic = (HeuristicType)ntmpHeu;

		printf("\nCompute ASTAR Immediate!? (0 - no/1 - yes):\n");
		std::cin >> generateInstantaneous;
	}

	HexSearchLoop(true, priorityFrontier, PathfindingAlgo::ALGO_ASTAR, npStart, npGoal, center, perimeter, CostType::COST_TOTAL_HEURISTIC, nheuristic, generateInstantaneous, autoCompute, showMap);

	if (!HexPostSearch(PathfindingAlgo::ALGO_ASTAR, COST_MAX_TERM, npStart, npGoal, goalPath, generateInstantaneous, autoCompute, showMap))
		return -1;

	//Return the goal cost stored in the cost_so_far(goal).
	return cost_so_far[npGoal.p_x][npGoal.p_y];
}
#endif