#ifndef GAME_H
#define GAME_H

#define DEFAULT_HEIGHT 8
#define DEFAULT_WIDTH 8

#include "Board.h"
#include <string>
#include <vector>
#include "Point.h"
#include "Client.h"
#include <stdlib.h>
#include "ReadConfig.h"
#include "Player.h"
#include "MoveGetter.h"

class Game
{
    public:
        /** Default constructor */
        Game();

        /**
         * Copy constructor
         * @param src source of the copy.
         */
        Game(Game &src);

        /** Default destructor */
        ~Game();

        /**
         * Operator overflow for <<. Will print the board.
         * @param out output
         * @param game input
         * @return out.
         */
        friend ostream& operator <<(ostream& out, const Game &game);


        /**
         * Used by copy constructor for getting current turn.
         * @return current_turn
         */
        int getTurn() { return current_turn; }

        /**
         * Used by AI for calculating best moves.
         * Calculate player score by calculating: player's coins - opposite player's coins
         * @param player the player checked
         * @return player's score.
         */
        int getCurrentScore(int player);

        /**
         * Run all over the board, checking for all available moves for current player.
         * Updates the current_available_moves vector.
         * @return the maximum of coins that can be flipped during this move.
         */
        int updateAvailableMoves();

        /**
         * Used for getting the board by copy constructor only.
         * @return a pointer to the board.
         */
        Board getBoard() const { return *board; }

        int checkMove(Point p);

        int checkDirection(Point p, string dir, bool flip);

        /**
        * Play one turn with given parameters.
        * @param x move parameter
        * @param y move parameter
        * @return 0 if not valid move. 1 if move played.
        */
        bool playTurn(Point move, bool print);

        /**
         * Start a session of gameplay with given MoveGetters as players.
         */
        int playSession(MoveGetter &player1, MoveGetter &player2);

        /**
         * Start a new multiplayer session of the game using the server.
         * @return 1 for game won, and 0 for game lost.
         */
        int playNetMultiplayer();

        /**
         * Determine winning player by counting coins on board.
         * @return 1 for White Player, -1 for Black Player, 0 for tie.
         */
        int gameOver();

    protected:

    private:
        Board *board;
        int current_turn;
        vector<Point> available_moves;
        void printBoard();
        void switchTurn() { this->current_turn *= (-1); }
};

#endif // GAME_H
