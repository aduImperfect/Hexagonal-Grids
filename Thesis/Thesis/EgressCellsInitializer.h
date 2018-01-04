///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: EgressCellsInitializer.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef EGRESS_CELLS_INITIALIZER_H
#define EGRESS_CELLS_INITIALIZER_H
//Including the base defines header.
#include "BaseDefines.h"
#include "PositionRelations.h"
#include "EgressCells.h"
#include "ValidEgressCells.h"

/*
Initialize the egress cells.
Parameters to the function:
NONE
Returns from the function:
NONE
This function takes in nothing, and calculates the egress cells for each block.
*/
void EgressCellsInitialize()
{
	//The total number of elements in each block.
	unsigned int nTotalSize = SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y;
	
	//The total number of non-corner elements in each block.
	unsigned int nInnerSize = (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 2) * (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 2);
	
	//The total number of (in and out)corner elements in each block.
	const unsigned int nOuterBordersSize = nTotalSize - nInnerSize;

	//Parse through the Blocks[I][J] (If a 20x20 grid with a block containing 4x4 elements then there are 25 (5x5) blocks).
	for (unsigned int blockI = 0; blockI < SQUARE_LDDB_BLOCK_SIZE_I; ++blockI)
	{
		for (unsigned int blockJ = 0; blockJ < SQUARE_LDDB_BLOCK_SIZE_J; ++blockJ)
		{

			PositionRelations * egressCellsArray = new PositionRelations[nOuterBordersSize];
			
			//Parse through all the corner nodes of the block.
			for (unsigned int nEgCell = 0; nEgCell < nOuterBordersSize; ++nEgCell)
			{
				egressCellsArray[nEgCell];
			}

			Position curBlock(blockI, blockJ);

			//Calculate the Egress Cells info for the current block.
			EgressCells(curBlock, egressCellsArray, nOuterBordersSize);

			//Validate the Egress Cells info for the current block.
			ValidateEgressCells(curBlock, egressCellsArray, nOuterBordersSize);

			//Parse through all the corner nodes of the block.
			for (unsigned int outerAxis = 0; outerAxis < nOuterBordersSize; ++outerAxis)
			{
				//Store the number of maximum relations to a printable array.
				SquareEGCellNumCorners[blockI][blockJ][outerAxis] = egressCellsArray[outerAxis].max_rel;

				BlockPosition blkPos = egressCellsArray[outerAxis].pos_From;

				//Store the current block's grid position to a printable array.
				SquareEGCellPos[blockI][blockJ][outerAxis].p_x = blkPos.pos_BlockNo.p_x * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + blkPos.pos_RelPos.p_x;
				SquareEGCellPos[blockI][blockJ][outerAxis].p_y = blkPos.pos_BlockNo.p_y * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + blkPos.pos_RelPos.p_y;
				SquareEGCellPos[blockI][blockJ][outerAxis].posCost = COST_MAX;

				//Parse through all the neighbor blocks' nodes' relations with the current node.
				for (unsigned int maxRel = 0; maxRel < egressCellsArray[outerAxis].max_rel; ++maxRel)
				{
					BlockPosition neighBlkPos = egressCellsArray[outerAxis].pos_To[maxRel];

					//Store the neighbor block's position's grid position to a printable array.
					SquareEGCellNeighborPos[blockI][blockJ][outerAxis][maxRel] = Position(neighBlkPos.pos_BlockNo.p_x * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + neighBlkPos.pos_RelPos.p_x, neighBlkPos.pos_BlockNo.p_y * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + neighBlkPos.pos_RelPos.p_y);
					SquareEGCellNeighborPos[blockI][blockJ][outerAxis][maxRel].posCost = COST_MAX;

					//Store the validity of the current block's position to the neighbor block's positions to a printable array.
					SquareEgressCells[blockI][blockJ][outerAxis][maxRel] = egressCellsArray[outerAxis].bValidRelation[maxRel];
				}
			}

			//Delete the temporary array.
			delete[] egressCellsArray;
		}
	}
}
#endif