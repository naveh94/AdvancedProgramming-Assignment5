#ifndef BOARD_H
#define BOARD_H

#include "Block.h"

class Board
{
    public:
        /** Default constructor */
        Board(int height, int width);
        /**
         * Copy constructor
         * @param src Source of the copy
         */
        Board(const Board &src);
        /** Default destructor */
        ~Board();

        /** Access height
         * @return The current value of height
         */
        int getHeight() const { return height; }

        /** Access width
         * @return The current value of width
         */
        int getWidth() const { return width; }

        /**
         * Get the mark on block (i,j) on the board.
         * @param i parameter
         * @param j parameter
         * @return mark
         */
        int getMark(int i, int j) const { return this->board[i][j]->getMark(); }

        /**
         * Set the mark for block (i,j) on the board.
         * @param i parameter
         * @param j parameter
         * @param mark would be changed to
         */
        void setMark(int i, int j, int mark) { this->board[i][j]->setMark(mark); }

        /**
         * translate mark the a char:
         * WHITE_PLAYER = 1 = 'O'.
         * BLACK_PLAYER = -1 = 'X'.
         * anything else will return ' '.
         * @param mark would be translated from
         * @return character.
         */
        char markToChar(int mark) const;

        /**
         * A representation of the board for cout.
         * show the board with a table not including border blocks.
         * @param out output
         * @param bor input
         * @return out
         */
        friend ostream& operator <<(ostream& out, const Board &bor);
    protected:

    private:
        int height;
        int width;
        Block ***board;
};

#endif // BOARD_H
