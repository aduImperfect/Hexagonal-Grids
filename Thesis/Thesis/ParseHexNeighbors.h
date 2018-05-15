///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017-2018 DigiPen Institute of Technology, all rights reserved
/// FILE: ParseHexNeighbors.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef PARSE_HEX_NEIGHBORS_H
#define PARSE_HEX_NEIGHBORS_H
//Including the header for position structure.
#include "Position.h"

/*
Parse through all the neighbors of a position in a hex grid.
Parameters to the function:
queueType : T & - the type of queue, a normal queue or a priority queue (being used as).
algoType : const PathfindingAlgo & - the algorithm type wherein the neighbors of a position are being parsed.
current : Position - the current position being used here to generate the 6 neighbor position internally.
npGoal : const Position & - the goal position.
center : const Position & - the center position of the hex grid.
perimeter : const int & - the perimeter of the hex grid.
costType : const CostType & - the type of cost associated with the path-finding algorithm.
heuType : const HeuristicType & - the type of heuristic associated with the path-finding algorithm.
Returns from the function:
NONE
This function makes internal neighbor position based on the current position in the 6 directions and has different checks associated with them (walls, visited, and outside checks). Then based on the type of algorithm, it is found which of the 6 different paths are valid neighbors. Based on their validity, the data is passed forward to the NextChildAssignments call for each direction (to add them to the queue). This function returns nothing.
*/
template<typename T>
void ParseHexNeighbors(T & queueType, const PathfindingAlgo & algoType, Position current, const Position & npGoal, const Position & center, const int & perimeter, const CostType & costType, const HeuristicType & heuType)
{
#pragma region NEIGHBOR_POSITIONS
	//The neighbors of the current position. (N, NE, SE, S, SW, NW).
	
	//currentNorth = (current.x - 2, current.y + 0).
	Position currentNorth = current + pos_HEXNORTH;

	//currentNorthEast = If (current.x is not even) => (current.x - 1, current.y + 0), else => (current.x - 1, current.y + 1).
	Position currentNorthEast = current + ((current.p_x % 2 != 0) ? pos_HEXODDNORTHEAST : pos_HEXEVENNORTHEAST);

	//currentSouthEast = If (current.x is not even) => (current.x + 1, current.y + 0), else => (current.x + 1, current.y + 1).
	Position currentSouthEast = current + ((current.p_x % 2 != 0) ? pos_HEXODDSOUTHEAST : pos_HEXEVENSOUTHEAST);

	//currentSouth = (current.x + 2, current.y + 0).
	Position currentSouth = current + pos_HEXSOUTH;

	//currentSouthWest = If (current.x is not even) => (current.x + 1, current.y - 1), else => (current.x + 1, current.y + 0).
	Position currentSouthWest = current + ((current.p_x % 2 != 0) ? pos_HEXODDSOUTHWEST : pos_HEXEVENSOUTHWEST);

	//currentNorthWest = If (current.x is not even) => (current.x - 1, current.y - 1), else => (current.x - 1, current.y + 0).
	Position currentNorthWest = current + ((current.p_x % 2 != 0) ? pos_HEXODDNORTHWEST : pos_HEXEVENNORTHWEST);
#pragma endregion

#pragma region IS_WALL_CHECKS
	//Checks to see if any of the directions are a wall.
	bool isNorthWall = mapVisited[currentNorth.p_x][currentNorth.p_y] == WALL;
	bool isNorthEastWall = mapVisited[currentNorthEast.p_x][currentNorthEast.p_y] == WALL;
	bool isSouthEastWall = mapVisited[currentSouthEast.p_x][currentSouthEast.p_y] == WALL;
	bool isSouthWall = mapVisited[currentSouth.p_x][currentSouth.p_y] == WALL;
	bool isSouthWestWall = mapVisited[currentSouthWest.p_x][currentSouthWest.p_y] == WALL;
	bool isNorthWestWall = mapVisited[currentNorthWest.p_x][currentNorthWest.p_y] == WALL;
#pragma endregion

#pragma region IS_VISITED_CHECKS
	//Checks to see if any of the directions have been visited.
	bool isNorthVisited = visited[currentNorth.p_x][currentNorth.p_y];
	bool isNorthEastVisited = visited[currentNorthEast.p_x][currentNorthEast.p_y];
	bool isSouthEastVisited = visited[currentSouthEast.p_x][currentSouthEast.p_y];
	bool isSouthVisited = visited[currentSouth.p_x][currentSouth.p_y];
	bool isSouthWestVisited = visited[currentSouthWest.p_x][currentSouthWest.p_y];
	bool isNorthWestVisited = visited[currentNorthWest.p_x][currentNorthWest.p_y];
#pragma endregion

#pragma region IS_OUTSIDE_CHECKS
	//Checks to see if any of the directions are outside the grid.
	bool isNorthOutside = HexIsOutside(currentNorth, center, perimeter);
	bool isNorthEastOutside = HexIsOutside(currentNorthEast, center, perimeter);
	bool isSouthEastOutside = HexIsOutside(currentSouthEast, center, perimeter);
	bool isSouthOutside = HexIsOutside(currentSouth, center, perimeter);
	bool isSouthWestOutside = HexIsOutside(currentSouthWest, center, perimeter);
	bool isNorthWestOutside = HexIsOutside(currentNorthWest, center, perimeter);
#pragma endregion

#pragma region IS_VALID_CHECK_INITIALIZERS
	//Checks to see if any of the directions are valid children.
	bool isNorthNeighborValid = false;
	bool isNorthEastNeighborValid = false;
	bool isSouthEastNeighborValid = false;
	bool isSouthNeighborValid = false;
	bool isSouthWestNeighborValid = false;
	bool isNorthWestNeighborValid = false;
#pragma endregion

#pragma region IS_VALID_CHECK_BFS_GREEDY
	//If the algorithm is BFS or GREEDY.
	if ((algoType == PathfindingAlgo::ALGO_BFS) || (algoType == PathfindingAlgo::ALGO_GREEDY))
	{
		//NorthValid = If north has not been visited and north is not outside the grid.
		isNorthNeighborValid = ((!isNorthVisited) && (!isNorthOutside));

		//NorthEastValid = If northeast has not been visited and northeast is not outside the grid.
		isNorthEastNeighborValid = ((!isNorthEastVisited) && (!isNorthEastOutside));

		//SouthEastValid = If southeast has not been visited and southeast is not outside the grid.
		isSouthEastNeighborValid = ((!isSouthEastVisited) && (!isSouthEastOutside));
		
		//SouthValid = If south has not been visited and south is not outside the grid.
		isSouthNeighborValid = ((!isSouthVisited) && (!isSouthOutside));

		//SouthWestValid = If southwest has not been visited and southwest is not outside the grid.
		isSouthWestNeighborValid = ((!isSouthWestVisited) && (!isSouthWestOutside));

		//NorthWestValid = If northwest has not been visited and northwest is not outside the grid.
		isNorthWestNeighborValid = ((!isNorthWestVisited) && (!isNorthWestOutside));
	}
#pragma endregion

#pragma region IS_VALID_CHECK_DIJKSTRA_ASTAR
	//If the algorithm is DIJKSTRA or ASTAR.
	else if ((algoType == PathfindingAlgo::ALGO_DIJKSTRA) || (algoType == PathfindingAlgo::ALGO_ASTAR))
	{
		//The new calculated cost_so_far for the neighbor (in all directions).
		double newCostAxis = cost_so_far[current.p_x][current.p_y] + COST_AXIS;

#pragma region IS_CHANGED_CHECKS
		//If north cost changed = if the new axis cost is less than the cost stored for north.
		bool isNorthCostChanged = (newCostAxis < cost_so_far[currentNorth.p_x][currentNorth.p_y]);

		//If northeast cost changed = if the new axis cost is less than the cost stored for northeast.
		bool isNorthEastCostChanged = (newCostAxis < cost_so_far[currentNorthEast.p_x][currentNorthEast.p_y]);

		//If southeast cost changed = if the new axis cost is less than the cost stored for southeast.
		bool isSouthEastCostChanged = (newCostAxis < cost_so_far[currentSouthEast.p_x][currentSouthEast.p_y]);

		//If south cost changed = if the new axis cost is less than the cost stored for south.
		bool isSouthCostChanged = (newCostAxis < cost_so_far[currentSouth.p_x][currentSouth.p_y]);

		//If southwest cost changed = if the new axis cost is less than the cost stored for southwest.
		bool isSouthWestCostChanged = (newCostAxis < cost_so_far[currentSouthWest.p_x][currentSouthWest.p_y]);

		//If northwest cost changed = if the new axis cost is less than the cost stored for northwest.
		bool isNorthWestCostChanged = (newCostAxis < cost_so_far[currentNorthWest.p_x][currentNorthWest.p_y]);
#pragma endregion

		//NorthValid = If north is not a wall and north is not outside and north has not been visited or north's cost has changed!
		isNorthNeighborValid = (((!isNorthWall) && (!isNorthOutside)) && ((!isNorthVisited) || (isNorthCostChanged)));

		//NorthEastValid = If northeast is not a wall and northeast is not outside and northeast has not been visited or northeast's cost has changed!
		isNorthEastNeighborValid = (((!isNorthEastWall) && (!isNorthEastOutside)) && ((!isNorthEastVisited) || (isNorthEastCostChanged)));

		//SouthEastValid = If southeast is not a wall and southeast is not outside and southeast has not been visited or southeast's cost has changed!
		isSouthEastNeighborValid = (((!isSouthEastWall) && (!isSouthEastOutside)) && ((!isSouthEastVisited) || (isSouthEastCostChanged)));

		//SouthValid = If south is not a wall and south is not outside and south has not been visited or south's cost has changed!
		isSouthNeighborValid = (((!isSouthWall) && (!isSouthOutside)) && ((!isSouthVisited) || (isSouthCostChanged)));

		//SouthWestValid = If southwest is not a wall and southwest is not outside and southwest has not been visited or southwest's cost has changed!
		isSouthWestNeighborValid = (((!isSouthWestWall) && (!isSouthWestOutside)) && ((!isSouthWestVisited) || (isSouthWestCostChanged)));

		//NorthWestValid = If northwest is not a wall and northwest is not outside and northwest has not been visited or northwest's cost has changed!
		isNorthWestNeighborValid = (((!isNorthWestWall) && (!isNorthWestOutside)) && ((!isNorthWestVisited) || (isNorthWestCostChanged)));
	}
#pragma endregion

#pragma region NEXT_CHILD_ASSIGNMENTS

	//If north valid then assign the values for the north child and push it to the queue.
	if (isNorthNeighborValid)
	{
		NextChildAssignments(current, currentNorth, SOUTH_DIR, COST_AXIS, costType, heuType, npGoal, HEX_GRID);
		queueType.push(currentNorth);
	}

	//If northeast valid then assign the values for the northeast child and push it to the queue.
	if (isNorthEastNeighborValid)
	{
		NextChildAssignments(current, currentNorthEast, SOUTHWEST_DIR, COST_AXIS, costType, heuType, npGoal, HEX_GRID);
		queueType.push(currentNorthEast);
	}

	//If southeast valid then assign the values for the southeast child and push it to the queue.
	if (isSouthEastNeighborValid)
	{
		NextChildAssignments(current, currentSouthEast, NORTHWEST_DIR, COST_AXIS, costType, heuType, npGoal, HEX_GRID);
		queueType.push(currentSouthEast);
	}

	//If south valid then assign the values for the south child and push it to the queue.
	if (isSouthNeighborValid)
	{
		NextChildAssignments(current, currentSouth, NORTH_DIR, COST_AXIS, costType, heuType, npGoal, HEX_GRID);
		queueType.push(currentSouth);
	}

	//If southwest valid then assign the values for the southwest child and push it to the queue.
	if (isSouthWestNeighborValid)
	{
		NextChildAssignments(current, currentSouthWest, NORTHEAST_DIR, COST_AXIS, costType, heuType, npGoal, HEX_GRID);
		queueType.push(currentSouthWest);
	}

	//If northwest valid then assign the values for the northwest child and push it to the queue.
	if (isNorthWestNeighborValid)
	{
		NextChildAssignments(current, currentNorthWest, SOUTHEAST_DIR, COST_AXIS, costType, heuType, npGoal, HEX_GRID);
		queueType.push(currentNorthWest);
	}
#pragma endregion
}
#endif