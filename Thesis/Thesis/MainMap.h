#pragma once
#include "BaseBFS.h"
#include "BaseDijkstra.h"
#include "BaseGreedy.h"
#include "BaseAStar.h"
#include "BaseBlockAStar.h"

double Map(int gridSpace, int algoType, Position nposStart, Position nposGoal)
{
  double gCost = -1;
  if (gridSpace == SQUARE_GRID)
  {
    switch (algoType)
    {
    case PathfindingAlgo::ALGO_BFS:
      InitializeFirstSquare(EMPTY_COST_SPACE);
      GenerateSquare(nposStart, nposGoal);
      PrintSquareMapGeneric(MapVisualType::MAP_VISITED);
      PrintSquareMapGeneric(MapVisualType::MAP_CAMEFROM);
      PrintSquareMapGeneric(MapVisualType::MAP_COST);
      gCost = SquareBFS(nposStart, nposGoal, false, Position(0,0), Position(SIZE + SQUARE_GRID, SIZE + SQUARE_GRID));
      break;
    case PathfindingAlgo::ALGO_DIJKSTRA:
      InitializeFirstSquare(COST_MAX_TERM);
      GenerateSquare(nposStart, nposGoal);
      PrintSquareMapGeneric(MapVisualType::MAP_VISITED);
      PrintSquareMapGeneric(MapVisualType::MAP_CAMEFROM);
      PrintSquareMapGeneric(MapVisualType::MAP_COST);
      gCost = SquareDijkstra(nposStart, nposGoal, false, Position(0, 0), Position(SIZE + SQUARE_GRID, SIZE + SQUARE_GRID));
      break;
    case PathfindingAlgo::ALGO_GREEDY:
      InitializeFirstSquare(COST_MAX_TERM);
      GenerateSquare(nposStart, nposGoal);
      PrintSquareMapGeneric(MapVisualType::MAP_VISITED);
      PrintSquareMapGeneric(MapVisualType::MAP_CAMEFROM);
      PrintSquareMapGeneric(MapVisualType::MAP_COST);
      PrintSquareMapGeneric(MapVisualType::MAP_HEUCOST);
      gCost = SquareGreedy(nposStart, nposGoal, false, Position(0, 0), Position(SIZE + SQUARE_GRID, SIZE + SQUARE_GRID));
      break;
    case PathfindingAlgo::ALGO_ASTAR:
      InitializeFirstSquare(COST_MAX_TERM);
      GenerateSquare(nposStart, nposGoal);
      PrintSquareMapGeneric(MapVisualType::MAP_VISITED);
      PrintSquareMapGeneric(MapVisualType::MAP_CAMEFROM);
      PrintSquareMapGeneric(MapVisualType::MAP_COST);
      PrintSquareMapGeneric(MapVisualType::MAP_HEUCOST);
      PrintSquareMapGeneric(MapVisualType::MAP_TOTALCOST);
      gCost = SquareAStar(nposStart, nposGoal, false, Position(0, 0), Position(SIZE + SQUARE_GRID, SIZE + SQUARE_GRID));
      break;
    case PathfindingAlgo::ALGO_BLOCKASTAR:
      SquareLDDBInitializer();
      InitializeFirstSquare(COST_MAX_TERM);
      GenerateSquare(nposStart, nposGoal);
      PrintSquareMapGeneric(MapVisualType::MAP_VISITED);
      PrintSquareMapGeneric(MapVisualType::MAP_CAMEFROM);
      PrintSquareMapGeneric(MapVisualType::MAP_COST);
      PrintSquareMapGeneric(MapVisualType::MAP_HEUCOST);
      PrintSquareMapGeneric(MapVisualType::MAP_TOTALCOST);
      gCost = SquareBlockAStar(nposStart, nposGoal);
      break;
    case PathfindingAlgo::ALGO_JPS:
      break;
    }
  }
  else if (gridSpace == HEX_GRID)
  {
    switch (algoType)
    {
    case PathfindingAlgo::ALGO_BFS:
      InitializeFirstHex(EMPTY_COST_SPACE);
      GenerateHex(nposStart, nposGoal);
      PrintHexMapGeneric(MapVisualType::MAP_VISITED);
      PrintHexMapGeneric(MapVisualType::MAP_CAMEFROM);
      PrintHexMapGeneric(MapVisualType::MAP_COST);
      gCost = HexBFS(nposStart, nposGoal, false, Position((SIZE + HEX_GRID + 1)/2, (SIZE + HEX_GRID + 1) / 2), 30);
      break;
    case PathfindingAlgo::ALGO_DIJKSTRA:
      InitializeFirstHex(COST_MAX_TERM);
      GenerateHex(nposStart, nposGoal);
      PrintHexMapGeneric(MapVisualType::MAP_VISITED);
      PrintHexMapGeneric(MapVisualType::MAP_CAMEFROM);
      PrintHexMapGeneric(MapVisualType::MAP_COST);
      gCost = HexDijkstra(nposStart, nposGoal, false, Position((SIZE + HEX_GRID + 1) / 2, (SIZE + HEX_GRID + 1) / 2), 30);
      break;
    case PathfindingAlgo::ALGO_GREEDY:
      InitializeFirstHex(COST_MAX_TERM);
      GenerateHex(nposStart, nposGoal);
      PrintHexMapGeneric(MapVisualType::MAP_VISITED);
      PrintHexMapGeneric(MapVisualType::MAP_CAMEFROM);
      PrintHexMapGeneric(MapVisualType::MAP_COST);
      PrintHexMapGeneric(MapVisualType::MAP_HEUCOST);
      gCost = HexGreedy(nposStart, nposGoal, false, Position((SIZE + HEX_GRID + 1) / 2, (SIZE + HEX_GRID + 1) / 2), 30);
      break;
    case PathfindingAlgo::ALGO_ASTAR:
      InitializeFirstHex(COST_MAX_TERM);
      GenerateHex(nposStart, nposGoal);
      PrintHexMapGeneric(MapVisualType::MAP_VISITED);
      PrintHexMapGeneric(MapVisualType::MAP_CAMEFROM);
      PrintHexMapGeneric(MapVisualType::MAP_COST);
      PrintHexMapGeneric(MapVisualType::MAP_HEUCOST);
      PrintHexMapGeneric(MapVisualType::MAP_TOTALCOST);
      gCost = HexAStar(nposStart, nposGoal, false, Position((SIZE + HEX_GRID + 1) / 2, (SIZE + HEX_GRID + 1) / 2), 30);
      break;
    case PathfindingAlgo::ALGO_BLOCKASTAR:
      break;
    case PathfindingAlgo::ALGO_JPS:
      break;
    }
  }

  return gCost;
}
