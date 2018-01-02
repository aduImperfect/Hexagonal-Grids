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
unsigned int FindOuterAxis(const Position & curBlock, const unsigned int & curOuterAxis, const unsigned int & curMaxRel)
{

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
This function takes in the neighboring block's heap costs, the current block, the ingress cells associated with the current block, the goal position, and the heuristic type being used to find and add the valid neighboring blocks to the open list.
*/
void SquareExpandCurBlock(const Position & curBlock, const std::vector<Position> ingress_Cells_curBlock, const Position & goalPos, const HeuristicType & heuType)
{
	/*
	Y = set of CurBlock's ingress nodes.
	Expand(CurBlock, Y)
	{
		for side of CurBlock with neighbor NextBlock
		{
			for valid egress node x on current side
			{
				x' = egress neighbor of x on current side
				x.g = min[y in Y](y.g + LDDB(y,x), x.g)
				x'.g = min(x'.g, x.g + cost(x,x'))
			}
			newheapvalue (priority) = min(updated x')(x'.g + x'.h)
			if(newheapvalue < NextBlock.heapvalue)
			{
				NextBlock.heapvalue = newheapvalue
				if(NextBlock not in OPEN)
				{
					insert NextBlock into OPEN
				}
				else
				{
					UpdateOPEN(NextBlock)
				}
			}
		}
	}
	*/

	//Parse through the outer nodes of the current block.
	for (unsigned int outerAxis = 0; outerAxis < OUTER_BORDERS_SIZE; ++outerAxis)
	{
		//Get the grid absolute value of the current position in the block.
		Position positionInCurBlockGridAbs = SquareEGCellPos[curBlock.p_x][curBlock.p_y][outerAxis];
		
		//Convert and find the current position with respect to the current block.
		Position positionInCurBlock((positionInCurBlockGridAbs.p_x - 1) % SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (positionInCurBlockGridAbs.p_y - 1) % SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);
		
		//Transfer the cost.
		positionInCurBlock.posCost = positionInCurBlockGridAbs.posCost;

		//////////////////////////////////////////////////////////
		//Code shift from INTERNAL:
		//It is redundant to be calculated there as it has no relation to any of the code inside the other for loops. 
		//Better to calculate it once for every outerAxis and then use it later as needed.

		//tempCost = x.g.
		double tempCost = positionInCurBlock.posCost;
		for (unsigned int parseIngress = 0; parseIngress < ingress_Cells_curBlock.size(); ++parseIngress)
		{
			Position ingressPos(ingress_Cells_curBlock[parseIngress].p_x, ingress_Cells_curBlock[parseIngress].p_y);
			ingressPos.posCost = ingress_Cells_curBlock[parseIngress].posCost;

			double LDDBCost = SquareLDDB[curBlock.p_x][curBlock.p_y][ingressPos.p_x][ingressPos.p_y][positionInCurBlock.p_x][positionInCurBlock.p_y];

			//newCost = y.g + LDDB(y,x).
			double newCost = ingressPos.posCost + (LDDBCost < 0) ? COST_MAX : LDDBCost;

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
			Position neighborPositionInNeighborBlockGridAbs = SquareEGCellNeighborPos[curBlock.p_x][curBlock.p_y][outerAxis][maxRel];

			//neighbor position in neighbor block.
			Position neighborPositionInNeighborBlock((neighborPositionInNeighborBlockGridAbs.p_x - 1) % SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (neighborPositionInNeighborBlockGridAbs.p_y - 1) % SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);

			if (neighborPositionInNeighborBlock.p_x < 0)
			{
				neighborPositionInNeighborBlock.p_x = SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + neighborPositionInNeighborBlock.p_x;
			}
			if (neighborPositionInNeighborBlock.p_y < 0)
			{
				neighborPositionInNeighborBlock.p_y = SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + neighborPositionInNeighborBlock.p_y;
			}

			//neighbor position's cost info.
			neighborPositionInNeighborBlock.posCost = neighborPositionInNeighborBlockGridAbs.posCost;

			Position tmpBlk(neighborPositionInNeighborBlockGridAbs.p_x - 1, neighborPositionInNeighborBlockGridAbs.p_y - 1);

			//neighbor block.
			Position neighborBlock((tmpBlk.p_x < 0) ? (tmpBlk.p_x / SQUARE_LDDB_BLOCK_SPLIT_SIZE_X) - 1 : tmpBlk.p_x / SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (tmpBlk.p_y < 0) ? (tmpBlk.p_y / SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y) - 1: tmpBlk.p_y / SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);

			//If current block's current position's (outerAxis) relation with one of the neighboring block positions (maxRel) is valid.
			if (SquareEgressCells[curBlock.p_x][curBlock.p_y][outerAxis][maxRel])
			{
				//INTERNAL:

				//costBetweenPosAndNeighbor = cost(x,x').
				double costBetweenPosAndNeighbor = ((neighborPositionInNeighborBlockGridAbs.p_x == positionInCurBlockGridAbs.p_x) || (neighborPositionInNeighborBlockGridAbs.p_y == positionInCurBlockGridAbs.p_y)) ? COST_AXIS : COST_DIAGONAL;

				//newCost = currentposCost + costBetweenPosAndNeighbor.
				double newCost = positionInCurBlock.posCost + costBetweenPosAndNeighbor;

				//neighborposCost = min(x'.g, newCost).
				if (newCost < neighborPositionInNeighborBlock.posCost)
				{
					neighborPositionInNeighborBlock.posCost = newCost;
				}

				//x'.g = neighborposCost [min(x'.g, x.g + cost(x,x'))].
				SquareEGCellNeighborPos[curBlock.p_x][curBlock.p_y][outerAxis][maxRel].posCost = cost_so_far[neighborPositionInNeighborBlockGridAbs.p_x][neighborPositionInNeighborBlockGridAbs.p_y] = neighborPositionInNeighborBlock.posCost;
			}

			//x'.h.
			double neighborPosToGoalHeuristic = Heuristic(heuType, goalPos.p_x - neighborPositionInNeighborBlockGridAbs.p_x, goalPos.p_y - neighborPositionInNeighborBlockGridAbs.p_y);

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

	//Parse through the neighbor blocks.
	for (unsigned int neighborI = 0; neighborI < 3; ++neighborI)
	{
		for (unsigned int neighborJ = 0; neighborJ < 3; ++neighborJ)
		{
			if ((neighborI == 1) && (neighborJ == 1))
				continue;

			//NextBlock.heapValue = newHeapValue.
			Position NeighBlock(curBlock.p_x + (neighborI - 1), curBlock.p_y + (neighborJ - 1));
			
			if ((NeighBlock.p_x < 0) || (NeighBlock.p_y < 0) || (NeighBlock.p_x >= SQUARE_LDDB_BLOCK_SIZE_I) || (NeighBlock.p_y >= SQUARE_LDDB_BLOCK_SIZE_J))
			{
				continue;
			}
			else
			{
				NeighBlock.posCost = BlockHeapCosts[NeighBlock.p_x][NeighBlock.p_y];
			}

			//if (NeighBlock.posCost == COST_MAX)
			//{
				//continue;
			//}

			std::list<Position> tempList;
			//Make and clear the temporary list.
			tempList.clear();

			bool isFound = false;

			//Parse through the priority queue until it is empty.
			while (!priorityFrontier.empty())
			{
				//Get the topmost element of the queue.
				Position topOfQueue = priorityFrontier.top();

				//Remove the top element of the priority queue.
				priorityFrontier.pop();

				//If that element was the neighbor block, then early exit.
				if ((topOfQueue.p_x == NeighBlock.p_x) && (topOfQueue.p_y == NeighBlock.p_y))
				{
					isFound = true;
					if (NeighBlock.posCost < topOfQueue.posCost)
					{
						//Push it to the back of the tempList.
						tempList.push_back(NeighBlock);
						break;
					}
				}
				
				//Push it to the back of the tempList.
				tempList.push_back(topOfQueue);
			}

			if (!isFound)
			{
				tempList.push_back(NeighBlock);
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
}
#endif