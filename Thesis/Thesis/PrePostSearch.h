///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: PrePostSearch.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef PRE_POST_SEARCH_H
#define PRE_POST_SEARCH_H
//Including the header for position structure.
#include "Position.h"
#include "BaseSquareOperations.h"
#include "BaseHexOperations.h"

/*
The allocations or checks before the main search loop.
Parameters to the function:
queueType : T & - the type of queue (a normal queue, or a priority queue).
npStart : Position & - the starting position.
npGoal : const Position & - the goal position.
topLeft : const Position & - the top left position of the square grid.
bottomRight : const Position & - the bottom right position of the square grid.
nCost : const double & - the initializer cost.
Returns from the function:
isValid : bool - the check that tells us if the pre-search allocations and checks are valid or not.
This function runs the allocations, and boundary checks needed to be done before running the main loop.
*/
template<typename T>
bool /*isValid*/ SquarePreSearch(T & queueType, Position & npStart, const Position & npGoal, const Position & topLeft, const Position & bottomRight, const double & nCost)
{
	//If the start node is outside of the range of the square grid (topLeft, bottomRight) then no goal found.
	if (SquareIsOutside(npStart, topLeft, bottomRight))
		return false;

	//If the goal node is outside of the range of the square grid (topLeft, bottomRight) then no goal found.
	if (SquareIsOutside(npGoal, topLeft, bottomRight))
		return false;

	//Popping out all the previous elements from the queue to clear the whole queue for a new algo run.
	while (!queueType.empty())
	{
		queueType.pop();
	}

	//Set the 2D array storages with default values having the initial costs of the cost_so_far, cost_heuristic, and cost_total set.
	InitializeVCC(SQUARE_GRID, nCost);

	//Set the position cost of the starting position to be equal to the cost_so_far at the starting position which is set.
	npStart.posCost = cost_so_far[npStart.p_x][npStart.p_y] = 0.00f;

	//Push starting position into the queue.
	queueType.push(npStart);

	//Set the visited(start) to true. Stating that start has been visited already.
	visited[npStart.p_x][npStart.p_y] = true;

	//As there is no other position existing before start from where the algo started, we set the came_from(start) = start.
	came_from[npStart.p_x][npStart.p_y] = npStart;

	//We check to see if the map of the visited nodes has a WALL in the starting position, then no goal found.
	if (mapVisited[npStart.p_x][npStart.p_y] == WALL)
		return false;

	//We check to see if the map of the visited nodes has a WALL in the goal position, then no goal found.
	if (mapVisited[npGoal.p_x][npGoal.p_y] == WALL)
		return false;

	return true;
}

/*
The allocations or checks before the main search loop.
Parameters to the function:
queueType : T & - the type of queue (a normal queue, or a priority queue).
npStart : Position & - the starting position.
npGoal : const Position & - the goal position.
center : const Position & - the center position of the hex grid.
perimeter : const Position & - the perimeter of the hex grid.
nCost : const double & - the initializer cost.
Returns from the function:
isValid : bool - the check that tells us if the pre-search allocations and checks are valid or not.
This function runs the allocations, and boundary checks needed to be done before running the main loop.
*/
template<typename T>
bool /*isValid*/ HexPreSearch(T & queueType, Position & npStart, const Position & npGoal, const Position & center, const int & perimeter, const double & nCost)
{
	//If the start node is outside of the range of the hex grid (center, perimeter) then no goal found.
	if (HexIsOutside(npStart, center, perimeter))
		return false;

	//If the goal node is outside of the range of the hex grid (center, perimeter) then no goal found.
	if (HexIsOutside(npGoal, center, perimeter))
		return false;

	//Popping out all the previous elements from the queue to clear the whole queue for a new algo run.
	while (!queueType.empty())
	{
		queueType.pop();
	}

	//Set the 2D array storages with default values having the initial costs of the cost_so_far, cost_heuristic, and cost_total set.
	InitializeVCC(HEX_GRID + 1, nCost);

	//Set the position cost of the starting position to be equal to the cost_so_far at the starting position which is set.
	npStart.posCost = cost_so_far[npStart.p_x][npStart.p_y] = 0.00f;

	//Push starting position into the queue.
	queueType.push(npStart);

	//Set the visited(start) to true. Stating that start has been visited already.
	visited[npStart.p_x][npStart.p_y] = true;

	//As there is no other position existing before start from where the algo started, we set the came_from(start) = start.
	came_from[npStart.p_x][npStart.p_y] = npStart;

	//We check to see if the map of the visited nodes has a WALL in the starting position, then no goal found.
	if (mapVisited[npStart.p_x][npStart.p_y] == WALL)
		return false;

	//We check to see if the map of the visited nodes has a WALL in the goal position, then no goal found.
	if (mapVisited[npGoal.p_x][npGoal.p_y] == WALL)
		return false;

	return true;
}

/*
The post search functionalities.
Parameters to the function:
algoType : const PathfindingAlgo & - the type of algorithm.
mCost : const std::string & - the string value to be passed into the mapCost(goal).
npStart : Position & - the starting position.
npGoal : const Position & - the goal position.
goalPath : std::vector<Position> & - the goal path to be formed.
generateInstantaneous : const bool & - the check to see if the grid is being generated step by step or instantaneously.
autoCompute : const bool & - a secondary layer check on the path-finding algorithm to make it run step by step or instantly.
showMap : const int & - the value based on which its decided to print all the maps or not.
Returns from the function:
isValid : bool - the check that tells us if the post-search functionalities and checks are valid or not.
This function runs the functionalities post-search, and boundary checks needed to be done after running the main loop.
*/
bool /*isValid*/ SquarePostSearch(const PathfindingAlgo & algoType, const std::string & mCost, const Position & npStart, const Position & npGoal, std::vector<Position> & goalPath, const bool & generateInstantaneous, const bool & autoCompute, const int & showMap)
{

	//If the cost at the goal is empty or the goal has not been visited yet, the goal point was not found.
	if ((mapCost[npGoal.p_x][npGoal.p_y] == mCost) || (!visited[npGoal.p_x][npGoal.p_y]))
	{
		return false;
	}

	//Retrace the goal path from goal to start.
	RetraceGoalPath(algoType, goalPath, npStart, npGoal);

	//If generate instantaneous is on or auto compute is not on.
	if (generateInstantaneous || !autoCompute)
	{
		//If printing of the map is allowed.
		if (showMap == 1)
		{
			//Generate the square grid and print the various types of visited, came_from, goal_path, cost, and goal_cost, heuristic cost, goal heuristic cost, total cost, and goal total cost square grids.
			GenerateSquare(npStart, npGoal);
			PrintSquareMapGeneric(MapVisualType::MAP_VISITED);
			PrintSquareMapGeneric(MapVisualType::MAP_CAMEFROM);
			PrintSquareMapGeneric(MapVisualType::MAP_GOALPATH);
			PrintSquareMapGeneric(MapVisualType::MAP_COST);
			PrintSquareMapGeneric(MapVisualType::MAP_GOALCOST);

			if (algoType == PathfindingAlgo::ALGO_GREEDY || algoType == PathfindingAlgo::ALGO_ASTAR)
			{
				PrintSquareMapGeneric(MapVisualType::MAP_HEUCOST);
				PrintSquareMapGeneric(MapVisualType::MAP_GOALHEUCOST);
			}

			if (algoType == PathfindingAlgo::ALGO_ASTAR)
			{
				PrintSquareMapGeneric(MapVisualType::MAP_TOTALCOST);
				PrintSquareMapGeneric(MapVisualType::MAP_GOALTOTALCOST);
			}
		}
	}

	return true;
}

/*
The post search functionalities.
Parameters to the function:
algoType : const PathfindingAlgo & - the type of algorithm.
mCost : const std::string & - the string value to be passed into the mapCost(goal).
npStart : Position & - the starting position.
npGoal : const Position & - the goal position.
goalPath : std::vector<Position> & - the goal path to be formed.
generateInstantaneous : const bool & - the check to see if the grid is being generated step by step or instantaneously.
autoCompute : const bool & - a secondary layer check on the path-finding algorithm to make it run step by step or instantly.
showMap : const int & - the value based on which its decided to print all the maps or not.
Returns from the function:
isValid : bool - the check that tells us if the post-search functionalities and checks are valid or not.
This function runs the functionalities post-search, and boundary checks needed to be done after running the main loop.
*/
bool /*isValid*/ HexPostSearch(const PathfindingAlgo & algoType, const std::string & mCost, const Position & npStart, const Position & npGoal, std::vector<Position> & goalPath, const bool & generateInstantaneous, const bool & autoCompute, const int & showMap)
{

	//If the cost at the goal is empty or the goal has not been visited yet, the goal point was not found.
	if ((mapCost[npGoal.p_x][npGoal.p_y] == mCost) || (!visited[npGoal.p_x][npGoal.p_y]))
	{
		return false;
	}

	//Retrace the goal path from goal to start.
	RetraceGoalPath(algoType, goalPath, npStart, npGoal);

	//If generate instantaneous is on or auto compute is not on.
	if (generateInstantaneous || !autoCompute)
	{
		//If printing of the map is allowed.
		if (showMap == 1)
		{
			//Generate the hex grid and print the various types of visited, came_from, goal_path, cost, and goal_cost, heuristic cost, goal heuristic cost, total cost, and goal total cost hex grids.
			GenerateHex(npStart, npGoal);
			PrintHexMapGeneric(MapVisualType::MAP_VISITED);
			PrintHexMapGeneric(MapVisualType::MAP_CAMEFROM);
			PrintHexMapGeneric(MapVisualType::MAP_GOALPATH);
			PrintHexMapGeneric(MapVisualType::MAP_COST);
			PrintHexMapGeneric(MapVisualType::MAP_GOALCOST);

			if (algoType == PathfindingAlgo::ALGO_GREEDY || algoType == PathfindingAlgo::ALGO_ASTAR)
			{
				PrintHexMapGeneric(MapVisualType::MAP_HEUCOST);
				PrintHexMapGeneric(MapVisualType::MAP_GOALHEUCOST);
			}

			if (algoType == PathfindingAlgo::ALGO_ASTAR)
			{
				PrintHexMapGeneric(MapVisualType::MAP_TOTALCOST);
				PrintHexMapGeneric(MapVisualType::MAP_GOALTOTALCOST);
			}
		}
	}

	return true;
}
#endif