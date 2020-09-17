#include "../include/Board.h"

Board::Board(int height, int width)
{
    this->height = height;
    this->width = width;
    this->board = new Block**[height + 2];
    for (int i = 0; i < height + 2; i++)
    {
        this->board[i] = new Block*[width + 2];
        for (int j = 0; j < width + 2; j++)
        {
            this->board[i][j] = new Block(i,j);
        }
    }
    for (int i = 0; i < height + 2; i++)
    {
        this->board[i][0]->setMark(BORDER);
        this->board[i][width+1]->setMark(BORDER);
    }
    for (int i = 0; i < width + 2; i++)
    {
        this->board[0][i]->setMark(BORDER);
        this->board[height+1][i]->setMark(BORDER);
    }
}

Board::Board(const Board &src)
{
    this->height = src.getHeight();
    this->width = src.getWidth();
    this->board = new Block**[height + 2];
    for (int i = 0; i < height + 2; i++)
    {
        this->board[i] = new Block*[width + 2];
        for (int j = 0; j < width + 2; j++)
        {
            this->board[i][j] = new Block(i,j);
            this->board[i][j]->setMark(src.getMark(i,j));
        }
    }
}

Board::~Board()
{
   for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            delete this->board[i][j];
        }
        delete[] this->board[i];
    }
    delete[] this->board;
}


ostream &operator <<(ostream &out, const Board &bor)
{
    out << "  ";
    for (int i = 1; i <= bor.getHeight(); i++)
    {
        out << " | " << i;
    }
    out << " |" << endl;
    for (int index = 1; index < bor.getWidth(); index++)
    {
        out << "-----";
    }
    out << endl;
    for (int i = 1; i <= bor.getHeight(); i++)
    {
        out << " " << i;
        for (int j = 1; j <= bor.getWidth(); j++)
        {
            out << " | " << bor.markToChar(bor.getMark(i,j));
        }
        out << " | " << endl;
        for (int index = 1; index < bor.getWidth(); index++)
    {
        out << "-----";
    }
    out << endl;
    }
    return out;
}

char Board::markToChar(int mark) const
{
    if (mark == WHITE_PLAYER) return 'O';
    if (mark == BLACK_PLAYER) return 'X';
    return ' ';
}

