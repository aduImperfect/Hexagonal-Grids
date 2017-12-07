///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: SquareLDDBCalculator.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef SQUARE_LDDB_CALCULATOR_H
#define SQUARE_LDDB_CALCULATOR_H
//Including the different standard libraries for file operations and headers for base defines, the position structure, the dijkstra algorithm, and the position relations structures.
#include <iostream>
#include <fstream>
#include "BaseDefines.h"
#include "Position.h"
#include "SquareDijkstra.h"
#include "PositionRelations.h"

//LDDB = {}.
double SquareLDDB[SQUARE_LDDB_BLOCK_SIZE_I][SQUARE_LDDB_BLOCK_SIZE_J][SQUARE_LDDB_BLOCK_SPLIT_SIZE_X][SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y][SQUARE_LDDB_BLOCK_SPLIT_SIZE_X][SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y];

void WriteSquareLDDBToFile()
{
	std::ofstream squareLDDB;
	squareLDDB.open("squareLDDB.txt");

	for (int blockI = 0; blockI < SQUARE_LDDB_BLOCK_SIZE_I; ++blockI)
	{
		for (int blockJ = 0; blockJ < SQUARE_LDDB_BLOCK_SIZE_J; ++blockJ)
		{
			squareLDDB << "\nBlock[" << blockI << "][" << blockJ << "]:\n";
			squareLDDB << "\t\t\t";
			for (int toM = 0; toM < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++toM)
			{
				for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
				{
					squareLDDB << "[" << toM << "][" << toN << "]\t\t";
				}
			}
			squareLDDB << "\n";

			for (int fromK = 0; fromK < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++fromK)
			{
				for (int fromL = 0; fromL < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++fromL)
				{
					squareLDDB << "[" << fromK << "][" << fromL << "]:\t\t";
					for (int toM = 0; toM < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++toM)
					{
						for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
						{
							squareLDDB << SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN];
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
				}
			}
		}
	}

	squareLDDB.close();
}

void WriteSquareLDDBToFileAlternate()
{
	std::ofstream squareLDDB;
	squareLDDB.open("squareLDDBAlternate.txt");

	for (int blockI = 0; blockI < SQUARE_LDDB_BLOCK_SIZE_I; ++blockI)
	{
		for (int blockJ = 0; blockJ < SQUARE_LDDB_BLOCK_SIZE_J; ++blockJ)
		{
			squareLDDB << "\nBlock[" << blockI << "][" << blockJ << "]:\n";
			/*
			squareLDDB << "\t\t\t";
			for (int toM = 0; toM < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++toM)
			{
			for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
			{
			squareLDDB << "[" << toM << "][" << toN << "]\t\t";
			}
			}
			squareLDDB << "\n";
			*/
			for (int fromK = 0; fromK < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++fromK)
			{
				for (int fromL = 0; fromL < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++fromL)
				{
					squareLDDB << "FROM[" << fromK << "][" << fromL << "]:\n";
					squareLDDB << "TO:\t\t\t";
					for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
					{
						squareLDDB << "[" << toN << "]\t\t\t";
					}
					squareLDDB << "\n";

					for (int toM = 0; toM < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++toM)
					{
						squareLDDB << "[" << toM << "]:\t\t";
						for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
						{
							squareLDDB << SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN];
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
						squareLDDB << "\n";
					}
					squareLDDB << "\n";
				}
			}
		}
	}

	squareLDDB.close();
}

void SquareLDDBInitializer()
{
  for (int blockI = 0; blockI < SQUARE_LDDB_BLOCK_SIZE_I; ++blockI)
  {
    for (int blockJ = 0; blockJ < SQUARE_LDDB_BLOCK_SIZE_J; ++blockJ)
    {
      for (int fromK = 0; fromK < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++fromK)
      {
        for (int fromL = 0; fromL < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++fromL)
        {
          for (int toM = 0; toM < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++toM)
          {
            for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
            {
              SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] = COST_MAX;
            }
          }
        }
      }
    }
  }
}

void SquareLDDBCalc(Position npStart, Position npGoal)
{
  for (int blockI = 0; blockI < SQUARE_LDDB_BLOCK_SIZE_I; ++blockI)
  {
    for (int blockJ = 0; blockJ < SQUARE_LDDB_BLOCK_SIZE_J; ++blockJ)
    {
      for (int fromK = 0; fromK < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++fromK)
      {
        for (int fromL = 0; fromL < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++fromL)
        {
          for (int toM = 0; toM < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++toM)
          {
            for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
            {
              /*
              If the cost in block[i][j]: from[K][L] - to[M][N] is already assigned then skip that distance.
              */
              if (SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] < COST_MAX)
                continue;
              //Position absolute_from = (K + I * (TOT_X) + 1, L + J * (TOT_Y) + 1). 
              Position pFrom = Position(fromK + blockI * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + 1, fromL + blockJ * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + 1);
              //Position absolute_to = (M + I*(TOT_X) + 1, N + J * (TOT_Y) + 1). 
              Position pTo = Position(toM + blockI * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + 1, toN + blockJ * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + 1);
              //Position absolute_top_left = (I * (TOT_X) + 1, J * (TOT_Y) + 1). 
              Position pTopLeft = Position(blockI * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + 1, blockJ * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + 1);
              //Position absolute_bottom_right = (I * (TOT_X) + TOT_X, J * (TOT_Y) + TOT_Y). 
              Position pBottomRight = Position(blockI * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, blockJ * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);
              /*
              If (absolute_from is not absolute_to) and (start is absolute_from) and (absolute_to is a border inside absolute_top_left and absolute_bottom_right).
              */
              if ((pFrom != pTo) && (((npStart == pFrom) && SquareIsBorder(pTo, pTopLeft, pBottomRight)) || ((npStart == pTo) && SquareIsBorder(pFrom, pTopLeft, pBottomRight))))
              {
                SquareLDDB[blockI][blockJ][toM][toN][fromK][fromL] = SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] = SquareDijkstra(pFrom, pTo, true, pTopLeft, pBottomRight, 0 /*showMap*/);
              }
              /*
              Else If (absolute_from is not absolute_to) and (goal is absolute_from) and (absolute_to is a border inside absolute_top_left and absolute_bottom_right).
              */
              else if ((pFrom != pTo) && (((npGoal == pFrom) && SquareIsBorder(pTo, pTopLeft, pBottomRight)) || ((npGoal == pTo) && SquareIsBorder(pFrom, pTopLeft, pBottomRight))))
              {
                SquareLDDB[blockI][blockJ][toM][toN][fromK][fromL] = SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] = SquareDijkstra(pFrom, pTo, true, pTopLeft, pBottomRight, 0 /*showMap*/);
              }
              /*
              Else
              If (absolute_from is not a border inside absolute_top_left and absolute_bottom_right). or
              If (absolute_to is not a border inside absolute_top_left and absolute_bottom_right).
              */
              else if (!SquareIsBorder(pFrom, pTopLeft, pBottomRight) || !SquareIsBorder(pTo, pTopLeft, pBottomRight))
              {
                SquareLDDB[blockI][blockJ][toM][toN][fromK][fromL] = SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] = -1;
              }
              /*
              Else If (absolute_from is absolute_to).
              */
              else if (pFrom == pTo)
              { 
                SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] = 0;
              }
              else
              {
                //Otherwise, for any other case.
                SquareLDDB[blockI][blockJ][toM][toN][fromK][fromL] = SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] = SquareDijkstra(pFrom, pTo, true, pTopLeft, pBottomRight, 0 /*showMap*/);
              }
            }
          }
        }
      }
    }
  }

  printf("\nSquare LDDB Calculated!!\n");

  WriteSquareLDDBToFile();
  WriteSquareLDDBToFileAlternate();

  printf("\nSquare LDDB written to file!!\n");
}
#endif
