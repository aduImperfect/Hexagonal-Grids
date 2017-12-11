///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: Position.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef POSITION_H
#define POSITION_H
/*
Position structure that keeps track of the position's values.
Data:
p_x : const int - the row alignment of the 2D position.
p_y : const int - the column alignment of the 2D position.
posCost : double - keeps track of the cost to/from/(to and from) the position (depending on where it is being used).
Functionalities:
Position(const int _x = 0, const int _y = 0) - The constructor which takes in the row and column values and also has a default value of (0,0) for when the user does not input any for the row/column. It initializes the p_x, p_y with the arguments and the posCost is initialized to 0.
operator+(const Position &otherPos) - adds the 'this' and the 'other' position's x and y values and returns a new position.
operator!=(const Position &otherPos) - checks to see if 'this' and the 'other' position's x or y values are not the same.
operator==(const Position &otherPos) - checks to see if 'this' and the 'other' position's x or y values are the same.
*/
struct Position
{
	//The x (row) part of the position in the grid.
	int p_x;

	//The y (column) part of the position in the grid.
	int p_y;

	//The cost at the position.
	double posCost;

	/*
	Construct a new position object.
	Parameters to the constructor:
	_x : const int - The row of the position.
	_y : const int - The column of the position.
	Returns from the constructor:
	NONE
	This constructor takes in the row,column combination of the position and assigns internally to the object's data and also sets its posCost to 0 and returns nothing.
	*/
	Position(const int _x = 0, const int _y = 0)
	{
		p_x = _x;
		p_y = _y;
		posCost = 0.00f;
	}

	/*
	Adds two positions together to form a new position.
	Parameters to the function:
	otherPos : const Position & - The otherPosition that gets added with the 'this' position.
	Returns from the function:
	newPos : Position - return value which is a new position calculated.
	This function takes in otherPos and adds its x and y values with the current position's x and y values.
	It returns the new position.
	*/
	Position /*newPos*/ operator+(const Position &otherPos)
	{
		return Position(this->p_x + otherPos.p_x, this->p_y + otherPos.p_y);
	}

	/*
	Checks to see if the two positions are not the same.
	Parameters to the function:
	otherPos : const Position & - The otherPosition that gets checked against the 'this' position.
	Returns from the function:
	isNotSame : bool - return value which tells us if the two position's are not the same.
	This function takes in otherPos and checks its x and y values with the current position's x and y values.
	It returns true if both position's are not the same, else false.
	*/
	bool /*isNotSame*/ operator!=(const Position &otherPos)
	{
		return ((this->p_x != otherPos.p_x) || (this->p_y != otherPos.p_y));
	}
	
	/*
	Checks to see if the two positions are the same.
	Parameters to the function:
	otherPos : const Position & - The otherPosition that gets checked against the 'this' position.
	Returns from the function:
	isSame : bool - return value which tells us if the two position's are the same.
	This function takes in otherPos and checks its x and y values with the current position's x and y values.
	It returns true if both position's are the same, else false.
	*/
	bool /*isSame*/ operator==(const Position &otherPos)
	{
		return ((this->p_x == otherPos.p_x) && (this->p_y == otherPos.p_y));
	}
};

//SQUARE_NORTH position object - contains the value (-1, 0).
Position pos_SQUARENORTH(-1, 0);

//SQUARE_SOUTH position object - contains the value (1, 0).
Position pos_SQUARESOUTH(1, 0);

//SQUARE_EAST position object - contains the value (0, 1).
Position pos_SQUAREEAST(0, 1);

//SQUARE_WEST position object - contains the value (0, -1).
Position pos_SQUAREWEST(0, -1);

//SQUARE_NORTHEAST position object - contains the value (-1, 1).
Position pos_SQUARENORTHEAST(-1, 1);

//SQUARE_NORTHWEST position object - contains the value (-1, -1).
Position pos_SQUARENORTHWEST(-1, -1);

//SQUARE_SOUTHEAST position object - contains the value (1, 1).
Position pos_SQUARESOUTHEAST(1, 1);

//SQUARE_SOUTHWEST position object - contains the value (1, -1).
Position pos_SQUARESOUTHWEST(1, -1);

//HEX_NORTH position object - contains the value (-2, 0).
Position pos_HEXNORTH(-2, 0);

//HEX_SOUTH position object - contains the value (2, 0).
Position pos_HEXSOUTH(2, 0);

//HEX_ODDNORTHEAST position object - contains the value (-1, 0).
Position pos_HEXODDNORTHEAST(-1, 0);

//HEX_ODDNORTHWEST position object - contains the value (-1, -1).
Position pos_HEXODDNORTHWEST(-1, -1);

//HEX_ODDSOUTHEAST position object - contains the value (1, 0).
Position pos_HEXODDSOUTHEAST(1, 0);

//HEX_ODDSOUTHWEST position object - contains the value (1, -1).
Position pos_HEXODDSOUTHWEST(1, -1);

//HEX_EVENNORTHEAST position object - contains the value (-1, 1).
Position pos_HEXEVENNORTHEAST(-1, 1);

//HEX_EVENNORTHWEST position object - contains the value (-1, 0).
Position pos_HEXEVENNORTHWEST(-1, 0);

//HEX_EVENSOUTHEAST position object - contains the value (1, 1).
Position pos_HEXEVENSOUTHEAST(1, 1);

//HEX_EVENSOUTHWEST position object - contains the value (1, 0).
Position pos_HEXEVENSOUTHWEST(1, 0);

/*
GreaterThanByCost structure that keeps track if the lhs Position is greater than the rhs position (used specifically for priority queues!).
Functionalities:
operator()(const Position &lhs, const Position &rhs) - checks to see if the lhs' posCost is greater than the rhs' position cost.
*/
struct GreaterThanByCost
{
	//operator()(const Position &lhs, const Position &rhs) - checks to see if the lhs' posCost is greater than the rhs' position cost.
	/*
	Checks to see which of the two position's has a greater cost.
	Parameters to the function:
	lhs : const Position & - first position.
	rhs : const Position & - second position.
	Returns from the function:
	isGreater : bool - return value which tells us if lhs's cost is greater than rhs's.
	This function takes in lhs and rhs and checks if lhs has a greater cost than rhs.
	It returns true if lhs.cost > rhs.cost, else false.
	*/
	bool /*isGreater*/ operator()(const Position& lhs, const Position& rhs) const
	{
		return lhs.posCost > rhs.posCost;
	}
};
#endif