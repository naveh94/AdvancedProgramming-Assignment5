/*
 * Server.h
 *
 *  Created on: Dec 11, 2017
 *      Author: naveh
 */

#ifndef SERVER_H_
#define SERVER_H_
#define GAMESTATE_NO_MOVES_AVAILABLE 0
#define GAMESTATE_MOVES_AVAILABLE 1
#define GAMESTATE_GAME_OVER -1
#define BLACK_PLAYER -1
#define WHITE_PLAYER 1

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "CommandManager.h"
#include "Point.h"
#include "GameList.h"

class Server {
public:
	Server(int port);
	void start();
	void stop();

private:
	int port;
	int serverSocket;
	pthread_t serverThreadId;

	void sendTurn(int clientSocket, int turn);

	void handleClients(int player1Socket, int player2Socket);

	/**
	 * Gets the current game's state from current player:
	 * 1 - Player has moves, and about to send them.
	 * 0 - Player don't have any moves.
	 * -1 - Game is over. Player disconnect.
	 */
	int getGamestate(int clientSocket);
	/**
	 * Get current move from player, and return it as a point.
	 */
	Point getMove(int clientSocket);
	/**
	 * Send other player's move to current player.
	 */
	void sendMove(int clientSocket, Point prevMove);

	/**
	 * Announce a player it is his turn, and we are waiting for his move.
	 */
	void announceTurn(int clientSocket);

};

#endif /* SERVER_H_ */
