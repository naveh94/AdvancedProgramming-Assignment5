#ifndef EX2_AI_H
#define EX2_AI_H

#include "Game.h"
#include "MoveGetter.h"

class AI : public MoveGetter {
public:
    /** Default constructor */
    AI(void * args) : MoveGetter(args), game((Game *)args), x(0), y(0) {}
    /** Default destructor */
    ~AI() {}
    void getMove(vector<Point> availableMoves) { calculateBestMove(availableMoves); }
    Point sendMove() const { return Point(x,y); }

protected:

private:
    /**
     * Get a vector of available moves, and check for each of them which move
     * will result in other player having less successful moves.
     * Will set x and y to be the best move currently available.
     * @param available_moves vector of available moves.
     * @return 0 if everything went fine. 1 if something went wrong.
     */
    void calculateBestMove(vector<Point> available_moves);
    Game *game;
    int x;
    int y;
};


#endif //EX2_AI_H
