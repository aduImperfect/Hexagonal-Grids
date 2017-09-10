#pragma once
#include <iostream>
#include <fstream>

#include "BaseDefines.h"
#include "Position.h"
#include "SquareDijkstra.h"

#define SQUARE_LDDB_BLOCK_SPLIT_SIZE_X 4
#define SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y 4

#define SQUARE_LDDB_BLOCK_SIZE_I (SIZE - 1)/SQUARE_LDDB_BLOCK_SPLIT_SIZE_X
#define SQUARE_LDDB_BLOCK_SIZE_J (SIZE - 1)/SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y

//LDDB = {}.
double SquareLDDB[SQUARE_LDDB_BLOCK_SIZE_I][SQUARE_LDDB_BLOCK_SIZE_J][SQUARE_LDDB_BLOCK_SPLIT_SIZE_X][SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y][SQUARE_LDDB_BLOCK_SPLIT_SIZE_X][SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y];

void WriteSquareLDDBToFile();
void WriteSquareLDDBToFileAlternate();

void SquareLDDBInitializer()
{
  for (int blockI = 0; blockI < SQUARE_LDDB_BLOCK_SIZE_I; ++blockI)
  {
    for (int blockJ = 0; blockJ < SQUARE_LDDB_BLOCK_SIZE_J; ++blockJ)
    {
      for (int fromK = 0; fromK < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++fromK)
      {
        for (int fromL = 0; fromL < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++fromL)
        {
          for (int toM = 0; toM < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++toM)
          {
            for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
            {
              SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] = COST_MAX;
            }
          }
        }
      }
    }
  }
}

void SquareLDDBCalc(Position npStart, Position npGoal)
{
  for (int blockI = 0; blockI < SQUARE_LDDB_BLOCK_SIZE_I; ++blockI)
  {
    for (int blockJ = 0; blockJ < SQUARE_LDDB_BLOCK_SIZE_J; ++blockJ)
    {
      for (int fromK = 0; fromK < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++fromK)
      {
        for (int fromL = 0; fromL < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++fromL)
        {
          for (int toM = 0; toM < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++toM)
          {
            for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
            {
              /*
              If the cost in block[i][j]: from[K][L] - to[M][N] is already assigned then skip that distance.
              */
              if (SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] < COST_MAX)
                continue;
              //Position absolute_from = (K + I * (TOT_X) + 1, L + J * (TOT_Y) + 1). 
              Position pFrom = Position(fromK + blockI * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + 1, fromL + blockJ * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + 1);
              //Position absolute_to = (M + I*(TOT_X) + 1, N + J * (TOT_Y) + 1). 
              Position pTo = Position(toM + blockI * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + 1, toN + blockJ * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + 1);
              //Position absolute_top_left = (I * (TOT_X) + 1, J * (TOT_Y) + 1). 
              Position pTopLeft = Position(blockI * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + 1, blockJ * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + 1);
              //Position absolute_bottom_right = (I * (TOT_X) + TOT_X, J * (TOT_Y) + TOT_Y). 
              Position pBottomRight = Position(blockI * SQUARE_LDDB_BLOCK_SPLIT_SIZE_X + SQUARE_LDDB_BLOCK_SPLIT_SIZE_X, blockJ * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y + SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y);
              /*
              If (absolute_from is not absolute_to) and (start is absolute_from) and (absolute_to is a border inside absolute_top_left and absolute_bottom_right).
              */
              if ((pFrom != pTo) && (((npStart == pFrom) && SquareIsBorder(pTo, pTopLeft, pBottomRight)) || ((npStart == pTo) && SquareIsBorder(pFrom, pTopLeft, pBottomRight))))
              {
                SquareLDDB[blockI][blockJ][toM][toN][fromK][fromL] = SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] = SquareDijkstra(pFrom, pTo, true, pTopLeft, pBottomRight);
              }
              /*
              Else If (absolute_from is not absolute_to) and (goal is absolute_from) and (absolute_to is a border inside absolute_top_left and absolute_bottom_right).
              */
              else if ((pFrom != pTo) && (((npGoal == pFrom) && SquareIsBorder(pTo, pTopLeft, pBottomRight)) || ((npGoal == pTo) && SquareIsBorder(pFrom, pTopLeft, pBottomRight))))
              {
                SquareLDDB[blockI][blockJ][toM][toN][fromK][fromL] = SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] = SquareDijkstra(pFrom, pTo, true, pTopLeft, pBottomRight);
              }
              /*
              Else
              If (absolute_from is not a border inside absolute_top_left and absolute_bottom_right). or
              If (absolute_to is not a border inside absolute_top_left and absolute_bottom_right).
              */
              else if (!SquareIsBorder(pFrom, pTopLeft, pBottomRight) || !SquareIsBorder(pTo, pTopLeft, pBottomRight))
              {
                SquareLDDB[blockI][blockJ][toM][toN][fromK][fromL] = SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] = -1;
              }
              /*
              Else If (absolute_from is absolute_to).
              */
              else if (pFrom == pTo)
              { 
                SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] = 0;
              }
              else
              {
                //Otherwise, for any other case.
                SquareLDDB[blockI][blockJ][toM][toN][fromK][fromL] = SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] = SquareDijkstra(pFrom, pTo, true, pTopLeft, pBottomRight);
              }
            }
          }
        }
      }
    }
  }

  printf("\nSquare LDDB Calculated!!\n");

  WriteSquareLDDBToFile();
  WriteSquareLDDBToFileAlternate();

  printf("\nSquare LDDB written to file!!\n");
}

void WriteSquareLDDBToFile()
{
  std::ofstream squareLDDB;
  squareLDDB.open("squareLDDB.txt");

  for (int blockI = 0; blockI < SQUARE_LDDB_BLOCK_SIZE_I; ++blockI)
  {
    for (int blockJ = 0; blockJ < SQUARE_LDDB_BLOCK_SIZE_J; ++blockJ)
    {
      squareLDDB << "\nBlock[" << blockI << "][" << blockJ << "]:\n";
      squareLDDB << "\t\t\t";
      for (int toM = 0; toM < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++toM)
      {
        for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
        {
          squareLDDB << "[" << toM << "][" << toN << "]\t\t";
        }
      }
      squareLDDB << "\n";

      for (int fromK = 0; fromK < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++fromK)
      {
        for (int fromL = 0; fromL < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++fromL)
        {
          squareLDDB << "[" << fromK << "][" << fromL << "]:\t\t";
          for (int toM = 0; toM < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++toM)
          {
            for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
            {
              squareLDDB << SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN];
              int tempVal = static_cast<int>(SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] * 100);
              if ((tempVal % 100) != 0)
              {
                squareLDDB << "\t\t";
              }
              else
              {
                squareLDDB << "\t\t\t";
              }
            }
          }
          squareLDDB << "\n";
        }
      }
    }
  }

  squareLDDB.close();
}

void WriteSquareLDDBToFileAlternate()
{
  std::ofstream squareLDDB;
  squareLDDB.open("squareLDDBAlternate.txt");

  for (int blockI = 0; blockI < SQUARE_LDDB_BLOCK_SIZE_I; ++blockI)
  {
    for (int blockJ = 0; blockJ < SQUARE_LDDB_BLOCK_SIZE_J; ++blockJ)
    {
      squareLDDB << "\nBlock[" << blockI << "][" << blockJ << "]:\n";
/*
      squareLDDB << "\t\t\t";
      for (int toM = 0; toM < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++toM)
      {
        for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
        {
          squareLDDB << "[" << toM << "][" << toN << "]\t\t";
        }
      }
      squareLDDB << "\n";
*/
      for (int fromK = 0; fromK < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++fromK)
      {
        for (int fromL = 0; fromL < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++fromL)
        {
          squareLDDB << "FROM[" << fromK << "][" << fromL << "]:\n";
          squareLDDB << "TO:\t\t\t";
          for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
          {
            squareLDDB << "[" << toN << "]\t\t\t";
          }
          squareLDDB << "\n";

          for (int toM = 0; toM < SQUARE_LDDB_BLOCK_SPLIT_SIZE_X; ++toM)
          {
            squareLDDB << "[" << toM << "]:\t\t";
            for (int toN = 0; toN < SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y; ++toN)
            {
              squareLDDB << SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN];
              int tempVal = static_cast<int>(SquareLDDB[blockI][blockJ][fromK][fromL][toM][toN] * 100);
              if ((tempVal % 100) != 0)
              {
                squareLDDB << "\t\t";
              }
              else
              {
                squareLDDB << "\t\t\t";
              }
            }
            squareLDDB << "\n";
          }
          squareLDDB << "\n";
        }
      }
    }
  }

  squareLDDB.close();
}

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
  for (int i = -1; i < 2; ++i)
  {
    for (int j = -1; j < 2; ++j)
    {
      if (i == 0 && j == 0)
        continue;

      Position NextBlock(curBlock.p_x + i, curBlock.p_y + j);
      
      if ((NextBlock.p_x < 0) || (NextBlock.p_y < 0) || (NextBlock.p_x >= SIZE) || (NextBlock.p_y >= SIZE))
        continue;

      std::vector<Position> sideCurBlock;
      //(Side of curblock) : [Neighborblk, side of neighbor blk].
      std::vector<std::pair<Position, std::pair<Position, Position> > > neigborsideNextBlock;

      //Neighbor: [-1, -1]
      if (i == -1 && j == -1)
      {
        //Side of CurBlock: [1, 1].
        sideCurBlock.push_back(Position(1, 1));
        //Side of NeighborBlock: NBlk[-1, -1]: [4, 4].
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(1, 1), std::make_pair<Position, Position>(Position(-1, -1), Position(4, 4))));
      }
      //Neighbor: [-1, 0]
      else if (i == -1 && j == 0)
      {
        //Side of CurBlock: [1, 1], [1, 2], [1, 3], [1, 4].
        sideCurBlock.push_back(Position(1, 1));
        sideCurBlock.push_back(Position(1, 2));
        sideCurBlock.push_back(Position(1, 3));
        sideCurBlock.push_back(Position(1, 4));
        //Side of NeighborBlock: NBlk[-1, 0]: [4, 1], NBlk[-1, 0]: [4, 2], NBlk[-1, 0]: [4, 3], NBlk[-1, 0]: [4, 4].
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(1, 1), std::make_pair<Position, Position>(Position(-1, 0), Position(4, 1))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(1, 1), std::make_pair<Position, Position>(Position(-1, 0), Position(4, 2))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(1, 2), std::make_pair<Position, Position>(Position(-1, 0), Position(4, 1))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(1, 2), std::make_pair<Position, Position>(Position(-1, 0), Position(4, 2))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(1, 2), std::make_pair<Position, Position>(Position(-1, 0), Position(4, 3))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(1, 3), std::make_pair<Position, Position>(Position(-1, 0), Position(4, 2))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(1, 3), std::make_pair<Position, Position>(Position(-1, 0), Position(4, 3))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(1, 3), std::make_pair<Position, Position>(Position(-1, 0), Position(4, 4))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(1, 4), std::make_pair<Position, Position>(Position(-1, 0), Position(4, 3))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(1, 4), std::make_pair<Position, Position>(Position(-1, 0), Position(4, 4))));
      }
      //Neighbor: [-1, 1]
      else if (i == -1 && j == 1)
      {
        //Side of CurBlock: [1, 4].
        sideCurBlock.push_back(Position(1, 4));
        //Side of NeighborBlock: NBlk[-1, 1]: [4, 1].
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(1, 4), std::make_pair<Position, Position>(Position(-1, 1), Position(4, 1))));
      }
      //Neighbor: [0, 1]
      else if (i == 0 && j == 1)
      {
        //Side of CurBlock: [1, 4], [2, 4], [3, 4], [4, 4].
        sideCurBlock.push_back(Position(1, 4));
        sideCurBlock.push_back(Position(2, 4));
        sideCurBlock.push_back(Position(3, 4));
        sideCurBlock.push_back(Position(4, 4));
        //Side of NeighborBlock: NBlk[0, 1]: [1, 1], NBlk[0, 1]: [2, 1], NBlk[0, 1]: [3, 1], NBlk[0, 1]: [4, 1].
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(1, 4), std::make_pair<Position, Position>(Position(0, 1), Position(1, 1))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(1, 4), std::make_pair<Position, Position>(Position(0, 1), Position(2, 1))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(2, 4), std::make_pair<Position, Position>(Position(0, 1), Position(1, 1))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(2, 4), std::make_pair<Position, Position>(Position(0, 1), Position(2, 1))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(2, 4), std::make_pair<Position, Position>(Position(0, 1), Position(3, 1))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(3, 4), std::make_pair<Position, Position>(Position(0, 1), Position(2, 1))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(3, 4), std::make_pair<Position, Position>(Position(0, 1), Position(3, 1))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(3, 4), std::make_pair<Position, Position>(Position(0, 1), Position(4, 1))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(4, 4), std::make_pair<Position, Position>(Position(0, 1), Position(3, 1))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(4, 4), std::make_pair<Position, Position>(Position(0, 1), Position(4, 1))));
      }
      //Neighbor: [1, 1]
      else if (i == 1 && j == 1)
      {
        //Side of CurBlock: [4, 4].
        sideCurBlock.push_back(Position(4, 4));
        //Side of NeighborBlock: NBlk[1, 1]: [1, 1].
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(4, 4), std::make_pair<Position, Position>(Position(1, 1), Position(1, 1))));
      }
      //Neighbor: [1, 0]
      else if (i == 1 && j == 0)
      {
        //Side of CurBlock: [4, 1], [4, 2], [4, 3], [4, 4].
        sideCurBlock.push_back(Position(4, 1));
        sideCurBlock.push_back(Position(4, 2));
        sideCurBlock.push_back(Position(4, 3));
        sideCurBlock.push_back(Position(4, 4));
        //Side of NeighborBlock: NBlk[1, 0]: [1, 1], NBlk[1, 0]: [1, 2], NBlk[1, 0]: [1, 3], NBlk[1, 0]: [1, 4].
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(4, 1), std::make_pair<Position, Position>(Position(1, 0), Position(1, 1))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(4, 1), std::make_pair<Position, Position>(Position(1, 0), Position(1, 2))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(4, 2), std::make_pair<Position, Position>(Position(1, 0), Position(1, 1))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(4, 2), std::make_pair<Position, Position>(Position(1, 0), Position(1, 2))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(4, 2), std::make_pair<Position, Position>(Position(1, 0), Position(1, 3))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(4, 3), std::make_pair<Position, Position>(Position(1, 0), Position(1, 2))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(4, 3), std::make_pair<Position, Position>(Position(1, 0), Position(1, 3))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(4, 3), std::make_pair<Position, Position>(Position(1, 0), Position(1, 4))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(4, 4), std::make_pair<Position, Position>(Position(1, 0), Position(1, 3))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(4, 4), std::make_pair<Position, Position>(Position(1, 0), Position(1, 4))));
      }
      //Neighbor: [1, -1]
      else if (i == 1 && j == -1)
      {
        //Side of CurBlock: [4, 1].
        sideCurBlock.push_back(Position(4, 1));
        //Side of NeighborBlock: NBlk[1, -1]: [1, -1].
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(4, 1), std::make_pair<Position, Position>(Position(1, -1), Position(1, -1))));
      }
      //Neighbor: [0, -1]
      else if (i == 0 && j == -1)
      {
        //Side of CurBlock: [1, 1], [2, 1], [3, 1], [4, 1].
        sideCurBlock.push_back(Position(1, 1));
        sideCurBlock.push_back(Position(2, 1));
        sideCurBlock.push_back(Position(3, 1));
        sideCurBlock.push_back(Position(4, 1));
        //Side of NeighborBlock: NBlk[0, -1]: [1, 4], NBlk[0, -1]: [2, 4], NBlk[0, -1]: [3, 4], NBlk[0, -1]: [4, 4].
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(1, 1), std::make_pair<Position, Position>(Position(0, -1), Position(1, 4))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(1, 1), std::make_pair<Position, Position>(Position(0, -1), Position(2, 4))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(2, 1), std::make_pair<Position, Position>(Position(0, -1), Position(1, 4))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(2, 1), std::make_pair<Position, Position>(Position(0, -1), Position(2, 4))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(2, 1), std::make_pair<Position, Position>(Position(0, -1), Position(3, 4))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(3, 1), std::make_pair<Position, Position>(Position(0, -1), Position(2, 4))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(3, 1), std::make_pair<Position, Position>(Position(0, -1), Position(3, 4))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(3, 1), std::make_pair<Position, Position>(Position(0, -1), Position(4, 4))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(4, 1), std::make_pair<Position, Position>(Position(0, -1), Position(3, 4))));
        neigborsideNextBlock.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(4, 1), std::make_pair<Position, Position>(Position(0, -1), Position(4, 4))));
      }

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
      std::vector<std::pair<Position, std::pair<Position, Position> > > validEgressCells;

      //Neighbor: [-1, -1]
      if (i == -1 && j == -1)
      {
        //If CurBlock[0, 0] : [1, 1], and NBlk[-1, -1] : [4, 4] are not WALLS! check.
        //If NBlk[0, -1] : [1, 4], and NBlk[-1, 0] : [4, 1] are not WALLS! check.
        if ((mapVisited[SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * curBlock.p_x + 1][SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * curBlock.p_y + 1] != WALL) && (mapVisited[SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * curBlock.p_x][SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * curBlock.p_y] != WALL))
        {
          if ((mapVisited[SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * curBlock.p_x + 1][SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * curBlock.p_y] != WALL) && (mapVisited[SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * curBlock.p_x][SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * curBlock.p_y + 1] != WALL))
          {
            validEgressCells.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(1, 1), std::make_pair<Position, Position>(Position(-1, -1), Position(4, 4))));
          }
        }
      }

      //Neighbor: [-1, 0]
      else if (i == -1 && j == 0)
      {
        //If CurBlock[0, 0] : [1, 1], and NBlk[-1, 0]: [4, 1] are not WALLS! check.
        if ((mapVisited[SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * curBlock.p_x + 1][SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * curBlock.p_y + 1] != WALL) && (mapVisited[SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * curBlock.p_x][SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y * curBlock.p_y + 1] != WALL))
        {
          validEgressCells.push_back(std::make_pair<Position, std::pair<Position, Position> >(Position(1, 1), std::make_pair<Position, Position>(Position(-1, 0), Position(4, 1))));
        }
        
      }

      //for valid egress node x on current side

      {
      }

    }
  }
}