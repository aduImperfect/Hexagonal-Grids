///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: SquareLDDBCalculator.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <iostream>
#include <fstream>

#include "BaseDefines.h"
#include "Position.h"
#include "SquareDijkstra.h"
#include "PositionRelations.h"

#define SQUARE_LDDB_BASE_PT_X 1
#define SQUARE_LDDB_BASE_PT_Y 1

#define SQUARE_LDDB_BLOCK_SPLIT_SIZE_X 4
#define SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y 4

#define SQUARE_LDDB_BLOCK_SIZE_I (SIZE - 1)/SQUARE_LDDB_BLOCK_SPLIT_SIZE_X
#define SQUARE_LDDB_BLOCK_SIZE_J (SIZE - 1)/SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y

//LDDB = {}.
double SquareLDDB[SQUARE_LDDB_BLOCK_SIZE_I][SQUARE_LDDB_BLOCK_SIZE_J][SQUARE_LDDB_BLOCK_SPLIT_SIZE_X][SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y][SQUARE_LDDB_BLOCK_SPLIT_SIZE_X][SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y];

void WriteSquareLDDBToFile();
void WriteSquareLDDBToFileAlternate();

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
                SquareLDDB[blockI][blockJ][toM][toN][fromK][fromL] = SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] = SquareDijkstra(pFrom, pTo, true, pTopLeft, pBottomRight);
              }
              /*
              Else If (absolute_from is not absolute_to) and (goal is absolute_from) and (absolute_to is a border inside absolute_top_left and absolute_bottom_right).
              */
              else if ((pFrom != pTo) && (((npGoal == pFrom) && SquareIsBorder(pTo, pTopLeft, pBottomRight)) || ((npGoal == pTo) && SquareIsBorder(pFrom, pTopLeft, pBottomRight))))
              {
                SquareLDDB[blockI][blockJ][toM][toN][fromK][fromL] = SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] = SquareDijkstra(pFrom, pTo, true, pTopLeft, pBottomRight);
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
                SquareLDDB[blockI][blockJ][toM][toN][fromK][fromL] = SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] = SquareDijkstra(pFrom, pTo, true, pTopLeft, pBottomRight);
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

//For an octile grid, a normal border item in a block has 3 neighbors in the adjacent block (2 diagonals and one horizontal/vertical).
void EgressCellsBorders(BlockPosition curPosInBlock, PositionRelations & posRel, Position NeighBlkArr, std::initializer_list<Position> NeighBlkPosArr)
{
	posRel.Set(curPosInBlock, BlockPosition(NeighBlkArr, *(NeighBlkPosArr.begin() + 0)), 0, MAX_IN_CORNER_RELATIONS);
	posRel.Set(curPosInBlock, BlockPosition(NeighBlkArr, *(NeighBlkPosArr.begin() + 1)), 1, MAX_IN_CORNER_RELATIONS);
	posRel.Set(curPosInBlock, BlockPosition(NeighBlkArr, *(NeighBlkPosArr.begin() + 2)), 2, MAX_IN_CORNER_RELATIONS);
}

//For an octile grid, a corner border item in a block has 5 neighbors in the 3 adjacent blocks (3 diagonals and 2 horizontal/vertical).
void EgressCellsCorners(BlockPosition curPosInBlock, PositionRelations & posRel, std::initializer_list<Position> NeighBlkArr, std::initializer_list<Position> NeighBlkPosArr)
{
	posRel.Set(curPosInBlock, BlockPosition(*(NeighBlkArr.begin() + 0), *(NeighBlkPosArr.begin() + 0)), 0, MAX_OUT_CORNER_RELATIONS);
	posRel.Set(curPosInBlock, BlockPosition(*(NeighBlkArr.begin() + 0), *(NeighBlkPosArr.begin() + 1)), 1, MAX_OUT_CORNER_RELATIONS);

	posRel.Set(curPosInBlock, BlockPosition(*(NeighBlkArr.begin() + 1), *(NeighBlkPosArr.begin() + 2)), 2, MAX_OUT_CORNER_RELATIONS);
	
	posRel.Set(curPosInBlock, BlockPosition(*(NeighBlkArr.begin() + 2), *(NeighBlkPosArr.begin() + 3)), 3, MAX_OUT_CORNER_RELATIONS);
	posRel.Set(curPosInBlock, BlockPosition(*(NeighBlkArr.begin() + 2), *(NeighBlkPosArr.begin() + 4)), 4, MAX_OUT_CORNER_RELATIONS);
}

void EgressCells(Position curBlock, PositionRelations posRel[], unsigned int limitSize)
{
	//Adjacent Blocks
	//NBlk[-1, -1]
	Position NorthWestBlk(curBlock.p_x - 1, curBlock.p_y - 1);
	//NBlk[-1, 0]
	Position NorthBlk(curBlock.p_x - 1, curBlock.p_y);
	//NBlk[-1, 1]
	Position NorthEastBlk(curBlock.p_x - 1, curBlock.p_y + 1);
	//NBlk[0, 1]
	Position EastBlk(curBlock.p_x, curBlock.p_y + 1);
	//NBlk[1, 1]
	Position SouthEastBlk(curBlock.p_x + 1, curBlock.p_y + 1);
	//NBlk[1, 0]
	Position SouthBlk(curBlock.p_x + 1, curBlock.p_y);
	//NBlk[1, -1]
	Position SouthWestBlk(curBlock.p_x + 1, curBlock.p_y - 1);
	//NBlk[0, -1]
	Position WestBlk(curBlock.p_x, curBlock.p_y - 1);

	//For a 4x4 block type example.

	///X vertical and Y horizontal
	unsigned int firstCorner = 0;														//First corner: 0
	unsigned int cornerSlice = limitSize / 2;											//Third corner: 3
	unsigned int additiveCornerBefore = cornerSlice - SQUARE_LDDB_BLOCK_SPLIT_SIZE_X;	//Second corner: 6
	unsigned int additiveCornerAfter = cornerSlice + SQUARE_LDDB_BLOCK_SPLIT_SIZE_X;	//Fourth corner: 9

	///[0]
	//Side of CurBlock: [1, 1]. Side of NeighborBlock: NBlk[0, -1]: [1, 4], NBlk[0, -1]: [2, 4], NBlk[-1, -1]: [4, 4], NBlk[-1, 0]: [4, 1], NBlk[-1, 0]: [4, 2].
	/*
	ValidEgressCellsCorners(BlockPosition(curBlock, Position(1, 1)), posRel[0], { WestBlk, NorthWestBlk, NorthBlk }, { Position(1, 4), Position(2, 4), Position(4, 4), Position(4, 1), Position(4, 2) });
	*/
	EgressCellsCorners(BlockPosition(curBlock, Position(1, 1)), posRel[firstCorner], { WestBlk, NorthWestBlk, NorthBlk }, { Position(1, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(2, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, 1), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, 2) });

	for (unsigned int yIncrement = 2; yIncrement < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++yIncrement)
	{
		///[1] ///2
		//Side of CurBlock: [1, 2]. Side of NeighborBlock: NBlk[-1, 0]: [4, 1], NBlk[-1, 0]: [4, 2], NBlk[-1, 0]: [4, 3].
		//Side of CurBlock: [1, 3]. Side of NeighborBlock: NBlk[-1, 0]: [4, 2], NBlk[-1, 0]: [4, 3], NBlk[-1, 0]: [4, 4].
		EgressCellsBorders(BlockPosition(curBlock, Position(1, yIncrement)), posRel[firstCorner + (yIncrement - 1)], { NorthBlk }, { Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (yIncrement - 1)), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, yIncrement), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (yIncrement + 1)) });
	}

	///[3]
	//Side of CurBlock: [1, 4]. Side of NeighborBlock: NBlk[-1, 0]: [4, 3], NBlk[-1, 0]: [4, 4], NBlk[-1, 1]: [4, 1], NBlk[0, 1]: [1, 1], NBlk[0, 1]: [2, 1].
	EgressCellsCorners(BlockPosition(curBlock, Position(1, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y)), posRel[additiveCornerBefore], { NorthBlk, NorthEastBlk, EastBlk }, { Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 1)), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, 1), Position(1, 1), Position(2, 1) });

	for (unsigned int xIncrement = 2; xIncrement < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++xIncrement)
	{
		///[4] ///[5]
		//Side of CurBlock: [2, 4]. Side of NeighborBlock: NBlk[0, 1]: [1, 1], NBlk[0, 1]: [2, 1], NBlk[0, 1]: [3, 1].
		//Side of CurBlock: [3, 4]. Side of NeighborBlock: NBlk[0, 1]: [2, 1], NBlk[0, 1]: [3, 1], NBlk[0, 1]: [4, 1].
		EgressCellsBorders(BlockPosition(curBlock, Position(xIncrement, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y)), posRel[additiveCornerBefore + (xIncrement - 1)], { EastBlk }, { Position((xIncrement - 1), 1), Position(xIncrement, 1), Position((xIncrement + 1), 1) });
	}

	///[6]
	//Side of CurBlock: [4, 4]. Side of NeighborBlock: NBlk[0, 1]: [3, 1], NBlk[0, 1]: [4, 1], NBlk[1, 1]: [1, 1], NBlk[1, 0]: [1, 3], NBlk[1, 0]: [1, 4].
	EgressCellsCorners(BlockPosition(curBlock, Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y)), posRel[cornerSlice], { EastBlk, SouthEastBlk, SouthBlk }, { Position((SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 1), 1), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, 1), Position(1, 1), Position(1, (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 1)), Position(1, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y) });

	for (unsigned int yIncrement = (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 1); yIncrement > 1; --yIncrement)
	{
		///[7] ///[8]
		//Side of CurBlock: [4, 3]. Side of NeighborBlock: NBlk[1, 0]: [1, 2], NBlk[1, 0]: [1, 3], NBlk[1, 0]: [1, 4].
		//Side of CurBlock: [4, 2]. Side of NeighborBlock: NBlk[1, 0]: [1, 1], NBlk[1, 0]: [1, 2], NBlk[1, 0]: [1, 3].
		EgressCellsBorders(BlockPosition(curBlock, Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, yIncrement)), posRel[cornerSlice + (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - yIncrement)], { SouthBlk }, { Position(1, (yIncrement - 1)), Position(1, yIncrement), Position(1, (yIncrement + 1)) });
	}

	///[9]
	//Side of CurBlock: [4, 1]. Side of NeighborBlock: NBlk[1, 0]: [1, 1], NBlk[1, 0]: [1, 2], NBlk[1, -1]: [1, 4], NBlk[0, -1]: [3, 4], NBlk[0, -1]: [4, 4].
	EgressCellsCorners(BlockPosition(curBlock, Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, 1)), posRel[additiveCornerAfter], { SouthBlk, SouthWestBlk, WestBlk }, { Position(1, 1), Position(1, 2), Position(1, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(3, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y) });

	for (unsigned int xIncrement = (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 1); xIncrement > 1; --xIncrement)
	{
		///[10] ///[11]
		//Side of CurBlock: [3, 1]. Side of NeighborBlock: NBlk[0, -1]: [2, 4], NBlk[0, -1]: [3, 4], NBlk[0, -1]: [4, 4].
		//Side of CurBlock: [2, 1]. Side of NeighborBlock: NBlk[0, -1]: [1, 4], NBlk[0, -1]: [2, 4], NBlk[0, -1]: [3, 4].
		EgressCellsBorders(BlockPosition(curBlock, Position(xIncrement, 1)), posRel[additiveCornerAfter + (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - xIncrement)], { WestBlk }, { Position((xIncrement - 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(xIncrement, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position((xIncrement + 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y) });
	}
}

bool IsWallCheck(Position actual, Position offset)
{
	if (mapVisited[actual.p_x + offset.p_x][actual.p_y + offset.p_y] != WALL)
		return false;
	return true;
}

void ValidateEgressCellsBorders(BlockPosition curPosInBlock, PositionRelations & posRel)
{

}

void ValidateEgressCellsCorners(Position curBlock, Position curPos, PositionRelations & posRel, std::initializer_list<Position> NeighBlkArr, std::initializer_list<Position> NeighBlkPosArr)
{
	//If CurBlock[0, 0] : [1, 1] is not a WALL.
	bool isNotCurBlkPosWall = IsWallCheck(curBlock, curPos);

	if (!isNotCurBlkPosWall)
	{
		posRel.bValidRelation[0] = posRel.bValidRelation[1] = posRel.bValidRelation[2] = posRel.bValidRelation[3] = posRel.bValidRelation[4] = false;
		return;
	}

	//If NBlk[0, -1] : [1, 4] are not WALLS! check.
	if (IsWallCheck(*(NeighBlkArr.begin() + 0), *(NeighBlkPosArr.begin() + 0)))
	{
		posRel.bValidRelation[0] = true;
	}
	//If NBlk[0, -1]: [2, 4] are not WALLS! check.
	if (IsWallCheck(*(NeighBlkArr.begin() + 0), *(NeighBlkPosArr.begin() + 1)))
	{
		//If CurBlock[0, 0] : [2, 1], and NBlk[0, -1] : [1, 4] are not WALLS! check.
		if (IsWallCheck(curBlock, Position(2, 1)) && IsWallCheck(*(NeighBlkArr.begin() + 0), *(NeighBlkPosArr.begin() + 0)))
		{
			posRel.bValidRelation[1] = true;
		}
	}
	//If NBlk[-1, -1] : [4, 4] are not WALLS! check.
	if (IsWallCheck(*(NeighBlkArr.begin() + 1), *(NeighBlkPosArr.begin() + 2)))
	{
		//If NBlk[0, -1] : [1, 4], and NBlk[-1, 0] : [4, 1] are not WALLS! check.
		if (IsWallCheck(*(NeighBlkArr.begin() + 0), *(NeighBlkPosArr.begin() + 0)) && IsWallCheck(*(NeighBlkArr.begin() + 2), *(NeighBlkPosArr.begin() + 3)))
		{
			posRel.bValidRelation[2] = true;
		}
	}
	//If NBlk[-1, 0]: [4, 1] are not WALLS! check.
	if (IsWallCheck(*(NeighBlkArr.begin() + 2), *(NeighBlkPosArr.begin() + 3)))
	{
		posRel.bValidRelation[3] = true;
	}
	//If NBlk[-1, 0]: [4, 2] are not WALLS! check.
	if (IsWallCheck(*(NeighBlkArr.begin() + 2), *(NeighBlkPosArr.begin() + 4)))
	{
		//If CurBlock[0, 0] : [1, 2], and NBlk[-1, 0] : [4, 1] are not WALLS! check.
		if (IsWallCheck(curBlock, Position(1, 2)) && IsWallCheck(*(NeighBlkArr.begin() + 2), *(NeighBlkPosArr.begin() + 3)))
		{
			posRel.bValidRelation[4] = true;
		}
	}
}

void ValidateEgressCells(Position curBlock, Position curPos, PositionRelations posRel[], unsigned int limitSize)
{
	//CurBlock[0, 0]
	Position CurentABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y));
	//NBlk[-1, -1]
	Position NorthWestABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x - 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y - 1));
	//NBlk[-1, 0]
	Position NorthABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x - 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y));
	//NBlk[-1, 1]
	Position NorthEastABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x - 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y + 1));
	//NBlk[0, 1]
	Position EastABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y + 1));
	//NBlk[1, 1]
	Position SouthEastABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x + 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y + 1));
	//NBlk[1, 0]
	Position SouthABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x + 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y));
	//NBlk[1, -1]
	Position SouthWestABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x + 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y - 1));
	//NBlk[0, -1]
	Position WestABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y - 1));

	//For a 4x4 block type example.

	///X vertical and Y horizontal
	unsigned int firstCorner = 0;														//First corner: 0
	unsigned int cornerSlice = limitSize / 2;											//Third corner: 3
	unsigned int additiveCornerBefore = cornerSlice - SQUARE_LDDB_BLOCK_SPLIT_SIZE_X;	//Second corner: 6
	unsigned int additiveCornerAfter = cornerSlice + SQUARE_LDDB_BLOCK_SPLIT_SIZE_X;	//Fourth corner: 9

	///[0]
	//Side of CurBlock: [1, 1]. Side of NeighborBlock: NBlk[0, -1]: [1, 4], NBlk[0, -1]: [2, 4], NBlk[-1, -1]: [4, 4], NBlk[-1, 0]: [4, 1], NBlk[-1, 0]: [4, 2].
	/*
	ValidateEgressCellsCorners(CurentABS, Position(1, 1), posRel[firstCorner], { WestABS, NorthWestABS, NorthABS }, { Position(1, 4), Position(2, 4), Position(4, 4), Position(4, 1), Position(4, 2) });
	*/
	ValidateEgressCellsCorners(CurentABS, Position(1, 1), posRel[firstCorner], { WestABS, NorthWestABS, NorthABS }, { Position(1, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(2, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, 1), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, 2) });



}

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
        x.g = min(y in Y)(y.g + LDDB(y,x), x.g)
        x'.g = min(x'.g, x.g + cost(x,x'))
      }
      newheapvalue (priority) = min(updated x')(x'.g +x'.h)
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

	unsigned int cSizeA = SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y;
	unsigned int cSizeB = (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 2) * (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 2);

	const unsigned int cornerSize = cSizeA - cSizeB;

    //(Side of curblock) : [Neighborblk, side of neighbor blk].
    PositionRelations * neigborsideNextBlock = new PositionRelations[cornerSize];
	for (unsigned int nBlki = 0; nBlki < cornerSize; ++nBlki)
	{
		neigborsideNextBlock[nBlki];
	}

    unsigned int rot_count = 0;
	EgressCells(curBlock, neigborsideNextBlock, cornerSize );


    /*
    Equation: for block (x, y): cells of block range: {(4x + 1), (4y + 1)} -> {(4x + 4), (4y + 4)}
    Generically,
    (x, y) block:
    Top Left cell:
    {(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * x + 1), (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * y + 1)}
    Bottom Right cell:
    {(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * x + SQUARE_LDDB_BLOCK_SPLIT_SIZE_X), (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * y + SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y)}
    */

    /*
    Valid egress node check is basically to check if the current node and neighbor nodes are walls. In addition for any diagonal neighbor nodes, any of the vertical/horizontal neighbor nodes are walls. If any of these checks come out to be true then the curnode is not a valid egress node.
    */


	//TODO: CLEANUP UNNECCESSARY CODE!!!
	//CurBlock[0, 0]
	Position CurentABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y));
	//NBlk[-1, -1]
	Position NorthWestABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x - 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y - 1));
	//NBlk[-1, 0]
	Position NorthABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x - 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y));
	//NBlk[-1, 1]
	Position NorthEastABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x - 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y + 1));
	//NBlk[0, 1]
	Position EastABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y + 1));
	//NBlk[1, 1]
	Position SouthEastABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x + 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y + 1));
	//NBlk[1, 0]
	Position SouthABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x + 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y));
	//NBlk[1, -1]
	Position SouthWestABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x + 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y - 1));
	//NBlk[0, -1]
	Position WestABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y - 1));

	///rot_count
	//If CurBlock[0, 0] : [1, 1], and NBlk[0, -1] : [1, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 1][WestABS.p_y + 4] != WALL))
	{
		neigborsideNextBlock[rot_count].bValidRelation[0] = true;
	}
	//If CurBlock[0, 0] : [1, 1], and NBlk[0, -1]: [2, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 2][WestABS.p_y + 4] != WALL))
	{
		//If CurBlock[0, 0] : [2, 1], and NBlk[0, -1] : [1, 4] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 1][WestABS.p_y + 4] != WALL))
		{
			neigborsideNextBlock[rot_count].bValidRelation[1] = true;
		}
	}
	//If CurBlock[0, 0] : [1, 1], and NBlk[-1, -1] : [4, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 1] != WALL) && (mapVisited[NorthWestABS.p_x + 4][NorthWestABS.p_y + 4] != WALL))
	{
		//If NBlk[0, -1] : [1, 4], and NBlk[-1, 0] : [4, 1] are not WALLS! check.
		if ((mapVisited[WestABS.p_x + 1][WestABS.p_y + 4] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 1] != WALL))
		{
			neigborsideNextBlock[rot_count].bValidRelation[2] = true;
		}
	}
	//If CurBlock[0, 0] : [1, 1], and NBlk[-1, 0]: [4, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 1] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 1] != WALL))
	{
		neigborsideNextBlock[rot_count].bValidRelation[3] = true;
	}
	//If CurBlock[0, 0] : [1, 1], and NBlk[-1, 0]: [4, 2] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 1] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 2] != WALL))
	{
		//If CurBlock[0, 0] : [1, 2], and NBlk[-1, 0] : [4, 1] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 2] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 1] != WALL))
		{
			neigborsideNextBlock[rot_count].bValidRelation[4] = true;
		}
	}

	///rot_count + 1
	//If CurBlock[0, 0] : [1, 2], and NBlk[-1, 0]: [4, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 2] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 1] != WALL))
	{
		//If CurBlock[0, 0] : [1, 1], and NBlk[-1, 0] : [4, 2] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 1] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 2] != WALL))
		{
			neigborsideNextBlock[rot_count + 1].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [1, 2], and NBlk[-1, 0]: [4, 2] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 2] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 2] != WALL))
	{
		neigborsideNextBlock[rot_count + 1].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [1, 2], and NBlk[-1, 0]: [4, 3] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 2] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 3] != WALL))
	{
		//If CurBlock[0, 0] : [1, 3], and NBlk[-1, 0] : [4, 2] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 3] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 2] != WALL))
		{
			neigborsideNextBlock[rot_count + 1].bValidRelation[2] = true;
		}
	}

	///rot_count + 2
	//If CurBlock[0, 0] : [1, 3], and NBlk[-1, 0]: [4, 2] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 3] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 2] != WALL))
	{
		//If CurBlock[0, 0] : [1, 2], and NBlk[-1, 0] : [4, 3] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 2] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 3] != WALL))
		{
			neigborsideNextBlock[rot_count + 2].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [1, 3], and NBlk[-1, 0]: [4, 3] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 3] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 3] != WALL))
	{
		neigborsideNextBlock[rot_count + 2].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [1, 3], and NBlk[-1, 0]: [4, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 3] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 4] != WALL))
	{
		//If CurBlock[0, 0] : [1, 4], and NBlk[-1, 0] : [4, 3] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 4] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 3] != WALL))
		{
			neigborsideNextBlock[rot_count + 2].bValidRelation[2] = true;
		}
	}

	///rot_count + 3
	//If CurBlock[0, 0] : [1, 4], and NBlk[-1, 0]: [4, 3] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 4] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 3] != WALL))
	{
		//If CurBlock[0, 0] : [1, 3], and NBlk[-1, 0] : [4, 4] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 3] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 4] != WALL))
		{
			neigborsideNextBlock[rot_count + 3].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [1, 4], and NBlk[-1, 0]: [4, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 4] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 4] != WALL))
	{
		neigborsideNextBlock[rot_count + 3].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [1, 4], and NBlk[-1, 1] : [4, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 4] != WALL) && (mapVisited[NorthEastABS.p_x + 4][NorthEastABS.p_y + 1] != WALL))
	{
		//If NBlk[0, 1] : [1, 1], and NBlk[-1, 0] : [4, 4] are not WALLS! check.
		if ((mapVisited[EastABS.p_x + 1][EastABS.p_y + 1] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 4] != WALL))
		{
			neigborsideNextBlock[rot_count + 3].bValidRelation[2] = true;
		}
	}
	//If CurBlock[0, 0] : [1, 4], and NBlk[0, 1]: [1, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 1][EastABS.p_y + 1] != WALL))
	{
		neigborsideNextBlock[rot_count + 3].bValidRelation[3] = true;
	}
	//If CurBlock[0, 0] : [1, 4], and NBlk[0, 1]: [2, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 2][EastABS.p_y + 1] != WALL))
	{
		//If CurBlock[0, 0] : [2, 4], and NBlk[0, 1] : [1, 1] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 1][EastABS.p_y + 1] != WALL))
		{
			neigborsideNextBlock[rot_count + 3].bValidRelation[4] = true;
		}
	}

	///rot_count + 4
	//If CurBlock[0, 0] : [2, 4], and NBlk[0, 1]: [1, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 1][EastABS.p_y + 1] != WALL))
	{
		//If CurBlock[0, 0] : [1, 4], and NBlk[0, 1] : [2, 1] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 2][EastABS.p_y + 1] != WALL))
		{
			neigborsideNextBlock[rot_count + 4].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [2, 4], and NBlk[0, 1]: [2, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 2][EastABS.p_y + 1] != WALL))
	{
		neigborsideNextBlock[rot_count + 4].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [2, 4], and NBlk[0, 1]: [3, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 3][EastABS.p_y + 1] != WALL))
	{
		//If CurBlock[0, 0] : [3, 4], and NBlk[0, 1] : [2, 1] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 2][EastABS.p_y + 1] != WALL))
		{
			neigborsideNextBlock[rot_count + 4].bValidRelation[2] = true;
		}
	}

	///rot_count + 5
	//If CurBlock[0, 0] : [3, 4], and NBlk[0, 1]: [2, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 2][EastABS.p_y + 1] != WALL))
	{
		//If CurBlock[0, 0] : [2, 4], and NBlk[0, 1] : [3, 1] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 3][EastABS.p_y + 1] != WALL))
		{
			neigborsideNextBlock[rot_count + 5].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [3, 4], and NBlk[0, 1]: [3, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 3][EastABS.p_y + 1] != WALL))
	{
		neigborsideNextBlock[rot_count + 5].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [3, 4], and NBlk[0, 1]: [4, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 4][EastABS.p_y + 1] != WALL))
	{
		//If CurBlock[0, 0] : [4, 4], and NBlk[0, 1] : [3, 1] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 3][EastABS.p_y + 1] != WALL))
		{
			neigborsideNextBlock[rot_count + 5].bValidRelation[2] = true;
		}
	}

	///rot_count + 6
	//If CurBlock[0, 0] : [4, 4], and NBlk[0, 1]: [3, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 3][EastABS.p_y + 1] != WALL))
	{
		//If CurBlock[0, 0] : [3, 4], and NBlk[0, 1] : [4, 1] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 4][EastABS.p_y + 1] != WALL))
		{
			neigborsideNextBlock[rot_count + 6].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [4, 4], and NBlk[0, 1] : [4, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 4][EastABS.p_y + 1] != WALL))
	{
		neigborsideNextBlock[rot_count + 6].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [4, 4], and NBlk[1, 1] : [1, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 4] != WALL) && (mapVisited[SouthEastABS.p_x + 1][SouthEastABS.p_y + 1] != WALL))
	{
		//If NBlk[0, 1] : [4, 1], and NBlk[1, 0] : [1, 4] are not WALLS! check.
		if ((mapVisited[EastABS.p_x + 4][EastABS.p_y + 1] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 4] != WALL))
		{
			neigborsideNextBlock[rot_count + 6].bValidRelation[2] = true;
		}
	}
	//If CurBlock[0, 0] : [4, 4], and NBlk[1, 0]: [1, 3] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 4] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 3] != WALL))
	{
		//If CurBlock[0, 0] : [4, 3], and NBlk[1, 0] : [1, 4] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 3] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 4] != WALL))
		{
			neigborsideNextBlock[rot_count + 6].bValidRelation[3] = true;
		}
	}
	//If CurBlock[0, 0] : [4, 4], and NBlk[1, 0]: [1, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 4] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 4] != WALL))
	{
		neigborsideNextBlock[rot_count + 6].bValidRelation[4] = true;
	}

	///rot_count + 7
	//If CurBlock[0, 0] : [4, 3], and NBlk[1, 0]: [1, 2] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 3] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 2] != WALL))
	{
		//If CurBlock[0, 0] : [4, 2], and NBlk[1, 0] : [1, 3] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 2] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 3] != WALL))
		{
			neigborsideNextBlock[rot_count + 7].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [4, 3], and NBlk[1, 0]: [1, 3] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 3] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 3] != WALL))
	{
		neigborsideNextBlock[rot_count + 7].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [4, 3], and NBlk[1, 0]: [1, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 3] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 4] != WALL))
	{
		//If CurBlock[0, 0] : [4, 4], and NBlk[1, 0] : [1, 3] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 4] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 3] != WALL))
		{
			neigborsideNextBlock[rot_count + 7].bValidRelation[2] = true;
		}
	}

	///rot_count + 8
	//If CurBlock[0, 0] : [4, 2], and NBlk[1, 0]: [1, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 2] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 1] != WALL))
	{
		//If CurBlock[0, 0] : [4, 1], and NBlk[1, 0] : [1, 2] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 1] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 2] != WALL))
		{
			neigborsideNextBlock[rot_count + 8].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [4, 2], and NBlk[1, 0]: [1, 2] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 2] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 2] != WALL))
	{
		neigborsideNextBlock[rot_count + 8].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [4, 2], and NBlk[1, 0]: [1, 3] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 2] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 3] != WALL))
	{
		//If CurBlock[0, 0] : [4, 3], and NBlk[1, 0] : [1, 2] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 3] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 2] != WALL))
		{
			neigborsideNextBlock[rot_count + 8].bValidRelation[2] = true;
		}
	}

	///rot_count + 9
	//If CurBlock[0, 0] : [4, 1], and NBlk[1, 0]: [1, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 1] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 1] != WALL))
	{
		neigborsideNextBlock[rot_count + 9].bValidRelation[0] = true;
	}
	//If CurBlock[0, 0] : [4, 1], and NBlk[1, 0]: [1, 2] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 1] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 2] != WALL))
	{
		//If CurBlock[0, 0] : [4, 2], and NBlk[1, 0] : [1, 1] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 2] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 1] != WALL))
		{
			neigborsideNextBlock[rot_count + 9].bValidRelation[1] = true;
		}
	}
	//If CurBlock[0, 0] : [4, 1], and NBlk[1, -1] : [1, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 1] != WALL) && (mapVisited[SouthWestABS.p_x + 1][SouthWestABS.p_y + 4] != WALL))
	{
		//If NBlk[0, -1] : [4, 4], and NBlk[1, 0] : [1, 1] are not WALLS! check.
		if ((mapVisited[WestABS.p_x + 4][WestABS.p_y + 4] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 1] != WALL))
		{
			neigborsideNextBlock[rot_count + 9].bValidRelation[2] = true;
		}
	}
	//If CurBlock[0, 0] : [4, 1], and NBlk[0, -1]: [3, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 3][WestABS.p_y + 4] != WALL))
	{
		//If CurBlock[0, 0] : [3, 1], and NBlk[0, -1] : [4, 4] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 4][WestABS.p_y + 4] != WALL))
		{
			neigborsideNextBlock[rot_count + 9].bValidRelation[3] = true;
		}
	}
	//If CurBlock[0, 0] : [4, 1], and NBlk[0, -1]: [4, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 4][WestABS.p_y + 4] != WALL))
	{
		neigborsideNextBlock[rot_count + 9].bValidRelation[4] = true;
	}

	///rot_count + 10
	//If CurBlock[0, 0] : [3, 1], and NBlk[0, -1]: [2, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 2][WestABS.p_y + 4] != WALL))
	{
		//If CurBlock[0, 0] : [2, 1], and NBlk[0, -1] : [3, 4] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 3][WestABS.p_y + 4] != WALL))
		{
			neigborsideNextBlock[rot_count + 10].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [3, 1], and NBlk[0, -1]: [3, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 3][WestABS.p_y + 4] != WALL))
	{
		neigborsideNextBlock[rot_count + 10].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [3, 1], and NBlk[0, -1]: [4, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 4][WestABS.p_y + 4] != WALL))
	{
		//If CurBlock[0, 0] : [4, 1], and NBlk[0, -1] : [3, 4] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 3][WestABS.p_y + 4] != WALL))
		{
			neigborsideNextBlock[rot_count + 10].bValidRelation[2] = true;
		}
	}

	///rot_count + 11
	//If CurBlock[0, 0] : [2, 1], and NBlk[0, -1]: [1, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 1][WestABS.p_y + 4] != WALL))
	{
		//If CurBlock[0, 0] : [1, 1], and NBlk[0, -1] : [2, 4] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 2][WestABS.p_y + 4] != WALL))
		{
			neigborsideNextBlock[rot_count + 11].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [2, 1], and NBlk[0, -1]: [2, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 2][WestABS.p_y + 4] != WALL))
	{
		neigborsideNextBlock[rot_count + 11].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [2, 1], and NBlk[0, -1]: [3, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 3][WestABS.p_y + 4] != WALL))
	{
		//If CurBlock[0, 0] : [3, 1], and NBlk[0, -1] : [2, 4] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 2][WestABS.p_y + 4] != WALL))
		{
			neigborsideNextBlock[rot_count + 11].bValidRelation[2] = true;
		}
	}



    //for valid egress node x on current side

}
