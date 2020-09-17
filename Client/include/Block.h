#ifndef BLOCK_H
#define BLOCK_H

#define TRUE 1
#define FALSE 0
#define BLACK_PLAYER -1
#define WHITE_PLAYER 1
#define BLANK 0
#define BORDER 2

#include <iostream>
#include "Point.h"

using namespace std;

class Block
{
    public:
        /** Default constructor */
        Block(int x, int y) : x(x), y(y), mark(BLANK) {}
        /** Constructor without variables. Set x, y and mark to 0. */
        Block() : x(0), y(0), mark(BLANK) {}
        /** Default destructor */
        ~Block() {}

        /** Access x
         * @return The current value of x
         */
        int getX() const { return x; }

        /** Access y
         * @return The current value of y
         */
        int getY() const { return y; }

        /** Access x and y
         * @return a point containing both parameters of x and y
         */
        Point getXY() const { return Point(x,y); }

        /**
         * Set mark to m
         * @param m new mark.
         */
        void setMark(int m) { mark = m; }

        /** Access mark
         * @return The current value of mark
         */
        int getMark() { return mark; }

    protected:

    private:
        int x; //!< Member variable "x"
        int y; //!< Member variable "y"
        int mark; //!< Member variable "mark"
};

#endif // BLOCK_H
