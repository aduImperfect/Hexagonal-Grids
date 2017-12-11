///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: BaseInitializers.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef BASE_INITIALIZERS_H
#define BASE_INITIALIZERS_H
//Including the different required base headers which contain the base defines, the different maps declarations, and any other base operators.
#include "BaseDefines.h"
#include "MapsVariety.h"
#include "BaseOperators.h"

/*
Initialize all the different types of square and hex 2D array storages (visited, came_from, cost_so_far, cost_heuristic, cost_total) with default values.
Parameters to the function:
extraSize : const int - the extra additive size limiter based on the grid type: square and hex.
nCost : const double - the initial cost for cost_so_far, cost_heuristic, and cost_total's 2D array storages'.
Returns from the function:
NONE
This function sets the values of the different kinds of the 2D array storages being used in the project with default initializer values and returns nothing.
*/
void InitializeVCC(const int extraSize, const double nCost)
{
	//Iterate through the square grid position (I, J) [Row, Column].
	for (int i = 0; i <= SIZE + extraSize; ++i)
	{
		for (int j = 0; j <= SIZE + extraSize; ++j)
		{
			//If the visited map has the string associated with WALL written in the (i,j)th location, then we set visited(i,j) to true or else it is set to false.
			if (mapVisited[i][j] == WALL)
			{
				visited[i][j] = true;
			}
			else
			{
				visited[i][j] = false;
			}

			//The other different arrays are initialized with the default values as such in all (i,j)th locations.
			came_from[i][j] = NULL;
			cost_so_far[i][j] = nCost;
			cost_heuristic[i][j] = nCost;
			cost_total[i][j] = nCost;
		}
	}
}

/*
Initialize all the different types of square and hex printable maps (mapVisited, mapCameFrom, mapGoalPath, mapCost, mapGoalCost, mapHeuCost, mapGoalHeuCost, mapTotCost, mapGoalTotCost) with default values.
Parameters to the function:
i : const int - the row value of the position in the grid.
j : const int - the column value of the position in the grid.
mVisit : const char * - the value to be input for mapVisited(i,j) if the new value is not NULL (else the value remains the old mapVisited(i,j) value).
mCameFrom : const char * - the value to be input for mapCameFrom(i,j) if the new value is not NULL (else the value remains the old mapCameFrom(i,j) value).
mGoalPath : const char * - the value to be input for mapGoalPath(i,j) if the new value is not NULL (else the value remains the old mapGoalPath(i,j) value).
mCost : const char * - the value to be input for mapCost(i,j) if the new value is not NULL (else the value remains the old mapCost(i,j) value).
mGoalCost : const char * - the value to be input for mapGoalCost(i,j) if the new value is not NULL (else the value remains the old mapGoalCost(i,j) value).
mHeuCost : const char * - the value to be input for mapHeuCost(i,j) if the new value is not NULL (else the value remains the old mapHeuCost(i,j) value).
mGoalHeuCost : const char * - the value to be input for mapGoalHeuCost(i,j) if the new value is not NULL (else the value remains the old mapGoalHeuCost(i,j) value).
mTotCost : const char * - the value to be input for mapTotCost(i,j) if the new value is not NULL (else the value remains the old mapTotCost(i,j) value).
mGoalTotCost : const char * - the value to be input for mapGoalTotCost(i,j) if the new value is not NULL (else the value remains the old mapGoalTotCost(i,j) value).
Returns from the function:
NONE
This function sets the values of the different kinds of the maps being used in the project with new initializer values and returns nothing.
*/
void Initializer(const int i, const int j, const char * mVisit, const char * mCameFrom, const char * mGoalPath, const char * mCost, const char * mGoalCost, const char * mHeuCost, const char * mGoalHeuCost, const char * mTotCost, const char * mGoalTotCost)
{
	(mVisit != NULL) ? (mapVisited[i][j] = mVisit) : mapVisited[i][j];
	(mCameFrom != NULL) ? (mapCameFrom[i][j] = mCameFrom) : mapCameFrom[i][j];
	(mGoalPath != NULL) ? (mapGoalPath[i][j] = mGoalPath) : mapGoalPath[i][j];
	(mCost != NULL) ? (mapCost[i][j] = mCost) : mapCost[i][j];
	(mGoalCost != NULL) ? (mapGoalCost[i][j] = mGoalCost) : mapGoalCost[i][j];
	(mHeuCost != NULL) ? (mapHeuCost[i][j] = mHeuCost) : mapHeuCost[i][j];
	(mGoalHeuCost != NULL) ? (mapGoalHeuCost[i][j] = mGoalHeuCost) : mapGoalHeuCost[i][j];
	(mTotCost != NULL) ? (mapTotCost[i][j] = mTotCost) : mapTotCost[i][j];
	(mGoalTotCost != NULL) ? (mapGoalTotCost[i][j] = mGoalTotCost) : mapGoalTotCost[i][j];
}
#endif