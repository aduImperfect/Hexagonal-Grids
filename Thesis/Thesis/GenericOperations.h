#pragma once
#include "BaseEnumerations.h"
#include "Position.h"
#include "BaseOperators.h"
#include "BaseCalculators.h"
#include "BaseInitializers.h"

void PrintHeader(MapVisualType mvType)
{
  switch (mvType)
  {
  case MapVisualType::MAP_VISITED:
    //Print Visited.
    printf("\nMap Visited:\n");
    break;
  case MapVisualType::MAP_CAMEFROM:
    //Print Came_From.
    printf("\nMap Came From:\n");
    break;
  case MapVisualType::MAP_GOALPATH:
    //Print Goal_Path.
    printf("\nMap Goal Path:\n");
    break;
  case MapVisualType::MAP_COST:
    //Print Cost.
    printf("\nMap Cost:\n");
    break;
  case MapVisualType::MAP_GOALCOST:
    //Print Goal Cost.
    printf("\nMap Goal Cost:\n");
    break;
  case MapVisualType::MAP_HEUCOST:
    //Print Heuristic Cost.
    printf("\nMap Heuristic Cost:\n");
    break;
  case MapVisualType::MAP_GOALHEUCOST:
    //Print Goal Heuristic Cost.
    printf("\nMap Goal Heuristic Cost:\n");
    break;
  case MapVisualType::MAP_TOTALCOST:
    //Print Total Cost.
    printf("\nMap Total Cost:\n");
    break;
  case MapVisualType::MAP_GOALTOTALCOST:
    //Print Goal Total Cost.
    printf("\nMap Goal Total Cost:\n");
    break;
  }
}

void NextChildAssignments(Position & current, Position & next, const char* dir, double nextCost, CostType cType, int hType, Position & goal, int gridType)
{
  visited[next.p_x][next.p_y] = true;
  came_from[next.p_x][next.p_y] = current;
  cost_so_far[next.p_x][next.p_y] = cost_so_far[current.p_x][current.p_y] + nextCost;
  switch (cType)
  {
  case COST_FROM_START_EXACT:
    next.posCost = cost_so_far[next.p_x][next.p_y];
    break;
  case COST_TO_GOAL_HEURISTIC:
    next.posCost = cost_heuristic[next.p_x][next.p_y] = Heuristic(hType, (gridType == HEX_GRID) ? abs((goal.p_x - next.p_x) / 2) : abs(goal.p_x - next.p_x), abs(goal.p_y - next.p_y));
    break;
  case COST_TOTAL_HEURISTIC:
    cost_heuristic[next.p_x][next.p_y] = Heuristic(hType, (gridType == HEX_GRID) ? abs((goal.p_x - next.p_x) / 2) : abs(goal.p_x - next.p_x), abs(goal.p_y - next.p_y));
    next.posCost = cost_total[next.p_x][next.p_y] = cost_so_far[next.p_x][next.p_y] + cost_heuristic[next.p_x][next.p_y];
    break;
  }
  std::string costInString = to_string_with_precision(cost_so_far[next.p_x][next.p_y], 2);
  std::string costHeuInString = to_string_with_precision(cost_heuristic[next.p_x][next.p_y], 2);
  std::string costTotInString = to_string_with_precision(cost_total[next.p_x][next.p_y], 2);
  Initializer(next.p_x, next.p_y, NEXT, dir, NULL, const_cast<char*>(costInString.c_str()), NULL, const_cast<char*>(costHeuInString.c_str()), NULL, const_cast<char*>(costTotInString.c_str()), NULL);
}
