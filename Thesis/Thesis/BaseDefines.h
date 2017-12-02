///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: BaseDefines.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#pragma once
#define SIZE 21

#define SQUARE_GRID 1
#define HEX_GRID 2
#define GRID_EXTRA 4

#define EMPTY_COST_SPACE "----"
#define WALL_COST "####"
#define START_COST "STRT"
#define GOAL_COST "GOAL"
#define COST_AXIS 1.00f
#define COST_DIAGONAL 1.41f
#define COST_TERMINATOR 99.0f
#define COST_MAX 100.0f
#define COST_MAX_TERM "CMAX"

#define NORTH_DIR "NN"
#define NORTHEAST_DIR "NE"
#define EAST_DIR "EE"
#define SOUTHEAST_DIR "SE"
#define SOUTH_DIR "SS"
#define SOUTHWEST_DIR "SW"
#define WEST_DIR "WW"
#define NORTHWEST_DIR "NW"
#define EMPTY_CAME_FROM_SPACE "--"
#define WALL_CAME_FROM "##"
#define START_CAME_FROM "ST"
#define GOAL_CAME_FROM "GO"
#define INACCESSIBLE_CAME_FROM_SPACE "  "
#define CURRENT_CAME_FROM "CC"

#define VISITED "V"
#define CURRENT "C"
#define NEXT "N"
#define WALL "#"
#define START "S"
#define GOAL "G"
#define EMPTY_SPACE "."
#define INACCESSIBLE_SPACE " "

#define SQUARE_GRID_OFFSET ""
#define HEX_GRID_OFFSET "   "

#define SQUARE_GRID_COST_SPACE " "
#define HEX_GRID_COST_SPACE "   "

#define SQUARE_GRID_CAME_FROM_SPACE "  "
#define HEX_GRID_CAME_FROM_SPACE "    "

#define SQUARE_GRID_SPACE "   "
#define HEX_GRID_SPACE "     "

#define EMPTY ""