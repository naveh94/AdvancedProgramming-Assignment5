/*
 * GameInfo.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: naveh
 */

#include "../include/GameInfo.h"
#define MAX_COMMAND_LEN 20

GameInfo::GameInfo(string name, int socket) :
name(name), player1socket(socket), player2socket(0), gameStatus(waitingPlayers) {
	cout << "Created new game: '" << name << "'." << endl;
}

bool GameInfo::operator ==(const GameInfo &g) {
	return (name == g.name && player1socket == g.player1socket && player2socket == g.player2socket);
}

void GameInfo::joinGame(int socket) {
	player2socket = socket;
	// Announcing players the game started:
	int startNotice = 0;
	int n = write(player1socket, &startNotice, sizeof(int));
	if (n == -1) {
		throw "Error sending start notice to client";
	}
	n = write(player2socket, &startNotice, sizeof(int));
	if (n == -1) {
		throw "Error sending start notice to client";
	}
	gameStatus = full;
}

void GameInfo::sendMove(Point move, int socket) {
	ostringstream oss;
	int acceptance = 0;
	oss << move.getX() << " " << move.getY();
	string comm = oss.str();
	const char * command = comm.c_str();
	if (socket == player1socket) {
		int n = write(player2socket, command, MAX_COMMAND_LEN);
		if (n == -1) {
			throw "Error sending move to player 2 on game: " + name;
		}
		n = write(player1socket, &acceptance, sizeof(int));
		if (n == -1) {
			throw "Error sending acceptance to player 1 on game: " + name;
		}
	} else {
		int n = write(player1socket, command, MAX_COMMAND_LEN);
		if (n == -1) {
			throw "Error sending move to player 1 on game: " + name;
		}
		n = write(player2socket, &acceptance, sizeof(int));
		if (n == -1) {
			throw "Error sending acceptance to player 2 on game: " + name;
		}
	}
}

void GameInfo::closeGame(int socket) {
	if (socket == player1socket) {
		cout << "Player 1 closed the game '" << name << "'." << endl;
	} else {
		cout << "Player 2 closed the game '" << name << "'." << endl;
	}
}
