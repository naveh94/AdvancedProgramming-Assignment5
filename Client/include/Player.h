/*
 * Player.h
 *
 *  Created on: Jan 3, 2018
 *      Author: naveh
 */

#ifndef INCLUDE_PLAYER_H_
#define INCLUDE_PLAYER_H_

#include <iostream>
#include <vector>
#include "Point.h"
#include "MoveGetter.h"
#include <sstream>

class Player: public MoveGetter {
public:
	Player(void * args): MoveGetter(args), x(0), y(0) {}
	~Player() {}
	void getMove(vector<Point> availableMoves);
	Point sendMove() const { return Point(x,y); }

private:
	void printAvailableMoves(vector<Point> availableMoves);
	int x;
	int y;
};

#endif /* INCLUDE_PLAYER_H_ */
