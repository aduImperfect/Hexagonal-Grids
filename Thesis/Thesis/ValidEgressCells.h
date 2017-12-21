///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: ValidEgressCells.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef VALID_EGRESS_CELLS_H
#define VALID_EGRESS_CELLS_H
//Including the base headers for the base square operations and the position relations structures.
#include "BaseSquareOperations.h"
#include "PositionRelations.h"

/*
Validate the In-Corners of the corner position of a block.
Parameters to the function:
curBlock : const Position & - The current block.
curPos : const Position & - The grid offset in the block.
posRel : PositionRelations & - The position relations object that will contain the curPosInBlock - Neighbor Block Positions relations.
NeighBlkArr : const Position & - the neighboring block.
NeighBlkPosArr : const std::initializer_list<Position> & - the positions inside the neighboring block (relative to the block).
Returns from the function:
NONE
This function takes in the position relations (posRel) that is validated with the current block position and its neighboring relations. It validates the In-Corners of the corner position of a block. For an octile grid, an in-corner position in a block has 3 neighbors (2 diagonals and 1 horizontal/vertical) in the (horizontal/vertical) adjacent block.
*/
void ValidateEgressCellsInCorners(const Position & curBlock, const Position & curPos, const std::initializer_list<Position> & dirOffset, PositionRelations & posRel, const Position & NeighBlkArr, std::initializer_list<Position> NeighBlkPosArr)
{
	Position gridPos(curBlock.p_x + curPos.p_x, curBlock.p_y + curPos.p_y);

	//If CurBlock[0, 0] : curPos is a WALL.
	if (IsWallCheck(curBlock, curPos))
	{
		posRel.bValidRelation[0] = posRel.bValidRelation[1] = posRel.bValidRelation[2] = false;
		return;
	}

	//If NBlk[0] : Position[0] is not WALL! check.
	if (!IsWallCheck(NeighBlkArr, *(NeighBlkPosArr.begin() + 0)))
	{
		//If CurBlock[0, 0] : (curPos + dirOffset), and NBlk[0] : Position[0] are not WALLS! check.
		if (!IsWallCheck(gridPos, *(dirOffset.begin() + 0)) && !IsWallCheck(NeighBlkArr, *(NeighBlkPosArr.begin() + 1)))
		{
			posRel.bValidRelation[0] = true;
		}
	}

	//If NBlk[0] : Position[1] is not WALL! check.
	if (!IsWallCheck(NeighBlkArr, *(NeighBlkPosArr.begin() + 1)))
	{
		posRel.bValidRelation[1] = true;
	}

	//If NBlk[0] : Position[2] is not WALL! check.
	if (!IsWallCheck(NeighBlkArr, *(NeighBlkPosArr.begin() + 2)))
	{
		//If CurBlock[0, 0] : (curPos + dirOffset), and NBlk[2] : Position[2] are not WALLS! check.
		if (!IsWallCheck(gridPos, *(dirOffset.begin() + 1)) && !IsWallCheck(NeighBlkArr, *(NeighBlkPosArr.begin() + 1)))
		{
			posRel.bValidRelation[2] = true;
		}
	}
}

/*
Validate the Out-Corners of the corner position of a block.
Parameters to the function:
curBlock : const Position & - The current block.
curPos : const Position & - The grid offset in the block.
posRel : PositionRelations & - The position relations object that will contain the curPosInBlock - Neighbor Block Positions relations.
NeighBlkArr : const std::initializer_list<Position> & - the neighboring blocks.
NeighBlkPosArr : const std::initializer_list<Position> & - the positions inside the neighboring blocks (relative to the blocks).
Returns from the function:
NONE
This function takes in the position relations (posRel) that is validated with the current block position and its neighboring relations. It validates the Out-Corners of the corner position of a block. For an octile grid, an out-corner position in a block has 5 neighbors (3 diagonals and 2 horizontal/vertical) in 2 (horizontal and vertical) adjacent blocks and 1 diagonal block.
*/
void ValidateEgressCellsOutCorners(Position curBlock, Position curPos, std::initializer_list<Position> dirOffset, PositionRelations & posRel, std::initializer_list<Position> NeighBlkArr, std::initializer_list<Position> NeighBlkPosArr)
{
	Position gridPos(curBlock.p_x + curPos.p_x, curBlock.p_y + curPos.p_y);

	//If CurBlock[0, 0] : curPos is a WALL.
	if (IsWallCheck(curBlock, curPos))
	{
		posRel.bValidRelation[0] = posRel.bValidRelation[1] = posRel.bValidRelation[2] = posRel.bValidRelation[3] = posRel.bValidRelation[4] = false;
		return;
	}

	//If NBlk[0] : Position[0] is not WALL! check.
	if (!IsWallCheck(*(NeighBlkArr.begin() + 0), *(NeighBlkPosArr.begin() + 0)))
	{
		//If CurBlock[0, 0] : (curPos + dirOffset), and NBlk[0] : Position[1] are not WALLS! check.
		if (!IsWallCheck(gridPos, *(dirOffset.begin() + 0)) && !IsWallCheck(*(NeighBlkArr.begin() + 0), *(NeighBlkPosArr.begin() + 1)))
		{
			posRel.bValidRelation[0] = true;
		}
	}
	
	//If NBlk[0] : Position[1] is not WALL! check.
	if (!IsWallCheck(*(NeighBlkArr.begin() + 0), *(NeighBlkPosArr.begin() + 1)))
	{
		posRel.bValidRelation[1] = true;
	}

	//If NBlk[1] : Position[2] is not WALL! check.
	if (!IsWallCheck(*(NeighBlkArr.begin() + 1), *(NeighBlkPosArr.begin() + 2)))
	{
		//If NBlk[0] : Position[1], and NBlk[2] : Position[3] are not WALLS! check.
		if (!IsWallCheck(*(NeighBlkArr.begin() + 0), *(NeighBlkPosArr.begin() + 1)) && !IsWallCheck(*(NeighBlkArr.begin() + 2), *(NeighBlkPosArr.begin() + 3)))
		{
			posRel.bValidRelation[2] = true;
		}
	}

	//If NBlk[2] : Position[3] is not WALL! check.
	if (!IsWallCheck(*(NeighBlkArr.begin() + 2), *(NeighBlkPosArr.begin() + 3)))
	{
		posRel.bValidRelation[3] = true;
	}

	//If NBlk[2] : Position[4] is not WALL! check.
	if (!IsWallCheck(*(NeighBlkArr.begin() + 2), *(NeighBlkPosArr.begin() + 4)))
	{
		//If CurBlock[0, 0] : (curPos + dirOffset), and NBlk[2] : Position[3] are not WALLS! check.
		if (!IsWallCheck(gridPos, *(dirOffset.begin() + 1)) && !IsWallCheck(*(NeighBlkArr.begin() + 2), *(NeighBlkPosArr.begin() + 3)))
		{
			posRel.bValidRelation[4] = true;
		}
	}
}

/*
Validate all the egress cells.
Parameters to the function:
curBlock : const Position & - The current block.
posRel : PositionRelations[] - The position relations to the outer positions of the current block.
nOuterBordersSize : const unsigned int & - The size of the position relations array.
Returns from the function:
NONE
This function takes in the current block and the position relations array that needs to be validated for the egress cells information of the current block's outer positions.
*/
void ValidateEgressCells(const Position & curBlock, PositionRelations * posRel, const unsigned int & nOuterBordersSize)
{
	//The CurBlock grid position at: [0, 0].
	Position CurrentABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y));
	
	//The NorthWestBlock grid position at: [-1, -1].
	Position NorthWestABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x - 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y - 1));

	//The NorthBlock grid position at: [-1, 0].
	Position NorthABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x - 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y));

	//The NorthEastBlock grid position at: [-1, 1].
	Position NorthEastABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x - 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y + 1));

	//The EastBlock grid position at: [0, 1].
	Position EastABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y + 1));

	//The SouthEastBlock grid position at: [1, 1].
	Position SouthEastABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x + 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y + 1));

	//The SouthBlock grid position at: [1, 0].
	Position SouthABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x + 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y));

	//The SouthWestBlock grid position at: [1, -1].
	Position SouthWestABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x + 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y - 1));

	//The WestBlock grid position at: [0, -1].
	Position WestABS(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * (curBlock.p_x), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * (curBlock.p_y - 1));

	//For a 4x4 block type example. (X rows-vertical and Y columns-horizontal).

	//The first corner (top left) of the square block. For a 4x4 block example: 0.
	unsigned int firstCorner = 0;

	//The third corner (bottom right) of the square block. For a 4x4 block example: 6.
	unsigned int thirdCorner = nOuterBordersSize / 2;

	//The second corner (top right) of the square block. For a 4x4 block example: 3.
	unsigned int secondCorner = thirdCorner - (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 1);

	//The fourth corner (bottom left) of the square block. For a 4x4 block example: 9.
	unsigned int fourthCorner = thirdCorner + (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 1);

	/*
	For a 4x4 block example: position[0]: (1, 1) of the outer border positions of the block.
	Side of CurBlock: [1, 1]. Side of NeighborBlock: NBlk[0, -1]: [2, 4], NBlk[0, -1]: [1, 4], NBlk[-1, -1]: [4, 4], NBlk[-1, 0]: [4, 1], NBlk[-1, 0]: [4, 2].
	Position(1, 1) of currentBlock has neighbors in the three blocks adjacent to the currentBlock: WestBlk, NorthWestBlk, and NorthBlk.
	WestBlk, we have positions: Position(2, Y), and Position(1, Y).
	NorthWestBlk, we have positions: Position(X, Y).
	NorthBlk, we have positions: Position(X, 1), and Position(X, 2).
	*/
	ValidateEgressCellsOutCorners(CurrentABS, Position(1, 1), { Position(1, 0), Position(0, 1) }, *(posRel + firstCorner), { WestABS, NorthWestABS, NorthABS }, { Position(2, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(1, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, 1), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, 2) });

	for (unsigned int yIncrement = 2; yIncrement < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++yIncrement)
	{
		/*
		For a 4x4 block example: position[1]: (1, 2) of the outer border positions of the block.
		For a 4x4 block example: position[2]: (1, 3) of the outer border positions of the block.
		Side of CurBlock: [1, 2]. Side of NeighborBlock: NBlk[-1, 0]: [4, 1], NBlk[-1, 0]: [4, 2], NBlk[-1, 0]: [4, 3].
		Side of CurBlock: [1, 3]. Side of NeighborBlock: NBlk[-1, 0]: [4, 2], NBlk[-1, 0]: [4, 3], NBlk[-1, 0]: [4, 4].
		Position(1, 2), Position(1, 3),.. Position(1, K),.. Position(1, Y - 1) of currentBlock has neighbors in one block adjacent to the currentBlock: NorthBlk.
		NorthBlk, we have positions: Position(X, K - 1), Position(X, K), and Position(X, K + 1).
		*/
		ValidateEgressCellsInCorners(CurrentABS, Position(1, yIncrement), { Position(0, -1), Position(0, 1) }, *(posRel + firstCorner + (yIncrement - 1)), { NorthABS }, { Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (yIncrement - 1)), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, yIncrement), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (yIncrement + 1)) });
	}

	/*
	For a 4x4 block example: position[3]: (1, 4) of the outer border positions of the block.
	Side of CurBlock: [1, 4]. Side of NeighborBlock: NBlk[-1, 0]: [4, 3], NBlk[-1, 0]: [4, 4], NBlk[-1, 1]: [4, 1], NBlk[0, 1]: [1, 1], NBlk[0, 1]: [2, 1].
	Position(1, Y) of currentBlock has neighbors in the three blocks adjacent to the currentBlock: NorthBlk, NorthEastBlk, and EastBlk.
	NorthBlk, we have positions: Position(X, Y - 1), and Position(X, Y).
	NorthEastBlk, we have positions: Position(X, 1).
	EastBlk, we have positions: Position(1, 1), and Position(2, 1).
	*/
	ValidateEgressCellsOutCorners(CurrentABS, Position(1, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), { Position(0, -1), Position(1, 0) }, *(posRel + secondCorner), { NorthABS, NorthEastABS, EastABS }, { Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 1), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, 1), Position(1, 1), Position(2, 1) });

	for (unsigned int xIncrement = 2; xIncrement < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++xIncrement)
	{
		/*
		For a 4x4 block example: position[4]: (2, 4) of the outer border positions of the block.
		For a 4x4 block example: position[5]: (3, 4) of the outer border positions of the block.
		Side of CurBlock: [2, 4]. Side of NeighborBlock: NBlk[0, 1]: [1, 1], NBlk[0, 1]: [2, 1], NBlk[0, 1]: [3, 1].
		Side of CurBlock: [3, 4]. Side of NeighborBlock: NBlk[0, 1]: [2, 1], NBlk[0, 1]: [3, 1], NBlk[0, 1]: [4, 1].
		Position(2, 1), Position(3, 1),.. Position(K, 1),.. Position(X - 1, 1) of currentBlock has neighbors in one block adjacent to the currentBlock: EastBlk.
		EastBlk, we have positions: Position(K - 1, 1), Position(K, 1), and Position(K + 1, 1).
		*/
		ValidateEgressCellsInCorners(CurrentABS, Position(xIncrement, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), { Position(-1, 0), Position(1, 0) }, *(posRel + secondCorner + (xIncrement - 1)), { EastABS }, { Position((xIncrement - 1), 1), Position(xIncrement, 1), Position((xIncrement + 1), 1) });
	}

	/*
	For a 4x4 block example: position[6]: (4, 4) of the outer border positions of the block.
	Side of CurBlock: [4, 4]. Side of NeighborBlock: NBlk[0, 1]: [3, 1], NBlk[0, 1]: [4, 1], NBlk[1, 1]: [1, 1], NBlk[1, 0]: [1, 4], NBlk[1, 0]: [1, 3].
	Position(X, Y) of currentBlock has neighbors in the three blocks adjacent to the currentBlock: EastBlk, SouthEastBlk, and SouthBlk.
	EastBlk, we have positions: Position(X - 1, 1), and Position(X, 1).
	SouthEastBlk, we have positions: Position(1, 1).
	SouthBlk, we have positions: Position(1, Y), and Position(1, Y - 1).
	*/
	ValidateEgressCellsOutCorners(CurrentABS, Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), { Position(-1, 0), Position(0, -1) }, *(posRel + thirdCorner), { EastABS, SouthEastABS, SouthABS }, { Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 1, 1), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, 1), Position(1, 1), Position(1, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(1, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 1) });

	for (unsigned int yIncrement = (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 1); yIncrement > 1; --yIncrement)
	{
		/*
		For a 4x4 block example: position[7]: (4, 3) of the outer border positions of the block.
		For a 4x4 block example: position[8]: (4, 2) of the outer border positions of the block.
		Side of CurBlock: [4, 3]. Side of NeighborBlock: NBlk[1, 0]: [1, 4], NBlk[1, 0]: [1, 3], NBlk[1, 0]: [1, 2].
		Side of CurBlock: [4, 2]. Side of NeighborBlock: NBlk[1, 0]: [1, 3], NBlk[1, 0]: [1, 2], NBlk[1, 0]: [1, 1].
		Position(X, Y - 1), Position(X, Y - 2),.. Position(X, K),.. Position(X, 2) of currentBlock has neighbors in one block adjacent to the currentBlock: SouthBlk.
		SouthBlk, we have positions: Position(1, K + 1), Position(1, K), and Position(1, K - 1).
		*/
		ValidateEgressCellsInCorners(CurrentABS, Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, yIncrement), { Position(0, 1), Position(0, -1) }, *(posRel + thirdCorner + (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - yIncrement)), { SouthABS }, { Position(1, (yIncrement + 1)), Position(1, yIncrement), Position(1, (yIncrement - 1)) });
	}

	/*
	For a 4x4 block example: position[9]: (4, 1) of the outer border positions of the block.
	Side of CurBlock: [4, 1]. Side of NeighborBlock: NBlk[1, 0]: [1, 2], NBlk[1, 0]: [1, 1], NBlk[1, -1]: [1, 4], NBlk[0, -1]: [4, 4], NBlk[0, -1]: [3, 4].
	Position(X, 1) of currentBlock has neighbors in the three blocks adjacent to the currentBlock: SouthBlk, SouthWestBlk, and WestBlk.
	SouthBlk, we have positions: Position(1, 2), and Position(1, 1).
	SouthWestBlk, we have positions: Position(1, Y).
	WestBlk, we have positions: Position(X, Y), and Position(X - 1, Y).
	*/
	ValidateEgressCellsOutCorners(CurrentABS, Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, 1), { Position(0, 1), Position(-1, 0) }, *(posRel + fourthCorner), { SouthABS, SouthWestABS, WestABS }, { Position(1, 2), Position(1, 1), Position(1, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 1, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y) });

	for (unsigned int xIncrement = (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 1); xIncrement > 1; --xIncrement)
	{
		/*
		For a 4x4 block example: position[10]: (3, 1) of the outer border positions of the block.
		For a 4x4 block example: position[11]: (2, 1) of the outer border positions of the block.
		Side of CurBlock: [3, 1]. Side of NeighborBlock: NBlk[0, -1]: [4, 4], NBlk[0, -1]: [3, 4], NBlk[0, -1]: [2, 4].
		Side of CurBlock: [2, 1]. Side of NeighborBlock: NBlk[0, -1]: [3, 4], NBlk[0, -1]: [2, 4], NBlk[0, -1]: [1, 4].
		Position(X - 1, 1), Position(X - 2, 1),.. Position(K, 1),.. Position(2, 1) of currentBlock has neighbors in one block adjacent to the currentBlock: WestBlk.
		WestBlk, we have positions: Position(K + 1, Y), Position(K, Y), and Position(K - 1, Y).
		*/
		ValidateEgressCellsInCorners(CurrentABS, Position(xIncrement, 1), { Position(1, 0), Position(-1, 0) }, *(posRel + fourthCorner + (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - xIncrement)), { WestABS }, { Position((xIncrement + 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(xIncrement, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position((xIncrement - 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y) });
	}
}
#endif