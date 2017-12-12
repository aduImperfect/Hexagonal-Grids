///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: SquareLDDBToFile.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef SQUARE_LDDB_TO_FILE_H
#define SQUARE_LDDB_TO_FILE_H
//Including the different file stream libraries and header for base defines.
#include <iostream>
#include <fstream>
#include "BaseDefines.h"

/*
Write the calculated LDDB to file.
Parameters to the function:
NONE
Returns from the function:
NONE
This function takes in nothing, transfers all the calculated LDDB values to a file and returns nothing. It appends 25 16x16 grids for each block to the file.
*/
void WriteSquareLDDBToFile()
{
	//Find the LDDB file squareLDDB.txt and open it.
	std::ofstream squareLDDB;
	squareLDDB.open("squareLDDB.txt");

	//Parse through the Blocks[I][J] (If a 20x20 grid with a block containing 4x4 elements then there are 25 (5x5) blocks).
	for (int blockI = 0; blockI < SQUARE_LDDB_BLOCK_SIZE_I; ++blockI)
	{
		for (int blockJ = 0; blockJ < SQUARE_LDDB_BLOCK_SIZE_J; ++blockJ)
		{

#pragma region BLOCK_NO
			//Append (print) Block[I][J].
			squareLDDB << "\nBlock[" << blockI << "][" << blockJ << "]:\n";
			squareLDDB << "\t\t\t";
#pragma endregion

#pragma region POSITION_TO_ROW_TABLE_HEADER
			//Parse through the Positions_To[M][N] (A block containing 4x4 elements then parse through 16 elements) and append (print) the Position_To's as the first ROW!!.
			for (int toM = 0; toM < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++toM)
			{
				for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
				{
					//Append the posTo[M][N].
					squareLDDB << "[" << toM << "][" << toN << "]\t\t";
				}
			}
			squareLDDB << "\n";
#pragma endregion

			//Parse through the Positions_From[K][L] (A block containing 4x4 elements then parse through 16 elements).
			for (int fromK = 0; fromK < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++fromK)
			{
				for (int fromL = 0; fromL < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++fromL)
				{
					//Append the posFrom[K][L].
					squareLDDB << "[" << fromK << "][" << fromL << "]:\t\t";

#pragma region POSITION_FROM_POSITION_TO_ROW_SQUARE_LDDB_VALUES
					//Parse through the Positions_To[M][N] (A block containing 4x4 elements then parse through 16 elements). Print the squareLDDB values for pos[K][L] to pos[M][N] as rows.
					for (int toM = 0; toM < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++toM)
					{
						for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
						{
							//Append the squareLDDB value associated.
							squareLDDB << SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN];
							
							//Calculate the number of \t (tabs) to be appended (printed) to the file based on the value.
							int tempVal = static_cast<int>(SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] * 100);
							if ((tempVal % 100) != 0)
							{
								squareLDDB << "\t\t";
							}
							else
							{
								squareLDDB << "\t\t\t";
							}
						}
					}
					squareLDDB << "\n";
#pragma endregion
				}
			}
		}
	}

	//Close the file after parsing through and appending all the calculated LDDB values.
	squareLDDB.close();
}

/*
Write the calculated LDDB in an alternate form to an alternate file.
Parameters to the function:
NONE
Returns from the function:
NONE
This function takes in nothing, transfers all the calculated LDDB values to a file and returns nothing. It appends (25 (5x5) * 16 (4x4)) 400 4x4 grids for each block at each position from to the file.
*/
void WriteSquareLDDBToFileAlternate()
{
	//Find the LDDB file squareLDDBAlternate.txt and open it.
	std::ofstream squareLDDB;
	squareLDDB.open("squareLDDBAlternate.txt");

	//Parse through the Blocks[I][J] (If a 20x20 grid with a block containing 4x4 elements then there are 25 (5x5) blocks).
	for (int blockI = 0; blockI < SQUARE_LDDB_BLOCK_SIZE_I; ++blockI)
	{
		for (int blockJ = 0; blockJ < SQUARE_LDDB_BLOCK_SIZE_J; ++blockJ)
		{

#pragma region BLOCK_NO
			//Append (print) Block[I][J].
			squareLDDB << "\nBlock[" << blockI << "][" << blockJ << "]:\n";
#pragma endregion

			//Parse through the Positions_From[K][L] (A block containing 4x4 elements then parse through 16 elements).
			for (int fromK = 0; fromK < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++fromK)
			{
				for (int fromL = 0; fromL < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++fromL)
				{
					//Append FROM[K][L].
					squareLDDB << "FROM[" << fromK << "][" << fromL << "]:\n";

					//Basically form a 4x4 smaller grid for the whole TO[M][N] as a table that contains all the values of LDDB for FROM[K][L] to TO[M][N].

#pragma region TO[N]_FIRST_HEADER
					//Append all the TO[n] subscripts as the first row header.
					squareLDDB << "TO:\t\t\t";
					for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
					{
						squareLDDB << "[" << toN << "]\t\t\t";
					}
					squareLDDB << "\n";
#pragma endregion

					//Parse through the Positions_To[M][N] (A block containing 4x4 elements then parse through 16 elements).
					for (int toM = 0; toM < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++toM)
					{
						squareLDDB << "[" << toM << "]:\t\t";

#pragma region FOR_EACH_ROW
						for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
						{
							//Append the calculated LDDB.
							squareLDDB << SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN];

							//Calculate the number of \t (tabs) to be appended (printed) to the file based on the value.
							int tempVal = static_cast<int>(SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] * 100);
							if ((tempVal % 100) != 0)
							{
								squareLDDB << "\t\t";
							}
							else
							{
								squareLDDB << "\t\t\t";
							}
						}
#pragma endregion
						squareLDDB << "\n";
					}
					squareLDDB << "\n";
				}
			}
		}
	}
	
	//Close the file after parsing through and appending all the calculated LDDB values.
	squareLDDB.close();
}
#endif