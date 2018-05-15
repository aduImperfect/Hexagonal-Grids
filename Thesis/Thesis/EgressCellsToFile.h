///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017-2018 DigiPen Institute of Technology, all rights reserved
/// FILE: EgressCellsToFile.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef EGRESS_CELLS_TO_FILE_H
#define EGRESS_CELLS_TO_FILE_H
//Including the different file stream libraries and header for base defines.
#include <iostream>
#include <fstream>
#include "BaseDefines.h"
#include "PositionRelations.h"

/*
Write the calculated Egress cells to file.
Parameters to the function:
NONE
Returns from the function:
NONE
This function takes in nothing, transfers all the calculated Egress cells values to a file and returns nothing. It appends each (25) blocks' information with each of its outer (12) positions containing 3-5 (3 - in corners, 5 - out corners) relations with neighbor blocks' positions' to the file.
*/
void WriteEgressCellsToFile()
{
	//The total number of elements in each block.
	unsigned int nTotalSize = SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y;

	//The total number of non-corner elements in each block.
	unsigned int nInnerSize = (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 2) * (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 2);

	//The total number of (in and out)corner elements in each block.
	const unsigned int nOuterBordersSize = nTotalSize - nInnerSize;

	//Find the Egress cells file egressCells.txt and open it.
	std::ofstream egressCellsFile;
	egressCellsFile.open("egressCells.txt");

	egressCellsFile << "\n";
	//Parse through the Blocks[I][J] (If a 20x20 grid with a block containing 4x4 elements then there are 25 (5x5) blocks).
	for (unsigned int blockI = 0; blockI < SQUARE_LDDB_BLOCK_SIZE_I; ++blockI)
	{
		for (unsigned int blockJ = 0; blockJ < SQUARE_LDDB_BLOCK_SIZE_I; ++blockJ)
		{
#pragma region BLOCK_NO
			//Append (print) Block[I][J].
			egressCellsFile << "\nBlock[" << blockI << "][" << blockJ << "]:\n";
#pragma endregion

			//Parse through all the corner nodes of the block.
			for (unsigned int outerAxis = 0; outerAxis < nOuterBordersSize; ++outerAxis)
			{
				//Print the number of relations the node contains along with its actual grid position.
				egressCellsFile << "MAX RELATIONS [" << SquareEGCellNumCorners[blockI][blockJ][outerAxis] << "] for POS[" << SquareEGCellPos[blockI][blockJ][outerAxis].p_x << "][" << SquareEGCellPos[blockI][blockJ][outerAxis].p_y << "]: ";
				
				//Parse through all the neighbor blocks' nodes' relations with the current node.
				for (unsigned int maxRel = 0; maxRel < SquareEGCellNumCorners[blockI][blockJ][outerAxis]; ++maxRel)
				{
					//Print the Neighbor position's grid value.
					egressCellsFile << "\tNP[" << SquareEGCellNeighborPos[blockI][blockJ][outerAxis][maxRel].p_x << "][" << SquareEGCellNeighborPos[blockI][blockJ][outerAxis][maxRel].p_y << "]";
				}

				//Append some tabs for formatting.
				egressCellsFile << "\n\t\t\t\t\t\t\t";

				//Parse through all the neighbor blocks' nodes' relations with the current node.
				for (unsigned int maxRel = 0; maxRel < SquareEGCellNumCorners[blockI][blockJ][outerAxis]; ++maxRel)
				{
					//If the relation with the neighbor blocks' node is valid then print _TRUE_, else _FALSE_.
					if (SquareEgressCells[blockI][blockJ][outerAxis][maxRel])
						egressCellsFile << "\t\t" << "_TRUE_";
					else
						egressCellsFile << "\t\t" << "_FALSE_";
				}
				egressCellsFile << "\n";
			}
			egressCellsFile << "\n";
		}
	}

	//Close the file after parsing through and appending the egress cells values.
	egressCellsFile.close();
}
#endif