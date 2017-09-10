#pragma once
#include "SquareLDDBCalculator.h"

double SquareBlockAStar(Position npStart, Position npGoal)
{
  /*
  frontier = PriorityQueue()
  frontier.put(start, 0)
  came_from = {}
  cost_so_far = {}
  came_from[start] = None
  cost_so_far[start] = 0

  while not frontier.empty():
  current = frontier.get()

  if current == goal:
  break

  for next in graph.neighbors(current):
  new_cost = cost_so_far[current] + graph.cost(current, next)
  if next not in cost_so_far or new_cost < cost_so_far[next]:
  cost_so_far[next] = new_cost
  priority = new_cost
  frontier.put(next, priority)
  came_from[next] = current
  */


  while (!priorityFrontier.empty())
  {
    priorityFrontier.pop();
  }

  InitializeVCC(SQUARE_GRID, COST_MAX);
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
  
  SquareLDDBCalc(npStart, npGoal);
  
  int nheuristic;
  printf("\nHeuristic Type (CHEBYSHEV: 1, MANHATTAN: 2, EUCLIDEAN: 3, OCTILE: 4):\n");
  std::cin >> nheuristic;

  bool generateInstantaneous = false;
  printf("\nCompute Block ASTAR Immediate!? (0 - no/1 - yes):\n");
  std::cin >> generateInstantaneous;

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
    Position currentNorth = current + pos_SQUARENORTH;
    Position currentNorthEast = current + pos_SQUARENORTHEAST;
    Position currentEast = current + pos_SQUAREEAST;
    Position currentSouthEast = current + pos_SQUARESOUTHEAST;
    Position currentSouth = current + pos_SQUARESOUTH;
    Position currentSouthWest = current + pos_SQUARESOUTHWEST;
    Position currentWest = current + pos_SQUAREWEST;
    Position currentNorthWest = current + pos_SQUARENORTHWEST;

    double newCostAxis = cost_so_far[current.p_x][current.p_y] + COST_AXIS;
    double newCostDiagonal = cost_so_far[current.p_x][current.p_y] + COST_DIAGONAL;

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
    if (mapVisited[currentNorth.p_x][currentNorth.p_y] != WALL)
    {
      if ((!visited[currentNorth.p_x][currentNorth.p_y]) || (newCostAxis < cost_so_far[currentNorth.p_x][currentNorth.p_y]))
      {
        NextChildAssignments(current, currentNorth, SOUTH_DIR, COST_AXIS, CostType::COST_TOTAL_HEURISTIC, nheuristic, npGoal, SQUARE_GRID);
        priorityFrontier.push(currentNorth);
      }
    }
    if (mapVisited[currentNorthEast.p_x][currentNorthEast.p_y] != WALL)
    {
      if ((mapVisited[currentNorth.p_x][currentNorth.p_y] != WALL) && (mapVisited[currentEast.p_x][currentEast.p_y] != WALL))
      {
        if ((!visited[currentNorthEast.p_x][currentNorthEast.p_y]) || (newCostDiagonal < cost_so_far[currentNorthEast.p_x][currentNorthEast.p_y]))
        {
          NextChildAssignments(current, currentNorthEast, SOUTHWEST_DIR, COST_DIAGONAL, CostType::COST_TOTAL_HEURISTIC, nheuristic, npGoal, SQUARE_GRID);
          priorityFrontier.push(currentNorthEast);
        }
      }
    }
    if (mapVisited[currentEast.p_x][currentEast.p_y] != WALL)
    {
      if ((!visited[currentEast.p_x][currentEast.p_y]) || (newCostAxis < cost_so_far[currentEast.p_x][currentEast.p_y]))
      {
        NextChildAssignments(current, currentEast, WEST_DIR, COST_AXIS, CostType::COST_TOTAL_HEURISTIC, nheuristic, npGoal, SQUARE_GRID);
        priorityFrontier.push(currentEast);
      }
    }
    if (mapVisited[currentSouthEast.p_x][currentSouthEast.p_y] != WALL)
    {
      if ((mapVisited[currentSouth.p_x][currentSouth.p_y] != WALL) && (mapVisited[currentEast.p_x][currentEast.p_y] != WALL))
      {
        if ((!visited[currentSouthEast.p_x][currentSouthEast.p_y]) || (newCostDiagonal < cost_so_far[currentSouthEast.p_x][currentSouthEast.p_y]))
        {
          NextChildAssignments(current, currentSouthEast, NORTHWEST_DIR, COST_DIAGONAL, CostType::COST_TOTAL_HEURISTIC, nheuristic, npGoal, SQUARE_GRID);
          priorityFrontier.push(currentSouthEast);
        }
      }
    }
    if (mapVisited[currentSouth.p_x][currentSouth.p_y] != WALL)
    {
      if ((!visited[currentSouth.p_x][currentSouth.p_y]) || (newCostAxis < cost_so_far[currentSouth.p_x][currentSouth.p_y]))
      {
        NextChildAssignments(current, currentSouth, NORTH_DIR, COST_AXIS, CostType::COST_TOTAL_HEURISTIC, nheuristic, npGoal, SQUARE_GRID);
        priorityFrontier.push(currentSouth);
      }
    }
    if (mapVisited[currentSouthWest.p_x][currentSouthWest.p_y] != WALL)
    {
      if ((mapVisited[currentSouth.p_x][currentSouth.p_y] != WALL) && (mapVisited[currentWest.p_x][currentWest.p_y] != WALL))
      {
        if ((!visited[currentSouthWest.p_x][currentSouthWest.p_y]) || (newCostDiagonal < cost_so_far[currentSouthWest.p_x][currentSouthWest.p_y]))
        {
          NextChildAssignments(current, currentSouthWest, NORTHEAST_DIR, COST_DIAGONAL, CostType::COST_TOTAL_HEURISTIC, nheuristic, npGoal, SQUARE_GRID);
          priorityFrontier.push(currentSouthWest);
        }
      }
    }
    if (mapVisited[currentWest.p_x][currentWest.p_y] != WALL)
    {
      if ((!visited[currentWest.p_x][currentWest.p_y]) || (newCostAxis < cost_so_far[currentWest.p_x][currentWest.p_y]))
      {
        NextChildAssignments(current, currentWest, EAST_DIR, COST_AXIS, CostType::COST_TOTAL_HEURISTIC, nheuristic, npGoal, SQUARE_GRID);
        priorityFrontier.push(currentWest);
      }
    }
    if (mapVisited[currentNorthWest.p_x][currentNorthWest.p_y] != WALL)
    {
      if ((mapVisited[currentNorth.p_x][currentNorth.p_y] != WALL) && (mapVisited[currentWest.p_x][currentWest.p_y] != WALL))
      {
        if ((!visited[currentNorthWest.p_x][currentNorthWest.p_y]) || (newCostDiagonal < cost_so_far[currentNorthWest.p_x][currentNorthWest.p_y]))
        {
          NextChildAssignments(current, currentNorthWest, SOUTHEAST_DIR, COST_DIAGONAL, CostType::COST_TOTAL_HEURISTIC, nheuristic, npGoal, SQUARE_GRID);
          priorityFrontier.push(currentNorthWest);
        }
      }
    }

    if (current != npStart)
    {
      mapVisited[current.p_x][current.p_y] = VISITED;
    }

    if (generateInstantaneous)
      continue;

    //Re-print square grid.
    GenerateSquare(npStart, npGoal);
    PrintSquareMapGeneric(MapVisualType::MAP_VISITED);
    PrintSquareMapGeneric(MapVisualType::MAP_CAMEFROM);
    PrintSquareMapGeneric(MapVisualType::MAP_COST);
    PrintSquareMapGeneric(MapVisualType::MAP_HEUCOST);
    PrintSquareMapGeneric(MapVisualType::MAP_TOTALCOST);

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
  mapGoalHeuCost[npGoal.p_x][npGoal.p_y] = mapHeuCost[npGoal.p_x][npGoal.p_y];
  mapGoalTotCost[npGoal.p_x][npGoal.p_y] = mapTotCost[npGoal.p_x][npGoal.p_y];
  goalPath.push_back(currentTraverse);
  while (currentTraverse != npStart)
  {
    mapGoalPath[currentTraverse.p_x][currentTraverse.p_y] = mapCameFrom[currentTraverse.p_x][currentTraverse.p_y];
    mapGoalCost[currentTraverse.p_x][currentTraverse.p_y] = mapCost[currentTraverse.p_x][currentTraverse.p_y];
    mapGoalHeuCost[currentTraverse.p_x][currentTraverse.p_y] = mapHeuCost[currentTraverse.p_x][currentTraverse.p_y];
    mapGoalTotCost[currentTraverse.p_x][currentTraverse.p_y] = mapTotCost[currentTraverse.p_x][currentTraverse.p_y];
    currentTraverse = came_from[currentTraverse.p_x][currentTraverse.p_y];
    goalPath.push_back(currentTraverse);
  }

  goalPath.push_back(npStart);
  std::reverse(goalPath.begin(), goalPath.end());

  //Print all types of grid maps for square grids.
  if (generateInstantaneous)
  {
    //Re-print square grid.
    GenerateSquare(npStart, npGoal);
    PrintSquareMapGeneric(MapVisualType::MAP_VISITED);
    PrintSquareMapGeneric(MapVisualType::MAP_CAMEFROM);
    PrintSquareMapGeneric(MapVisualType::MAP_GOALPATH);
    PrintSquareMapGeneric(MapVisualType::MAP_COST);
    PrintSquareMapGeneric(MapVisualType::MAP_GOALCOST);
    PrintSquareMapGeneric(MapVisualType::MAP_HEUCOST);
    PrintSquareMapGeneric(MapVisualType::MAP_GOALHEUCOST);
    PrintSquareMapGeneric(MapVisualType::MAP_TOTALCOST);
    PrintSquareMapGeneric(MapVisualType::MAP_GOALTOTALCOST);
  }

  return npGoal.posCost;
}
