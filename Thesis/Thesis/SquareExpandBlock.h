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
#include "EgressCellsToFile.h"

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
				x.g = min[y in Y](y.g + LDDB(y,x), x.g)
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

	//for valid egress node x on current side

}
#endif