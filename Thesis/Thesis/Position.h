///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: Position.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#pragma once

struct Position
{
  int p_x;
  int p_y;
  double posCost;

  Position(int _x = 0, int _y = 0)
  {
    p_x = _x;
    p_y = _y;
    posCost = 0.00f;
  }

  Position operator+(Position &otherPos)
  {
    return Position(this->p_x + otherPos.p_x, this->p_y + otherPos.p_y);
  }
  bool operator!=(Position &otherPos)
  {
    return ((this->p_x != otherPos.p_x) || (this->p_y != otherPos.p_y));
  }
  bool operator==(Position &otherPos)
  {
    return ((this->p_x == otherPos.p_x) && (this->p_y == otherPos.p_y));
  }
};

Position pos_SQUARENORTH(-1, 0);
Position pos_SQUARESOUTH(1, 0);
Position pos_SQUAREEAST(0, 1);
Position pos_SQUAREWEST(0, -1);
Position pos_SQUARENORTHEAST(-1, 1);
Position pos_SQUARENORTHWEST(-1, -1);
Position pos_SQUARESOUTHEAST(1, 1);
Position pos_SQUARESOUTHWEST(1, -1);

Position pos_HEXNORTH(-2, 0);
Position pos_HEXSOUTH(2, 0);
Position pos_HEXODDNORTHEAST(-1, 0);
Position pos_HEXODDNORTHWEST(-1, -1);
Position pos_HEXODDSOUTHEAST(1, 0);
Position pos_HEXODDSOUTHWEST(1, -1);
Position pos_HEXEVENNORTHEAST(-1, 1);
Position pos_HEXEVENNORTHWEST(-1, 0);
Position pos_HEXEVENSOUTHEAST(1, 1);
Position pos_HEXEVENSOUTHWEST(1, 0);

struct GreaterThanByCost
{
  bool operator()(const Position& lhs, const Position& rhs) const
  {
    return lhs.posCost > rhs.posCost;
  }
};
