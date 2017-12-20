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

*/
void EgressCellsInitialize()
{
	unsigned int nTotalSize = SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y;
	unsigned int nInnerSize = (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 2) * (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 2);
	const unsigned int nOuterBordersSize = nTotalSize - nInnerSize;

	for (unsigned int blockI = 0; blockI < SQUARE_LDDB_BLOCK_SIZE_I; ++blockI)
	{
		for (unsigned int blockJ = 0; blockJ < SQUARE_LDDB_BLOCK_SIZE_J; ++blockJ)
		{
			PositionRelations * egressCellsArray = new PositionRelations[nOuterBordersSize];
			for (unsigned int nEgCell = 0; nEgCell < nOuterBordersSize; ++nEgCell)
			{
				egressCellsArray[nEgCell];
			}

			Position curBlock(blockI, blockJ);

			EgressCells(curBlock, egressCellsArray, nOuterBordersSize);
			ValidateEgressCells(curBlock, egressCellsArray, nOuterBordersSize);

			for (unsigned int outerAxis = 0; outerAxis < nOuterBordersSize; ++outerAxis)
			{
				SquareEGCellNumCorners[blockI][blockJ][outerAxis] = egressCellsArray[outerAxis].max_rel;
				BlockPosition blkPos = egressCellsArray[outerAxis].pos_From;
				SquareEGCellPos[blockI][blockJ][outerAxis] = Position(blkPos.pos_BlockNo.p_x + blkPos.pos_RelPos.p_x, blkPos.pos_BlockNo.p_y + blkPos.pos_RelPos.p_y);
				for (unsigned int maxRel = 0; maxRel < egressCellsArray[outerAxis].max_rel; ++maxRel)
				{
					SquareEgressCells[blockI][blockJ][outerAxis][maxRel] = egressCellsArray[outerAxis].bValidRelation[maxRel];
				}
			}
		}
	}
}

#endif