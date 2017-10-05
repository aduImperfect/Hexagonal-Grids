#pragma once
#include "Position.h"

#define MAX_RELATIONS 5
#define MAX_BLOCK_CORNERS 12

struct BlockPosition
{
public:
  Position pos_BlockNo;
  Position pos_RelPos;

  BlockPosition()
  {
    pos_BlockNo = Position(-1, -1);
    pos_RelPos = Position(-1, -1);
  }

  BlockPosition(Position pos_BNo, Position pos_RPos)
  {
    pos_BlockNo = pos_BNo;
    pos_RelPos = pos_RPos;
  }

  bool operator==(BlockPosition &rhs)
  {
    if (rhs.pos_BlockNo != this->pos_BlockNo)
      return false;

    if (rhs.pos_RelPos != this->pos_RelPos)
      return false;

    return true;
  }
};

BlockPosition Block_Invalid(Position(-1, -1), Position(-1, -1));

class PositionRelations
{
public:
  BlockPosition pos_From;
  BlockPosition pos_To[MAX_RELATIONS];
  bool bValidRelation[MAX_RELATIONS];
  
  PositionRelations(BlockPosition pos_F = Block_Invalid)
  {
    pos_From = pos_F;
    for (unsigned int i = 0; i < MAX_RELATIONS; ++i)
    {
      pos_To[i] = Block_Invalid;
      bValidRelation[i] = false;
    }
  }

  bool Set(BlockPosition pos_F, BlockPosition pos_T, int nRelNo)
  {
    pos_From = pos_F;
    if (nRelNo >= MAX_RELATIONS)
      return false;

    bValidRelation[nRelNo] = false;
    pos_To[nRelNo] = pos_T;
    return true;
  }
};
