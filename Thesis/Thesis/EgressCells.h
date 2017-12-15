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

/*
Set the In-Corners of the corner position of a block.
Parameters to the function:
curPosInBlock : const BlockPosition & - The current position in block.
posRel : PositionRelations & - The position relations object that will contain the curPosInBlock - Neighbor Block Positions relations.
NeighBlkArr : const Position & - the neighboring block.
NeighBlkPosArr : const std::initializer_list<Position> & - the positions inside the neighboring block (relative to the block).
Returns from the function:
NONE
This function takes in the position relations (posRel) that is set with the current block position and its neighboring relations. It sets the In-Corners of the corner position of a block. For an octile grid, an in-corner position in a block has 3 neighbors (2 diagonals and 1 horizontal/vertical) in the (horizontal/vertical) adjacent block.
*/
void EgressCellsInCorners(const BlockPosition & curPosInBlock, PositionRelations & posRel, const Position & NeighBlkArr, const std::initializer_list<Position> & NeighBlkPosArr)
{
	//posRel.posFrom = curPosInBlock, posRel.posTo[0] = BlockPosition(NeighBlkArr, NeighBlkPosArr[0]).
	posRel.Set(curPosInBlock, BlockPosition(NeighBlkArr, *(NeighBlkPosArr.begin() + 0)), 0, MAX_IN_CORNER_RELATIONS);

	//posRel.posFrom = curPosInBlock, posRel.posTo[1] = BlockPosition(NeighBlkArr, NeighBlkPosArr[1]).
	posRel.Set(curPosInBlock, BlockPosition(NeighBlkArr, *(NeighBlkPosArr.begin() + 1)), 1, MAX_IN_CORNER_RELATIONS);

	//posRel.posFrom = curPosInBlock, posRel.posTo[2] = BlockPosition(NeighBlkArr, NeighBlkPosArr[2]).
	posRel.Set(curPosInBlock, BlockPosition(NeighBlkArr, *(NeighBlkPosArr.begin() + 2)), 2, MAX_IN_CORNER_RELATIONS);
}

/*
Set the Out-Corners of the corner position of a block.
Parameters to the function:
curPosInBlock : const BlockPosition & - The current position in block.
posRel : PositionRelations & - The position relations object that will contain the curPosInBlock - Neighbor Block Positions relations.
NeighBlkArr : const std::initializer_list<Position> & - the neighboring blocks.
NeighBlkPosArr : const std::initializer_list<Position> & - the positions inside the neighboring blocks (relative to the blocks).
Returns from the function:
NONE
This function takes in the position relations (posRel) that is set with the current block position and its neighboring relations. It sets the Out-Corners of the corner position of a block. For an octile grid, an out-corner position in a block has 5 neighbors (3 diagonals and 2 horizontal/vertical) in 2 (horizontal and vertical) adjacent blocks and 1 diagonal block.
*/
void EgressCellsOutCorners(const BlockPosition & curPosInBlock, PositionRelations & posRel, const std::initializer_list<Position> & NeighBlkArr, const std::initializer_list<Position> & NeighBlkPosArr)
{
	//posRel.posFrom = curPosInBlock, posRel.posTo[0] = BlockPosition(NeighBlkArr[0], NeighBlkPosArr[0]).
	posRel.Set(curPosInBlock, BlockPosition(*(NeighBlkArr.begin() + 0), *(NeighBlkPosArr.begin() + 0)), 0, MAX_OUT_CORNER_RELATIONS);

	//posRel.posFrom = curPosInBlock, posRel.posTo[1] = BlockPosition(NeighBlkArr[0], NeighBlkPosArr[1]).
	posRel.Set(curPosInBlock, BlockPosition(*(NeighBlkArr.begin() + 0), *(NeighBlkPosArr.begin() + 1)), 1, MAX_OUT_CORNER_RELATIONS);

	//posRel.posFrom = curPosInBlock, posRel.posTo[2] = BlockPosition(NeighBlkArr[1], NeighBlkPosArr[2]).
	posRel.Set(curPosInBlock, BlockPosition(*(NeighBlkArr.begin() + 1), *(NeighBlkPosArr.begin() + 2)), 2, MAX_OUT_CORNER_RELATIONS);

	//posRel.posFrom = curPosInBlock, posRel.posTo[3] = BlockPosition(NeighBlkArr[2], NeighBlkPosArr[3]).
	posRel.Set(curPosInBlock, BlockPosition(*(NeighBlkArr.begin() + 2), *(NeighBlkPosArr.begin() + 3)), 3, MAX_OUT_CORNER_RELATIONS);

	//posRel.posFrom = curPosInBlock, posRel.posTo[4] = BlockPosition(NeighBlkArr[2], NeighBlkPosArr[4]).
	posRel.Set(curPosInBlock, BlockPosition(*(NeighBlkArr.begin() + 2), *(NeighBlkPosArr.begin() + 4)), 4, MAX_OUT_CORNER_RELATIONS);
}

/*
Set the Egress Cells of the corner positions of a block.
Parameters to the function:
curBlock : const Position & - The current block.
posRel : PositionRelations[] - The position relations to the outer positions of the current block.
nOuterBordersSize : const unsigned int & - The size of the position relations array.
Returns from the function:
NONE
This function takes in the current block and the position relations array that needs to be filled in with the egress cells information (valid or invalid!!) of the current block's outer positions. (No validity check of egress cells done here!!). It returns nothing.
*/
void EgressCells(const Position & curBlock, PositionRelations posRel[], const unsigned int & nOuterBordersSize)
{
	//Adjacent blocks' positions.

	//NBlk[-1, -1] - NorthWest block.
	Position NorthWestBlk(curBlock.p_x - 1, curBlock.p_y - 1);

	//NBlk[-1, 0] - North block.
	Position NorthBlk(curBlock.p_x - 1, curBlock.p_y);

	//NBlk[-1, 1] - NorthEast block.
	Position NorthEastBlk(curBlock.p_x - 1, curBlock.p_y + 1);

	//NBlk[0, 1] - East block.
	Position EastBlk(curBlock.p_x, curBlock.p_y + 1);

	//NBlk[1, 1] - SouthEast block.
	Position SouthEastBlk(curBlock.p_x + 1, curBlock.p_y + 1);

	//NBlk[1, 0] - South block.
	Position SouthBlk(curBlock.p_x + 1, curBlock.p_y);

	//NBlk[1, -1] - SouthWest block.
	Position SouthWestBlk(curBlock.p_x + 1, curBlock.p_y - 1);

	//NBlk[0, -1] - West block.
	Position WestBlk(curBlock.p_x, curBlock.p_y - 1);

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
	Side of CurBlock: [1, 1]. Side of NeighborBlock: NBlk[0, -1]: [1, 4], NBlk[0, -1]: [2, 4], NBlk[-1, -1]: [4, 4], NBlk[-1, 0]: [4, 1], NBlk[-1, 0]: [4, 2].
	Position(1, 1) of currentBlock has neighbors in the three blocks adjacent to the currentBlock: WestBlk, NorthWestBlk, and NorthBlk.
	WestBlk, we have positions: Position(1, Y), and Position(2, Y).
	NorthWestBlk, we have positions: Position(X, Y).
	NorthBlk, we have positions: Position(X, 1), and Position(X, 2).
	*/
	EgressCellsOutCorners(BlockPosition(curBlock, Position(1, 1)), posRel[firstCorner], { WestBlk, NorthWestBlk, NorthBlk }, { Position(1, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(2, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, 1), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, 2) });

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
		EgressCellsInCorners(BlockPosition(curBlock, Position(1, yIncrement)), posRel[firstCorner + (yIncrement - 1)], { NorthBlk }, { Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (yIncrement - 1)), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, yIncrement), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, (yIncrement + 1)) });
	}

	/*
	For a 4x4 block example: position[3]: (1, 4) of the outer border positions of the block.
	Side of CurBlock: [1, 4]. Side of NeighborBlock: NBlk[-1, 0]: [4, 3], NBlk[-1, 0]: [4, 4], NBlk[-1, 1]: [4, 1], NBlk[0, 1]: [1, 1], NBlk[0, 1]: [2, 1].
	Position(1, Y) of currentBlock has neighbors in the three blocks adjacent to the currentBlock: NorthBlk, NorthEastBlk, and EastBlk.
	NorthBlk, we have positions: Position(X, Y - 1), and Position(X, Y).
	NorthEastBlk, we have positions: Position(X, 1).
	EastBlk, we have positions: Position(1, 1), and Position(2, 1).
	*/
	EgressCellsOutCorners(BlockPosition(curBlock, Position(1, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y)), posRel[secondCorner], { NorthBlk, NorthEastBlk, EastBlk }, { Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 1), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, 1), Position(1, 1), Position(2, 1) });

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
		EgressCellsInCorners(BlockPosition(curBlock, Position(xIncrement, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y)), posRel[secondCorner + (xIncrement - 1)], { EastBlk }, { Position((xIncrement - 1), 1), Position(xIncrement, 1), Position((xIncrement + 1), 1) });
	}

	/*
	For a 4x4 block example: position[6]: (4, 4) of the outer border positions of the block.
	Side of CurBlock: [4, 4]. Side of NeighborBlock: NBlk[0, 1]: [3, 1], NBlk[0, 1]: [4, 1], NBlk[1, 1]: [1, 1], NBlk[1, 0]: [1, 3], NBlk[1, 0]: [1, 4].
	Position(X, Y) of currentBlock has neighbors in the three blocks adjacent to the currentBlock: EastBlk, SouthEastBlk, and SouthBlk.
	EastBlk, we have positions: Position(X - 1, 1), and Position(X, 1).
	SouthEastBlk, we have positions: Position(1, 1).
	SouthBlk, we have positions: Position(1, Y - 1), and Position(1, Y).
	*/
	EgressCellsOutCorners(BlockPosition(curBlock, Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y)), posRel[thirdCorner], { EastBlk, SouthEastBlk, SouthBlk }, { Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 1, 1), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, 1), Position(1, 1), Position(1, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 1), Position(1, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y) });

	for (unsigned int yIncrement = (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 1); yIncrement > 1; --yIncrement)
	{
		/*
		For a 4x4 block example: position[7]: (4, 3) of the outer border positions of the block.
		For a 4x4 block example: position[8]: (4, 2) of the outer border positions of the block.
		Side of CurBlock: [4, 3]. Side of NeighborBlock: NBlk[1, 0]: [1, 2], NBlk[1, 0]: [1, 3], NBlk[1, 0]: [1, 4].
		Side of CurBlock: [4, 2]. Side of NeighborBlock: NBlk[1, 0]: [1, 1], NBlk[1, 0]: [1, 2], NBlk[1, 0]: [1, 3].
		Position(X, Y - 1), Position(X, Y - 2),.. Position(X, K),.. Position(X, 2) of currentBlock has neighbors in one block adjacent to the currentBlock: SouthBlk.
		SouthBlk, we have positions: Position(1, K - 1), Position(1, K), and Position(1, K + 1).
		*/
		EgressCellsInCorners(BlockPosition(curBlock, Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, yIncrement)), posRel[thirdCorner + (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - yIncrement)], { SouthBlk }, { Position(1, (yIncrement - 1)), Position(1, yIncrement), Position(1, (yIncrement + 1)) });
	}

	/*
	For a 4x4 block example: position[9]: (4, 1) of the outer border positions of the block.
	Side of CurBlock: [4, 1]. Side of NeighborBlock: NBlk[1, 0]: [1, 1], NBlk[1, 0]: [1, 2], NBlk[1, -1]: [1, 4], NBlk[0, -1]: [3, 4], NBlk[0, -1]: [4, 4].
	Position(X, 1) of currentBlock has neighbors in the three blocks adjacent to the currentBlock: SouthBlk, SouthWestBlk, and WestBlk.
	SouthBlk, we have positions: Position(1, 1), and Position(1, 2).
	SouthWestBlk, we have positions: Position(1, Y).
	WestBlk, we have positions: Position(X - 1, Y), and Position(X, Y).
	*/
	EgressCellsOutCorners(BlockPosition(curBlock, Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, 1)), posRel[fourthCorner], { SouthBlk, SouthWestBlk, WestBlk }, { Position(1, 1), Position(1, 2), Position(1, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 1, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y) });

	for (unsigned int xIncrement = (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 1); xIncrement > 1; --xIncrement)
	{
		/*
		For a 4x4 block example: position[10]: (3, 1) of the outer border positions of the block.
		For a 4x4 block example: position[11]: (2, 1) of the outer border positions of the block.
		Side of CurBlock: [3, 1]. Side of NeighborBlock: NBlk[0, -1]: [2, 4], NBlk[0, -1]: [3, 4], NBlk[0, -1]: [4, 4].
		Side of CurBlock: [2, 1]. Side of NeighborBlock: NBlk[0, -1]: [1, 4], NBlk[0, -1]: [2, 4], NBlk[0, -1]: [3, 4].
		Position(X - 1, 1), Position(X - 2, 1),.. Position(K, 1),.. Position(2, 1) of currentBlock has neighbors in one block adjacent to the currentBlock: WestBlk.
		WestBlk, we have positions: Position(K - 1, Y), Position(K, Y), and Position(K + 1, Y).
		*/
		EgressCellsInCorners(BlockPosition(curBlock, Position(xIncrement, 1)), posRel[fourthCorner + (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - xIncrement)], { WestBlk }, { Position((xIncrement - 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position(xIncrement, SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y), Position((xIncrement + 1), SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y) });
	}
}
#endif