///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: BaseDefines.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef BASE_DEFINES_H
#define BASE_DEFINES_H

//The size of the grid + 1 (0 - 20).
#define SIZE 20

//Additive for square and hex grids.
#define SQUARE_GRID 1
#define HEX_GRID 2
#define GRID_EXTRA 4

//The Square grid's total size (including the corner walls)!
#define SQUARE_BOTTOM_RIGHT SIZE + SQUARE_GRID
#define SQUARE_SIZE SIZE + SQUARE_GRID
#define SQUARE_SIZE_PLUS SIZE + SQUARE_GRID + 1

//The hex grid's total size based on the center! (including the corner walls)!
#define HEX_CENTER (SIZE + HEX_GRID + 1) / 2
#define HEX_SIZE SIZE + HEX_GRID + 1

//Different cost values in string form (useful for printing).
#define EMPTY_COST_SPACE "----"
#define WALL_COST "####"
#define START_COST "STRT"
#define GOAL_COST "GOAL"
#define COST_AXIS 1.00f
#define COST_DIAGONAL 1.41f
#define COST_MAX HUGE_VAL
#define COST_MAX_TERM "CMAX"

//Different direction in string form (useful for printing).
#define NORTH_DIR "NN"
#define NORTHEAST_DIR "NE"
#define EAST_DIR "EE"
#define SOUTHEAST_DIR "SE"
#define SOUTH_DIR "SS"
#define SOUTHWEST_DIR "SW"
#define WEST_DIR "WW"
#define NORTHWEST_DIR "NW"

//Came from grid indicators in string form (useful for printing).
#define EMPTY_CAME_FROM_SPACE "--"
#define WALL_CAME_FROM "##"
#define START_CAME_FROM "ST"
#define GOAL_CAME_FROM "GO"
#define INACCESSIBLE_CAME_FROM_SPACE "  "
#define CURRENT_CAME_FROM "CC"

//Visited grid indicators in string form (useful for printing).
#define VISITED "V"
#define CURRENT "C"
#define NEXT "N"
#define WALL "#"
#define START "S"
#define GOAL "G"
#define EMPTY_SPACE "."
#define INACCESSIBLE_SPACE " "

//Offset in terms of string output of the grid to make it viewable to the user.
#define SQUARE_GRID_OFFSET ""
#define HEX_GRID_OFFSET "   "

//Other string forms used in printing.
#define SQUARE_GRID_COST_SPACE " "
#define HEX_GRID_COST_SPACE "   "

#define SQUARE_GRID_CAME_FROM_SPACE "  "
#define HEX_GRID_CAME_FROM_SPACE "    "

#define SQUARE_GRID_SPACE "   "
#define HEX_GRID_SPACE "     "

#define EMPTY ""

//Square LDDB defines.

//The maximum ROW positions (1-4) available inside a block.
#define SQUARE_LDDB_BLOCK_SPLIT_SIZE_X 4

//The maximum COLUMN positions (1-4) available inside a block.
#define SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y 4

//The number of Blocks in the horizontal ROW direction. Example: (20/4) = 5.
#define SQUARE_LDDB_BLOCK_SIZE_I SIZE / SQUARE_LDDB_BLOCK_SPLIT_SIZE_X

//The number of Blocks in the vertical COLUMN direction. Example: (20/4) = 5.
#define SQUARE_LDDB_BLOCK_SIZE_J SIZE / SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y

/*
The square LDDB multi-dimensional array!
SquareLDDB[BLOCK_ROW][BLOCK_COL][POS_FROM_ROW][POS_FROM_COL][POS_TO_ROW][POS_TO_COL].
Example:
A 20x20 square grid with 4x4 blocks will divide into 25 blocks (5x5).
Each POS_FROM is inside a 4x4 block and the POS_TO is also inside the same 4x4 block.
Hence, SquareLDDB[5][5][4][4][4][4].
*/
double SquareLDDB[SQUARE_LDDB_BLOCK_SIZE_I][SQUARE_LDDB_BLOCK_SIZE_J][SQUARE_LDDB_BLOCK_SPLIT_SIZE_X][SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y][SQUARE_LDDB_BLOCK_SPLIT_SIZE_X][SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y];

//Block relations defines.

#define MAX_RELATIONS 5

//The maximum out-corner relations. 2 in one neighboring (horizontal/vertical) block, 1 in the diagonal block, and 2 more in another neighboring (horizontal/vertical) block.
#define MAX_OUT_CORNER_RELATIONS 5

//The maximum in-corner relations. 3 in the only neighboring (horizontal/vertical) block.
#define MAX_IN_CORNER_RELATIONS 3

//Egress cells defines.

#define OUTER_BORDERS_SIZE (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X * SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y) - (SQUARE_LDDB_BLOCK_SPLIT_SIZE_X - 2) * (SQUARE_LDDB_BLOCK_SPLIT_SIZE_Y - 2)

unsigned int SquareEGCellNumCorners[SQUARE_LDDB_BLOCK_SIZE_I][SQUARE_LDDB_BLOCK_SIZE_J][OUTER_BORDERS_SIZE];
bool SquareEgressCells[SQUARE_LDDB_BLOCK_SIZE_I][SQUARE_LDDB_BLOCK_SIZE_J][OUTER_BORDERS_SIZE][MAX_RELATIONS];

#endif