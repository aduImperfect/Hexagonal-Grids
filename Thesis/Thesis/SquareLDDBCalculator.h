///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: SquareLDDBCalculator.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef SQUARE_LDDB_CALCULATOR_H
#define SQUARE_LDDB_CALCULATOR_H
//Including the headers for base defines, the position structure, the DIJKSTRA algorithm, and the position relations structures and the LDDB to file header.
#include "BaseDefines.h"
#include "Position.h"
#include "SquareDijkstra.h"
#include "PositionRelations.h"

/*
Initializes all the elements of the SquareLDDB.
Parameters to the function:
NONE
Returns from the function:
NONE
This function takes in nothing, sets all the elements of the SquareLDDB[BLOCK_ROW][BLOCK_COL][POS_FROM_ROW][POS_FROM_COL][POS_TO_ROW][POS_TO_COL] to COST_MAX (100.0f) and returns nothing.
*/
void SquareLDDBInitializer()
{
	//Parse through the Blocks[I][J] (If a 20x20 grid with a block containing 4x4 elements then there are 25 (5x5) blocks).
	for (int blockI = 0; blockI < SQUARE_LDDB_BLOCK_SIZE_I; ++blockI)
	{
		for (int blockJ = 0; blockJ < SQUARE_LDDB_BLOCK_SIZE_J; ++blockJ)
		{
			//Parse through the Positions_From[K][L] (A block containing 4x4 elements then parse through 16 elements).
			for (int fromK = 0; fromK < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++fromK)
			{
				for (int fromL = 0; fromL < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++fromL)
				{
					//Parse through the Positions_To[M][N] (A block containing 4x4 elements then parse through 16 elements).
					for (int toM = 0; toM < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++toM)
					{
						for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
						{
							//SquareLDDB(Block(i,j) : [Pos_From(k,l) - Pos_To(m,n)] = COST_MAX).
							SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] = COST_MAX;
						}
					}
				}
			}
		}
	}
}

/*
Calculates the Local Distance Database.
Parameters to the function:
NONE
Returns from the function:
NONE
This function takes in nothing, computes the LDDB for each blocks -> (from-to) position sets and ultimately writes the result to two types of files and returns nothing.
*/
void SquareLDDBCalc()
{
	//Parse through the Blocks[I][J] (If a 20x20 grid with a block containing 4x4 elements then there are 25 (5x5) blocks).
	for (int blockI = 0; blockI < SQUARE_LDDB_BLOCK_SIZE_I; ++blockI)
	{
		for (int blockJ = 0; blockJ < SQUARE_LDDB_BLOCK_SIZE_J; ++blockJ)
		{
			//Parse through the Positions_From[K][L] (A block containing 4x4 elements then parse through 16 elements).
			for (int fromK = 0; fromK < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++fromK)
			{
				for (int fromL = 0; fromL < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++fromL)
				{
					//Parse through the Positions_To[M][N] (A block containing 4x4 elements then parse through 16 elements).
					for (int toM = 0; toM < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++toM)
					{
						for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
						{
#pragma region LDDB_EXAMPLE
							//Lets take I = 2 (between 0-4), J = 3 (between 0-4).
							//Lets take K = 1 (between 0-3), L = 2 (between 0-3).
							//Lets take M = 2 (between 0-3), N = 3 (between 0-3).
							//Given: TOT_X = 4, TOT_Y = 4.
#pragma endregion

#pragma region LDDB_ALREADY_CALCULATED
							//If the cost in block[i][j]: (from[K][L] - to[M][N]) is already assigned then skip that distance. Example: SquareLDDB at block[2][3] for position [1][2] to position [2][3].
							if (SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] < COST_MAX)
								continue;
#pragma endregion

#pragma region LDDB_ABSOLUTE_GRID_POSITIONS
							//Position absolute_from = (K + I * (TOT_X) + 1, L + J * (TOT_Y) + 1). Example: (1 + 2*4 + 1, 2 + 3*4 + 1) = (10, 15). 
							Position pFrom = Position(fromK + blockI * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + 1, fromL + blockJ * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + 1);
							
							//Position absolute_to = (M + I*(TOT_X) + 1, N + J * (TOT_Y) + 1). Example: (2 + 2*4 + 1, 3 + 3*4 + 1) = (11, 16).
							Position pTo = Position(toM + blockI * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + 1, toN + blockJ * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + 1);
							
							//Position absolute_top_left = (I * (TOT_X) + 1, J * (TOT_Y) + 1). Example: (2*4 + 1, 3*4 + 1) = (9, 13).
							Position pTopLeft = Position(blockI * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + 1, blockJ * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + 1);
							
							//Position absolute_bottom_right = (I * (TOT_X) + TOT_X, J * (TOT_Y) + TOT_Y). Example: (2*4 + 4, 3*4 + 4) = (12, 16).
							Position pBottomRight = Position(blockI * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, blockJ * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);
							
							//We have pos_From = (10, 15), and pos_To = (11, 16) in the main square grid.
							//The block area where pos_From and pos_To are situated in spans from (9, 13) to (12, 16).
#pragma endregion

#pragma region LDDB_INVALIDS
							//If (absolute_from is not a border inside absolute_top_left and absolute_bottom_right). or If (absolute_to is not a border inside absolute_top_left and absolute_bottom_right). Example: ((10, 15) is not a border inside (9, 13) to (12, 16)) or ((11, 16) is not a border inside (9, 13) to (12, 16)).
							if (!SquareIsBorder(pFrom, pTopLeft, pBottomRight) || !SquareIsBorder(pTo, pTopLeft, pBottomRight))
							{
								//Set the LDDB and reverse too with -1. (as its a mirrored save).  Example: SquareLDDB at block[2][3] for position [1][2] to position [2][3] = SquareLDDB at block[2][3] for position [2][3] to position [1][2].
								SquareLDDB[blockI][blockJ][toM][toN][fromK][fromL] = SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] = -1;
								continue;
							}
#pragma endregion

#pragma region LDDB_VALID_SELF
							//If (absolute_from is absolute_to). Example: (10, 15) == (11, 16).
							if (pFrom == pTo)
							{ 
								//We set the value to 0. No cost to go from and to the same position.
								SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] = 0;
								continue;
							}
#pragma endregion

#pragma region LDDB_VALIDS
							//Do not print the SquareDijkstra() maps when they are being calculated!!
							int showMap = 0;

							//Otherwise, for any other case. As, in for all border set cases, we calculate the Dijkstra for pFrom to pTo.
							std::vector<Position> tempGoalPath;
							SquareLDDB[blockI][blockJ][toM][toN][fromK][fromL] = SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] = SquareDijkstra(pFrom, pTo, true, pTopLeft, pBottomRight, showMap, tempGoalPath);
#pragma endregion
						}
					}
				}
			}
		}
	}
}
#endif