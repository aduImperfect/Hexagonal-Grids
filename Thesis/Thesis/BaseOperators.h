#pragma once
#include <queue>

#include "BaseDefines.h"
#include "Position.h"

//PriorityFrontier = PriorityQueue().
std::priority_queue<Position, std::vector<Position>, GreaterThanByCost> priorityFrontier;

//frontier = queue().
std::queue<Position> frontier;
//visited = {}.
bool visited[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];
//came_from = {}.
Position came_from[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];
//cost_so_far = {}.
double cost_so_far[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];
//cost_heuristic = {}.
double cost_heuristic[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];
//cost_total = {}.
double cost_total[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];
