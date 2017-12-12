///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: SearchLoop.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef SEARCH_LOOP_H
#define SEARCH_LOOP_H
//Including the header for position structure.
#include "Position.h"

/*
The current gets set with a new value.
Parameters to the function:
current : Position & - the current position inside the loop.
Returns from the function:
NONE
This function sets the current's value to be the frontier's first element.
*/
void CurrentFrontier(Position & current)
{
	current = frontier.front();
}

/*
The current gets set with a new value.
Parameters to the function:
current : Position & - the current position inside the loop.
Returns from the function:
NONE
This function sets the current's value to be the priority frontier's first element.
*/
void CurrentPriorityFrontier(Position & current)
{
	current = priorityFrontier.top();
}

/*
The main searching loop which finds the path.
Parameters to the function:
isPriorityQueue : const bool & - the check that tells us if it is a priority queue or not.
queueType : T & - the type of queue (a normal queue, or a priority queue).
algoType : const PathfindingAlgo & - the algorithm type.
npStart : const Position & - the starting position.
npGoal : const Position & - the goal position.
topLeft : const Position & - the top left position of the square grid.
bottomRight : const Position & - the bottom right position of the square grid.
costType : const CostType & - the type of cost associated with the path-finding algorithm.
heuType : const HeuristicType & - the type of heuristic associated with the path-finding algorithm.
generateInstantaneous : bool & - the check that is changed from making a step-by-step algorithm parsing to complete parsing.
autoCompute : const bool & - the main check given by the user that overrides the instantaneous check.
showMap : const int & - the maps to be printed.
Returns from the function:
NONE
This function runs the main search loop. It goes on until the queue is empty or the goal is found. It parses through all the neighbors of the square grid, prints the maps if needed, and checks to see if the user wants a step by step algorithm expansion. It returns nothing.
*/
template<typename T>
void SquareSearchLoop(const bool & isPriorityQueue, T & queueType, const PathfindingAlgo & algoType, const Position & npStart, const Position & npGoal, const Position & topLeft, const Position & bottomRight, const CostType & costType, const HeuristicType & heuType, bool & generateInstantaneous, const bool & autoCompute, const int & showMap)
{	
	//Keep running this loop until there is nothing left in the queue.
	while (!queueType.empty())
	{
		//Find the first element out of the queue. (FIFO).
		//That is our current element.
		Position current;
		if (!isPriorityQueue)
		{
			CurrentFrontier(current);
		}
		else
		{
			CurrentPriorityFrontier(current);
		}

		//Pop out (remove) the first element from the queue.
		queueType.pop();

		//If the current position is same as the goal, we early exit out of the while loop.
		if (current == npGoal)
			break;

		//Parse through and add the neighbors to the current position to the queue.
		ParseSquareNeighbors(queueType, algoType, current, npGoal, topLeft, bottomRight, costType, heuType);

		//Check to see if current is not the same as start and set mapVisted(current) = "V" (VISITED).
		if (current != npStart)
		{
			mapVisited[current.p_x][current.p_y] = VISITED;
		}

		//If autoCompute or generateInstantaneous is set to true we just keep going through the while loop without asking the user for the next step or printing out the map.
		if (generateInstantaneous || autoCompute)
			continue;

		//If we are going to show the various maps.
		if (showMap == 1)
		{
			//Re-generate the square grid and then print the visited, came_from, and cost, heuristic cost, and total cost square grid maps.
			GenerateSquare(npStart, npGoal);
			PrintSquareMapGeneric(MapVisualType::MAP_VISITED);
			PrintSquareMapGeneric(MapVisualType::MAP_CAMEFROM);
			PrintSquareMapGeneric(MapVisualType::MAP_COST);

			if (algoType == PathfindingAlgo::ALGO_GREEDY || algoType == PathfindingAlgo::ALGO_ASTAR || algoType == PathfindingAlgo::ALGO_BLOCKASTAR)
			{
				PrintSquareMapGeneric(MapVisualType::MAP_HEUCOST);
			}
			if (algoType == PathfindingAlgo::ALGO_ASTAR || algoType == PathfindingAlgo::ALGO_BLOCKASTAR)
			{
				PrintSquareMapGeneric(MapVisualType::MAP_TOTALCOST);
			}
		}

		//If step by step algorithm is being expanded then we use nextStep's value to know if we want to get the next step.
		//If this is set to false by the user, we change the mode to computing automatically.
		bool nextStep = false;
		printf("\nGet next step? (0 - no/1 - yes):\n");
		std::cin >> nextStep;

		//If the user does not want to get the next step, we set it to calculating the next steps automatically.
		if (!nextStep)
		{
			generateInstantaneous = true;
		}
	}
}

/*
The main searching loop which finds the path.
Parameters to the function:
isPriorityQueue : const bool & - the check that tells us if it is a priority queue or not.
queueType : T & - the type of queue (a normal queue, or a priority queue).
algoType : const PathfindingAlgo & - the algorithm type.
npStart : const Position & - the starting position.
npGoal : const Position & - the goal position.
center : const Position & - the center position of the hex grid.
perimeter : const int & - the perimeter of the hex grid.
costType : const CostType & - the type of cost associated with the path-finding algorithm.
heuType : const HeuristicType & - the type of heuristic associated with the path-finding algorithm.
generateInstantaneous : bool & - the check that is changed from making a step-by-step algorithm parsing to complete parsing.
autoCompute : const bool & - the main check given by the user that overrides the instantaneous check.
showMap : const int & - the maps to be printed.
Returns from the function:
NONE
This function runs the main search loop. It goes on until the queue is empty or the goal is found. It parses through all the neighbors of the hex grid, prints the maps if needed, and checks to see if the user wants a step by step algorithm expansion. It returns nothing.
*/
template<typename T>
void HexSearchLoop(const bool & isPriorityQueue, T & queueType, const PathfindingAlgo & algoType, const Position & npStart, const Position & npGoal, const Position & center, const int & perimeter, const CostType & costType, const HeuristicType & heuType, bool & generateInstantaneous, const bool & autoCompute, const int & showMap)
{
	//Keep running this loop until there is nothing left in the queue.
	while (!queueType.empty())
	{
		//Find the first element out of the queue. (FIFO).
		//That is our current element.
		Position current;
		if (!isPriorityQueue)
		{
			CurrentFrontier(current);
		}
		else
		{
			CurrentPriorityFrontier(current);
		}

		//Pop out (remove) the first element from the queue.
		queueType.pop();

		//If the current position is same as the goal, we early exit out of the while loop.
		if (current == npGoal)
			break;

		//Parse through and add the neighbors to the current position to the queue.
		ParseHexNeighbors(queueType, algoType, current, npGoal, center, perimeter, costType, heuType);

		//Check to see if current is not the same as start and set mapVisted(current) = "V" (VISITED).
		if (current != npStart)
		{
			mapVisited[current.p_x][current.p_y] = VISITED;
		}

		//If autoCompute or generateInstantaneous is set to true we just keep going through the while loop without asking the user for the next step or printing out the map.
		if (generateInstantaneous || autoCompute)
			continue;

		//If we are going to show the various maps.
		if (showMap == 1)
		{
			//Re-generate the hex grid and then print the visited, came_from, and cost, heuristic cost, and total cost hex grid maps.
			GenerateHex(npStart, npGoal);
			PrintHexMapGeneric(MapVisualType::MAP_VISITED);
			PrintHexMapGeneric(MapVisualType::MAP_CAMEFROM);
			PrintHexMapGeneric(MapVisualType::MAP_COST);

			if (algoType == PathfindingAlgo::ALGO_GREEDY || algoType == PathfindingAlgo::ALGO_ASTAR || algoType == PathfindingAlgo::ALGO_BLOCKASTAR)
			{
				PrintHexMapGeneric(MapVisualType::MAP_HEUCOST);
			}
			if (algoType == PathfindingAlgo::ALGO_ASTAR || algoType == PathfindingAlgo::ALGO_BLOCKASTAR)
			{
				PrintHexMapGeneric(MapVisualType::MAP_TOTALCOST);
			}
		}

		//If step by step algorithm is being expanded then we use nextStep's value to know if we want to get the next step.
		//If this is set to false by the user, we change the mode to computing automatically.
		bool nextStep = false;
		printf("\nGet next step? (0 - no/1 - yes):\n");
		std::cin >> nextStep;

		//If the user does not want to get the next step, we set it to calculating the next steps automatically.
		if (!nextStep)
		{
			generateInstantaneous = true;
		}
	}
}
#endif