#pragma once
#include "BaseDefines.h"
#include "BaseInitializers.h"
#include "BaseEnumerations.h"
#include "GenericOperations.h"

void InitializeFirstHex(const char * strCostSpace)
{
  for (int i = 0; i <= SIZE + HEX_GRID + 1; ++i)
  {
    for (int j = 0; j <= SIZE + HEX_GRID + 1; ++j)
    {
      Initializer(i, j, EMPTY_SPACE, EMPTY_CAME_FROM_SPACE, EMPTY_CAME_FROM_SPACE, strCostSpace, EMPTY_COST_SPACE, strCostSpace, EMPTY_COST_SPACE, strCostSpace, EMPTY_COST_SPACE);
    }
  }
}

void GenerateHex(Position nposStart, Position nposGoal)
{
  for (int i = 0; i <= SIZE + HEX_GRID + 1; ++i)
  {
    for (int j = 0; j <= SIZE + HEX_GRID + 1; ++j)
    {
      if (j == 0 || j == (SIZE + HEX_GRID + 1))
      {
        Initializer(i, j, WALL, WALL_CAME_FROM, WALL_CAME_FROM, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST);
      }
      else if (i == 0 || i == 1 || i == (SIZE + SQUARE_GRID + 1) || i == (SIZE + HEX_GRID + 1))
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
      else if ((i == 10 || i == 11) && (j > 9 && j < 20))
      {
        Initializer(i, j, WALL, WALL_CAME_FROM, WALL_CAME_FROM, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST);
      }
      else if ((j == 10 || j == 11) && (i > 10 && i < 18))
      {
        Initializer(i, j, WALL, WALL_CAME_FROM, WALL_CAME_FROM, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST, WALL_COST);
      }
    }
  }
}

void PrintHexMapGeneric(MapVisualType mvType)
{
  PrintHeader(mvType);
  for (int i = 0; i <= SIZE + HEX_GRID + 1; ++i)
  {
    if (i % 2 == 0)
    {
      printf(HEX_GRID_OFFSET);
    }
    for (int j = 0; j <= SIZE + HEX_GRID + 1; ++j)
    {
      switch (mvType)
      {
      case MapVisualType::MAP_VISITED:
        printf(mapVisited[i][j].c_str());
        printf(HEX_GRID_SPACE);
        break;
      case MapVisualType::MAP_CAMEFROM:
        printf(mapCameFrom[i][j].c_str());
        printf(HEX_GRID_CAME_FROM_SPACE);
        break;
      case MapVisualType::MAP_GOALPATH:
        printf(mapGoalPath[i][j].c_str());
        printf(HEX_GRID_CAME_FROM_SPACE);
        break;
      case MapVisualType::MAP_COST:
        printf(mapCost[i][j].c_str());
        printf(HEX_GRID_COST_SPACE);
        break;
      case MapVisualType::MAP_GOALCOST:
        printf(mapGoalCost[i][j].c_str());
        printf(HEX_GRID_COST_SPACE);
        break;
      case MapVisualType::MAP_HEUCOST:
        printf(mapHeuCost[i][j].c_str());
        printf(HEX_GRID_COST_SPACE);
        break;
      case MapVisualType::MAP_GOALHEUCOST:
        printf(mapGoalHeuCost[i][j].c_str());
        printf(HEX_GRID_COST_SPACE);
        break;
      case MapVisualType::MAP_TOTALCOST:
        printf(mapTotCost[i][j].c_str());
        printf(HEX_GRID_COST_SPACE);
        break;
      case MapVisualType::MAP_GOALTOTALCOST:
        printf(mapGoalTotCost[i][j].c_str());
        printf(HEX_GRID_COST_SPACE);
        break;
      }
    }
    printf("\n");
  }
}

bool HexIsOutside(Position pvertex, Position center, int perimeter)
{
  int phalf = static_cast<int>(floor(perimeter / 2));
  int pdouble = 2 * perimeter;

  if (pvertex.p_y == center.p_y)
  {
    if (pvertex.p_x < (center.p_x - pdouble) || pvertex.p_x > (center.p_x + pdouble))
    {
      return true;
    }
  }

  if ((center.p_y % 2) != 0)
  {
    if (pvertex.p_y < (center.p_y - phalf))
      return true;

    if ((perimeter % 2 != 0) && (pvertex.p_y == (center.p_y + phalf)))
      return true;

    if ((perimeter % 2 == 0) && (pvertex.p_y > (center.p_y + phalf)))
      return true;
  }
  else
  {
    if (pvertex.p_y > (center.p_y + phalf))
      return true;

    if ((perimeter % 2 != 0) && (pvertex.p_y == (center.p_y - phalf)))
      return true;

    if ((perimeter % 2 == 0) && (pvertex.p_y < (center.p_y - phalf)))
      return true;
  }

  return false;
}
