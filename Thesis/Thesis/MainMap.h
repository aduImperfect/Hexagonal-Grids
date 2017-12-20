///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: MainMap.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef MAIN_MAP_H
#define MAIN_MAP_H
//Including the different base path-finding algorithms headers (they contain the includes to the square and hex headers internally!).
#include "BaseBFS.h"
#include "BaseDijkstra.h"
#include "BaseGreedy.h"
#include "BaseAStar.h"
#include "BaseBlockAStar.h"
#include "SquareLDDBToFile.h"
#include "EgressCellsInitializer.h"
#include "EgressCellsToFile.h"

/*
Square Map pre-computations.
Parameters to the function:
algoType : const int - the algorithm type.
nposStart : const Position - the starting position.
nposGoal : const Position - the goal position.
showMap : const int - the map should be shown (printed) or not.
Returns from the function:
NONE
This function calls the required initializers and generators to generate the square grid based on the type of the algorithm with the start and goal positions and values set and return nothing.
*/
void SquareMap(const int algoType, const Position nposStart, const Position nposGoal, const int showMap)
{
	switch (algoType)
	{
	case PathfindingAlgo::ALGO_BFS:
		InitializeFirstSquare(EMPTY_COST_SPACE);
		GenerateSquare(nposStart, nposGoal);
		
		if (showMap == 0)
			break;
		PrintSquareMapGeneric(MapVisualType::MAP_VISITED);
		PrintSquareMapGeneric(MapVisualType::MAP_CAMEFROM);
		PrintSquareMapGeneric(MapVisualType::MAP_COST);
		break;
	case PathfindingAlgo::ALGO_DIJKSTRA:
		InitializeFirstSquare(COST_MAX_TERM);
		GenerateSquare(nposStart, nposGoal);
		
		if (showMap == 0)
			break;
		PrintSquareMapGeneric(MapVisualType::MAP_VISITED);
		PrintSquareMapGeneric(MapVisualType::MAP_CAMEFROM);
		PrintSquareMapGeneric(MapVisualType::MAP_COST);
		break;
	case PathfindingAlgo::ALGO_GREEDY:
		InitializeFirstSquare(COST_MAX_TERM);
		GenerateSquare(nposStart, nposGoal);
		
		if (showMap == 0)
			break;
		PrintSquareMapGeneric(MapVisualType::MAP_VISITED);
		PrintSquareMapGeneric(MapVisualType::MAP_CAMEFROM);
		PrintSquareMapGeneric(MapVisualType::MAP_COST);
		PrintSquareMapGeneric(MapVisualType::MAP_HEUCOST);
		break;
	case PathfindingAlgo::ALGO_ASTAR:
		InitializeFirstSquare(COST_MAX_TERM);
		GenerateSquare(nposStart, nposGoal);

		if (showMap == 0)
			break;
		PrintSquareMapGeneric(MapVisualType::MAP_VISITED);
		PrintSquareMapGeneric(MapVisualType::MAP_CAMEFROM);
		PrintSquareMapGeneric(MapVisualType::MAP_COST);
		PrintSquareMapGeneric(MapVisualType::MAP_HEUCOST);
		PrintSquareMapGeneric(MapVisualType::MAP_TOTALCOST);
		break;
	case PathfindingAlgo::ALGO_BLOCKASTAR:
		InitializeFirstSquare(COST_MAX_TERM);
		GenerateSquare(nposStart, nposGoal);

		if (showMap == 1)
		{
			PrintSquareMapGeneric(MapVisualType::MAP_VISITED);
			PrintSquareMapGeneric(MapVisualType::MAP_CAMEFROM);
			PrintSquareMapGeneric(MapVisualType::MAP_COST);
			PrintSquareMapGeneric(MapVisualType::MAP_HEUCOST);
			PrintSquareMapGeneric(MapVisualType::MAP_TOTALCOST);
		}

		SquareLDDBInitializer();
		SquareLDDBCalc();

		//A print confirming that the LDDB calculation ran without any errors/bugs by reaching this state.
		printf("\nSquare LDDB Calculated!!\n");

		//Write the calculated LDDB to two types of files.
		WriteSquareLDDBToFile();
		WriteSquareLDDBToFileAlternate();

		//A print confirming that the writing to files ran without any errors/bugs by reaching this state.
		printf("\nSquare LDDB written to file!!\n");

		EgressCellsInitialize();

		//A print confirming that the Egress cells Initializations ran without any errors/bugs by reaching this state.
		printf("\nEgress cells Calculated!!\n");

		WriteEgressCellsToFile();

		//A print confirming that the writing to files ran without any errors/bugs by reaching this state.
		printf("\nEgress cells written to file!!\n");
		break;
	case PathfindingAlgo::ALGO_JPS:
		break;
	}
}

/*
Hex Map pre-computations.
Parameters to the function:
algoType : const int - the algorithm type.
nposStart : const Position - the starting position.
nposGoal : const Position - the goal position.
showMap : const int - the map should be shown (printed) or not.
Returns from the function:
NONE
This function calls the required initializers and generators to generate the hex grid based on the type of the algorithm with the start and goal positions and values set and return nothing.
*/
void HexMap(const int algoType, const Position nposStart, const Position nposGoal, const int showMap)
{
	switch (algoType)
	{
	case PathfindingAlgo::ALGO_BFS:
		InitializeFirstHex(EMPTY_COST_SPACE);
		GenerateHex(nposStart, nposGoal);
		
		if (showMap == 0)
			break;
		PrintHexMapGeneric(MapVisualType::MAP_VISITED);
		PrintHexMapGeneric(MapVisualType::MAP_CAMEFROM);
		PrintHexMapGeneric(MapVisualType::MAP_COST);
		break;
	case PathfindingAlgo::ALGO_DIJKSTRA:
		InitializeFirstHex(COST_MAX_TERM);
		GenerateHex(nposStart, nposGoal);
		
		if (showMap == 0)
			break;
		PrintHexMapGeneric(MapVisualType::MAP_VISITED);
		PrintHexMapGeneric(MapVisualType::MAP_CAMEFROM);
		PrintHexMapGeneric(MapVisualType::MAP_COST);
		break;
	case PathfindingAlgo::ALGO_GREEDY:
		InitializeFirstHex(COST_MAX_TERM);
		GenerateHex(nposStart, nposGoal);
		
		if (showMap == 0)
			break;
		PrintHexMapGeneric(MapVisualType::MAP_VISITED);
		PrintHexMapGeneric(MapVisualType::MAP_CAMEFROM);
		PrintHexMapGeneric(MapVisualType::MAP_COST);
		PrintHexMapGeneric(MapVisualType::MAP_HEUCOST);
		break;
	case PathfindingAlgo::ALGO_ASTAR:
		InitializeFirstHex(COST_MAX_TERM);
		GenerateHex(nposStart, nposGoal);
		
		if (showMap == 0)
			break;
		PrintHexMapGeneric(MapVisualType::MAP_VISITED);
		PrintHexMapGeneric(MapVisualType::MAP_CAMEFROM);
		PrintHexMapGeneric(MapVisualType::MAP_COST);
		PrintHexMapGeneric(MapVisualType::MAP_HEUCOST);
		PrintHexMapGeneric(MapVisualType::MAP_TOTALCOST);
		break;
	case PathfindingAlgo::ALGO_BLOCKASTAR:
		break;
	case PathfindingAlgo::ALGO_JPS:
		break;
	}
}

/*
Map pre-computations.
Parameters to the function:
gridSpace : const int - The type of grid space: Square or Hex.
algoType : const int - the algorithm type.
nposStart : const Position - the starting position.
nposGoal : const Position - the goal position.
showMap : const int - the map should be shown (printed) or not.
Returns from the function:
NONE
This function calls the required gridSpace Map generation function and passes in the algorithm type along with the start and goal positions, and the showMap value and returns nothing.
*/
void Map(const int gridSpace, const int algoType, const Position nposStart, const Position nposGoal, const int showMap)
{
	//If its a square grid then compute the square grid elements and early exit.
	if (gridSpace == SQUARE_GRID)
	{
		SquareMap(algoType, nposStart, nposGoal, showMap);
		return;
	}

	//Otherwise, compute for the hex map elements.
	HexMap(algoType, nposStart, nposGoal, showMap);
}

/*
Running the square grid path-finding algorithms.
Parameters to the function:
algoType : const int - the algorithm type.
nposStart : const Position - the starting position.
nposGoal : const Position - the goal position.
topLeft : const Position - the top left most position of the square grid.
bottomRight : const Position - the bottom right most position of the square grid.
showMap : const int - the map should be shown (printed) or not.
goalPath : std::vector<Position> - the goal path vector that contains the position list from where the goal came from by starting at the start position.
Returns from the function:
goalCost : double - the cost to reach the goal.
This function calls the required search space algorithms for a square grid based on the algorithm type and passes in the start and goal positions along with the top left and bottom right corner positions of the square grid to give it a bound on its size.
It then returns the cost to reach the goal.
*/
double /*goalCost*/ RunPathfindingOnSquare(const int algoType, const Position nposStart, const Position nposGoal, const Position topLeft, const Position bottomRight, const int showMap, std::vector<Position> & goalPath)
{
	double gCost = -1;
	switch (algoType)
	{
	case PathfindingAlgo::ALGO_BFS:
		gCost = SquareBFS(nposStart, nposGoal, false, topLeft, bottomRight, showMap, goalPath);
		break;
	case PathfindingAlgo::ALGO_DIJKSTRA:
		gCost = SquareDijkstra(nposStart, nposGoal, false, topLeft, bottomRight, showMap, goalPath);
		break;
	case PathfindingAlgo::ALGO_GREEDY:
		gCost = SquareGreedy(nposStart, nposGoal, false, topLeft, bottomRight, showMap, goalPath);
		break;
	case PathfindingAlgo::ALGO_ASTAR:
		gCost = SquareAStar(nposStart, nposGoal, false, topLeft, bottomRight, showMap, goalPath);
		break;
	case PathfindingAlgo::ALGO_BLOCKASTAR:
		gCost = SquareBlockAStar(nposStart, nposGoal, false, topLeft, bottomRight, showMap, goalPath);
		break;
	case PathfindingAlgo::ALGO_JPS:
		break;
	}

	//Return the cost of reaching the goal.
	return gCost;
}

/*
Running the hex grid path-finding algorithms.
Parameters to the function:
algoType : const int - the algorithm type.
nposStart : const Position - the starting position.
nposGoal : const Position - the goal position.
center : const Position - the center position of the hex grid.
perimeter : const Position - the perimeter of the hex grid.
showMap : const int - the map should be shown (printed) or not.
goalPath : std::vector<Position> - the goal path vector that contains the position list from where the goal came from by starting at the start position.
Returns from the function:
goalCost : double - the cost to reach the goal.
This function calls the required search space algorithms for a hex grid based on the algorithm type and passes in the start and goal positions along with the center position and the total perimeter span of the hex grid to give it a bound on its size.
It then returns the cost to reach the goal.
*/
double /*goalCost*/ RunPathfindingOnHex(const int algoType, const Position nposStart, const Position nposGoal, const Position center, const unsigned int perimeter, const int showMap, std::vector<Position> & goalPath)
{
	double gCost = -1;
	switch (algoType)
	{
	case PathfindingAlgo::ALGO_BFS:
		gCost = HexBFS(nposStart, nposGoal, false, center, perimeter, showMap, goalPath);
		break;
	case PathfindingAlgo::ALGO_DIJKSTRA:
		gCost = HexDijkstra(nposStart, nposGoal, false, center, perimeter, showMap, goalPath);
		break;
	case PathfindingAlgo::ALGO_GREEDY:
		gCost = HexGreedy(nposStart, nposGoal, false, center, perimeter, showMap, goalPath);
		break;
	case PathfindingAlgo::ALGO_ASTAR:
		gCost = HexAStar(nposStart, nposGoal, false, center, perimeter, showMap, goalPath);
		break;
	case PathfindingAlgo::ALGO_BLOCKASTAR:
		break;
	case PathfindingAlgo::ALGO_JPS:
		break;
	}

	//Return the cost of reaching the goal.
	return gCost;
}

/*
Running the grid path-finding algorithms.
Parameters to the function:
gridSpace : const int - The type of grid space: Square or Hex.
algoType : const int - the algorithm type.
nposStart : const Position - the starting position.
nposGoal : const Position - the goal position.
showMap : const int - the map should be shown (printed) or not.
goalPath : std::vector<Position> - the goal path vector that contains the position list from where the goal came from by starting at the start position.
Returns from the function:
goalCost : double - the cost to reach the goal.
This function calls the required grid space path-finding function based on the gridSpace type and passes in the algorithm type, the start and goal positions, and the size limiter values for the type of grids (topLeft and bottomRight for square grid, and center and perimeter for hex grid).
It then returns the cost to reach the goal.
*/
double /*goalCost*/ RunPathfinding(const int gridSpace, const int algoType, const Position nposStart, const Position nposGoal, const int showMap, std::vector<Position> & goalPath)
{
	if (gridSpace == SQUARE_GRID)
		return RunPathfindingOnSquare(algoType, nposStart, nposGoal, Position(0, 0), Position(SQUARE_BOTTOM_RIGHT, SQUARE_BOTTOM_RIGHT), showMap, goalPath);

	return RunPathfindingOnHex(algoType, nposStart, nposGoal, Position(HEX_CENTER, HEX_CENTER), 30, showMap, goalPath);
}
#endif