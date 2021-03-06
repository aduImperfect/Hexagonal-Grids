///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017-2018 DigiPen Institute of Technology, all rights reserved
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
Initialize the node.
Parameters to the function:
blockIJ : const Position & - The block which needs to be initialized.
fromKL : const Position & - The position (in the block) from which the LDDB is calculated (It is either the start or goal position here!).
pFrom : const Position & - The position (in the square grid) based on which the Dijkstra is calculated.
Returns from the function:
NONE.
This function initializes the different border values of the (start and/or goal) block with their distance from the (start/goal) position into the LDDB 6D array.
*/
void InitNodes(const Position & blockIJ, const Position & fromKL, const Position & pFrom)
{
	//Position absolute_top_left = (I * (TOT_X) + 1, J * (TOT_Y) + 1). Example: (2*4 + 1, 3*4 + 1) = (9, 13).
	Position pTopLeft = Position(blockIJ.p_x * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + 1, blockIJ.p_y * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + 1);

	//Position absolute_bottom_right = (I * (TOT_X) + TOT_X, J * (TOT_Y) + TOT_Y). Example: (2*4 + 4, 3*4 + 4) = (12, 16).
	Position pBottomRight = Position(blockIJ.p_x * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, blockIJ.p_y * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);

	//Parse through the Positions_To[M][N] (A block containing 4x4 elements then parse through 16 elements).
	for (int toM = 0; toM < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++toM)
	{
		for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
		{
			//Position absolute_to = (M + I*(TOT_X) + 1, N + J * (TOT_Y) + 1). Example: (2 + 2*4 + 1, 3 + 3*4 + 1) = (11, 16).
			Position pTo = Position(toM + blockIJ.p_x * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + 1, toN + blockIJ.p_y * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + 1);

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
void CalculateBlockIngressNodes(Position & curBlock, std::vector<Position> & ingress_Cells_curBlock, const Position & startPosInBlock, const bool & isFirstExpansion)
{
	//Ingress cells (Y) = Boundary cells that have a different g-value now than what they had when the current block had been previously expanded.
	//If the block is being expanded for the first time, all the boundary cells with a finite g-value are ingress cells.

	//The ingress cell values stored are as positions local to the block.

	for (unsigned int rowI = 0; rowI < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++rowI)
	{
		for (unsigned int rowJ = 0; rowJ < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++rowJ)
		{
			Position posInCurBlock(rowI, rowJ);
			
			if ((posInCurBlock.p_x > 0) && (posInCurBlock.p_y > 0) && (posInCurBlock.p_x < (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 1)) && (posInCurBlock.p_y < (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 1)))
			{
				continue;
			}

			Position curPos(curBlock.p_x * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + rowI + 1, curBlock.p_y * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + rowJ + 1);

			if (isFirstExpansion)
			{
				double tmpCost = (SquareLDDB[curBlock.p_x][curBlock.p_y][startPosInBlock.p_x][startPosInBlock.p_y][rowI][rowJ] < 0) ? COST_MAX: SquareLDDB[curBlock.p_x][curBlock.p_y][startPosInBlock.p_x][startPosInBlock.p_y][rowI][rowJ];

				//Use LDDB for the start block ingress cells info.
				posInCurBlock.posCost = tmpCost;
				cost_so_far[curPos.p_x][curPos.p_y] = posInCurBlock.posCost;
			}
			else
			{
				//TODO!!.
				posInCurBlock.posCost = cost_so_far[curPos.p_x][curPos.p_y];
			}

			if (posInCurBlock.posCost != COST_MAX)
			{
				ingress_Cells_curBlock.push_back(posInCurBlock);
			}
		}
	}
}

/*

*/
void PrintIngressNodes(Position & curBlock, std::vector<Position> & ingress_Cells_curBlock)
{
	std::cout << "\nIngress Cells of Current Block[" << curBlock.p_x << "][" << curBlock.p_y << "]:\n";

	for (unsigned int ingressIndex = 0; ingressIndex < ingress_Cells_curBlock.size(); ++ingressIndex)
	{
		std::cout << "Ingress Cell[" << ingress_Cells_curBlock[ingressIndex].p_x << "][" << ingress_Cells_curBlock[ingressIndex].p_y << "]'s cost: " << ingress_Cells_curBlock[ingressIndex].posCost << "\n";
	}
}

/*

*/
void CalculateStartHeapCost(const Position & curBlock, const Position & startPosInBlock, const HeuristicType & heuType, const Position & goalPos)
{
	//The total number of elements in each block.
	unsigned int nTotalSize = SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y;

	//The total number of non-corner elements in each block.
	unsigned int nInnerSize = (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 2) * (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 2);

	//The total number of (in and out)corner elements in each block.
	const unsigned int nOuterBordersSize = nTotalSize - nInnerSize;

	//Parse through the outer nodes of the current block.
	for (unsigned int outerAxis = 0; outerAxis < nOuterBordersSize; ++outerAxis)
	{
		//Get the grid absolute value of the current position in the block.
		Position positionInCurBlockGridAbs = SquareEGCellPos[curBlock.p_x][curBlock.p_y][outerAxis];

		//Convert and find the current position with respect to the current block.
		Position positionInCurBlock((positionInCurBlockGridAbs.p_x - 1) % SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (positionInCurBlockGridAbs.p_y - 1) % SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);

		//Transfer the cost.
		positionInCurBlock.posCost = positionInCurBlockGridAbs.posCost;

		//x.h.
		double posToGoalHeuristic = Heuristic(heuType, abs(goalPos.p_x - positionInCurBlockGridAbs.p_x), abs(goalPos.p_y - positionInCurBlockGridAbs.p_y));

		//Get the LDDB cost stored in the SquareLDDB database = LDDB(y,x).
		double LDDBCost = SquareLDDB[curBlock.p_x][curBlock.p_y][startPosInBlock.p_x][startPosInBlock.p_y][positionInCurBlock.p_x][positionInCurBlock.p_y];

		//Convert float to int with a large multiplier of 1000 for better approximation.
		int LDDBInt = (int)(LDDBCost * 1000.00000f);

		//If the integral value is between -1 and 1 (negligible compared to large numbers) then set it to 0.
		LDDBInt = ((LDDBInt >= -1) && (LDDBInt <= 1)) ? 0 : LDDBInt;

		//tempHeapValue = x.g + x.h.
		double tempHeapValue = ((LDDBInt < 0) ? COST_MAX : LDDBCost) + posToGoalHeuristic;

		//tempHeapValue < neighborHeapCost.
		if (((curBlock.p_x >= 0) && (curBlock.p_y >= 0) && (curBlock.p_x < SQUARE_LDDB_BLOCK_SIZE_I) && (curBlock.p_y < SQUARE_LDDB_BLOCK_SIZE_J)) && (tempHeapValue < BlockHeapCosts[curBlock.p_x][curBlock.p_y]))
		{
			//min(updated x')(tempHeapValue).
			//Update the temporary neighbor heap cost storage.
			BlockHeapCosts[curBlock.p_x][curBlock.p_y] = tempHeapValue;
		}
	}
}

void PrintCostSoFar()
{
	//Find the Egress cells file SquareEGCellPos.txt and open it.
	std::ofstream costSoFarFile;
	costSoFarFile.open("CostSoFar.txt");

	costSoFarFile << "\n";

#pragma region COL_FIRST_HEADER
	//Append all the TO[n] subscripts as the first row header.
	costSoFarFile << "\t\t";
	for (int icol = 0; icol < SIZE + GRID_EXTRA; ++icol)
	{
		if (icol > 9)
		{
			costSoFarFile << "[" << icol << "]\t";
		}
		else
		{
			costSoFarFile << "[" << icol << "]\t\t";
		}
	}
	costSoFarFile << "\n";
#pragma endregion

	for (unsigned int irow = 0; irow < SIZE + GRID_EXTRA; ++irow)
	{
		costSoFarFile << "[" << irow << "]:\t";
		for (unsigned int icol = 0; icol < SIZE + GRID_EXTRA; ++icol)
		{
			bool isInf = false;
			if (cost_so_far[irow][icol] == COST_MAX)
			{
				isInf = true;
				costSoFarFile << "infi";
			}
			else
			{
				costSoFarFile << cost_so_far[irow][icol];
			}

			int tempVal = static_cast<int>(cost_so_far[irow][icol] * 100);
			if ((tempVal % 100) != 0)
			{
				costSoFarFile << "\t";
			}
			else
			{
				if (isInf)
				{
					costSoFarFile << "\t";
				}
				else
				{
					costSoFarFile << "\t\t";
				}
			}
		}
		costSoFarFile << "\n";
	}
	costSoFarFile << "\n";
}

/*

*/
void CalculateAxisArray()
{
	unsigned int x = 0;
	unsigned int y = 0;

	//The total number of elements in each block.
	unsigned int nTotalSize = SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y;

	//The total number of non-corner elements in each block.
	unsigned int nInnerSize = (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 2) * (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 2);

	//The total number of (in and out)corner elements in each block.
	const unsigned int nOuterBordersSize = nTotalSize - nInnerSize;

	//The first corner (top left) of the square block. For a 4x4 block example: 0.
	unsigned int firstCorner = 0;

	//The third corner (bottom right) of the square block. For a 4x4 block example: 6.
	unsigned int thirdCorner = (nOuterBordersSize / 2);

	//The second corner (top right) of the square block. For a 4x4 block example: 3.
	unsigned int secondCorner = thirdCorner - (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 1);

	//The fourth corner (bottom left) of the square block. For a 4x4 block example: 9.
	unsigned int fourthCorner = thirdCorner + (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 1);

	for (unsigned int i = 0; i < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++i)
	{
		for (unsigned int j = 0; j < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++j)
		{
			AxisArray[i][j] = -1;
		}
	}

	for (unsigned int i = 0; i < nOuterBordersSize; ++i)
	{
		AxisArray[x][y] = i;
		if (i < secondCorner)
		{
			++y;
		}
		else if (i < thirdCorner)
		{
			++x;
		}
		else if (i < fourthCorner)
		{
			--y;
		}
		else
		{
			--x;
		}
	}
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
	//If the start node is outside of the range of the square grid (topLeft, bottomRight) then no goal found.
	if (SquareIsOutside(npStart, topLeft, bottomRight))
		return -1;

	//If the goal node is outside of the range of the square grid (topLeft, bottomRight) then no goal found.
	if (SquareIsOutside(npGoal, topLeft, bottomRight))
		return -1;

	//Set the 2D array storages with default values having the initial costs of the cost_so_far, cost_heuristic, and cost_total set.
	InitializeVCC(SQUARE_GRID, COST_MAX);

	//Set the position cost of the starting position to be equal to the cost_so_far at the starting position which is set.
	npStart.posCost = 0.00f;

	//Set the visited(start) to true. Stating that start has been visited already.
	visited[npStart.p_x][npStart.p_y] = true;

	//As there is no other position existing before start from where the algo started, we set the came_from(start) = start.
	came_from[npStart.p_x][npStart.p_y] = npStart;

	//We check to see if the map of the visited nodes has a WALL in the starting position, then no goal found.
	if (mapVisited[npStart.p_x][npStart.p_y] == WALL)
		return -1;

	//We check to see if the map of the visited nodes has a WALL in the goal position, then no goal found.
	if (mapVisited[npGoal.p_x][npGoal.p_y] == WALL)
		return -1;

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
	Position startPosInBlock((npStart.p_x - 1) % SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (npStart.p_y - 1) % SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);

	//The goal position inside its relative block.
	Position goalPosInBlock((npGoal.p_x - 1) % SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (npGoal.p_y - 1) % SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);

	//Find the start block.
	Position startBlock((npStart.p_x - 1) / SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (npStart.p_y - 1) / SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);
	startBlock.posCost = COST_MAX;

	//Find the goal block.
	Position goalBlock((npGoal.p_x - 1) / SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (npGoal.p_y - 1) / SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);
	goalBlock.posCost = COST_MAX;

	//Init(Start).
	InitNodes(startBlock, startPosInBlock, npStart);

	//Init(Goal).
	InitNodes(goalBlock, goalPosInBlock, npGoal);

	//The length to be calculated.
	double startToGoalCost = COST_MAX;

	//Popping out all the previous elements from the queue to clear the whole queue for a new algo run.
	while (!priorityFrontier.empty())
	{
		priorityFrontier.pop();
	}

	for (unsigned int neighborI = 0; neighborI < SQUARE_LDDB_BLOCK_SIZE_I; ++neighborI)
	{
		for (unsigned int neighborJ = 0; neighborJ < SQUARE_LDDB_BLOCK_SIZE_J; ++neighborJ)
		{
			BlockHeapCosts[neighborI][neighborJ] = COST_MAX;
		}
	}

	for (unsigned int ir = 0; ir < SIZE + GRID_EXTRA; ++ir)
	{
		for (unsigned int ic = 0; ic < SIZE + GRID_EXTRA; ++ic)
		{
			cost_so_far[ir][ic] = COST_MAX;
		}
	}

	CalculateAxisArray();

	//CalculateStartHeapCost(startBlock, startPosInBlock, nheuristic, npGoal);
	startBlock.posCost = BlockHeapCosts[startBlock.p_x][startBlock.p_y];

	for (unsigned int blkI = 0; blkI < SQUARE_LDDB_BLOCK_SIZE_I; ++blkI)
	{
		for (unsigned int blkJ = 0; blkJ < SQUARE_LDDB_BLOCK_SIZE_J; ++blkJ)
		{
			ClosedList[blkI][blkJ] = false;
			SquarePrevBlock[blkI][blkJ] = Position(-1, -1);
			SquarePrevBlock[blkI][blkJ].posCost = -1;
			SquareClosedList[blkI][blkJ].posCost = COST_MAX;
		}
	}

	SquarePrevBlock[startBlock.p_x][startBlock.p_y] = Position(startBlock.p_x, startBlock.p_y);
	SquarePrevBlock[startBlock.p_x][startBlock.p_y].posCost = COST_MAX;

	priorityFrontier.push(startBlock);

	PrintEgressCellsValuesToFile();
	PrintEgressCellsNeighborValuesToFile();
	PrintCostSoFar();

	bool isFirstExpansion = true;

	while ((!priorityFrontier.empty()) && ((priorityFrontier.top().posCost < startToGoalCost) || (isFirstExpansion)))
	{
		Position curBlock = priorityFrontier.top();

		//Make and clear the temporary list.
		std::list<Position> tempList;
		tempList.clear();

		//Parse through the priority queue until it is empty.
		while (!priorityFrontier.empty())
		{
			//Get the topmost element of the queue.
			Position topOfQueue = priorityFrontier.top();

			//Remove the top element of the priority queue.
			priorityFrontier.pop();

			//Push it to the back of the tempList.
			tempList.push_back(topOfQueue);
		}

		std::cout << "\n Priority Queue:\n";
		for each (Position listItem in tempList)
		{
			std::cout << "[" << listItem.p_x << ", " << listItem.p_y << "]: " << listItem.posCost << ".\t";
		}
		std::cout << "\n";

		//Parse through the temporary list's elements until it is empty.
		while (!tempList.empty())
		{
			//Add the temporary list's front element to the priority queue.
			priorityFrontier.push(tempList.front());

			//Pop out the front element of the tempList.
			tempList.pop_front();
		}


		priorityFrontier.pop();

		//Ingress cells in current block (Y).
		std::vector<Position> ingress_Cells_curBlock;

		CalculateBlockIngressNodes(curBlock, ingress_Cells_curBlock, startPosInBlock, isFirstExpansion);
		isFirstExpansion = false;

		PrintIngressNodes(curBlock, ingress_Cells_curBlock);

		if (curBlock == goalBlock)
		{
			goalBlock.posCost = curBlock.posCost;
			//length = min (y in Y) (y.g + dist(y, goal), length).
			for (unsigned int y = 0; y < ingress_Cells_curBlock.size(); ++y)
			{
				Position ingressPos(ingress_Cells_curBlock[y].p_x, ingress_Cells_curBlock[y].p_y);
				ingressPos.posCost = ingress_Cells_curBlock[y].posCost;

				//dist(y, goal) = SquareLDDB[CurrentBlock][ingress(Y)][GoalPosInBlock].
				double distYG = SquareLDDB[curBlock.p_x][curBlock.p_y][ingressPos.p_x][ingressPos.p_y][goalPosInBlock.p_x][goalPosInBlock.p_y];

				if (distYG < 0.000f)
				{
					continue;
				}

				if ((ingressPos.posCost + distYG) < startToGoalCost)
				{
					//length = y.g + dist(y, goal).
					startToGoalCost = ingressPos.posCost + distYG;
				}
			}
			//break;
		}

		SquareExpandCurBlock(curBlock, ingress_Cells_curBlock, npGoal, nheuristic);

		PrintCostSoFar();

		//If autoCompute or generateInstantaneous is set to true we just keep going through the while loop without asking the user for the next step or printing out the map.
		if (generateInstantaneous || autoCompute)
			continue;

		//If we are going to show the various maps.
		if (showMap == 1)
		{
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
	if (startToGoalCost != COST_MAX)
	{
		//TODO: Reconstruct goal path.

		//Now, traverse backwards from goal to start to save the goal path in a vector.
		Position currentTraverse = goalBlock;

		//Empty the goal path vector completely!
		goalPath.clear();

		//Add the goal position to the goal path vector.
		goalPath.push_back(currentTraverse);

		//Until, we cannot trace back to the start position, we keep repeating the process of updating the current position.
		while (currentTraverse != startBlock)
		{
			//Update currentTraverse to point to the previous position from whence it came.
			currentTraverse = SquarePrevBlock[currentTraverse.p_x][currentTraverse.p_y];

			//Add currentTraverse to the goal path vector.
			goalPath.push_back(currentTraverse);
		}

		//Reverse the whole vector to contain the whole list.
		std::reverse(goalPath.begin(), goalPath.end());

		return startToGoalCost;
	}

	//If goal not found.
	return -1;
}
#endif