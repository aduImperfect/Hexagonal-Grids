///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: HexBFS.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef HEX_BFS_H
#define HEX_BFS_H
//Including the base header for different hex operations.
#include "BaseHexOperations.h"

double HexBFS(Position npStart, Position npGoal, bool autoCompute, Position center, int perimeter, const int showMap)
{
  if (HexIsOutside(npStart, center, perimeter))
    return -1;

  if (HexIsOutside(npGoal, center, perimeter))
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
  while (!frontier.empty())
  {
    frontier.pop();
  }

  InitializeVCC(HEX_GRID + 1, 0.00f);
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
    Position currentNorth = current + pos_HEXNORTH;
    Position currentNorthEast = current + ((current.p_x % 2 != 0) ? pos_HEXODDNORTHEAST : pos_HEXEVENNORTHEAST);
    Position currentSouthEast = current + ((current.p_x % 2 != 0) ? pos_HEXODDSOUTHEAST : pos_HEXEVENSOUTHEAST);
    Position currentSouth = current + pos_HEXSOUTH;
    Position currentSouthWest = current + ((current.p_x % 2 != 0) ? pos_HEXODDSOUTHWEST : pos_HEXEVENSOUTHWEST);
    Position currentNorthWest = current + ((current.p_x % 2 != 0) ? pos_HEXODDNORTHWEST : pos_HEXEVENNORTHWEST);

    /*
    if next not in visited :
    frontier.put(next)
    visited[next] = True
    came_from[next] = current
    */
    if (!visited[currentNorth.p_x][currentNorth.p_y] && !HexIsOutside(currentNorth, center, perimeter))
    {
      NextChildAssignments(current, currentNorth, SOUTH_DIR, COST_AXIS, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, HEX_GRID);
      frontier.push(currentNorth);
    }
    if (!visited[currentNorthEast.p_x][currentNorthEast.p_y] && !HexIsOutside(currentNorthEast, center, perimeter))
    {
      NextChildAssignments(current, currentNorthEast, SOUTHWEST_DIR, COST_AXIS, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, HEX_GRID);
      frontier.push(currentNorthEast);
    }
    if (!visited[currentSouthEast.p_x][currentSouthEast.p_y] && !HexIsOutside(currentSouthEast, center, perimeter))
    {
      NextChildAssignments(current, currentSouthEast, NORTHWEST_DIR, COST_AXIS, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, HEX_GRID);
      frontier.push(currentSouthEast);
    }
    if (!visited[currentSouth.p_x][currentSouth.p_y] && !HexIsOutside(currentSouth, center, perimeter))
    {
      NextChildAssignments(current, currentSouth, NORTH_DIR, COST_AXIS, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, HEX_GRID);
      frontier.push(currentSouth);
    }
    if (!visited[currentSouthWest.p_x][currentSouthWest.p_y] && !HexIsOutside(currentSouthWest, center, perimeter))
    {
      NextChildAssignments(current, currentSouthWest, NORTHEAST_DIR, COST_AXIS, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, HEX_GRID);
      frontier.push(currentSouthWest);
    }
    if (!visited[currentNorthWest.p_x][currentNorthWest.p_y] && !HexIsOutside(currentNorthWest, center, perimeter))
    {
      NextChildAssignments(current, currentNorthWest, SOUTHEAST_DIR, COST_AXIS, CostType::COST_FROM_START_EXACT, HeuristicType::HEURISTIC_CHEBYSHEV, npGoal, HEX_GRID);
      frontier.push(currentNorthWest);
    }

    if (current != npStart)
    {
      mapVisited[current.p_x][current.p_y] = VISITED;
    }

    if (generateInstantaneous || autoCompute)
      continue;

    //Re-print hex grid.
    GenerateHex(npStart, npGoal);
	if (showMap == 1)
	{
		PrintHexMapGeneric(MapVisualType::MAP_VISITED);
		PrintHexMapGeneric(MapVisualType::MAP_CAMEFROM);
		PrintHexMapGeneric(MapVisualType::MAP_COST);
	}

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

  //Print all types of grid maps for hex grids.
  if (generateInstantaneous || !autoCompute)
  {
    //Re-print hex grid.
    GenerateHex(npStart, npGoal);
	if (showMap == 1)
	{
		PrintHexMapGeneric(MapVisualType::MAP_VISITED);
		PrintHexMapGeneric(MapVisualType::MAP_CAMEFROM);
		PrintHexMapGeneric(MapVisualType::MAP_GOALPATH);
		PrintHexMapGeneric(MapVisualType::MAP_COST);
		PrintHexMapGeneric(MapVisualType::MAP_GOALCOST);
	}
  }

  return cost_so_far[npGoal.p_x][npGoal.p_y];
}
#endif