///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: EgressCells.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef EGRESS_CELLS_H
#define EGRESS_CELLS_H
//Including the standard libraries for file operations and headers for the base square operations and the position relations structures.
#include <iostream>
#include <fstream>
#include "BaseSquareOperations.h"
#include "PositionRelations.h"

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
#endif