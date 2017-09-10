#pragma once
#include "BaseHexOperations.h"

double HexDijkstra(Position npStart, Position npGoal, bool autoCompute, Position center, int perimeter)
{
  if (HexIsOutside(npStart, center, perimeter))
    return -1;

  if (HexIsOutside(npGoal, center, perimeter))
    return -1;

  /*priorityFrontier = Queue()
  frontier.put(start)
  visited = {}
  visited[start] = True

  while not frontier.empty() :
  current = frontier.get()
  for next in graph.neighbors(current) :
  if next not in visited :
  frontier.put(next)
  visited[next] = True
  */
  while (!priorityFrontier.empty())
  {
    priorityFrontier.pop();
  }

  InitializeVCC(HEX_GRID + 1, COST_MAX);
  npStart.posCost = cost_so_far[npStart.p_x][npStart.p_y] = 0.00f;

  //priorityFrontier.put(start).
  priorityFrontier.push(npStart);

  //visited[start] = true.
  visited[npStart.p_x][npStart.p_y] = true;

  //came_from[start] = start.
  came_from[npStart.p_x][npStart.p_y] = npStart;

  //start is a wall.
  if (mapVisited[npStart.p_x][npStart.p_y] == WALL)
    return -1;

  //goal is a wall.
  if (mapVisited[npGoal.p_x][npGoal.p_y] == WALL)
    return -1;

  bool generateInstantaneous = false;
  if (!autoCompute)
  {
    printf("\nCompute Dijkstra Immediate!? (0 - no/1 - yes):\n");
    std::cin >> generateInstantaneous;
  }

  bool nextStep = false;

  //while not priorityFrontier.empty().Give next steps button
  while (!priorityFrontier.empty())
  {
    //current = priorityFrontier.get().
    Position current = priorityFrontier.top();

    //oldest element removed which is the priorityFrontier.front().
    priorityFrontier.pop();

    if (current == npGoal)
      break;

    if (current != npStart)
    {
      mapVisited[current.p_x][current.p_y] = CURRENT;
    }

    //for next in graph.neighbors(current).
    Position currentNorth = current + pos_HEXNORTH;
    Position currentNorthEast = current + ((current.p_x % 2 != 0) ? pos_HEXODDNORTHEAST : pos_HEXEVENNORTHEAST);
    Position currentSouthEast = current + ((current.p_x % 2 != 0) ? pos_HEXODDSOUTHEAST : pos_HEXEVENSOUTHEAST);
    Position currentSouth = current + pos_HEXSOUTH;
    Position currentSouthWest = current + ((current.p_x % 2 != 0) ? pos_HEXODDSOUTHWEST : pos_HEXEVENSOUTHWEST);
    Position currentNorthWest = current + ((current.p_x % 2 != 0) ? pos_HEXODDNORTHWEST : pos_HEXEVENNORTHWEST);

    double newCostAxis = cost_so_far[current.p_x][current.p_y] + COST_AXIS;

    /*
    if next not in visited :
    frontier.put(next)
    visited[next] = True
    came_from[next] = current
    */
    if ((mapVisited[currentNorth.p_x][currentNorth.p_y] != WALL) && !HexIsOutside(currentNorth, center, perimeter))
    {
      if ((!visited[currentNorth.p_x][currentNorth.p_y]) || (newCostAxis < cost_so_far[currentNorth.p_x][currentNorth.p_y]))
      {
        NextChildAssignments(current, currentNorth, SOUTH_DIR, COST_AXIS, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, HEX_GRID);
        priorityFrontier.push(currentNorth);
      }
    }
    if ((mapVisited[currentNorthEast.p_x][currentNorthEast.p_y] != WALL) && !HexIsOutside(currentNorthEast, center, perimeter))
    {
      if ((!visited[currentNorthEast.p_x][currentNorthEast.p_y]) || (newCostAxis < cost_so_far[currentNorthEast.p_x][currentNorthEast.p_y]))
      {
        NextChildAssignments(current, currentNorthEast, SOUTHWEST_DIR, COST_AXIS, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, HEX_GRID);
        priorityFrontier.push(currentNorthEast);
      }
    }
    if ((mapVisited[currentSouthEast.p_x][currentSouthEast.p_y] != WALL) && !HexIsOutside(currentSouthEast, center, perimeter))
    {
      if ((!visited[currentSouthEast.p_x][currentSouthEast.p_y]) || (newCostAxis < cost_so_far[currentSouthEast.p_x][currentSouthEast.p_y]))
      {
        NextChildAssignments(current, currentSouthEast, NORTHWEST_DIR, COST_AXIS, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, HEX_GRID);
        priorityFrontier.push(currentSouthEast);
      }
    }
    if ((mapVisited[currentSouth.p_x][currentSouth.p_y] != WALL) && !HexIsOutside(currentSouth, center, perimeter))
    {
      if ((!visited[currentSouth.p_x][currentSouth.p_y]) || (newCostAxis < cost_so_far[currentSouth.p_x][currentSouth.p_y]))
      {
        NextChildAssignments(current, currentSouth, NORTH_DIR, COST_AXIS, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, HEX_GRID);
        priorityFrontier.push(currentSouth);
      }
    }
    if ((mapVisited[currentSouthWest.p_x][currentSouthWest.p_y] != WALL) && !HexIsOutside(currentSouthWest, center, perimeter))
    {
      if ((!visited[currentSouthWest.p_x][currentSouthWest.p_y]) || (newCostAxis < cost_so_far[currentSouthWest.p_x][currentSouthWest.p_y]))
      {
        NextChildAssignments(current, currentSouthWest, NORTHEAST_DIR, COST_AXIS, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, HEX_GRID);
        priorityFrontier.push(currentSouthWest);
      }
    }
    if ((mapVisited[currentNorthWest.p_x][currentNorthWest.p_y] != WALL) && !HexIsOutside(currentNorthWest, center, perimeter))
    {
      if ((!visited[currentNorthWest.p_x][currentNorthWest.p_y]) || (newCostAxis < cost_so_far[currentNorthWest.p_x][currentNorthWest.p_y]))
      {
        NextChildAssignments(current, currentNorthWest, SOUTHEAST_DIR, COST_AXIS, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, HEX_GRID);
        priorityFrontier.push(currentNorthWest);
      }
    }

    if (current != npStart)
    {
      mapVisited[current.p_x][current.p_y] = VISITED;
    }

    if (generateInstantaneous || autoCompute)
      continue;

    //Re-print hex grid.
    GenerateHex(npStart, npGoal);
    PrintHexMapGeneric(MapVisualType::MAP_VISITED);
    PrintHexMapGeneric(MapVisualType::MAP_CAMEFROM);
    PrintHexMapGeneric(MapVisualType::MAP_COST);

    nextStep = false;
    printf("\nGet next step? (0 - no/1 - yes):\n");
    std::cin >> nextStep;

    if (!nextStep)
    {
      generateInstantaneous = true;
    }
  }

  //if goal not found.
  if ((mapCost[npGoal.p_x][npGoal.p_y] == COST_MAX_TERM) || (mapVisited[npGoal.p_x][npGoal.p_y] == WALL))
  {
    return -1.0f;
  }

  /*
  current = goal
  path = [current]
  while current != start:
  current = came_from[current]
  path.append(current)
  path.append(start) # optional
  path.reverse() # optional
  */
  Position currentTraverse = npGoal;
  std::vector<Position> goalPath;

  mapGoalCost[npGoal.p_x][npGoal.p_y] = mapCost[npGoal.p_x][npGoal.p_y];
  goalPath.push_back(currentTraverse);
  while (currentTraverse != npStart)
  {
    mapGoalPath[currentTraverse.p_x][currentTraverse.p_y] = mapCameFrom[currentTraverse.p_x][currentTraverse.p_y];
    mapGoalCost[currentTraverse.p_x][currentTraverse.p_y] = mapCost[currentTraverse.p_x][currentTraverse.p_y];
    currentTraverse = came_from[currentTraverse.p_x][currentTraverse.p_y];
    goalPath.push_back(currentTraverse);
  }

  goalPath.push_back(npStart);
  std::reverse(goalPath.begin(), goalPath.end());

  //Print all types of grid maps for hex grids.
  if (generateInstantaneous || !autoCompute)
  {
    //Re-print hex grid.
    GenerateHex(npStart, npGoal);
    PrintHexMapGeneric(MapVisualType::MAP_VISITED);
    PrintHexMapGeneric(MapVisualType::MAP_CAMEFROM);
    PrintHexMapGeneric(MapVisualType::MAP_GOALPATH);
    PrintHexMapGeneric(MapVisualType::MAP_COST);
    PrintHexMapGeneric(MapVisualType::MAP_GOALCOST);
  }

  return cost_so_far[npGoal.p_x][npGoal.p_y];
}
