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
The expansion of the current block.
Parameters to the function:
curBlock : Position - The current block position.
ingress_Cells_curBlock : std::vector<Position> - The ingress cells of the current block.
goalPos : Position - The goal position.
heuType : HeuristicType - The type of heuristic.
Returns from the function:
NONE
This function takes in the current block, the ingress cells associated with the current block, the goal position, and the heuristic type being used to find and add the valid neighboring blocks to the open list.
*/
void SquareExpandCurBlock(Position curBlock, std::vector<Position> ingress_Cells_curBlock, Position goalPos, HeuristicType heuType)
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

	//The 8 directions heap cost stored.
	double neighborBlocksHeapCost[3][3];

	/*
	Parse through [I,J] for neighbor blocks from (0,0) to (2,2).
	(0,0) - NW.
	(0,1) - N.
	(0,2) - NE.
	(1,0) - W.
	(1,1) - CURRENT.
	(1,2) - E.
	(2,0) - SW.
	(2,1) - S.
	(2,2) - SE.
	*/
	for (unsigned int neighborI = 0; neighborI < 3; ++neighborI)
	{
		for (unsigned int neighborJ = 0; neighborJ < 3; ++neighborJ)
		{
			neighborBlocksHeapCost[neighborI][neighborJ] = COST_MAX;
		}
	}

	//The first corner (top left) of the square block. For a 4x4 block example: 0.
	unsigned int firstCorner = 0;

	//The third corner (bottom right) of the square block. For a 4x4 block example: 6.
	unsigned int thirdCorner = OUTER_BORDERS_SIZE / 2;

	//The second corner (top right) of the square block. For a 4x4 block example: 3.
	unsigned int secondCorner = thirdCorner - (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 1);

	//The fourth corner (bottom left) of the square block. For a 4x4 block example: 9.
	unsigned int fourthCorner = thirdCorner + (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 1);

	//Parse through the outer nodes of the current block.
	for (unsigned int outerAxis = 0; outerAxis < OUTER_BORDERS_SIZE; ++outerAxis)
	{
		//Get the grid absolute value of the current position in the block.
		Position positionInCurBlockGridAbs = SquareEGCellPos[curBlock.p_x][curBlock.p_y][outerAxis];
		
		//Convert and find the current position with respect to the current block.
		Position positionInCurBlock = Position(positionInCurBlockGridAbs.p_x % SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, positionInCurBlockGridAbs.p_y % SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);
		
		//Transfer the cost.
		positionInCurBlock.posCost = positionInCurBlockGridAbs.posCost;

		//Parse through the neighbor relations, in the neighboring blocks, of the current position.
		for (unsigned int maxRel = 0; maxRel < SquareEGCellNumCorners[curBlock.p_x][curBlock.p_y][outerAxis]; ++maxRel)
		{
			//neighbor position in square grid.
			Position neighborPositionInNeighborBlockGridAbs = SquareEGCellNeighborPos[curBlock.p_x][curBlock.p_y][outerAxis][maxRel];

			//neighbor position in neighbor block.
			Position neighborPositionInNeighborBlock(neighborPositionInNeighborBlockGridAbs.p_x % SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, neighborPositionInNeighborBlockGridAbs.p_y % SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);

			//neighbor position's cost info.
			neighborPositionInNeighborBlock.posCost = neighborPositionInNeighborBlockGridAbs.posCost;

			//neighbor block.
			Position neighborBlock((neighborPositionInNeighborBlockGridAbs.p_x - 1) / SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (neighborPositionInNeighborBlockGridAbs.p_y - 1) / SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);

			//If current block's current position's (outerAxis) relation with one of the neighboring block positions (maxRel) is valid.
			if (SquareEgressCells[curBlock.p_x][curBlock.p_y][outerAxis][maxRel])
			{
				//tempCost = x.g.
				double tempCost = positionInCurBlock.posCost;
				for (unsigned int parseIngress = 0; parseIngress < ingress_Cells_curBlock.size(); ++parseIngress)
				{
					Position ingressPos(ingress_Cells_curBlock[parseIngress].p_x, ingress_Cells_curBlock[parseIngress].p_y);
					ingressPos.posCost = ingress_Cells_curBlock[parseIngress].posCost;

					//newCost = y.g + LDDB(y,x).
					double newCost = ingressPos.posCost + SquareLDDB[curBlock.p_x][curBlock.p_y][ingressPos.p_x][ingressPos.p_y][positionInCurBlock.p_x][positionInCurBlock.p_y];

					//min[y in Y](newCost, x.g).
					if (newCost < tempCost)
					{
						//tempCost = newCost.
						tempCost = newCost;
					}
				}

				//currentposCost = tempCost.
				positionInCurBlock.posCost = tempCost;

				//costBetweenPosAndNeighbor = cost(x,x').
				double costBetweenPosAndNeighbor = ((neighborPositionInNeighborBlockGridAbs.p_x == positionInCurBlockGridAbs.p_x) || (neighborPositionInNeighborBlockGridAbs.p_y == positionInCurBlockGridAbs.p_y)) ? COST_AXIS : COST_DIAGONAL;

				//newCost = currentposCost + costBetweenPosAndNeighbor.
				double newCost = positionInCurBlock.posCost + costBetweenPosAndNeighbor;

				//neighborposCost = min(x'.g, newCost).
				if (newCost < neighborPositionInNeighborBlock.posCost)
				{
					neighborPositionInNeighborBlock.posCost = newCost;
				}

				//x.g = currentposCost [x.g = min[y in Y](y.g + LDDB(y,x), x.g)].
				SquareEGCellPos[curBlock.p_x][curBlock.p_y][outerAxis].posCost = positionInCurBlock.posCost;

				//x'.g = neighborposCost [min(x'.g, x.g + cost(x,x'))].
				SquareEGCellNeighborPos[curBlock.p_x][curBlock.p_y][outerAxis][maxRel].posCost = neighborPositionInNeighborBlock.posCost;
			}

			//x'.h.
			double neighborPosToGoalHeuristic = Heuristic(heuType, goalPos.p_x - neighborPositionInNeighborBlockGridAbs.p_x, goalPos.p_y - neighborPositionInNeighborBlockGridAbs.p_y);

			//tempHeapValue = x'.g + x'.h.
			double tempHeapValue = SquareEGCellNeighborPos[curBlock.p_x][curBlock.p_y][outerAxis][maxRel].posCost + neighborPosToGoalHeuristic;

			//One of the 8 directions.
			//Offset addition to remove negativity and change range from (-1 to 1) to (0 to 2).
			//(1,1) will be the current block itself!!
			Position directionBlock((curBlock.p_x - neighborBlock.p_x) + 1, (curBlock.p_y - neighborBlock.p_y) + 1);

			//tempHeapValue < neighborHeapCost.
			if (tempHeapValue < neighborBlocksHeapCost[directionBlock.p_x][directionBlock.p_y])
			{
				//min(updated x')(tempHeapValue).
				//Update the temporary neighbor heap cost storage.
				neighborBlocksHeapCost[directionBlock.p_x][directionBlock.p_y] = tempHeapValue;
			}
		}
	}

	//Parse through the neighbor blocks.
	for (unsigned int neighborI = 0; neighborI < 3; ++neighborI)
	{
		for (unsigned int neighborJ = 0; neighborJ < 3; ++neighborJ)
		{
			//NextBlock.heapValue = newHeapValue.
			Position NeighBlock(curBlock.p_x - (neighborI - 1), curBlock.p_y - (neighborJ - 1));
			NeighBlock.posCost = neighborBlocksHeapCost[neighborI][neighborJ];

			std::list<Position> tempList;
			//Make and clear the temporary list.
			tempList.clear();

			//Parse through the priority queue until it is empty.
			while (!priorityFrontier.empty())
			{
				//Get the topmost element of the queue.
				Position topOfQueue = priorityFrontier.top();

				//Remove the top element of the priority queue.
				priorityFrontier.pop();

				//If that element was the neighbor block, then early exit.
				if ((topOfQueue.p_x == NeighBlock.p_x) || (topOfQueue.p_y == NeighBlock.p_y))
				{
					break;
				}

				//Push it to the back of the tempList.
				tempList.push_back(topOfQueue);
			}

			//Parse through the temporary list's elements until it is empty.
			while (!tempList.empty())
			{
				//Add the temporary list's front element to the priority queue.
				priorityFrontier.push(tempList.front());

				//Pop out the front element of the tempList.
				tempList.pop_front();
			}

			//Push the Neighbor block into the priority queue (updated!).
			//If it was there before, it was removed from the queue!
			//If it was not there before, it is added into the priority queue normally.
			priorityFrontier.push(NeighBlock);
		}
	}
}
#endif