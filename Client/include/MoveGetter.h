/*
 * MoveGetter.h
 *
 *  Created on: Jan 3, 2018
 *      Author: naveh
 */

#ifndef INCLUDE_MOVEGETTER_H_
#define INCLUDE_MOVEGETTER_H_


class MoveGetter {
public:
	MoveGetter(void *) {}
	virtual ~MoveGetter() {};
	virtual void getMove(vector<Point> availableMoves) = 0;
	virtual Point sendMove() const = 0;

};




#endif /* INCLUDE_MOVEGETTER_H_ */
