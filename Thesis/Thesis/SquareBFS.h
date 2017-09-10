#pragma once
#include "BaseSquareOperations.h"

double SquareBFS(Position npStart, Position npGoal, bool autoCompute, Position topLeft, Position bottomRight)
{
  if (SquareIsOutside(npStart, topLeft, bottomRight))
    return -1;

  if (SquareIsOutside(npGoal, topLeft, bottomRight))
    return -1;

  /*frontier = Queue()
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

  /*
  frontier = Queue()
  frontier.put(start )
  came_from = {}
  came_from[start] = None

  while not frontier.empty():
  current = frontier.get()
  for next in graph.neighbors(current):
  if next not in came_from:
  frontier.put(next)
  came_from[next] = current
  */
  while (!frontier.empty())
  {
    frontier.pop();
  }

  InitializeVCC(SQUARE_GRID, 0.00f);
  npStart.posCost = cost_so_far[npStart.p_x][npStart.p_y] = 0.00f;

  //frontier.put(start).
  frontier.push(npStart);

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
    printf("\nCompute BFS Immediate!? (0 - no/1 - yes):\n");
    std::cin >> generateInstantaneous;
  }

  bool nextStep = false;

  //while not frontier.empty().Give next steps button
  while (!frontier.empty())
  {
    //current = frontier.get().
    Position current = frontier.front();

    //oldest element removed which is the frontier.front().
    frontier.pop();

    if (current == npGoal)
      break;

    if (current != npStart)
    {
      mapVisited[current.p_x][current.p_y] = CURRENT;
    }

    //for next in graph.neighbors(current).
    Position currentNorth = current + pos_SQUARENORTH;
    Position currentNorthEast = current + pos_SQUARENORTHEAST;
    Position currentEast = current + pos_SQUAREEAST;
    Position currentSouthEast = current + pos_SQUARESOUTHEAST;
    Position currentSouth = current + pos_SQUARESOUTH;
    Position currentSouthWest = current + pos_SQUARESOUTHWEST;
    Position currentWest = current + pos_SQUAREWEST;
    Position currentNorthWest = current + pos_SQUARENORTHWEST;

    /*
    if next not in visited :
    frontier.put(next)
    visited[next] = True
    came_from[next] = current
    */

    /*
    new_cost = cost_so_far[current] + graph.cost(current, next)
    if next not in cost_so_far or new_cost < cost_so_far[next]:
    cost_so_far[next] = new_cost
    */
    if (!visited[currentNorth.p_x][currentNorth.p_y] && !SquareIsOutside(currentNorth, topLeft, bottomRight))
    {
      NextChildAssignments(current, currentNorth, SOUTH_DIR, COST_AXIS, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, SQUARE_GRID);
      frontier.push(currentNorth);
    }
    if (!visited[currentNorthEast.p_x][currentNorthEast.p_y] && !SquareIsOutside(currentNorthEast, topLeft, bottomRight))
    {
      if ((mapVisited[currentNorth.p_x][currentNorth.p_y] != WALL) && (mapVisited[currentEast.p_x][currentEast.p_y] != WALL))
      {
        NextChildAssignments(current, currentNorthEast, SOUTHWEST_DIR, COST_DIAGONAL, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, SQUARE_GRID);
        frontier.push(currentNorthEast);
      }
    }
    if (!visited[currentEast.p_x][currentEast.p_y] && !SquareIsOutside(currentEast, topLeft, bottomRight))
    {
      NextChildAssignments(current, currentEast, WEST_DIR, COST_AXIS, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, SQUARE_GRID);
      frontier.push(currentEast);
    }
    if (!visited[currentSouthEast.p_x][currentSouthEast.p_y] && !SquareIsOutside(currentSouthEast, topLeft, bottomRight))
    {
      if ((mapVisited[currentSouth.p_x][currentSouth.p_y] != WALL) && (mapVisited[currentEast.p_x][currentEast.p_y] != WALL))
      {
        NextChildAssignments(current, currentSouthEast, NORTHWEST_DIR, COST_DIAGONAL, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, SQUARE_GRID);
        frontier.push(currentSouthEast);
      }
    }
    if (!visited[currentSouth.p_x][currentSouth.p_y] && !SquareIsOutside(currentSouth, topLeft, bottomRight))
    {
      NextChildAssignments(current, currentSouth, NORTH_DIR, COST_AXIS, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, SQUARE_GRID);
      frontier.push(currentSouth);
    }
    if (!visited[currentSouthWest.p_x][currentSouthWest.p_y] && !SquareIsOutside(currentSouthWest, topLeft, bottomRight))
    {
      if ((mapVisited[currentSouth.p_x][currentSouth.p_y] != WALL) && (mapVisited[currentWest.p_x][currentWest.p_y] != WALL))
      {
        NextChildAssignments(current, currentSouthWest, NORTHEAST_DIR, COST_DIAGONAL, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, SQUARE_GRID);
        frontier.push(currentSouthWest);
      }
    }
    if (!visited[currentWest.p_x][currentWest.p_y] && !SquareIsOutside(currentWest, topLeft, bottomRight))
    {
      NextChildAssignments(current, currentWest, EAST_DIR, COST_AXIS, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, SQUARE_GRID);
      frontier.push(currentWest);
    }
    if (!visited[currentNorthWest.p_x][currentNorthWest.p_y] && !SquareIsOutside(currentNorthWest, topLeft, bottomRight))
    {
      if ((mapVisited[currentNorth.p_x][currentNorth.p_y] != WALL) && (mapVisited[currentWest.p_x][currentWest.p_y] != WALL))
      {
        NextChildAssignments(current, currentNorthWest, SOUTHEAST_DIR, COST_DIAGONAL, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, SQUARE_GRID);
        frontier.push(currentNorthWest);
      }
    }

    if (current != npStart)
    {
      mapVisited[current.p_x][current.p_y] = VISITED;
    }

    if (generateInstantaneous || autoCompute)
      continue;

    //Re-print square grid.
    GenerateSquare(npStart, npGoal);
    PrintSquareMapGeneric(MapVisualType::MAP_VISITED);
    PrintSquareMapGeneric(MapVisualType::MAP_CAMEFROM);
    PrintSquareMapGeneric(MapVisualType::MAP_COST);

    nextStep = false;
    printf("\nGet next step? (0 - no/1 - yes):\n");
    std::cin >> nextStep;

    if (!nextStep)
    {
      generateInstantaneous = true;
    }
  }

  //if goal not found.
  if ((mapCost[npGoal.p_x][npGoal.p_y] == EMPTY_COST_SPACE) || (mapVisited[npGoal.p_x][npGoal.p_y] == WALL))
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

  //Print all types of grid maps for square grids.
  if (generateInstantaneous || !autoCompute)
  {
    //Re-print square grid.
    GenerateSquare(npStart, npGoal);
    PrintSquareMapGeneric(MapVisualType::MAP_VISITED);
    PrintSquareMapGeneric(MapVisualType::MAP_CAMEFROM);
    PrintSquareMapGeneric(MapVisualType::MAP_GOALPATH);
    PrintSquareMapGeneric(MapVisualType::MAP_COST);
    PrintSquareMapGeneric(MapVisualType::MAP_GOALCOST);
  }

  return cost_so_far[npGoal.p_x][npGoal.p_y];
}
