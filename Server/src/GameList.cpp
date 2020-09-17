/*
 * GameList.cpp
 *
 *  Created on: Jan 2, 2018
 *      Author: naveh
 */

#include "../include/GameList.h"
#define MAX_COMMAND_LEN 20

GameList* GameList::instance = 0;
pthread_mutex_t GameList::lock;

GameList* GameList::getInstance() {
	if (instance == 0) {
		pthread_mutex_lock(&lock);
		if (instance == 0) {
			instance = new GameList();
		}
		pthread_mutex_unlock(&lock);
	}
	return instance;
}

GameList::GameList() {
}


bool GameList::createNewGame(string gameName, int socket) {
	int status = 0;
	if (doesGameExists(gameName)) {
		cout << "Game '" << gameName << "' already exists." << endl;
		status = -1;
	}
	games[gameName] = new GameInfo(gameName, socket);
	gamesBySocket[socket] = games[gameName];

	int n = write(socket, &status, sizeof(int));
	if (n == -1) {
		throw "Error sending status in game creation command.";
	}
	return (status == 0) ? true : false;
}

bool GameList::joinGame(string gameName, int socket) {
	int status = 0;
	if (!doesGameExists(gameName)) {
		cout << "Game '" << gameName << "' doesn't exists." << endl;
		status = -1;
	} else if (games[gameName]->getStatus() != waitingPlayers) {
		cout << "Game '" << gameName << "' isn't waiting for players." << endl;
		status = -1;
	} else {
		games[gameName]->joinGame(socket);
		gamesBySocket[socket] = games[gameName];
	}
	int n = write(socket, &status, sizeof(int));
	if (n == -1) {
		throw "Error sending status at game joining command";
	}
	return (status == 0) ? true : false;
}

void GameList::printWaitingGames(int socket) {
	map<string, GameInfo *>::iterator it;
	it = games.begin();
	const char * gameName;
	for (; it != games.end(); it++) {
		if (it->second->getStatus() == waitingPlayers) {
			gameName = it->first.c_str();
			int n = write(socket, gameName, MAX_COMMAND_LEN);
			if (n == -1) {
				throw "Error sending games' list to client.";
			}
		}
		gameName = "eos";
		int n = write(socket, gameName, MAX_COMMAND_LEN);
		if (n == -1) {
			throw "Error sending eos to client";
		}
	}
}

bool GameList::removeGame(string gameName, int socket) {
	if (!doesGameExists(gameName)) {
		return false;
	}
	map<string, GameInfo *>::iterator it;
	for (it = games.begin(); it != games.end(); it++) {
		if (it->first == gameName) {
			break;
		}
	}
	it->second->closeGame(socket);
	games.erase(it);
	return true;
}

bool GameList::doesGameExists(string name) {
	if (games.find(name) == games.end()) {
		return false;
	}
	return true;
}

void GameList::sendMove(Point move, int socket) {
	if (!doesSocketExists(socket)) {
		return;
	}
	gamesBySocket[socket]->sendMove(move, socket);
}

bool GameList::doesSocketExists(int socket){
	if (gamesBySocket.find(socket) == gamesBySocket.end()) {
		return false;
	}
	return true;
}

