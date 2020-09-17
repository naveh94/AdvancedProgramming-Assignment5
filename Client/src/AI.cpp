#include "../include/AI.h"

void AI::calculateBestMove(vector<Point> available_moves)
{
    int current_score, worst_score, temp;
    Point best_move;

    // Set best to first move.
    best_move = available_moves.at(0);

    // Create a copy of the game in order to check the result of each move.
    Game game_copy(*game);
    game_copy.playTurn(available_moves.at(0), false);
    current_score = game_copy.getCurrentScore(BLACK_PLAYER);
    // updateAvailableMoves() returns the maximum number of coins flipped while calculating
    // available moves for current player. So we set the maximum score of player X to be
    // the sum of Player X's current score, and the maximum of coins flipped on his available
    // moves.
    worst_score = current_score + game_copy.updateAvailableMoves();
    for (size_t i = 1; i < available_moves.size(); i++)
    {
        Game game_copy(*game);
        game_copy.playTurn(available_moves.at(i), false);
        current_score = game_copy.getCurrentScore(BLACK_PLAYER);
        // If on this move, player X's maximum available score is lower than the previous worst
        // score, we would obviously want to keep this move instead.
        temp = current_score + game_copy.updateAvailableMoves();
        if (temp < worst_score)
        {
            worst_score = temp;
            best_move = available_moves.at(i);
        }
    }
    x = best_move.getX();
    y = best_move.getY();
}
