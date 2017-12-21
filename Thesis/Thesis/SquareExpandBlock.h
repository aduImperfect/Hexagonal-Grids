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
void SquareExpandCurBlock(Position curBlock, std::vector<Position> ingress_Cells_curBlock)
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

	//The first corner (top left) of the square block. For a 4x4 block example: 0.
	unsigned int firstCorner = 0;

	//The third corner (bottom right) of the square block. For a 4x4 block example: 6.
	unsigned int thirdCorner = OUTER_BORDERS_SIZE / 2;

	//The second corner (top right) of the square block. For a 4x4 block example: 3.
	unsigned int secondCorner = thirdCorner - (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 1);

	//The fourth corner (bottom left) of the square block. For a 4x4 block example: 9.
	unsigned int fourthCorner = thirdCorner + (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 1);

	for (unsigned int outerAxis = 0; outerAxis < OUTER_BORDERS_SIZE; ++outerAxis)
	{
		Position positionInCurBlockGridAbs = SquareEGCellPos[curBlock.p_x][curBlock.p_y][outerAxis];
		Position positionInCurBlock = Position(positionInCurBlockGridAbs.p_x % SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, positionInCurBlockGridAbs.p_y % SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);
		
		positionInCurBlock.posCost = positionInCurBlockGridAbs.posCost;

		for (unsigned int maxRel = 0; maxRel < SquareEGCellNumCorners[curBlock.p_x][curBlock.p_y][outerAxis]; ++maxRel)
		{
			if (SquareEgressCells[curBlock.p_x][curBlock.p_y][outerAxis][maxRel])
			{
				Position neighborPositionInNeighborBlockGridAbs = SquareEGCellNeighborPos[curBlock.p_x][curBlock.p_y][outerAxis][maxRel];
				Position neighborPositionInNeighborBlock = Position(neighborPositionInNeighborBlockGridAbs.p_x % SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, neighborPositionInNeighborBlockGridAbs.p_y % SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);

				neighborPositionInNeighborBlock.posCost = neighborPositionInNeighborBlockGridAbs.posCost;

				double tempCost = positionInCurBlock.posCost;
				for (unsigned int parseIngress = 0; parseIngress < ingress_Cells_curBlock.size(); ++parseIngress)
				{
					Position ingressPos(ingress_Cells_curBlock[parseIngress].p_x, ingress_Cells_curBlock[parseIngress].p_y);
					ingressPos.posCost = ingress_Cells_curBlock[parseIngress].posCost;

					double newCost = ingressPos.posCost + SquareLDDB[curBlock.p_x][curBlock.p_y][ingressPos.p_x][ingressPos.p_y][positionInCurBlock.p_x][positionInCurBlock.p_y];

					if (newCost < tempCost)
					{
						tempCost = newCost;
					}
				}
				positionInCurBlock.posCost = tempCost;

				double costBetweenPosAndNeighbor = ((neighborPositionInNeighborBlockGridAbs.p_x == positionInCurBlockGridAbs.p_x) || (neighborPositionInNeighborBlockGridAbs.p_y == positionInCurBlockGridAbs.p_y)) ? COST_AXIS : COST_DIAGONAL;
				
				double newCost = positionInCurBlock.posCost + costBetweenPosAndNeighbor;
				neighborPositionInNeighborBlock.posCost = (neighborPositionInNeighborBlock.posCost < newCost) ? neighborPositionInNeighborBlock.posCost : newCost;

				SquareEGCellPos[curBlock.p_x][curBlock.p_y][outerAxis].posCost = positionInCurBlock.posCost;
				SquareEGCellNeighborPos[curBlock.p_x][curBlock.p_y][outerAxis][maxRel].posCost = neighborPositionInNeighborBlock.posCost;

				//ABOVE CODE NOT YET NEIGHBOR SIDE DEPENDENT!! NEED TO DO THAT FOR THE NEXT STEP BELOW. (Min being found only in the side of current block adjacent to a neighbor block).
				/*
				newheapvalue (priority) = min(updated x')(x'.g + x'.h)
				if(newheapvalue < NextBlock.heapvalue)
				*/


			}
		}
	}
}
#endif