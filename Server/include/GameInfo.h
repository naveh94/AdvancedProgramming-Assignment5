/*
 * GameInfo.h
 *
 *  Created on: Jan 4, 2018
 *      Author: naveh
 */

#ifndef INCLUDE_GAMEINFO_H_
#define INCLUDE_GAMEINFO_H_

#include <string>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "Point.h"

using namespace std;

enum Status { waitingPlayers, full };

class GameInfo {
public:
	GameInfo(string name, int socket);
	~GameInfo() {}
	Status getStatus() const { return gameStatus; } // Return the current game's status
	void sendMove(Point move, int socket); // Send a move to the other player.
	void joinGame(int socket); // Join the game (only on 'waiting' status)
	bool operator ==(const GameInfo &g); // return true if g is this GameInfo.
	void closeGame(int socket);
private:
	string name;
	int player1socket;
	int player2socket;
	Status gameStatus;
};

#endif /* INCLUDE_GAMEINFO_H_ */
