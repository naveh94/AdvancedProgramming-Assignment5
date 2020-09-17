/*
 * GameList.h
 *
 *  Created on: Jan 2, 2018
 *      Author: naveh
 */

#ifndef INCLUDE_GAMELIST_H_
#define INCLUDE_GAMELIST_H_

#include <vector>
#include <string>
#include <iostream>
#include <pthread.h>
#include "GameInfo.h"

using namespace std;

class GameList {
public:
	static GameList* getInstance();
	~GameList();
	bool createNewGame(string gameName, int socket);
	bool joinGame(string gameName, int socket);
	bool removeGame(string gameName, int socket);
	void sendMove(Point move, int socket);
	void printWaitingGames(int socket);

private:

	static GameList* instance;
	static pthread_mutex_t lock;
	GameList();
	bool doesGameExists(string name);
	bool doesSocketExists(int socket);
	Status getGameStatus(string name);
	map<string, GameInfo *> games;
	map<long, GameInfo *> gamesBySocket;
};

#endif /* INCLUDE_GAMELIST_H_ */
