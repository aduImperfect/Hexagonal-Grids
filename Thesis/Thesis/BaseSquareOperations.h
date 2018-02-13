///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: BaseSquareOperations.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef BASE_SQUARE_OPERATIONS_H
#define BASE_SQUARE_OPERATIONS_H
//Including the different required base headers which contain the initializers, defines, enumerations, and other generic operations.
#include "BaseDefines.h"
#include "BaseInitializers.h"
#include "BaseEnumerations.h"
#include "GenericOperations.h"

/*
Initialize the square grid elements.
Parameters to the function:
strCostSpace : const char * - this is the cost value in string form to fill the printed version of the map's Cost, HeuristicCost, and TotalCost values for each position on the grid.
Returns from the function:
NONE
This function calls the Initializer for every position on the square grid and passes in the strCostSpace as arguments for the Cost, HeuristicCost, and TotalCost associated with the position and return nothing.
*/
void InitializeFirstSquare(const char * strCostSpace)
{
	//Iterate through the square grid position (I, J) [Row, Column].
	for (int i = 0; i <= SQUARE_SIZE; ++i)
	{
		for (int j = 0; j <= SQUARE_SIZE; ++j)
		{
			Initializer(i, j, EMPTY_SPACE, EMPTY_CAME_FROM_SPACE, EMPTY_CAME_FROM_SPACE, strCostSpace, EMPTY_COST_SPACE, strCostSpace, EMPTY_COST_SPACE, strCostSpace, EMPTY_COST_SPACE);
		}
	}
}

/*
Re-Generate the square grid each iteration with the WALL, START, and GOAL values!.
Parameters to the function:
nposStart : const Position - the starting position.
nposGoal : const Position - the goal position.
Returns from the function:
NONE
This function takes in the positions of start and goal, it sets the values of all the walls, and the start and goal positions, and in addition randomly fills in empty spaces inside the grid with walls and return nothing.
*/
void GenerateSquare(const Position nposStart, const Position nposGoal)
{
	bool makeWall = false;
	//Iterate through the square grid position (I, J) [Row, Column].
	for (int i = 0; i <= SQUARE_SIZE; ++i)
	{
		for (int j = 0; j <= SQUARE_SIZE; ++j)
		{
			makeWall = false;
			//The boundary walls initialization.
			if (j == 0 || j == SQUARE_SIZE)
			{
				Initializer(i, j, WALL, WALL_CAME_FROM, WALL_CAME_FROM, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST);
			}
			else if (i == 0 || i == SQUARE_SIZE)
			{
				Initializer(i, j, WALL, WALL_CAME_FROM, WALL_CAME_FROM, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST);
			}
			//The starting position initialization.
			else if (i == nposStart.p_x && j == nposStart.p_y)
			{
				Initializer(i, j, START, START_CAME_FROM, START_CAME_FROM, START_COST, START_COST, START_COST, START_COST, START_COST, START_COST);
			}
			//The goal position initialization.
			else if (i == nposGoal.p_x && j == nposGoal.p_y)
			{
				Initializer(i, j, GOAL, GOAL_CAME_FROM, GOAL_CAME_FROM, GOAL_COST, NULL, GOAL_COST, NULL, GOAL_COST, NULL);
			}
			else if (j == 2 && i < 5)
			{
				makeWall = true;
			}
			else if (i == 9 && j < 11)
			{
				makeWall = true;
			}
			else if (j == 9 && i < 11)
			{
				makeWall = true;
			}
			//The random walls position initialization.
			else if (((i / 2) % (5) == 0) && ((2 * j) % (3) == 0))
			{
				makeWall = true;
			}
			else if ((i == 10) && (j > 10 && j < 20))
			{
				makeWall = true;
			}
			else if ((j == 10) && (i > 10 && i < 17))
			{
				makeWall = true;
			}

			if (makeWall)
			{
				Initializer(i, j, WALL, WALL_CAME_FROM, WALL_CAME_FROM, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST);
			}
		}
	}
}

/*
Print the square map of any type.
Parameters to the function:
mvType : const MapVisualType - the visual type of the map: visited, came_from, goal_path....
Returns from the function:
NONE
This function takes in the map visual type and based on that prints the associated values for each position of the square grid and returns nothing.
*/
void PrintSquareMapGeneric(const MapVisualType mvType)
{
	//Print the type of the map's visual type.
	PrintHeader(mvType);

	//Iterate through the square grid position (I, J) [Row, Column].
	for (int i = 0; i <= SQUARE_SIZE; ++i)
	{
		for (int j = 0; j <= SQUARE_SIZE; ++j)
		{
			switch (mvType)
			{
			case MapVisualType::MAP_VISITED:
				printf(mapVisited[i][j].c_str());
				printf(SQUARE_GRID_SPACE);
				break;
			case MapVisualType::MAP_CAMEFROM:
				printf(mapCameFrom[i][j].c_str());
				printf(SQUARE_GRID_CAME_FROM_SPACE);
				break;
			case MapVisualType::MAP_GOALPATH:
				printf(mapGoalPath[i][j].c_str());
				printf(SQUARE_GRID_CAME_FROM_SPACE);
				break;
			case MapVisualType::MAP_COST:
				printf(mapCost[i][j].c_str());
				printf(SQUARE_GRID_COST_SPACE);
				break;
			case MapVisualType::MAP_GOALCOST:
				printf(mapGoalCost[i][j].c_str());
				printf(SQUARE_GRID_COST_SPACE);
				break;
			case MapVisualType::MAP_HEUCOST:
				printf(mapHeuCost[i][j].c_str());
				printf(SQUARE_GRID_COST_SPACE);
				break;
			case MapVisualType::MAP_GOALHEUCOST:
				printf(mapGoalHeuCost[i][j].c_str());
				printf(SQUARE_GRID_COST_SPACE);
				break;
			case MapVisualType::MAP_TOTALCOST:
				printf(mapTotCost[i][j].c_str());
				printf(SQUARE_GRID_COST_SPACE);
				break;
			case MapVisualType::MAP_GOALTOTALCOST:
				printf(mapGoalTotCost[i][j].c_str());
				printf(SQUARE_GRID_COST_SPACE);
				break;
			}
		}
		printf("\n");
		printf("\n");
	}
}

/*
Check to see if position is outside the square map.
Parameters to the function:
pvertex : const Position - The position for which the check is being done.
topLeft : const Position - The top left position of the square grid.
bottomRight : const Position - The bottom right position of the square grid.
Returns from the function:
isOutside : bool - return value for if the position is outside the square grid.
This function takes in the vertex position that needs to be checked against the top left and bottom right positions of the square grid to determine if it is inside or outside the square grid.
It returns if the position is outside or not.
*/
bool /*isOutside*/ SquareIsOutside(const Position pvertex, const Position topLeft, const Position bottomRight)
{
	//If the vertex's x or y position is leff than the topLeft's x or y respectively or greater than the bottomRight's x or y respectively.
	if ((pvertex.p_x < topLeft.p_x) || (pvertex.p_y < topLeft.p_y) || (pvertex.p_x > bottomRight.p_x) || (pvertex.p_y > bottomRight.p_y))
		return true;

	return false;
}

/*
Check to see if position is a border of the square map.
Parameters to the function:
pvertex : const Position - The position for which the check is being done.
topLeft : const Position - The top left position of the square grid.
bottomRight : const Position - The bottom right position of the square grid.
Returns from the function:
isBorder : bool - return value for if the position is a border of the square grid.
This function takes in the vertex position that needs to be checked against the top left and bottom right positions of the square grid to determine if it is the border of the square grid.
It returns if the position is a border or not.
*/
bool /*isBorder*/ SquareIsBorder(const Position pvertex, const Position topLeft, const Position bottomRight)
{
	if (SquareIsOutside(pvertex, topLeft, bottomRight))
		return false;

	//If the position is inside the grid but is not in the first row, first column, last row, and/or the last column of the grid.
	if ((pvertex.p_x > topLeft.p_x) && (pvertex.p_y > topLeft.p_y) && (pvertex.p_x < bottomRight.p_x) && (pvertex.p_y < bottomRight.p_y))
		return false;

	return true;
}
#endif