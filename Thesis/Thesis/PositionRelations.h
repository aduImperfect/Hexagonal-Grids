///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: PositionRelations.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef POSITION_RELATIONS_H
#define POSITION_RELATIONS_H
//Including the base defines header and the position structure.
#include "BaseDefines.h"
#include "Position.h"

/*
Block Position structure that keeps track of a position's block and its internal relative position to the block.
Data:
pos_BlockNo : Position - the block position number (this points to the position of the whole block in the grid).
pos_RelPos : Position - the relative position internal to the block.
Functionalities:
BlockPosition() - The constructor which takes in nothing and sets the BlockNo and RelPos to Position(-1, -1).
BlockPosition(const Position pos_BNo, const Position pos_RPos) - The constructor that takes in a pos_BNo, and a pos_RPos with whom it sets the pos_BlockNo, and pos_RelPos values of the struct.
operator==(const BlockPosition &rhs) const - checks to see if 'this' and the 'other' 's pos_BlockNo and pos_RelPos values are the same.
*/
struct BlockPosition
{
	//The block number of the position.
	Position pos_BlockNo;

	//The relative position inside the block.
	Position pos_RelPos;

	/*
	Construct a new block position object.
	Parameters to the constructor:
	NONE
	Returns from the constructor:
	NONE
	This constructor takes in nothing and internally sets the position's block number to (-1, -1) and the relative position to its block to (-1, -1) and returns nothing.
	*/
	BlockPosition()
	{
		pos_BlockNo = Position(-1, -1);
		pos_RelPos = Position(-1, -1);
	}

	/*
	Construct a new block position object.
	Parameters to the constructor:
	pos_BNo : const Position - the block position of the grid position.
	pos_RPos : const Position - the relative position inside the block of the grid position.
	Returns from the constructor:
	NONE
	This constructor takes in a new block number and relative position values and sets the position's block number and the relative position to them and returns nothing.
	*/
	BlockPosition(const Position pos_BNo, const Position pos_RPos)
	{
		pos_BlockNo = pos_BNo;
		pos_RelPos = pos_RPos;
	}

	/*
	Checks to see if the two block positions are the same.
	Parameters to the function:
	rhs : const BlockPosition & - The rhs that gets checked against the 'this' block position.
	Returns from the function:
	isSame : bool - return value which tells us if the two block position's are the same.
	This function takes in rhs and checks its pos_BlockNo and pos_RelPos values with the current block position's pos_BlockNo and pos_RelPos values.
	It returns true if both block position's are the same, else false.
	*/
	bool /*isSame*/ operator==(const BlockPosition & rhs) const
	{
		if (rhs.pos_BlockNo != this->pos_BlockNo)
			return false;

		if (rhs.pos_RelPos != this->pos_RelPos)
			return false;

		return true;
	}
};

//Block_Invalid is a block position that is located at the block(-1, -1) with a relative position of (-1, -1).
BlockPosition Block_Invalid(Position(-1, -1), Position(-1, -1));

/*
Position Relations class keeps track of a block position and its nearby block positions if they are a valid relation or not.
Data:
PUBLIC:
pos_From : BlockPosition - the central block position to which all the relation relate to.
pos_To : BlockPosition[MAX_RELATIONS] - the relative block positions (they keep changing from 3-5 and vice versa for a square grid). Basically, the 5 points associated with an out-corner position which are in the 3 other blocks adjacent to its block OR the 3 points associated with an in-corner position which are in the single block adjacent to its block.
bValidRelations : bool[MAX_RELATIONS] - the result of each relation be it for an out-corner or an in-corner to find out how many valid relations are there.
Functionalities:
PositionRelations(const BlockPosition pos_F = Block_Invalid) - The constructor which takes in the from block position which it defaults to Block_Invalid. It sets all the pos_To[] elements to Block_Invalid and the bValidRelation[] array to all false.
Set(const BlockPosition pos_f, const BlockPosition pos_T, const int nRelNo, const int nMaxRel) - The function takes in the from position, the to position, the relation number for where the to position is located in the array of pos_To[] if the relation number is within the MAX_RELATIONS range. Otherwise, it returns false.
*/
class PositionRelations
{
public:
	//The block position for which the relations are saved.
	BlockPosition pos_From;

	//The array of block positions that are related to the pos_From block position.
	BlockPosition pos_To[MAX_RELATIONS];

	//The array of valid relations that tells us which pos_To[] element is a valid relation to pos_From.
	bool bValidRelation[MAX_RELATIONS];

	/*
	Construct a new block position object.
	Parameters to the constructor:
	pos_F : const BlockPosition - the block position for which the relations are to be saved.
	Returns from the constructor:
	NONE
	This constructor takes in the block position to which all the relations are to be tied internally, it sets pos_From to pos_F and sets all the relational block positions to Block_Invalid along with setting their respective valid relations values to false and returns nothing.
	*/
	PositionRelations(const BlockPosition pos_F = Block_Invalid)
	{
		pos_From = pos_F;
		for (unsigned int i = 0; i < MAX_RELATIONS; ++i)
		{
			pos_To[i] = Block_Invalid;
			bValidRelation[i] = false;
		}
	}

	/*
	Sets the values of the block position from and its block position to relations.
	Parameters to the function:
	pos_F : const BlockPosition - The block position to which all the relations will be set.
	pos_T : const BlockPosition - The block position that is set as related to the pos_From (pos_F) block position based on what its relation number is.
	nRelNo : const int - The relation number for the pos_To relational block position with respect to the pos_From block position.
	nMaxRel : const int - The maximum number of relations the pos_From block position can have.
	Returns from the function:
	isSet : bool - Return value which tells us if the pos_From block position gets set the pos_T block position at relation no: nRelNo.
	This function takes in the from block position and the to block position which gets set at nRelNo if the nRelNo is within bounds of the nMaxRel. It returns true if the relational block position gets set for pos_From, otherwise false.
	*/
	bool /*isSet*/ Set(const BlockPosition pos_F, const BlockPosition pos_T, const int nRelNo, const int nMaxRel)
	{
		//Set the pos_From to pos_F.
		pos_From = pos_F;

		//If nRelNo is greater than the nMaxRel then early exit with returning false, as we could not set the relation.
		if (nRelNo >= nMaxRel)
			return false;

		//If within the relation number, set the valid relation value to false, and set the pos_To[nRelNo] to pos_T.
		//Valid relations are set to true only if it is a relation that is also not a wall or outside the bounds!! (which is not being checked here!).
		bValidRelation[nRelNo] = false;
		pos_To[nRelNo] = pos_T;

		//Return true after all the operations are completed.
		return true;
	}
};
#endif