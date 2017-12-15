///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: SquareExpandBlock.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef SQUARE_EXPAND_BLOCK_H
#define SQUARE_EXPAND_BLOCK_H
//Including the base headers for the base square operations, the position structure, the position relations structures, and the egress cells calculations.
#include "BaseSquareOperations.h"
#include "Position.h"
#include "PositionRelations.h"
#include "EgressCells.h"
#include "ValidEgressCells.h"

/*

*/
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

	unsigned int nTotalSize = SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y;
	unsigned int nInnerSize = (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 2) * (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 2);

	const unsigned int nOuterBordersSize = nTotalSize - nInnerSize;

	//(Side of curblock) : [Neighborblk, side of neighbor blk].
	PositionRelations * neighborsideNextBlock = new PositionRelations[nOuterBordersSize];
	for (unsigned int nBlki = 0; nBlki < nOuterBordersSize; ++nBlki)
	{
		neighborsideNextBlock[nBlki];
	}

	EgressCells(curBlock, neighborsideNextBlock, nOuterBordersSize);


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

	unsigned int rot_count = 0;

	///rot_count
	//If CurBlock[0, 0] : [1, 1], and NBlk[0, -1] : [1, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 1][WestABS.p_y + 4] != WALL))
	{
		neighborsideNextBlock[rot_count].bValidRelation[0] = true;
	}
	//If CurBlock[0, 0] : [1, 1], and NBlk[0, -1]: [2, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 2][WestABS.p_y + 4] != WALL))
	{
		//If CurBlock[0, 0] : [2, 1], and NBlk[0, -1] : [1, 4] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 1][WestABS.p_y + 4] != WALL))
		{
			neighborsideNextBlock[rot_count].bValidRelation[1] = true;
		}
	}
	//If CurBlock[0, 0] : [1, 1], and NBlk[-1, -1] : [4, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 1] != WALL) && (mapVisited[NorthWestABS.p_x + 4][NorthWestABS.p_y + 4] != WALL))
	{
		//If NBlk[0, -1] : [1, 4], and NBlk[-1, 0] : [4, 1] are not WALLS! check.
		if ((mapVisited[WestABS.p_x + 1][WestABS.p_y + 4] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 1] != WALL))
		{
			neighborsideNextBlock[rot_count].bValidRelation[2] = true;
		}
	}
	//If CurBlock[0, 0] : [1, 1], and NBlk[-1, 0]: [4, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 1] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 1] != WALL))
	{
		neighborsideNextBlock[rot_count].bValidRelation[3] = true;
	}
	//If CurBlock[0, 0] : [1, 1], and NBlk[-1, 0]: [4, 2] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 1] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 2] != WALL))
	{
		//If CurBlock[0, 0] : [1, 2], and NBlk[-1, 0] : [4, 1] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 2] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 1] != WALL))
		{
			neighborsideNextBlock[rot_count].bValidRelation[4] = true;
		}
	}

	///rot_count + 1
	//If CurBlock[0, 0] : [1, 2], and NBlk[-1, 0]: [4, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 2] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 1] != WALL))
	{
		//If CurBlock[0, 0] : [1, 1], and NBlk[-1, 0] : [4, 2] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 1] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 2] != WALL))
		{
			neighborsideNextBlock[rot_count + 1].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [1, 2], and NBlk[-1, 0]: [4, 2] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 2] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 2] != WALL))
	{
		neighborsideNextBlock[rot_count + 1].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [1, 2], and NBlk[-1, 0]: [4, 3] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 2] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 3] != WALL))
	{
		//If CurBlock[0, 0] : [1, 3], and NBlk[-1, 0] : [4, 2] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 3] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 2] != WALL))
		{
			neighborsideNextBlock[rot_count + 1].bValidRelation[2] = true;
		}
	}

	///rot_count + 2
	//If CurBlock[0, 0] : [1, 3], and NBlk[-1, 0]: [4, 2] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 3] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 2] != WALL))
	{
		//If CurBlock[0, 0] : [1, 2], and NBlk[-1, 0] : [4, 3] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 2] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 3] != WALL))
		{
			neighborsideNextBlock[rot_count + 2].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [1, 3], and NBlk[-1, 0]: [4, 3] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 3] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 3] != WALL))
	{
		neighborsideNextBlock[rot_count + 2].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [1, 3], and NBlk[-1, 0]: [4, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 3] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 4] != WALL))
	{
		//If CurBlock[0, 0] : [1, 4], and NBlk[-1, 0] : [4, 3] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 4] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 3] != WALL))
		{
			neighborsideNextBlock[rot_count + 2].bValidRelation[2] = true;
		}
	}

	///rot_count + 3
	//If CurBlock[0, 0] : [1, 4], and NBlk[-1, 0]: [4, 3] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 4] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 3] != WALL))
	{
		//If CurBlock[0, 0] : [1, 3], and NBlk[-1, 0] : [4, 4] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 3] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 4] != WALL))
		{
			neighborsideNextBlock[rot_count + 3].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [1, 4], and NBlk[-1, 0]: [4, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 4] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 4] != WALL))
	{
		neighborsideNextBlock[rot_count + 3].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [1, 4], and NBlk[-1, 1] : [4, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 4] != WALL) && (mapVisited[NorthEastABS.p_x + 4][NorthEastABS.p_y + 1] != WALL))
	{
		//If NBlk[0, 1] : [1, 1], and NBlk[-1, 0] : [4, 4] are not WALLS! check.
		if ((mapVisited[EastABS.p_x + 1][EastABS.p_y + 1] != WALL) && (mapVisited[NorthABS.p_x + 4][NorthABS.p_y + 4] != WALL))
		{
			neighborsideNextBlock[rot_count + 3].bValidRelation[2] = true;
		}
	}
	//If CurBlock[0, 0] : [1, 4], and NBlk[0, 1]: [1, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 1][EastABS.p_y + 1] != WALL))
	{
		neighborsideNextBlock[rot_count + 3].bValidRelation[3] = true;
	}
	//If CurBlock[0, 0] : [1, 4], and NBlk[0, 1]: [2, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 2][EastABS.p_y + 1] != WALL))
	{
		//If CurBlock[0, 0] : [2, 4], and NBlk[0, 1] : [1, 1] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 1][EastABS.p_y + 1] != WALL))
		{
			neighborsideNextBlock[rot_count + 3].bValidRelation[4] = true;
		}
	}

	///rot_count + 4
	//If CurBlock[0, 0] : [2, 4], and NBlk[0, 1]: [1, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 1][EastABS.p_y + 1] != WALL))
	{
		//If CurBlock[0, 0] : [1, 4], and NBlk[0, 1] : [2, 1] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 2][EastABS.p_y + 1] != WALL))
		{
			neighborsideNextBlock[rot_count + 4].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [2, 4], and NBlk[0, 1]: [2, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 2][EastABS.p_y + 1] != WALL))
	{
		neighborsideNextBlock[rot_count + 4].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [2, 4], and NBlk[0, 1]: [3, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 3][EastABS.p_y + 1] != WALL))
	{
		//If CurBlock[0, 0] : [3, 4], and NBlk[0, 1] : [2, 1] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 2][EastABS.p_y + 1] != WALL))
		{
			neighborsideNextBlock[rot_count + 4].bValidRelation[2] = true;
		}
	}

	///rot_count + 5
	//If CurBlock[0, 0] : [3, 4], and NBlk[0, 1]: [2, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 2][EastABS.p_y + 1] != WALL))
	{
		//If CurBlock[0, 0] : [2, 4], and NBlk[0, 1] : [3, 1] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 3][EastABS.p_y + 1] != WALL))
		{
			neighborsideNextBlock[rot_count + 5].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [3, 4], and NBlk[0, 1]: [3, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 3][EastABS.p_y + 1] != WALL))
	{
		neighborsideNextBlock[rot_count + 5].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [3, 4], and NBlk[0, 1]: [4, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 4][EastABS.p_y + 1] != WALL))
	{
		//If CurBlock[0, 0] : [4, 4], and NBlk[0, 1] : [3, 1] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 3][EastABS.p_y + 1] != WALL))
		{
			neighborsideNextBlock[rot_count + 5].bValidRelation[2] = true;
		}
	}

	///rot_count + 6
	//If CurBlock[0, 0] : [4, 4], and NBlk[0, 1]: [3, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 3][EastABS.p_y + 1] != WALL))
	{
		//If CurBlock[0, 0] : [3, 4], and NBlk[0, 1] : [4, 1] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 4][EastABS.p_y + 1] != WALL))
		{
			neighborsideNextBlock[rot_count + 6].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [4, 4], and NBlk[0, 1] : [4, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 4] != WALL) && (mapVisited[EastABS.p_x + 4][EastABS.p_y + 1] != WALL))
	{
		neighborsideNextBlock[rot_count + 6].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [4, 4], and NBlk[1, 1] : [1, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 4] != WALL) && (mapVisited[SouthEastABS.p_x + 1][SouthEastABS.p_y + 1] != WALL))
	{
		//If NBlk[0, 1] : [4, 1], and NBlk[1, 0] : [1, 4] are not WALLS! check.
		if ((mapVisited[EastABS.p_x + 4][EastABS.p_y + 1] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 4] != WALL))
		{
			neighborsideNextBlock[rot_count + 6].bValidRelation[2] = true;
		}
	}
	//If CurBlock[0, 0] : [4, 4], and NBlk[1, 0]: [1, 3] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 4] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 3] != WALL))
	{
		//If CurBlock[0, 0] : [4, 3], and NBlk[1, 0] : [1, 4] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 3] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 4] != WALL))
		{
			neighborsideNextBlock[rot_count + 6].bValidRelation[3] = true;
		}
	}
	//If CurBlock[0, 0] : [4, 4], and NBlk[1, 0]: [1, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 4] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 4] != WALL))
	{
		neighborsideNextBlock[rot_count + 6].bValidRelation[4] = true;
	}

	///rot_count + 7
	//If CurBlock[0, 0] : [4, 3], and NBlk[1, 0]: [1, 2] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 3] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 2] != WALL))
	{
		//If CurBlock[0, 0] : [4, 2], and NBlk[1, 0] : [1, 3] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 2] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 3] != WALL))
		{
			neighborsideNextBlock[rot_count + 7].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [4, 3], and NBlk[1, 0]: [1, 3] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 3] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 3] != WALL))
	{
		neighborsideNextBlock[rot_count + 7].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [4, 3], and NBlk[1, 0]: [1, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 3] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 4] != WALL))
	{
		//If CurBlock[0, 0] : [4, 4], and NBlk[1, 0] : [1, 3] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 4] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 3] != WALL))
		{
			neighborsideNextBlock[rot_count + 7].bValidRelation[2] = true;
		}
	}

	///rot_count + 8
	//If CurBlock[0, 0] : [4, 2], and NBlk[1, 0]: [1, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 2] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 1] != WALL))
	{
		//If CurBlock[0, 0] : [4, 1], and NBlk[1, 0] : [1, 2] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 1] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 2] != WALL))
		{
			neighborsideNextBlock[rot_count + 8].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [4, 2], and NBlk[1, 0]: [1, 2] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 2] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 2] != WALL))
	{
		neighborsideNextBlock[rot_count + 8].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [4, 2], and NBlk[1, 0]: [1, 3] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 2] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 3] != WALL))
	{
		//If CurBlock[0, 0] : [4, 3], and NBlk[1, 0] : [1, 2] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 3] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 2] != WALL))
		{
			neighborsideNextBlock[rot_count + 8].bValidRelation[2] = true;
		}
	}

	///rot_count + 9
	//If CurBlock[0, 0] : [4, 1], and NBlk[1, 0]: [1, 1] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 1] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 1] != WALL))
	{
		neighborsideNextBlock[rot_count + 9].bValidRelation[0] = true;
	}
	//If CurBlock[0, 0] : [4, 1], and NBlk[1, 0]: [1, 2] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 1] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 2] != WALL))
	{
		//If CurBlock[0, 0] : [4, 2], and NBlk[1, 0] : [1, 1] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 2] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 1] != WALL))
		{
			neighborsideNextBlock[rot_count + 9].bValidRelation[1] = true;
		}
	}
	//If CurBlock[0, 0] : [4, 1], and NBlk[1, -1] : [1, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 1] != WALL) && (mapVisited[SouthWestABS.p_x + 1][SouthWestABS.p_y + 4] != WALL))
	{
		//If NBlk[0, -1] : [4, 4], and NBlk[1, 0] : [1, 1] are not WALLS! check.
		if ((mapVisited[WestABS.p_x + 4][WestABS.p_y + 4] != WALL) && (mapVisited[SouthABS.p_x + 1][SouthABS.p_y + 1] != WALL))
		{
			neighborsideNextBlock[rot_count + 9].bValidRelation[2] = true;
		}
	}
	//If CurBlock[0, 0] : [4, 1], and NBlk[0, -1]: [3, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 3][WestABS.p_y + 4] != WALL))
	{
		//If CurBlock[0, 0] : [3, 1], and NBlk[0, -1] : [4, 4] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 4][WestABS.p_y + 4] != WALL))
		{
			neighborsideNextBlock[rot_count + 9].bValidRelation[3] = true;
		}
	}
	//If CurBlock[0, 0] : [4, 1], and NBlk[0, -1]: [4, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 4][WestABS.p_y + 4] != WALL))
	{
		neighborsideNextBlock[rot_count + 9].bValidRelation[4] = true;
	}

	///rot_count + 10
	//If CurBlock[0, 0] : [3, 1], and NBlk[0, -1]: [2, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 2][WestABS.p_y + 4] != WALL))
	{
		//If CurBlock[0, 0] : [2, 1], and NBlk[0, -1] : [3, 4] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 3][WestABS.p_y + 4] != WALL))
		{
			neighborsideNextBlock[rot_count + 10].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [3, 1], and NBlk[0, -1]: [3, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 3][WestABS.p_y + 4] != WALL))
	{
		neighborsideNextBlock[rot_count + 10].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [3, 1], and NBlk[0, -1]: [4, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 4][WestABS.p_y + 4] != WALL))
	{
		//If CurBlock[0, 0] : [4, 1], and NBlk[0, -1] : [3, 4] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 4][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 3][WestABS.p_y + 4] != WALL))
		{
			neighborsideNextBlock[rot_count + 10].bValidRelation[2] = true;
		}
	}

	///rot_count + 11
	//If CurBlock[0, 0] : [2, 1], and NBlk[0, -1]: [1, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 1][WestABS.p_y + 4] != WALL))
	{
		//If CurBlock[0, 0] : [1, 1], and NBlk[0, -1] : [2, 4] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 1][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 2][WestABS.p_y + 4] != WALL))
		{
			neighborsideNextBlock[rot_count + 11].bValidRelation[0] = true;
		}
	}
	//If CurBlock[0, 0] : [2, 1], and NBlk[0, -1]: [2, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 2][WestABS.p_y + 4] != WALL))
	{
		neighborsideNextBlock[rot_count + 11].bValidRelation[1] = true;
	}
	//If CurBlock[0, 0] : [2, 1], and NBlk[0, -1]: [3, 4] are not WALLS! check.
	if ((mapVisited[CurentABS.p_x + 2][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 3][WestABS.p_y + 4] != WALL))
	{
		//If CurBlock[0, 0] : [3, 1], and NBlk[0, -1] : [2, 4] are not WALLS! check.
		if ((mapVisited[CurentABS.p_x + 3][CurentABS.p_y + 1] != WALL) && (mapVisited[WestABS.p_x + 2][WestABS.p_y + 4] != WALL))
		{
			neighborsideNextBlock[rot_count + 11].bValidRelation[2] = true;
		}
	}



	//for valid egress node x on current side

}
#endif