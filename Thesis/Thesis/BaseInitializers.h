#pragma once
#include "BaseDefines.h"
#include "MapsVariety.h"
#include "BaseOperators.h"

void InitializeVCC(int extraSize, double nCost)
{
  for (int i = 0; i <= SIZE + extraSize; ++i)
  {
    for (int j = 0; j <= SIZE + extraSize; ++j)
    {
      if (mapVisited[i][j] == WALL)
      {
        visited[i][j] = true;
      }
      else
      {
        visited[i][j] = false;
      }
      came_from[i][j] = NULL;
      cost_so_far[i][j] = nCost;
      cost_heuristic[i][j] = nCost;
      cost_total[i][j] = nCost;
    }
  }
}

void Initializer(int i, int j, const char * mVisit, const char * mCameFrom, const char * mGoalPath, const char * mCost, const char * mGoalCost, const char * mHeuCost, const char * mGoalHeuCost, const char * mTotCost, const char * mGoalTotCost)
{
  (mVisit != NULL) ? (mapVisited[i][j] = mVisit) : mapVisited[i][j];
  (mCameFrom != NULL) ? (mapCameFrom[i][j] = mCameFrom) : mapCameFrom[i][j];
  (mGoalPath != NULL) ? (mapGoalPath[i][j] = mGoalPath) : mapGoalPath[i][j];
  (mCost != NULL) ? (mapCost[i][j] = mCost) : mapCost[i][j];
  (mGoalCost != NULL) ? (mapGoalCost[i][j] = mGoalCost) : mapGoalCost[i][j];
  (mHeuCost != NULL) ? (mapHeuCost[i][j] = mHeuCost) : mapHeuCost[i][j];
  (mGoalHeuCost != NULL) ? (mapGoalHeuCost[i][j] = mGoalHeuCost) : mapGoalHeuCost[i][j];
  (mTotCost != NULL) ? (mapTotCost[i][j] = mTotCost) : mapTotCost[i][j];
  (mGoalTotCost != NULL) ? (mapGoalTotCost[i][j] = mGoalTotCost) : mapGoalTotCost[i][j];
}
