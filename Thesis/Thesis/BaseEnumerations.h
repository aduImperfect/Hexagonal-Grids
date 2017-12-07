///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: BaseEnumerations.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef BASE_ENUMERATIONS_H
#define BASE_ENUMERATIONS_H
/*
An enumeration that associates the different types of path-finding algorithms.
ALGO_BFS = 1, ALGO_DIJKSTRA = 2, ALGO_GREEDY = 3, ALGO_ASTAR = 4, ALGO_BLOCKASTAR = 5, ALGO_JPS = 6, ALGO_TOTAL = 7.
*/
enum PathfindingAlgo
{
	ALGO_BFS = 1,
	ALGO_DIJKSTRA,
	ALGO_GREEDY,
	ALGO_ASTAR,
	ALGO_BLOCKASTAR,
	ALGO_JPS,
	ALGO_TOTAL,
};

/*
An enumeration that associates the different types of map representations.
MAP_VISITED = 1, MAP_CAMEFROM = 2, MAP_GOALPATH = 3, MAP_COST = 4, MAP_GOALCOST = 5, MAP_HEUCOST = 6, MAP_GOALHEUCOST = 7, MAP_TOTALCOST = 8, MAP_GOALTOTALCOST = 9, MAP_TYPE_TOTAL = 10.
*/
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
	MAP_TYPE_TOTAL,
};

/*
An enumeration that associates the different types of heuristic functionalities.
HEURISTIC_CHEBYSHEV = 1, HEURISTIC_MANHATTAN = 2, HEURISTIC_EUCLIDEAN = 3, HEURISTIC_OCTILE = 4, HEURISTIC_TYPE_TOTAL = 5.
*/
enum HeuristicType
{
	HEURISTIC_CHEBYSHEV = 1,
	HEURISTIC_MANHATTAN,
	HEURISTIC_EUCLIDEAN,
	HEURISTIC_OCTILE,
	HEURISTIC_TYPE_TOTAL,
};

/*
An enumeration that associates the different types of costs.
COST_FROM_START_EXACT = 1, COST_TO_GOAL_HEURISTIC = 2, COST_TOTAL_HEURISTIC = 3, COST_TYPE_TOTAL = 4.
*/
enum CostType
{
	COST_FROM_START_EXACT = 1,
	COST_TO_GOAL_HEURISTIC,
	COST_TOTAL_HEURISTIC,
	COST_TYPE_TOTAL,
};
#endif