///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017-2018 DigiPen Institute of Technology, all rights reserved
/// FILE: GenericOperations.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef GENERIC_OPERATIONS_H
#define GENERIC_OPERATIONS_H
//Including the different base headers which contain the base enumerations, the position structure, the operators, calculators, and initializers.
#include "BaseEnumerations.h"
#include "Position.h"
#include "BaseOperators.h"
#include "BaseCalculators.h"
#include "BaseInitializers.h"

/*
Prints the header - what type of map is being printed!
Parameters to the function:
mvType : const MapVisualType - the map's visual type.
Returns from the function:
NONE
This function prints what type of map is being printed and returns nothing.
*/
void PrintHeader(const MapVisualType mvType)
{
	switch (mvType)
	{
	case MapVisualType::MAP_VISITED:
		//Print Visited.
		printf("\nMap Visited:\n");
		break;
	case MapVisualType::MAP_CAMEFROM:
		//Print Came_From.
		printf("\nMap Came From:\n");
		break;
	case MapVisualType::MAP_GOALPATH:
		//Print Goal_Path.
		printf("\nMap Goal Path:\n");
		break;
	case MapVisualType::MAP_COST:
		//Print Cost.
		printf("\nMap Cost:\n");
		break;
	case MapVisualType::MAP_GOALCOST:
		//Print Goal Cost.
		printf("\nMap Goal Cost:\n");
		break;
	case MapVisualType::MAP_HEUCOST:
		//Print Heuristic Cost.
		printf("\nMap Heuristic Cost:\n");
		break;
	case MapVisualType::MAP_GOALHEUCOST:
		//Print Goal Heuristic Cost.
		printf("\nMap Goal Heuristic Cost:\n");
		break;
	case MapVisualType::MAP_TOTALCOST:
		//Print Total Cost.
		printf("\nMap Total Cost:\n");
		break;
	case MapVisualType::MAP_GOALTOTALCOST:
		//Print Goal Total Cost.
		printf("\nMap Goal Total Cost:\n");
		break;
	}
}

/*
Assigning of the 'next' child position with new values.
Parameters to the function:
current : const Position & - the current position.
next : Position & - the child position which needs to be updated.
dir : const char * - the direction in which the next position exists with respect to the current position.
nextCost : const double - the cost to be added to the cost_so_far calculation.
cType : const CostType - the type of cost.
hType : const HeuristicType - the type of the heuristic.
goal : const Position & - the goal position used here to find the new heuristic value from next position to goal.
gridType : const int - the grid type: square or hex.
Returns from the function:
NONE
This function calculates the values for the next position and updates the information for it alongwith updating the printable maps.
*/
void NextChildAssignments(const Position & current, Position & next, const char* dir, const double nextCost, const CostType cType, const HeuristicType hType, const Position & goal, const int gridType)
{
	//The next node has now been visited.
	visited[next.p_x][next.p_y] = true;

	//The next node came from the current node.
	came_from[next.p_x][next.p_y] = current;

	//We now calculate the cost for the next node from start uptil now. Accumulated by adding up the current node's cost_so_far with the nextCost.
	cost_so_far[next.p_x][next.p_y] = cost_so_far[current.p_x][current.p_y] + nextCost;
	
	//Parse through which type of position cost is being calculated (START-NEXT (EXACT), NEXT-GOAL (HEURISTIC), START-NEXT-GOAL (EXACT + HEURISTIC = TOTAL).
	switch (cType)
	{
	case COST_FROM_START_EXACT:
		//EXACT cost.
		//cost_so_far.
		next.posCost = cost_so_far[next.p_x][next.p_y];
		break;
	case COST_TO_GOAL_HEURISTIC:
		//HEURISTIC cost.
		//If HEX GRID - XDIFF = ABS((x2 - x1)/2), YDIFF = ABS(y2 - y1).
		//If SQUARE GRID - XDIFF = ABS(x2 - x1), YDIFF = ABS(y2 - y1).
		//cost_heuristic.
		next.posCost = cost_heuristic[next.p_x][next.p_y] = Heuristic(hType, (gridType == HEX_GRID) ? abs((goal.p_x - next.p_x) / 2) : abs(goal.p_x - next.p_x), abs(goal.p_y - next.p_y));
		break;
	case COST_TOTAL_HEURISTIC:
		//cost_heuristic calculated as:
		//If HEX GRID - XDIFF = ABS((x2 - x1)/2), YDIFF = ABS(y2 - y1).
		//If SQUARE GRID - XDIFF = ABS(x2 - x1), YDIFF = ABS(y2 - y1).
		cost_heuristic[next.p_x][next.p_y] = Heuristic(hType, (gridType == HEX_GRID) ? abs((goal.p_x - next.p_x) / 2) : abs(goal.p_x - next.p_x), abs(goal.p_y - next.p_y));

		//TOTAL cost.
		//cost_total = cost_so_far + cost_heuristic.
		next.posCost = cost_total[next.p_x][next.p_y] = cost_so_far[next.p_x][next.p_y] + cost_heuristic[next.p_x][next.p_y];
		break;
	}

	//Find the stringified form of EXACT, HEURISTIC, and TOTAL cost.
	std::string costInString = to_string_with_precision(cost_so_far[next.p_x][next.p_y], 2);
	std::string costHeuInString = to_string_with_precision(cost_heuristic[next.p_x][next.p_y], 2);
	std::string costTotInString = to_string_with_precision(cost_total[next.p_x][next.p_y], 2);

	//Ultimately, initialize all the different types of printable maps.
	Initializer(next.p_x, next.p_y, NEXT, dir, NULL, const_cast<char*>(costInString.c_str()), NULL, const_cast<char*>(costHeuInString.c_str()), NULL, const_cast<char*>(costTotInString.c_str()), NULL);
		
}

/*
Retracing the goal path found from goal back to the start.
Parameters to the function:
algoType : const PathfindingAlgo & - the algorithm type.
goalPath : std::vector<Position> & - the goal path vector that stores the positions from start to goal.
npStart : const Position & - the starting position.
npGoal : const Position & - the goal position.
Returns from the function:
NONE
This function finds the path back from the goal to the start position and saves it in a vector.
*/
void RetraceGoalPath(const PathfindingAlgo & algoType, std::vector<Position> & goalPath, const Position & npStart, const Position & npGoal)
{
	//Now, traverse backwards from goal to start to save the goal path in a vector.
	Position currentTraverse = npGoal;

	//Empty the goal path vector completely!
	goalPath.clear();

	//Set the mapGoalCost(goal) = mapCost(goal).
	mapGoalCost[npGoal.p_x][npGoal.p_y] = mapCost[npGoal.p_x][npGoal.p_y];

	//The heuristic costs get updated only if the algorithm is Greedy or AStar.
	if (algoType == PathfindingAlgo::ALGO_GREEDY || algoType == PathfindingAlgo::ALGO_ASTAR)
	{
		//Set the mapGoalHeuCost(goal) = mapHeuCost(goal).
		mapGoalHeuCost[npGoal.p_x][npGoal.p_y] = mapGoalHeuCost[npGoal.p_x][npGoal.p_y];
	}

	//The total costs get updated only if the algorithm is AStar.
	if (algoType == PathfindingAlgo::ALGO_ASTAR)
	{
		//Set the mapGoalTotCost(goal) = mapTotCost(goal).
		mapGoalTotCost[npGoal.p_x][npGoal.p_y] = mapTotCost[npGoal.p_x][npGoal.p_y];
	}

	//Set the current traverse position's cost to cost_so_far's value at that position to show the gradual increase in the cost.
	currentTraverse.posCost = cost_so_far[currentTraverse.p_x][currentTraverse.p_y];

	//Add the goal position to the goal path vector.
	goalPath.push_back(currentTraverse);

	//Until, we cannot trace back to the start position, we keep repeating the process of updating the current position.
	while (currentTraverse != npStart)
	{
		//mapGoalPath(currentTraverse) = mapCameFrom(currentTraverse).
		//Basically, find the previous position from where we reached to the current position.
		mapGoalPath[currentTraverse.p_x][currentTraverse.p_y] = mapCameFrom[currentTraverse.p_x][currentTraverse.p_y];

		//mapGoalCost(currentTraverse) = mapCost(currentTraverse).
		//Then update the map goal cost with the calculated map cost.
		mapGoalCost[currentTraverse.p_x][currentTraverse.p_y] = mapCost[currentTraverse.p_x][currentTraverse.p_y];

		//The heuristic costs get updated only if the algorithm is Greedy or AStar.
		if (algoType == PathfindingAlgo::ALGO_GREEDY || algoType == PathfindingAlgo::ALGO_ASTAR)
		{
			//Set mapGoalHeuCost(currentTraverse) = mapHeuCost(currentTraverse).
			mapGoalHeuCost[currentTraverse.p_x][currentTraverse.p_y] = mapHeuCost[currentTraverse.p_x][currentTraverse.p_y];
		}

		//The total costs get updated only if the algorithm is AStar.
		if (algoType == PathfindingAlgo::ALGO_ASTAR)
		{
			//Set the mapGoalTotCost(currentTraverse) = mapTotCost(currentTraverse).
			mapGoalTotCost[currentTraverse.p_x][currentTraverse.p_y] = mapTotCost[currentTraverse.p_x][currentTraverse.p_y];
		}

		//Update currentTraverse to point to the previous position from whence it came.
		currentTraverse = came_from[currentTraverse.p_x][currentTraverse.p_y];

		//Set the current traverse position's cost to cost_so_far's value at that position to show the gradual increase in the cost.
		currentTraverse.posCost = cost_so_far[currentTraverse.p_x][currentTraverse.p_y];

		//Add currentTraverse to the goal path vector.
		goalPath.push_back(currentTraverse);
	}

	//Reverse the whole vector to contain the whole list.
	std::reverse(goalPath.begin(), goalPath.end());
}

/*
Check if a position is a wall.
Parameters to the function:
actual : const Position & - The origin value.
offset : const Position & - The offset to be added.
Returns from the function:
isWall : bool - The check for if it is a wall.
This function takes in an origin and an offset, joins them together to find the position for which it finds if the position is a wall. Then it returns true, if wall, and false, otherwise.
*/
bool /*isWall*/ IsWallCheck(const Position & origin, const Position & offset)
{
	//If not a wall, return false.
	if (mapVisited[origin.p_x + offset.p_x][origin.p_y + offset.p_y] != WALL)
		return false;

	//If wall, return true.
	return true;
}
#endif