///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: SquareExpandBlock.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef SQUARE_EXPAND_BLOCK_H
#define SQUARE_EXPAND_BLOCK_H
//Including the base headers for the base square operations, the position structure, the position relations structures, and the egress cells calculations.
#include "BaseSquareOperations.h"
#include "Position.h"
#include "PositionRelations.h"
#include "EgressCells.h"
#include "ValidEgressCells.h"
#include "EgressCellsToFile.h"

/*

*/
void RegisterNeighborToCur(const Position & curBlock, const unsigned int & curOuterAxis, const unsigned int & curMaxRel, const Position & neighBlock, const Position & neighPosInBlock, const Position & neighPosGridAbs)
{
	if (AxisArray[neighPosInBlock.p_x][neighPosInBlock.p_y] == -1)
	{
		return;
	}

	unsigned int neiOuterAxis = AxisArray[neighPosInBlock.p_x][neighPosInBlock.p_y];

	if (SquareEGCellNeighborPos[curBlock.p_x][curBlock.p_y][curOuterAxis][curMaxRel].posCost < SquareEGCellPos[neighBlock.p_x][neighBlock.p_y][neiOuterAxis].posCost)
	{
		SquareEGCellPos[neighBlock.p_x][neighBlock.p_y][neiOuterAxis] = SquareEGCellNeighborPos[curBlock.p_x][curBlock.p_y][curOuterAxis][curMaxRel];
		cost_so_far[neighPosGridAbs.p_x][neighPosGridAbs.p_y] = SquareEGCellPos[neighBlock.p_x][neighBlock.p_y][neiOuterAxis].posCost;
	}
}

/*

*/
void EgressCellsUpdation(const Position & curBlock)
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
		//Parse through the neighbor relations, in the neighboring blocks, of the current position.
		for (unsigned int maxRel = 0; maxRel < SquareEGCellNumCorners[curBlock.p_x][curBlock.p_y][outerAxis]; ++maxRel)
		{
			//neighbor position in square grid.
			Position neighborPositionInSquareGrid = SquareEGCellNeighborPos[curBlock.p_x][curBlock.p_y][outerAxis][maxRel];

			//neighbor position in neighbor block.
			Position neighborPositionInNeighborBlock((neighborPositionInSquareGrid.p_x - 1) % SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (neighborPositionInSquareGrid.p_y - 1) % SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);

			if (neighborPositionInNeighborBlock.p_x < 0)
			{
				neighborPositionInNeighborBlock.p_x = SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + neighborPositionInNeighborBlock.p_x;
			}
			if (neighborPositionInNeighborBlock.p_y < 0)
			{
				neighborPositionInNeighborBlock.p_y = SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + neighborPositionInNeighborBlock.p_y;
			}

			//neighbor position's cost info.
			neighborPositionInNeighborBlock.posCost = neighborPositionInSquareGrid.posCost;

			Position tmpBlk(neighborPositionInSquareGrid.p_x - 1, neighborPositionInSquareGrid.p_y - 1);

			//neighbor block.
			Position neighborBlock((tmpBlk.p_x < 0) ? (tmpBlk.p_x / SQUARE_LDDB_BLOCK_SPLIT_SIZE_X) - 1 : tmpBlk.p_x / SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (tmpBlk.p_y < 0) ? (tmpBlk.p_y / SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y) - 1 : tmpBlk.p_y / SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);

			RegisterNeighborToCur(curBlock, outerAxis, maxRel, neighborBlock, neighborPositionInNeighborBlock, neighborPositionInSquareGrid);
		}
	}
}

/*

*/
void PrintEgressCellsValuesToFile()
{
	//Find the Egress cells file SquareEGCellPos.txt and open it.
	std::ofstream egressCellsPosFile;
	egressCellsPosFile.open("SquareEGCellPos.txt");

	egressCellsPosFile << "\n";

	//Parse through the outer nodes of the current block.
	for (unsigned int blockI = 0; blockI < SQUARE_LDDB_BLOCK_SIZE_I; ++blockI)
	{
		for (unsigned int blockJ = 0; blockJ < SQUARE_LDDB_BLOCK_SIZE_J; ++blockJ)
		{
#pragma region BLOCK_NO
			//Append (print) Block[I][J].
			egressCellsPosFile << "\nBlock[" << blockI << "][" << blockJ << "]:\n";
#pragma endregion


#pragma region COL_FIRST_HEADER
			//Append all the TO[n] subscripts as the first row header.
			egressCellsPosFile << "\t\t\t";
			for (int axisCol = 0; axisCol < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++axisCol)
			{
				egressCellsPosFile << "[" << axisCol << "]\t\t\t";
			}
			egressCellsPosFile << "\n";
#pragma endregion

			for (unsigned int axisRow = 0; axisRow < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++axisRow)
			{
				egressCellsPosFile << "[" << axisRow << "]:\t\t";
				for (unsigned int axisCol = 0; axisCol < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++axisCol)
				{
					bool isInf = false;
					if ((AxisArray[axisRow][axisCol] == -1) || (SquareEGCellPos[blockI][blockJ][AxisArray[axisRow][axisCol]].posCost == COST_MAX))
					{
						isInf = true;
						egressCellsPosFile << "infi";
					}
					else
					{
						egressCellsPosFile << SquareEGCellPos[blockI][blockJ][AxisArray[axisRow][axisCol]].posCost;
					}

					//Calculate the number of \t (tabs) to be appended (printed) to the file based on the value.
					int tempVal = static_cast<int>(SquareEGCellPos[blockI][blockJ][AxisArray[axisRow][axisCol]].posCost * 100);
					if ((tempVal % 100) != 0)
					{
						egressCellsPosFile << "\t\t";
					}
					else
					{
						if (isInf)
						{
							egressCellsPosFile << "\t\t";
						}
						else
						{
							egressCellsPosFile << "\t\t\t";
						}
					}
				}
				egressCellsPosFile << "\n";
			}
			egressCellsPosFile << "\n";
		}
	}

	egressCellsPosFile.close();
}

/*

*/
void PrintEgressCellsNeighborValuesToFile()
{
	//Find the Egress cells file SquareEGCellPos.txt and open it.
	std::ofstream egressCellsNeigborPosFile;
	egressCellsNeigborPosFile.open("SquareEGCellNeighborPos.txt");

	egressCellsNeigborPosFile << "\n";

	//The total number of elements in each block.
	unsigned int nTotalSize = SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y;

	//The total number of non-corner elements in each block.
	unsigned int nInnerSize = (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 2) * (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 2);

	//The total number of (in and out)corner elements in each block.
	const unsigned int nOuterBordersSize = nTotalSize - nInnerSize;

	//Parse through the outer nodes of the current block.
	for (unsigned int blockI = 0; blockI < SQUARE_LDDB_BLOCK_SIZE_I; ++blockI)
	{
		for (unsigned int blockJ = 0; blockJ < SQUARE_LDDB_BLOCK_SIZE_J; ++blockJ)
		{
#pragma region BLOCK_NO
			//Append (print) Block[I][J].
			egressCellsNeigborPosFile << "\nBlock[" << blockI << "][" << blockJ << "]:\n";
#pragma endregion

			for (unsigned int outerK = 0; outerK < nOuterBordersSize; ++outerK)
			{
				egressCellsNeigborPosFile << "\t\t\t";
				for (unsigned int relL = 0; relL < SquareEGCellNumCorners[blockI][blockJ][outerK]; ++relL)
				{
					if ((SquareEGCellNeighborPos[blockI][blockJ][outerK][relL].p_x > 9) && (SquareEGCellNeighborPos[blockI][blockJ][outerK][relL].p_y > 9))
					{
						egressCellsNeigborPosFile << "[" << SquareEGCellNeighborPos[blockI][blockJ][outerK][relL].p_x << "][" << SquareEGCellNeighborPos[blockI][blockJ][outerK][relL].p_y << "]\t";
					}
					else if ((SquareEGCellNeighborPos[blockI][blockJ][outerK][relL].p_x < 0) && (SquareEGCellNeighborPos[blockI][blockJ][outerK][relL].p_y < 0))
					{
						egressCellsNeigborPosFile << "[" << SquareEGCellNeighborPos[blockI][blockJ][outerK][relL].p_x << "][" << SquareEGCellNeighborPos[blockI][blockJ][outerK][relL].p_y << "]\t";
					}
					else
					{
						egressCellsNeigborPosFile << "[" << SquareEGCellNeighborPos[blockI][blockJ][outerK][relL].p_x << "][" << SquareEGCellNeighborPos[blockI][blockJ][outerK][relL].p_y << "]\t\t";
					}
				}
				egressCellsNeigborPosFile << "\n";

				if ((SquareEGCellPos[blockI][blockJ][outerK].p_x > 9) || (SquareEGCellPos[blockI][blockJ][outerK].p_y > 9))
				{
					egressCellsNeigborPosFile << "[" << SquareEGCellPos[blockI][blockJ][outerK].p_x << "][" << SquareEGCellPos[blockI][blockJ][outerK].p_y << "]:\t";
				}
				else
				{
					egressCellsNeigborPosFile << "[" << SquareEGCellPos[blockI][blockJ][outerK].p_x << "][" << SquareEGCellPos[blockI][blockJ][outerK].p_y << "]:\t\t";
				}

				for (unsigned int relL = 0; relL < SquareEGCellNumCorners[blockI][blockJ][outerK]; ++relL)
				{
					bool isInf = false;
					if(SquareEGCellNeighborPos[blockI][blockJ][outerK][relL].posCost == COST_MAX)
					{
						isInf = true;
						egressCellsNeigborPosFile << "infi";
					}
					else
					{
						egressCellsNeigborPosFile << SquareEGCellNeighborPos[blockI][blockJ][outerK][relL].posCost;
					}

					//Calculate the number of \t (tabs) to be appended (printed) to the file based on the value.
					int tempVal = static_cast<int>(SquareEGCellNeighborPos[blockI][blockJ][outerK][relL].posCost * 100);
					if ((tempVal % 100) != 0)
					{
						egressCellsNeigborPosFile << "\t\t";
					}
					else
					{
						if (isInf)
						{
							egressCellsNeigborPosFile << "\t\t";
						}
						else
						{
							egressCellsNeigborPosFile << "\t\t\t";
						}
					}
				}
				
				egressCellsNeigborPosFile << "\n";
			}

			egressCellsNeigborPosFile << "\n";
		}
	}

	egressCellsNeigborPosFile.close();
}

/*
Updating the OPEN AND CLOSED LISTS.
Parameters to the function:
curBlock : const Position & - The current block position.
Returns from the function:
NONE
This function takes in the current block and updates the OPEN and CLOSED lists based on the Heap cost values.
*/
void UpdateOpenClosedLists(const Position & curBlock)
{
	//Parse through the neighbor blocks.
	for (unsigned int neighborI = 0; neighborI < 3; ++neighborI)
	{
		for (unsigned int neighborJ = 0; neighborJ < 3; ++neighborJ)
		{
			//If it is the current block (continue).
			if ((neighborI == 1) && (neighborJ == 1))
				continue;

			Position ChildBlock(curBlock.p_x + (neighborI - 1), curBlock.p_y + (neighborJ - 1));

			//If ChildBlock axis points are out of bounds of the square grid, skip it.
			if ((ChildBlock.p_x < 0) || (ChildBlock.p_y < 0) || (ChildBlock.p_x >= SQUARE_LDDB_BLOCK_SIZE_I) || (ChildBlock.p_y >= SQUARE_LDDB_BLOCK_SIZE_J))
			{
				continue;
			}
			else
			{
				//ChildBlock.heapValue = newHeapValue (stored in the BlockHeapCosts[][] array).
				ChildBlock.posCost = BlockHeapCosts[ChildBlock.p_x][ChildBlock.p_y];
			}

			//If ChildBlock's heap cost is INFINITE (MAX!!!), skip as we don't care about an unreachable block.
			if (ChildBlock.posCost == COST_MAX)
			{
				continue;
			}

			//Make and clear the temporary list.
			std::list<Position> tempList;
			tempList.clear();

			//A boolean for if the 'Block' isFound.
			bool isFoundInOpen = false;
			bool isFoundInClosed = false;

			bool isLessInOpen = false;
			bool isLessInClosed = false;

			Position * itemFoundInOpen = nullptr;

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

			for each (Position listItem in tempList)
			{
				//If that element was the neighbor block.
				//If ChildBlock is not in open list (priorityFrontier), skip.
				if ((listItem.p_x != ChildBlock.p_x) || (listItem.p_y != ChildBlock.p_y))
					continue;

				isFoundInOpen = true;
				itemFoundInOpen = &listItem;

				//If ChildBlock's cost is more than that the same item's cost in the open list, skip.
				if (ChildBlock.posCost >= listItem.posCost)
					continue;

				//Found the item in the OPEN (Priority queue) list and the new heap cost is smaller.
				isLessInOpen = true;

				//Break out of the loop as the search has ended.
				break;
			}

			//If ChildBlock is in ClosedList. (If it was already checked against in the OPEN list and found with cheaper cost, then it would have already been removed from the Closed List.
			//Hence, the ChildBlock (if found in the ClosedList) points to either, it not being in the OPEN list or it being in the OPEN list but with an already cheapest cost than ChildBlock's heap cost info.
			if (ClosedList[ChildBlock.p_x][ChildBlock.p_y])
			{
				isFoundInClosed = true;

				//If ChildBlock's cost is less than that the same item's cost in the closed list.
				if (ChildBlock.posCost < SquareClosedList[ChildBlock.p_x][ChildBlock.p_y].posCost)
				{
					isLessInClosed = true;
				}
			}

			//*
			//If not found in open list and not found in closed list!!
			if (!isFoundInOpen && !isFoundInClosed)
			{	
				//Store the path to previous block (which is the current block) from this Neighbor block.
				SquarePrevBlock[ChildBlock.p_x][ChildBlock.p_y] = curBlock;

				//Push it to the back of the tempList.
				tempList.push_back(ChildBlock);
			}
			//*/

			//If found in open list/closed list and is having less heap cost!!
			//If check below auto implies that it is found in OPEN list.
			else
			{
				if (isLessInOpen || isLessInClosed)
				{
					//We remove it from the closed list.
					ClosedList[ChildBlock.p_x][ChildBlock.p_y] = false;

					//Set the heap cost for that block position in the closed list to INFINITY to signify that its not in the list anymore!!
					SquareClosedList[ChildBlock.p_x][ChildBlock.p_y].posCost = COST_MAX;
					//

					//Store the path to previous block (which is the current block) from this Neighbor block.
					SquarePrevBlock[ChildBlock.p_x][ChildBlock.p_y] = curBlock;

					if (itemFoundInOpen)
					{
						//Remove item from OPEN LIST.
						tempList.remove(*itemFoundInOpen);
					}

					//Push the new cheaper heap cost ChildBlock into the OPEN LIST.
					tempList.push_back(ChildBlock);
				}
			}

			//Parse through the temporary list's elements until it is empty.
			while (!tempList.empty())
			{
				//Add the temporary list's front element to the priority queue.
				priorityFrontier.push(tempList.front());

				//Pop out the front element of the tempList.
				tempList.pop_front();
			}
		}
	}

	//In the end, add the current block to the ClosedList.
	ClosedList[curBlock.p_x][curBlock.p_y] = true;

	//Set the value of the closed list item with the block position and its heap cost.
	SquareClosedList[curBlock.p_x][curBlock.p_y] = Position(curBlock.p_x, curBlock.p_y);
	SquareClosedList[curBlock.p_x][curBlock.p_y].posCost = curBlock.posCost;
}

/*
The expansion of the current block.
Parameters to the function:
curBlock : const Position & - The current block position.
ingress_Cells_curBlock : std::vector<Position> - The ingress cells of the current block.
goalPos : Position - The goal position.
heuType : HeuristicType - The type of heuristic.
Returns from the function:
NONE
This function takes in the current block, the ingress cells associated with the current block, the goal position, and the heuristic type being used to find and add the valid neighboring blocks to the open list.
*/
void SquareExpandCurBlock(const Position & curBlock, const std::vector<Position> ingress_Cells_curBlock, const Position & goalPos, const HeuristicType & heuType)
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
		//Current Position in Square Grid.
		Position currentPosInSquareGrid = SquareEGCellPos[curBlock.p_x][curBlock.p_y][outerAxis];
		
		//Convert and find the current position with respect to the current block.
		Position positionInCurBlock((currentPosInSquareGrid.p_x - 1) % SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (currentPosInSquareGrid.p_y - 1) % SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);
		
		//Transfer the cost.
		positionInCurBlock.posCost = currentPosInSquareGrid.posCost;

		//////////////////////////////////////////////////////////
		//Code shift from ORIGINAL ALGO!
		//It is redundant to be calculated there as it has no relation to any of the code inside the other for loops. 
		//Better to calculate it once for every outerAxis and then use it later as needed.

		//tempCost = x.g.
		double tempCost = positionInCurBlock.posCost;
		
		//Parse the ingress cells of the current block.
		for (unsigned int parseIngress = 0; parseIngress < ingress_Cells_curBlock.size(); ++parseIngress)
		{
			//Store Ingress Position into a local variable.
			Position ingressPos(ingress_Cells_curBlock[parseIngress].p_x, ingress_Cells_curBlock[parseIngress].p_y);
			ingressPos.posCost = ingress_Cells_curBlock[parseIngress].posCost;

			//Get the LDDB cost stored in the SquareLDDB database = LDDB(y,x).
			double LDDBCost = SquareLDDB[curBlock.p_x][curBlock.p_y][ingressPos.p_x][ingressPos.p_y][positionInCurBlock.p_x][positionInCurBlock.p_y];

			//Convert float to int with a large multiplier of 1000 for better approximation.
			int LDDBInt = (int)(LDDBCost * 1000.00000f);

			//If the integral value is between -1 and 1 (negligible compared to large numbers) then set it to 0.
			LDDBInt = ((LDDBInt >= -1) && (LDDBInt <= 1)) ? 0 : LDDBInt;

			//newCost = y.g + LDDB(y,x).
			double newCost = ingressPos.posCost + ((LDDBInt < 0) ? COST_MAX : LDDBCost);

			//min[y in Y](newCost, x.g).
			if (newCost < tempCost)
			{
				//tempCost = newCost.
				tempCost = newCost;
			}
		}

		//currentposCost = tempCost.
		positionInCurBlock.posCost = tempCost;

		//x.g = currentposCost [x.g = min[y in Y](y.g + LDDB(y,x), x.g)].
		SquareEGCellPos[curBlock.p_x][curBlock.p_y][outerAxis].posCost = positionInCurBlock.posCost;
		//////////////////////////////////////////////////////////

		//Parse through the neighbor relations, in the neighboring blocks, of the current position.
		for (unsigned int maxRel = 0; maxRel < SquareEGCellNumCorners[curBlock.p_x][curBlock.p_y][outerAxis]; ++maxRel)
		{
			//neighbor position in square grid.
			Position neighborPositionInSquareGrid = SquareEGCellNeighborPos[curBlock.p_x][curBlock.p_y][outerAxis][maxRel];

			//neighbor position in neighbor block.
			Position neighborPositionInNeighborBlock((neighborPositionInSquareGrid.p_x - 1) % SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (neighborPositionInSquareGrid.p_y - 1) % SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);

			if (neighborPositionInNeighborBlock.p_x < 0)
			{
				neighborPositionInNeighborBlock.p_x = SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + neighborPositionInNeighborBlock.p_x;
			}
			if (neighborPositionInNeighborBlock.p_y < 0)
			{
				neighborPositionInNeighborBlock.p_y = SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + neighborPositionInNeighborBlock.p_y;
			}

			//neighbor position's cost info.
			neighborPositionInNeighborBlock.posCost = neighborPositionInSquareGrid.posCost;

			//Array type neighbor Pos?
			Position neiPosMinOne(neighborPositionInSquareGrid.p_x - 1, neighborPositionInSquareGrid.p_y - 1);

			//neighbor block.
			Position neighborBlock((neiPosMinOne.p_x < 0) ? (neiPosMinOne.p_x / SQUARE_LDDB_BLOCK_SPLIT_SIZE_X) - 1 : neiPosMinOne.p_x / SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (neiPosMinOne.p_y < 0) ? (neiPosMinOne.p_y / SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y) - 1: neiPosMinOne.p_y / SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);

			//If current block's current position's (outerAxis) relation with one of the neighboring block positions (maxRel) is valid.
			if (SquareEgressCells[curBlock.p_x][curBlock.p_y][outerAxis][maxRel])
			{
				//costBetweenCurrentAndNeighbor = cost(x,x').
				double costBetweenCurrentAndNeighbor = ((neighborPositionInSquareGrid.p_x == currentPosInSquareGrid.p_x) || (neighborPositionInSquareGrid.p_y == currentPosInSquareGrid.p_y)) ? COST_AXIS : COST_DIAGONAL;

				//newCost = currentposCost + costBetweenPosAndNeighbor.
				double newCost = positionInCurBlock.posCost + costBetweenCurrentAndNeighbor;

				//neighborposCost = min(x'.g, newCost).
				if (newCost < neighborPositionInNeighborBlock.posCost)
				{
					neighborPositionInNeighborBlock.posCost = newCost;
				}

				//x'.g = neighborposCost [min(x'.g, x.g + cost(x,x'))].
				SquareEGCellNeighborPos[curBlock.p_x][curBlock.p_y][outerAxis][maxRel].posCost = neighborPositionInNeighborBlock.posCost;
			}

			//Neighbor Position To Goal Heuristic = x'.h.
			double neighborPosToGoalHeuristic = Heuristic(heuType, abs(goalPos.p_x - neighborPositionInSquareGrid.p_x), abs(goalPos.p_y - neighborPositionInSquareGrid.p_y));

			//tempHeapValue = x'.g + x'.h.
			double tempHeapValue = SquareEGCellNeighborPos[curBlock.p_x][curBlock.p_y][outerAxis][maxRel].posCost + neighborPosToGoalHeuristic;

			//tempHeapValue < neighborHeapCost.
			if (((neighborBlock.p_x >= 0) && (neighborBlock.p_y >= 0) && (neighborBlock.p_x < SQUARE_LDDB_BLOCK_SIZE_I) && (neighborBlock.p_y < SQUARE_LDDB_BLOCK_SIZE_J)) && (tempHeapValue < BlockHeapCosts[neighborBlock.p_x][neighborBlock.p_y]))
			{
				//min(updated x')(tempHeapValue).
				//Update the temporary neighbor heap cost storage.
				BlockHeapCosts[neighborBlock.p_x][neighborBlock.p_y] = tempHeapValue;
			}
		}
	}

	//Update the Egress Cells values' of the Current (and Neighbor Block).
	EgressCellsUpdation(curBlock);

	//Print the Egress Cells' Values to File.
	PrintEgressCellsValuesToFile();

	//Print the Egress Cells' Neighbor Values to File.
	PrintEgressCellsNeighborValuesToFile();

	//Update the Open and Closed lists with the Neighboring Blocks as needed.
	UpdateOpenClosedLists(curBlock);
}
#endif