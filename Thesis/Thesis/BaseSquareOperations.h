///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: BaseSquareOperations.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "BaseDefines.h"
#include "BaseInitializers.h"
#include "BaseEnumerations.h"
#include "GenericOperations.h"

void InitializeFirstSquare(const char * strCostSpace)
{
  for (int i = 0; i <= SIZE + SQUARE_GRID; ++i)
  {
    for (int j = 0; j <= SIZE + SQUARE_GRID; ++j)
    {
      Initializer(i, j, EMPTY_SPACE, EMPTY_CAME_FROM_SPACE, EMPTY_CAME_FROM_SPACE, strCostSpace, EMPTY_COST_SPACE, strCostSpace, EMPTY_COST_SPACE, strCostSpace, EMPTY_COST_SPACE);
    }
  }
}

void GenerateSquare(Position nposStart, Position nposGoal)
{
  for (int i = 0; i <= SIZE + SQUARE_GRID; ++i)
  {
    for (int j = 0; j <= SIZE + SQUARE_GRID; ++j)
    {
      if (j == 0 || j == (SIZE + SQUARE_GRID))
      {
        Initializer(i, j, WALL, WALL_CAME_FROM, WALL_CAME_FROM, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST);
      }
      else if (i == 0 || i == (SIZE + SQUARE_GRID))
      {
        Initializer(i, j, WALL, WALL_CAME_FROM, WALL_CAME_FROM, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST);
      }
      else if (i == nposStart.p_x && j == nposStart.p_y)
      {
        Initializer(i, j, START, START_CAME_FROM, START_CAME_FROM, START_COST, START_COST, START_COST, START_COST, START_COST, START_COST);
      }
      else if (i == nposGoal.p_x && j == nposGoal.p_y)
      {
        Initializer(i, j, GOAL, GOAL_CAME_FROM, GOAL_CAME_FROM, GOAL_COST, NULL, GOAL_COST, NULL, GOAL_COST, NULL);
      }
      else if (((i / 2) % (5) == 0) && ((2 * j) % (3) == 0))
      {
        Initializer(i, j, WALL, WALL_CAME_FROM, WALL_CAME_FROM, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST);
      }
      else if ((i == 10) && (j > 10 && j < 20))
      {
        Initializer(i, j, WALL, WALL_CAME_FROM, WALL_CAME_FROM, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST);
      }
      else if ((j == 10) && (i > 10 && i < 18))
      {
        Initializer(i, j, WALL, WALL_CAME_FROM, WALL_CAME_FROM, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST);
      }
    }
  }
}

void PrintSquareMapGeneric(MapVisualType mvType)
{
  PrintHeader(mvType);
  for (int i = 0; i <= SIZE + SQUARE_GRID; ++i)
  {
    for (int j = 0; j <= SIZE + SQUARE_GRID; ++j)
    {
      switch (mvType)
      {
      case MapVisualType::MAP_VISITED:
        printf(mapVisited[i][j].c_str());
        printf(SQUARE_GRID_SPACE);
        break;
      case MapVisualType::MAP_CAMEFROM:
        printf(mapCameFrom[i][j].c_str());
        printf(SQUARE_GRID_CAME_FROM_SPACE);
        break;
      case MapVisualType::MAP_GOALPATH:
        printf(mapGoalPath[i][j].c_str());
        printf(SQUARE_GRID_CAME_FROM_SPACE);
        break;
      case MapVisualType::MAP_COST:
        printf(mapCost[i][j].c_str());
        printf(SQUARE_GRID_COST_SPACE);
        break;
      case MapVisualType::MAP_GOALCOST:
        printf(mapGoalCost[i][j].c_str());
        printf(SQUARE_GRID_COST_SPACE);
        break;
      case MapVisualType::MAP_HEUCOST:
        printf(mapHeuCost[i][j].c_str());
        printf(SQUARE_GRID_COST_SPACE);
        break;
      case MapVisualType::MAP_GOALHEUCOST:
        printf(mapGoalHeuCost[i][j].c_str());
        printf(SQUARE_GRID_COST_SPACE);
        break;
      case MapVisualType::MAP_TOTALCOST:
        printf(mapTotCost[i][j].c_str());
        printf(SQUARE_GRID_COST_SPACE);
        break;
      case MapVisualType::MAP_GOALTOTALCOST:
        printf(mapGoalTotCost[i][j].c_str());
        printf(SQUARE_GRID_COST_SPACE);
        break;
      }
    }
    printf("\n");
    printf("\n");
  }
}

bool SquareIsOutside(Position pvertex, Position topLeft, Position bottomRight)
{
  if ((pvertex.p_x < topLeft.p_x) || (pvertex.p_y < topLeft.p_y) || (pvertex.p_x > bottomRight.p_x) || (pvertex.p_y > bottomRight.p_y))
    return true;

  return false;
}

bool SquareIsBorder(Position pvertex, Position topLeft, Position bottomRight)
{
  if ((pvertex.p_x < topLeft.p_x) || (pvertex.p_y < topLeft.p_y) || (pvertex.p_x > bottomRight.p_x) || (pvertex.p_y > bottomRight.p_y))
    return false;

  if ((pvertex.p_x > topLeft.p_x) && (pvertex.p_y > topLeft.p_y) && (pvertex.p_x < bottomRight.p_x) && (pvertex.p_y < bottomRight.p_y))
    return false;

  return true;
}
