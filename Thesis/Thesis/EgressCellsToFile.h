///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
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

void WriteEgressCellsToFile()
{
	//Find the Egress cells file egressCells.txt and open it.
	std::ofstream egressCellsFile;
	egressCellsFile.open("egressCells.txt");

	egressCellsFile << "\n";
	for (unsigned int blockI = 0; blockI < SQUARE_LDDB_BLOCK_SIZE_I; ++blockI)
	{
		for (unsigned int blockJ = 0; blockJ < SQUARE_LDDB_BLOCK_SIZE_I; ++blockJ)
		{
#pragma region BLOCK_NO
			//Append (print) Block[I][J].
			egressCellsFile << "\nBlock[" << blockI << "][" << blockJ << "]:\n";
#pragma endregion

			for (unsigned int outerAxis = 0; outerAxis < OUTER_BORDERS_SIZE; ++outerAxis)
			{
				egressCellsFile << "MAX RELATIONS [" << SquareEGCellNumCorners[blockI][blockJ][outerAxis] << "] for POS[" << SquareEGCellPos[blockI][blockJ][outerAxis].p_x << "][" << SquareEGCellPos[blockI][blockJ][outerAxis].p_y << "]: ";

				for (unsigned int maxRel = 0; maxRel < SquareEGCellNumCorners[blockI][blockJ][outerAxis]; ++maxRel)
				{
					if (SquareEgressCells[blockI][blockJ][outerAxis][maxRel])
						egressCellsFile << "\t" << "_TRUE_";
					else
						egressCellsFile << "\t" << "_FALSE_";
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