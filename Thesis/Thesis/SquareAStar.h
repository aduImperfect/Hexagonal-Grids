///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017-2018 DigiPen Institute of Technology, all rights reserved
/// FILE: SquareAStar.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef SQUARE_ASTAR_H
#define SQUARE_ASTAR_H
//Including the base header for different square operations and parsing the square neighbors, along with the search loop and pre and post search functionalities.
#include "BaseSquareOperations.h"
#include "ParseSquareNeighbors.h"
#include "SearchLoop.h"
#include "SquarePrePostSearch.h"

/*
Calculates the cost from start to goal using ASTAR.
Parameters to the function:
npStart : Position - the starting position.
npGoal : Position - the goal position.
autoCompute : bool - compute the ASTAR node expansion until it finishes searching for the goal or goal is not found. If false, we get step by step results of the ASTAR nodes expansion.
topLeft : Position - the top left position of the square grid.
bottomRight : Position - the bottom right position of the square grid.
showMap : int - this numeric value is used to check against if the user wants to view the printed maps or not.
goalPath : std::vector<Position> - the goal path vector that contains the position list from where the goal came from by starting at the start position.
Returns from the function:
startToGoalCost : double - return the calculated start to goal cost.
This function takes in the start and goal positions input by the user (or by other mechanisms) and takes in the boundary points of the square grid along with the check to see if the result needs to be given step by step or auto computed and if the square grid maps be printed or not.
*/
double /*startToGoalCost*/ SquareAStar(Position npStart, Position npGoal, bool autoCompute, Position topLeft, Position bottomRight, const int showMap, std::vector<Position> & goalPath)
{
	if (!SquarePreSearch(priorityFrontier, npStart, npGoal, topLeft, bottomRight, COST_MAX))
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

	SquareSearchLoop(true, priorityFrontier, PathfindingAlgo::ALGO_ASTAR, npStart, npGoal, topLeft, bottomRight, CostType::COST_TOTAL_HEURISTIC, nheuristic, generateInstantaneous, autoCompute, showMap);

	if (!SquarePostSearch(PathfindingAlgo::ALGO_ASTAR, COST_MAX_TERM, npStart, npGoal, goalPath, generateInstantaneous, autoCompute, showMap))
		return -1;

	//Return the goal cost stored in the cost_so_far(goal).
	return cost_so_far[npGoal.p_x][npGoal.p_y];
}
#endif