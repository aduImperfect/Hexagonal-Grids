///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: MapsVariety.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef MAPS_VARIETY_H
#define MAPS_VARIETY_H
//Including the different required standard library for strings and base headers which contain the base defines.
#include <string>
#include "BaseDefines.h"

//The map which stores all the visited information. (Basically which positions on the grid are already visited.
std::string mapVisited[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];

//The map which stores the information for from which older position did we arrive to the current position.
std::string mapCameFrom[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];

//The map which stores the goal path info for from which older position did we arrive to the current position (from start to goal).
std::string mapGoalPath[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];

//The map which stores the information for the current cost of the position based on the path traversed from the start node to the current position.
std::string mapCost[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];

//The map which stores the goal path info for the current cost of the position based on the path traversed from the start node to the goal node.
std::string mapGoalCost[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];

//The map which stores the information for the current heuristic cost of the position based on the path it supposedly traverses the current position to the goal position.
std::string mapHeuCost[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];

//The map which stores the goal path info for the current heuristic cost of the position based on the path it supposedly traverses the current position to the goal position (from start to goal).
std::string mapGoalHeuCost[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];

//The map which stores the information for the current total (cost + heuristic cost) of the position based on the path it traversed to reach here from the start node and the path it supposedly traverses from the current position to the goal position.
std::string mapTotCost[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];

//The map which stores the goal path info for the current total (cost + heuristic cost) of the position based on the path it traversed to reach here from the start node and the path it supposedly traverses from the current position to the goal position (from start to goal).
std::string mapGoalTotCost[SIZE + GRID_EXTRA][SIZE + GRID_EXTRA];
#endif