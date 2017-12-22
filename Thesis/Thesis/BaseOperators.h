///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: BaseOperators.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef BASE_OPERATORS_H
#define BASE_OPERATORS_H
//Including the different required standard library for queues, and lists and base headers which contain the base defines and the position structure.
#include <queue>
#include <list>
#include "BaseDefines.h"
#include "Position.h"

//A priority queue that keeps the lowest cost of all the cost values at the top along with working as a FIFO.
std::priority_queue<Position, std::vector<Position>, GreaterThanByCost> priorityFrontier;

//A normal queue which does not care about cost values and works normally as a FIFO.
std::queue<Position> frontier;

//A boolean that keeps track if the position(i,j) has already been visited.
bool visited[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];

//A Position that keeps track of where from did we arrive to this current position(i,j).
Position came_from[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];

//A double that keeps track of the cost accumulated from start node to the current position(i,j).
double cost_so_far[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];

//A double that keeps track of the cost supposedly to be accumulated for going from the current position(i,j) to the goal node.
double cost_heuristic[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];

//A double that keeps track of the total of the cost accumulated from the start node to the current position(i,j) and the cost supposedly to be accumulated for going from the current position(i,j) to the goal node.
double cost_total[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];
#endif