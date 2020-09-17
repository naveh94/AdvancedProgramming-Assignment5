/*
 * Client.h
 *
 *  Created on: Dec 11, 2017
 *      Author: naveh
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include "Point.h"
#define GAMESTATE_NO_MOVES_AVAILABLE 0
#define GAMESTATE_MOVES_AVAILABLE 1
#define GAMESTATE_GAME_OVER -1
#define MAX_COMMAND_LEN 20

class Client {
public:
	Client(const char *serverIP, int serverPort);
	void connectToServer();

	int startGame(string name);
	int joinGame(string name);
	void getListOfGames();
	void closeGame();
	void sendGamestate(int gamestate);
	void sendMove(Point move);

	Point recieveMove();
	int recievePlayerTurn();
	int recieveTurnAnnouncement();

private:
	string gameName;
	const char *serverIP;
	int serverPort;
	int clientSocket;
};

#endif /* CLIENT_H_ */
