/*
 * CommandManager.cpp
 *
 *  Created on: Jan 3, 2018
 *      Author: naveh
 */

#include "../include/CommandManager.h"


CommandManager* CommandManager::instance = 0;
pthread_mutex_t CommandManager::lock;

CommandManager* CommandManager::getInstance() {
	if (instance == 0) {
		pthread_mutex_lock(&lock);
		if (instance == 0) {
			instance = new CommandManager();
		}
		pthread_mutex_unlock(&lock);
	}
	return instance;
}

CommandManager::CommandManager() {
	commandsMap["exit"] = new ExitCommand();
	commandsMap["play"] = new PlayMoveCommand();
	commandsMap["list_games"] = new PrintListCommand();
	commandsMap["start"] = new StartCommand();
	commandsMap["join"] = new JoinCommand();
	commandsMap["close"] = new CloseCommand();
}

void * CommandManager::executeCommand(string command, vector<string> args, int socket) {
	Command *commandObj = commandsMap[command];
	return commandObj->execute(args, socket);
}

CommandManager::~CommandManager() {
	map<string, Command*>::iterator it = commandsMap.begin();
	for (; it!=commandsMap.end(); it++) {
		delete it->second;
	}
}
