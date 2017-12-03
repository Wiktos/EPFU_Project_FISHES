#pragma once
#include "game.h"

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


/*
* boardDimension counts last column and row? 
* this situation:
* [0,0] [1,0] [2,0]
* [0,1] [1,1] [2,1]
* means that boardDimension.col = 3 and boardDimension.row = 2 ?
* OR
* boardDimension.col = 2 and boardDimension.row = 1 ?
*/

static bool checkMove(int x, int y, int VecX, int VecY, int Distance, Game* Game) {
	if (x + VecX < 0 || ii + VecY < 0 || i + VecX >= Game->boardDimension.col || ii + VecY >= Game->boardDimension.row)return false; // if actual checking position is outside board then return false
	if (Distance == 0)return true; // if we achive last field in sequence then return true
	if (!Game->getField(x + VecX, y + VecY, Game)->EXISTANCE_FLAG || Game->getField(x + VecX, y + VecY, Game)->OCCUPIED_FLAG)return false; // if actual checking field is occupied or doesn't exist then return false
	return checkMove(x + VecX, y + VecY, VecX, VecY, Distance - 1, Game); // reqursion on new field in sequence, decresing Distance
}

static bool handleMovment(int x, int y, int EndX, int EndY, int Player, Game* Game) {
	if (x < 0 || y < 0 || x >= Game->boardDimension.col || y >= Game->boardDimension.row)return false; // if start position is ouside the board then return false
	if (EndX < 0 || EndY < 0 || EndX >= Game->boardDimension.col || EndY >= Game->boardDimension.row)return false; // if end position is ouside the board then return false

	if (Game->getField(x, y, Game)->PlayerID != Player)return false; // if this player is not on this field at all then return false
	if (!Game->getField(EndX, EndX, Game)->EXISTANCE_FLAG || Game->getField(EndX, EndX, Game)->OCCUPIED_FLAG)return false; // if End position is invalid then return false

	int DifX = EndX - x;
	int DifY = EndY - y;
	int MoveDirection = -1;
	int MoveRadius = max(abs(DifX), abs(DifY)); // move distance

	int VecX = 0; // move direction in X (-1, 0, 1)
	int VecY = 0; // move direction in Y (-1, 0, 1)

	/*
	* check if even move direction is valid
	*/
	if (DifX < 0 && DifY == 0) VecX = -1; // move left

	if (DifX < 0 && DifY > 0) { // move left down
		if (abs(DifX) == abs(DifY)) { VecX = -1; VecY = 1; }
		else return false;
	}

	if (DifX == 0 && DifY > 0)VecY = 1; // move down

	if (DifX > 0 && DifY == 0)VecX = 1; // move right
	
	if (DifX > 0 && DifY < 0) { // move right up
		if (abs(DifX) == abs(DifY)) { VecX = 1; VecY = -1; }
		else return false;
	}

	if (DifX == 0 && DifY < 0) VecY = -1; // move up

	if ((VecX == 0 && VecY == 0) || MoveRadius == 0)return false; // if move has 0 distance then return false
	if (!checkMove(x, y, VecX, VecY, MoveRadius, Game))return false; // check if move is avaible by recursion, if not return false
	else {
		/*
		* Perform Movement
		*/
		Game->getPlayer(PlayerID, Game)->score += Game->getField(x, y, Game)->fishNumber; // add score
		Game->getField(x, y, Game)->fishNumber = 0; // set fishes to 0
		Game->getField(x, y, Game)->EXISTANCE_FLAG = false; // destroy field
		Game->getField(x, y, Game)->OCCUPIED_FLAG = false; // set occupied to false
		Game->getField(x, y, Game)->PlayerID = -1; // set player to none

		Game->getField(EndX, EndX, Game)->PlayerID = Player; // move player on new position
		Game->getField(EndX, EndX, Game)->OCCUPIED_FLAG = true; // set occupied on new position
		return true;
	}
	return false;
}


static bool hasAvaibleMovement(int Player, Game* Game) {
	int i = 0, ii = 0;
	for (i = 0; i < Game->boardDimension.col; ++i) {
		for (ii = 0; ii < Game->boardDimension.row; ++ii) {
			if (!getField(i, ii, Game)->EXISTANCE_FLAG || !getField(i, ii, Game)->OCCUPIED_FLAG ||getField(i, ii, Game)->PlayerID != Player)continue; // we are seraching player's penguins on board
			// if there exist at leastone  move by 1 field then return true 	
			if (i - 1 >= 0) { 
					if (getField(i - 1, ii, Game)->EXISTANCE_FLAG && !getField(i - 1, ii, Game)->OCCUPIED_FLAG)return true;
				}

				if (i - 1 >= 0 && ii + 1 < Game->boardDimension.row) { 
					if (getField(i - 1, ii + 1, Game)->EXISTANCE_FLAG && !getField(i - 1, ii + 1, Game)->OCCUPIED_FLAG)return true;
				}

				if (ii + 1 < Game->boardDimension.row) {
					if (getField(i, ii + 1, Game)->EXISTANCE_FLAG && !getField(i, ii + 1, Game)->OCCUPIED_FLAG)return true;
				}

				if (i + 1 < Game->boardDimension.col) { 
					if (getField(i + 1, ii, Game)->EXISTANCE_FLAG && !getField(i + 1, ii, Game)->OCCUPIED_FLAG)return true;
				}

				if (i + 1 < Game->boardDimension.col && ii - 1 >= 0) { 
					if (getField(i + 1, ii - 1, Game)->EXISTANCE_FLAG && !getField(i + 1, ii - 1, Game)->OCCUPIED_FLAG)return true;
				}
				if (ii - 1 >= 0) { 
					if (getField(i, ii - 1, Game)->EXISTANCE_FLAG && !getField(i, ii - 1, Game)->OCCUPIED_FLAG)return true;
				}

		}
	}
	// if we cheked whole board and by this time we didnt't returned true then return false because there is no avaible movement
	return false;
}
