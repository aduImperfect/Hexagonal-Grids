#pragma once
#include <string>

#include "BaseDefines.h"

std::string mapVisited[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];
std::string mapCameFrom[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];
std::string mapGoalPath[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];
std::string mapCost[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];
std::string mapGoalCost[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];
std::string mapHeuCost[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];
std::string mapGoalHeuCost[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];
std::string mapTotCost[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];
std::string mapGoalTotCost[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];
