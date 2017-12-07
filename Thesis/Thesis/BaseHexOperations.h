///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: BaseHexOperations.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef BASE_HEX_OPERATIONS_H
#define BASE_HEX_OPERATIONS_H
//Including the different required base headers which contain the initializers, defines, enumerations, and other generic operations.
#include "BaseDefines.h"
#include "BaseInitializers.h"
#include "BaseEnumerations.h"
#include "GenericOperations.h"

/*
Initialize the hex grid elements.
Parameters to the function:
strCostSpace : const char * - this is the cost value in string form to fill the printed version of the map's Cost, HeuristicCost, and TotalCost values for each position on the grid.
Returns from the function:
NONE
This function calls the Initializer for every position on the hex grid and passes in the strCostSpace as arguments for the Cost, HeuristicCost, and TotalCost associated with the position and return nothing.
*/
void InitializeFirstHex(const char * strCostSpace)
{
	//Iterate through the hex grid position (I, J) [Column, Row].
	for (int i = 0; i <= HEX_SIZE; ++i)
	{
		for (int j = 0; j <= HEX_SIZE; ++j)
		{
			Initializer(i, j, EMPTY_SPACE, EMPTY_CAME_FROM_SPACE, EMPTY_CAME_FROM_SPACE, strCostSpace, EMPTY_COST_SPACE, strCostSpace, EMPTY_COST_SPACE, strCostSpace, EMPTY_COST_SPACE);
		}
	}
}

/*
Re-Generate the hex grid each iteration with the WALL, START, and GOAL values!.
Parameters to the function:
nposStart : const Position - the starting position.
nposGoal : const Position - the goal position.
Returns from the function:
NONE
This function takes in the positions of start and goal, it sets the values of all the walls, and the start and goal positions, and in addition randomly fills in empty spaces inside the grid with walls and return nothing.
*/
void GenerateHex(const Position nposStart, const Position nposGoal)
{
	//Iterate through the hex grid position (I, J) [Column, Row].
	for (int i = 0; i <= HEX_SIZE; ++i)
	{
		for (int j = 0; j <= HEX_SIZE; ++j)
		{
			//The boundary walls initialization.
			if (j == 0 || j == HEX_SIZE)
			{
				Initializer(i, j, WALL, WALL_CAME_FROM, WALL_CAME_FROM, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST);
			}
			else if (i == 0 || i == 1 || i == SQUARE_SIZE_PLUS || i == HEX_SIZE)
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
			//The random walls position initialization.
			else if (((i / 2) % (5) == 0) && ((2 * j) % (3) == 0))
			{
				Initializer(i, j, WALL, WALL_CAME_FROM, WALL_CAME_FROM, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST);
			}
			else if ((i == 10 || i == 11) && (j > 9 && j < 20))
			{
				Initializer(i, j, WALL, WALL_CAME_FROM, WALL_CAME_FROM, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST);
			}
			else if ((j == 10 || j == 11) && (i > 10 && i < 18))
			{
				Initializer(i, j, WALL, WALL_CAME_FROM, WALL_CAME_FROM, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST);
			}
		}
	}
}

/*
Print the hex map of any type.
Parameters to the function:
mvType : const MapVisualType - the visual type of the map: visited, came_from, goal_path....
Returns from the function:
NONE
This function takes in the map visual type and based on that prints the associated values for each position of the hex grid and returns nothing.
*/
void PrintHexMapGeneric(const MapVisualType mvType)
{
	//Print the type of the map's visual type.
	PrintHeader(mvType);

	//Iterate through the hex grid position (I, J) [Column, Row].
	for (int i = 0; i <=HEX_SIZE; ++i)
	{
		//Offset space added alternating for every other column.
		if (i % 2 == 0)
		{
			printf(HEX_GRID_OFFSET);
		}
		for (int j = 0; j <=HEX_SIZE; ++j)
		{
			switch (mvType)
			{
			case MapVisualType::MAP_VISITED:
				printf(mapVisited[i][j].c_str());
				printf(HEX_GRID_SPACE);
				break;
			case MapVisualType::MAP_CAMEFROM:
				printf(mapCameFrom[i][j].c_str());
				printf(HEX_GRID_CAME_FROM_SPACE);
				break;
			case MapVisualType::MAP_GOALPATH:
				printf(mapGoalPath[i][j].c_str());
				printf(HEX_GRID_CAME_FROM_SPACE);
				break;
			case MapVisualType::MAP_COST:
				printf(mapCost[i][j].c_str());
				printf(HEX_GRID_COST_SPACE);
				break;
			case MapVisualType::MAP_GOALCOST:
				printf(mapGoalCost[i][j].c_str());
				printf(HEX_GRID_COST_SPACE);
				break;
			case MapVisualType::MAP_HEUCOST:
				printf(mapHeuCost[i][j].c_str());
				printf(HEX_GRID_COST_SPACE);
				break;
			case MapVisualType::MAP_GOALHEUCOST:
				printf(mapGoalHeuCost[i][j].c_str());
				printf(HEX_GRID_COST_SPACE);
				break;
			case MapVisualType::MAP_TOTALCOST:
				printf(mapTotCost[i][j].c_str());
				printf(HEX_GRID_COST_SPACE);
				break;
			case MapVisualType::MAP_GOALTOTALCOST:
				printf(mapGoalTotCost[i][j].c_str());
				printf(HEX_GRID_COST_SPACE);
				break;
			}
		}
		printf("\n");
	}
}

/*
Check to see if position is outside the hex map.
Parameters to the function:
pvertex : const Position - The position for which the check is being done.
center : const Position - The center position of the hex grid.
perimeter : const int - The perimeter of the hex grid.
Returns from the function:
isOutside : bool - return value for if the position is outside the hex grid.
This function takes in the vertex position that needs to be checked against the perimeter of the whole hex grid with the center information given to determine if it is inside or outside the hex grid.
It returns if the position is outside or not.
*/
bool /*isOutside*/ HexIsOutside(const Position pvertex, const Position center, const int perimeter)
{
	//phalf is half the perimeter value (like a radius!).
	int phalf = static_cast<int>(floor(perimeter / 2));

	//pdouble is double the perimeter's value.
	int pdouble = 2 * perimeter;

	//If the vertex's y axis is at the same position as the center's y.
	if (pvertex.p_y == center.p_y)
	{
		if (pvertex.p_x < (center.p_x - pdouble) || pvertex.p_x > (center.p_x + pdouble))
		{
			return true;
		}
	}

	//If center's y is not an even number.
	if ((center.p_y % 2) != 0)
	{
		if (pvertex.p_y < (center.p_y - phalf))
			return true;

		if ((perimeter % 2 != 0) && (pvertex.p_y == (center.p_y + phalf)))
			return true;

		if ((perimeter % 2 == 0) && (pvertex.p_y > (center.p_y + phalf)))
			return true;
	}

	//If center's y is an even number.
	else
	{
		if (pvertex.p_y > (center.p_y + phalf))
			return true;

		if ((perimeter % 2 != 0) && (pvertex.p_y == (center.p_y - phalf)))
			return true;

		if ((perimeter % 2 == 0) && (pvertex.p_y < (center.p_y - phalf)))
			return true;
	}

	return false;
}
#endif