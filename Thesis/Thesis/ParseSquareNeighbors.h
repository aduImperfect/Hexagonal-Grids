///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017-2018 DigiPen Institute of Technology, all rights reserved
/// FILE: ParseSquareNeighbors.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef PARSE_SQUARE_NEIGHBORS_H
#define PARSE_SQUARE_NEIGHBORS_H
//Including the header for position structure.
#include "Position.h"

/*
Parse through all the neighbors of a position in a square grid.
Parameters to the function:
queueType : T & - the type of queue, a normal queue or a priority queue (being used as).
algoType : const PathfindingAlgo & - the algorithm type wherein the neighbors of a position are being parsed.
current : Position - the current position being used here to generate the 8 neighbor position internally.
npGoal : const Position & - the goal position.
topLeft : const Position & - the top left position of the square grid.
bottomRight : const Position & - the bottom right position of the square grid.
costType : const CostType & - the type of cost associated with the path-finding algorithm.
heuType : const HeuristicType & - the type of heuristic associated with the path-finding algorithm.
Returns from the function:
NONE
This function makes internal neighbor position based on the current position in the 8 directions and has different checks associated with them (walls, visited, and outside checks). Then based on the type of algorithm, it is found which of the 8 different paths are valid neighbors. Based on their validity, the data is passed forward to the NextChildAssignments call for each direction (to add them to the queue). This function returns nothing.
*/
template<typename T>
void ParseSquareNeighbors(T & queueType, const PathfindingAlgo & algoType, Position current, const Position & npGoal, const Position & topLeft, const Position & bottomRight, const CostType & costType, const HeuristicType & heuType)
{
#pragma region NEIGHBOR_POSITIONS
	//The neighbors of the current position. (N, NE, E, SE, S, SW, W, NW).

	//currentNorth = (current.x - 1, current.y + 0).
	Position currentNorth = current + pos_SQUARENORTH;

	//currentNorthEast = (current.x - 1, current.y + 1).
	Position currentNorthEast = current + pos_SQUARENORTHEAST;

	//currentEast = (current.x + 0, current.y + 1).
	Position currentEast = current + pos_SQUAREEAST;

	//currentSouthEast = (current.x + 1, current.y + 1).
	Position currentSouthEast = current + pos_SQUARESOUTHEAST;

	//currentSouth = (current.x + 1, current.y + 0).
	Position currentSouth = current + pos_SQUARESOUTH;

	//currentSouthWest = (current.x + 1, current.y - 1).
	Position currentSouthWest = current + pos_SQUARESOUTHWEST;

	//currentWest = (current.x + 0, current.y - 1).
	Position currentWest = current + pos_SQUAREWEST;

	//currentNorthWest = (current.x - 1, current.y - 1).
	Position currentNorthWest = current + pos_SQUARENORTHWEST;
#pragma endregion

#pragma region IS_WALL_CHECKS
	//Checks to see if any of the directions are a wall.
	bool isNorthWall = mapVisited[currentNorth.p_x][currentNorth.p_y] == WALL;
	bool isNorthEastWall = mapVisited[currentNorthEast.p_x][currentNorthEast.p_y] == WALL;
	bool isEastWall = mapVisited[currentEast.p_x][currentEast.p_y] == WALL;
	bool isSouthEastWall = mapVisited[currentSouthEast.p_x][currentSouthEast.p_y] == WALL;
	bool isSouthWall = mapVisited[currentSouth.p_x][currentSouth.p_y] == WALL;
	bool isSouthWestWall = mapVisited[currentSouthWest.p_x][currentSouthWest.p_y] == WALL;
	bool isWestWall = mapVisited[currentWest.p_x][currentWest.p_y] == WALL;
	bool isNorthWestWall = mapVisited[currentNorthWest.p_x][currentNorthWest.p_y] == WALL;
#pragma endregion

#pragma region IS_VISITED_CHECKS
	//Checks to see if any of the directions have been visited.
	bool isNorthVisited = visited[currentNorth.p_x][currentNorth.p_y];
	bool isNorthEastVisited = visited[currentNorthEast.p_x][currentNorthEast.p_y];
	bool isEastVisited = visited[currentEast.p_x][currentEast.p_y];
	bool isSouthEastVisited = visited[currentSouthEast.p_x][currentSouthEast.p_y];
	bool isSouthVisited = visited[currentSouth.p_x][currentSouth.p_y];
	bool isSouthWestVisited = visited[currentSouthWest.p_x][currentSouthWest.p_y];
	bool isWestVisited = visited[currentWest.p_x][currentWest.p_y];
	bool isNorthWestVisited = visited[currentNorthWest.p_x][currentNorthWest.p_y];
#pragma endregion

#pragma region IS_OUTSIDE_CHECKS
	//Checks to see if any of the directions are outside the grid.
	bool isNorthOutside = SquareIsOutside(currentNorth, topLeft, bottomRight);
	bool isNorthEastOutside = SquareIsOutside(currentNorthEast, topLeft, bottomRight);
	bool isEastOutside = SquareIsOutside(currentEast, topLeft, bottomRight);
	bool isSouthEastOutside = SquareIsOutside(currentSouthEast, topLeft, bottomRight);
	bool isSouthOutside = SquareIsOutside(currentSouth, topLeft, bottomRight);
	bool isSouthWestOutside = SquareIsOutside(currentSouthWest, topLeft, bottomRight);
	bool isWestOutside = SquareIsOutside(currentWest, topLeft, bottomRight);
	bool isNorthWestOutside = SquareIsOutside(currentNorthWest, topLeft, bottomRight);
#pragma endregion

#pragma region IS_VALID_CHECK_INITIALIZERS
	//Checks to see if any of the directions are valid children.
	bool isNorthNeighborValid = false;
	bool isNorthEastNeighborValid = false;
	bool isEastNeighborValid = false;
	bool isSouthEastNeighborValid = false;
	bool isSouthNeighborValid = false;
	bool isSouthWestNeighborValid = false;
	bool isWestNeighborValid = false;
	bool isNorthWestNeighborValid = false;
#pragma endregion

#pragma region IS_VALID_CHECK_BFS_GREEDY
	//If the algorithm is BFS or GREEDY.
	if ((algoType == PathfindingAlgo::ALGO_BFS) || (algoType == PathfindingAlgo::ALGO_GREEDY))
	{
		//NorthValid = If north has not been visited and north is not outside the grid.
		isNorthNeighborValid = ((!isNorthVisited) && (!isNorthOutside));

		//NorthEastValid = If north is not a wall and east is not a wall and, in addition, if northeast is not been visited and northeast is not outside the grid.
		isNorthEastNeighborValid = (((!isNorthWall) && (!isEastWall)) && ((!isNorthEastVisited) && (!isNorthEastOutside)));
		
		//EastValid = If east has not been visited and east is not outside the grid.
		isEastNeighborValid = ((!isEastVisited) && (!isEastOutside));
		
		//SouthEastValid = If south is not a wall and east is not a wall and, in addition, if southeast is not been visited and southeast is not outside the grid.
		isSouthEastNeighborValid = (((!isSouthWall) && (!isEastWall)) && ((!isSouthEastVisited) && (!isSouthEastOutside)));

		//SouthValid = If south has not been visited and south is not outside the grid.
		isSouthNeighborValid = ((!isSouthVisited) && (!isSouthOutside));

		//SouthWestValid = If south is not a wall and west is not a wall and, in addition, if southwest is not been visited and southwest is not outside the grid.
		isSouthWestNeighborValid = (((!isSouthWall) && (!isWestWall)) && ((!isSouthWestVisited) && (!isSouthWestOutside)));

		//WestValid = If west has not been visited and west is not outside the grid.
		isWestNeighborValid = ((!isWestVisited) && (!isWestOutside));

		//NorthWestValid = If north is not a wall and west is not a wall and, in addition, if northwest is not been visited and northwest is not outside the grid.
		isNorthWestNeighborValid = (((!isNorthWall) && (!isWestWall)) && ((!isNorthWestVisited) && (!isNorthWestOutside)));
	}
#pragma endregion

#pragma region IS_VALID_CHECK_DIJKSTRA_ASTAR
	//If the algorithm is DIJKSTRA or ASTAR.
	else if ((algoType == PathfindingAlgo::ALGO_DIJKSTRA) || (algoType == PathfindingAlgo::ALGO_ASTAR))
	{
		//The new calculated cost_so_far for the neighbor (in axis).
		double newCostAxis = cost_so_far[current.p_x][current.p_y] + COST_AXIS;

		//The new calculated cost_so_far for the neighbor (in diagonal).
		double newCostDiagonal = cost_so_far[current.p_x][current.p_y] + COST_DIAGONAL;

#pragma region IS_CHANGED_CHECKS
		//If north cost changed = if the new axis cost is less than the cost stored for north.
		bool isNorthCostChanged = (newCostAxis < cost_so_far[currentNorth.p_x][currentNorth.p_y]);

		//If northeast cost changed = if the new diagonal cost is less than the cost stored for northeast.
		bool isNorthEastCostChanged = (newCostDiagonal < cost_so_far[currentNorthEast.p_x][currentNorthEast.p_y]);

		//If east cost changed = if the new axis cost is less than the cost stored for east.
		bool isEastCostChanged = (newCostAxis < cost_so_far[currentEast.p_x][currentEast.p_y]);

		//If southeast cost changed = if the new diagonal cost is less than the cost stored for southeast.
		bool isSouthEastCostChanged = (newCostDiagonal < cost_so_far[currentSouthEast.p_x][currentSouthEast.p_y]);

		//If south cost changed = if the new axis cost is less than the cost stored for south.
		bool isSouthCostChanged = (newCostAxis < cost_so_far[currentSouth.p_x][currentSouth.p_y]);

		//If southwest cost changed = if the new diagonal cost is less than the cost stored for southwest.
		bool isSouthWestCostChanged = (newCostDiagonal < cost_so_far[currentSouthWest.p_x][currentSouthWest.p_y]);

		//If west cost changed = if the new axis cost is less than the cost stored for west.
		bool isWestCostChanged = (newCostAxis < cost_so_far[currentWest.p_x][currentWest.p_y]);

		//If northwest cost changed = if the new diagonal cost is less than the cost stored for northwest.
		bool isNorthWestCostChanged = (newCostDiagonal < cost_so_far[currentNorthWest.p_x][currentNorthWest.p_y]);
#pragma endregion

		//NorthValid = If north is not a wall and north is not outside and north has not been visited or north's cost has changed!
		isNorthNeighborValid = (((!isNorthWall) && (!isNorthOutside)) && ((!isNorthVisited) || (isNorthCostChanged)));

		//NorthEastValid = If northeast is not a wall and northeast is not outside and north is not a wall and east is not a wall and northeast has not been visited or northeast's cost has changed!
		isNorthEastNeighborValid = (((!isNorthEastWall) && (!isNorthEastOutside)) && ((!isNorthWall) && (!isEastWall)) && ((!isNorthEastVisited) || (isNorthEastCostChanged)));

		//EastValid = If east is not a wall and east is not outside and east has not been visited or east's cost has changed!
		isEastNeighborValid = (((!isEastWall) && (!isEastOutside)) && ((!isEastVisited) || (isEastCostChanged)));

		//SouthEastValid = If southeast is not a wall and southeast is not outside and south is not a wall and east is not a wall and southeast has not been visited or southeast's cost has changed!
		isSouthEastNeighborValid = (((!isSouthEastWall) && (!isSouthEastOutside)) && ((!isSouthWall) && (!isEastWall)) && ((!isSouthEastVisited) || (isSouthEastCostChanged)));

		//SouthValid = If south is not a wall and south is not outside and south has not been visited or south's cost has changed!
		isSouthNeighborValid = (((!isSouthWall) && (!isSouthOutside)) && ((!isSouthVisited) || (isSouthCostChanged)));

		//SouthWestValid = If southwest is not a wall and southwest is not outside and south is not a wall and west is not a wall and southwest has not been visited or southwest's cost has changed!
		isSouthWestNeighborValid = (((!isSouthWestWall) && (!isSouthWestOutside)) && ((!isSouthWall) && (!isWestWall)) && ((!isSouthWestVisited) || (isSouthWestCostChanged)));

		//WestValid = If west is not a wall and west is not outside and west has not been visited or west's cost has changed!
		isWestNeighborValid = (((!isWestWall) && (!isWestOutside)) && ((!isWestVisited) || (isWestCostChanged)));

		//NorthWestValid = If northwest is not a wall and northwest is not outside and north is not a wall and west is not a wall and northwest has not been visited or northwest's cost has changed!
		isNorthWestNeighborValid = (((!isNorthWestWall) && (!isNorthWestOutside)) && ((!isNorthWall) && (!isWestWall)) && ((!isNorthWestVisited) || (isNorthWestCostChanged)));
	}
#pragma endregion

#pragma region NEXT_CHILD_ASSIGNMENTS

	//If north valid then assign the values for the north child and push it to the queue.
	if (isNorthNeighborValid)
	{
		NextChildAssignments(current, currentNorth, SOUTH_DIR, COST_AXIS, costType, heuType, npGoal, SQUARE_GRID);
		queueType.push(currentNorth);
	}

	//If northeast valid then assign the values for the northeast child and push it to the queue.
	if (isNorthEastNeighborValid)
	{
		NextChildAssignments(current, currentNorthEast, SOUTHWEST_DIR, COST_DIAGONAL, costType, heuType, npGoal, SQUARE_GRID);
		queueType.push(currentNorthEast);
	}

	//If east valid then assign the values for the east child and push it to the queue.
	if (isEastNeighborValid)
	{
		NextChildAssignments(current, currentEast, WEST_DIR, COST_AXIS, costType, heuType, npGoal, SQUARE_GRID);
		queueType.push(currentEast);
	}

	//If southeast valid then assign the values for the southeast child and push it to the queue.
	if (isSouthEastNeighborValid)
	{
		NextChildAssignments(current, currentSouthEast, NORTHWEST_DIR, COST_DIAGONAL, costType, heuType, npGoal, SQUARE_GRID);
		queueType.push(currentSouthEast);
	}

	//If south valid then assign the values for the south child and push it to the queue.
	if (isSouthNeighborValid)
	{
		NextChildAssignments(current, currentSouth, NORTH_DIR, COST_AXIS, costType, heuType, npGoal, SQUARE_GRID);
		queueType.push(currentSouth);
	}

	//If southwest valid then assign the values for the southwest child and push it to the queue.
	if (isSouthWestNeighborValid)
	{
		NextChildAssignments(current, currentSouthWest, NORTHEAST_DIR, COST_DIAGONAL, costType, heuType, npGoal, SQUARE_GRID);
		queueType.push(currentSouthWest);
	}

	//If west valid then assign the values for the west child and push it to the queue.
	if (isWestNeighborValid)
	{
		NextChildAssignments(current, currentWest, EAST_DIR, COST_AXIS, costType, heuType, npGoal, SQUARE_GRID);
		queueType.push(currentWest);
	}

	//If northwest valid then assign the values for the northwest child and push it to the queue.
	if (isNorthWestNeighborValid)
	{
		NextChildAssignments(current, currentNorthWest, SOUTHEAST_DIR, COST_DIAGONAL, costType, heuType, npGoal, SQUARE_GRID);
		queueType.push(currentNorthWest);
	}
#pragma endregion
}
#endif