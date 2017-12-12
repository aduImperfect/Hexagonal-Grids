///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: ValidEgressCells.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef VALID_EGRESS_CELLS_H
#define VALID_EGRESS_CELLS_H
#include "BaseSquareOperations.h"
#include "PositionRelations.h"

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