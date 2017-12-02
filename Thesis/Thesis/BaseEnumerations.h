///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: BaseEnumerations.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#pragma once
enum PathfindingAlgo
{
  ALGO_BFS = 1,
  ALGO_DIJKSTRA,
  ALGO_GREEDY,
  ALGO_ASTAR,
  ALGO_BLOCKASTAR,
  ALGO_JPS,
};

enum MapVisualType
{
  MAP_VISITED = 1,
  MAP_CAMEFROM,
  MAP_GOALPATH,
  MAP_COST,
  MAP_GOALCOST,
  MAP_HEUCOST,
  MAP_GOALHEUCOST,
  MAP_TOTALCOST,
  MAP_GOALTOTALCOST,
};

enum HeuristicType
{
  HEURISTIC_CHEBYSHEV = 1,
  HEURISTIC_MANHATTAN,
  HEURISTIC_EUCLIDEAN,
  HEURISTIC_OCTILE,
};

enum CostType
{
  COST_FROM_START_EXACT = 1,
  COST_TO_GOAL_HEURISTIC,
  COST_TOTAL_HEURISTIC,
};