///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: SquareBlockAStar.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef SQUARE_BLOCK_ASTAR_H
#define SQUARE_BLOCK_ASTAR_H
//Including the header for LDDB calculations and the base header for different square operations and parsing the square neighbors, along with the search loop and pre and post search functionalities.
#include "SquareLDDBCalculator.h"
#include "ParseSquareNeighbors.h"
#include "SearchLoop.h"
#include "SquarePrePostSearch.h"
#include "SquareDijkstra.h"
#include "SquareExpandBlock.h"

/*

*/
void InitNodes(const Position & blockIJ, const Position & fromKL, const Position & pFrom)
{
	//Parse through the Positions_To[M][N] (A block containing 4x4 elements then parse through 16 elements).
	for (int toM = 0; toM < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++toM)
	{
		for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
		{
			//Position absolute_to = (M + I*(TOT_X) + 1, N + J * (TOT_Y) + 1). Example: (2 + 2*4 + 1, 3 + 3*4 + 1) = (11, 16).
			Position pTo = Position(toM + blockIJ.p_x * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + 1, toN + blockIJ.p_y * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + 1);

			//Position absolute_top_left = (I * (TOT_X) + 1, J * (TOT_Y) + 1). Example: (2*4 + 1, 3*4 + 1) = (9, 13).
			Position pTopLeft = Position(blockIJ.p_x * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + 1, blockIJ.p_y * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + 1);

			//Position absolute_bottom_right = (I * (TOT_X) + TOT_X, J * (TOT_Y) + TOT_Y). Example: (2*4 + 4, 3*4 + 4) = (12, 16).
			Position pBottomRight = Position(blockIJ.p_x * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, blockIJ.p_y * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);

			//We have pos_From = (10, 15), and pos_To = (11, 16) in the main square grid.
			//The block area where pos_From and pos_To are situated in spans from (9, 13) to (12, 16).


#pragma region INVALIDS
			//If (absolute_to is not a border inside absolute_top_left and absolute_bottom_right). Example: ((11, 16) is not a border inside (9, 13) to (12, 16)).
			if (!SquareIsBorder(pTo, pTopLeft, pBottomRight))
			{
				//Set the LDDB and reverse too with -1. (as its a mirrored save).  Example: SquareLDDB at block[2][3] for position [1][2] to position [2][3] = SquareLDDB at block[2][3] for position [2][3] to position [1][2].
				SquareLDDB[blockIJ.p_x][blockIJ.p_y][toM][toN][fromKL.p_x][fromKL.p_y] = SquareLDDB[blockIJ.p_x][blockIJ.p_y][fromKL.p_x][fromKL.p_y][toM][toN] = -1;
				continue;
			}
#pragma endregion

#pragma region VALID_SELF
			//If (absolute_from is absolute_to). Example: (10, 15) == (11, 16).
			if (pFrom == pTo)
			{
				//We set the value to 0. No cost to go from and to the same position.
				SquareLDDB[blockIJ.p_x][blockIJ.p_y][fromKL.p_x][fromKL.p_y][toM][toN] = 0;
				continue;
			}
#pragma endregion

#pragma region VALIDS
			//Do not print the SquareDijkstra() maps when they are being calculated!!
			int showMap = 0;

			//Otherwise, for any other case. As, in for all border set cases, we calculate the Dijkstra for pFrom to pTo.
			std::vector<Position> tempGoalPath;
			SquareLDDB[blockIJ.p_x][blockIJ.p_y][toM][toN][fromKL.p_x][fromKL.p_y] = SquareLDDB[blockIJ.p_x][blockIJ.p_y][fromKL.p_x][fromKL.p_y][toM][toN] = SquareDijkstra(pFrom, pTo, true, pTopLeft, pBottomRight, showMap, tempGoalPath);
#pragma endregion
		}
	}
}

/*

*/
void CalculateBlockIngressNodes(std::vector<Position> & ingress_Cells_curBlock)
{
	//Ingress cells (Y) = Boundary cells that have a different g-value now than what they had the current block had been previously expanded.
	//If the block is being expanded for the first time, all the boundary cells with a finite g-value are ingress cells.


}

/*
Calculates the cost from start to goal using BLOCKASTAR.
Parameters to the function:
npStart : Position - the starting position.
npGoal : Position - the goal position.
autoCompute : bool - compute the BLOCKASTAR node expansion until it finishes searching for the goal or goal is not found. If false, we get step by step results of the BLOCKASTAR nodes expansion.
topLeft : Position - the top left position of the square grid.
bottomRight : Position - the bottom right position of the square grid.
showMap : int - this numeric value is used to check against if the user wants to view the printed maps or not.
goalPath : std::vector<Position> - the goal path vector that contains the position list from where the goal came from by starting at the start position.
Returns from the function:
startToGoalCost : double - return the calculated start to goal cost.
This function takes in the start and goal positions input by the user (or by other mechanisms) and takes in the boundary points of the square grid along with the check to see if the result needs to be given step by step or auto computed and if the square grid maps be printed or not.
*/
double /*startToGoalCost*/ SquareBlockAStar(Position npStart, Position npGoal, bool autoCompute, Position topLeft, Position bottomRight, const int showMap, std::vector<Position> & goalPath)
{
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

		printf("\nCompute BLOCK ASTAR Immediate!? (0 - no/1 - yes):\n");
		std::cin >> generateInstantaneous;
	}

	//INIT START AND INIT GOAL BLOCKS.

	//The start position inside its relative block.
	Position startPosInBlock(npStart.p_x % SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, npStart.p_y % SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);

	//The goal position inside its relative block.
	Position goalPosInBlock(npGoal.p_x % SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, npGoal.p_y % SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);

	//Find the start block.
	Position startBlock((npStart.p_x - 1) / SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (npStart.p_y - 1) / SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);
	startBlock.posCost = 0.0f;

	//Find the goal block.
	Position goalBlock((npGoal.p_x - 1) / SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (npGoal.p_y - 1) / SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);
	goalBlock.posCost = -1.0f;

	//Init(Start).
	InitNodes(startBlock, startPosInBlock, npStart);

	//Init(Goal).
	InitNodes(goalBlock, goalPosInBlock, npGoal);

	//The length to be calculated.
	double startToGoalCost = HUGE_VAL;

	priorityFrontier.push(startBlock);

	while ((!priorityFrontier.empty()) && (priorityFrontier.top().posCost < startToGoalCost))
	{
		Position curBlock = priorityFrontier.top();
		priorityFrontier.pop();

		//Ingress cells in current block (Y).
		std::vector<Position> ingress_Cells_curBlock;
		CalculateBlockIngressNodes(ingress_Cells_curBlock);

		if (curBlock == goalBlock)
		{
			//length = min (y in Y) (y.g + dist(y, goal), length).
			for (unsigned int y = 0; y < ingress_Cells_curBlock.size(); ++y)
			{
				Position ingressPos(ingress_Cells_curBlock[y].p_x, ingress_Cells_curBlock[y].p_y);
				ingressPos.posCost = ingress_Cells_curBlock[y].posCost;

				//dist(y, goal) = SquareLDDB[CurrentBlock][ingress(Y)][GoalPosInBlock].
				double distYG = SquareLDDB[curBlock.p_x][curBlock.p_y][ingressPos.p_x][ingressPos.p_y][goalPosInBlock.p_x][goalPosInBlock.p_y];

				if ((ingressPos.posCost + distYG) < startToGoalCost)
				{
					//length = y.g + dist(y, goal).
					startToGoalCost = ingressPos.posCost + distYG;
				}
			}

			break;
		}

		SquareExpandCurBlock(curBlock, ingress_Cells_curBlock, npGoal, nheuristic);

		//If autoCompute or generateInstantaneous is set to true we just keep going through the while loop without asking the user for the next step or printing out the map.
		if (generateInstantaneous || autoCompute)
			continue;

		//If we are going to show the various maps.
		if (showMap == 1)
		{
			//Re-generate the square grid.
			GenerateSquare(npStart, npGoal);
		}

		//If step by step algorithm is being expanded then we use nextStep's value to know if we want to get the next step.
		//If this is set to false by the user, we change the mode to computing automatically.
		bool nextStep = false;
		printf("\nGet next step? (0 - no/1 - yes):\n");
		std::cin >> nextStep;

		//If the user does not want to get the next step, we set it to calculating the next steps automatically.
		if (!nextStep)
		{
			generateInstantaneous = true;
		}
	}

	//If goal is found.
	if (startToGoalCost != HUGE_VAL)
	{
		//TODO: Reconstruct goal path.

		return startToGoalCost;
	}

	//If goal not found.
	return -1;
}
#endif