/*
 * CommandManager.cpp
 *
 *  Created on: Jan 1, 2018
 *      Author: naveh
 */

#include "../include/CommandManager.h"

CommandManager::CommandManager() {
	commandMap["local"] = new LocalMultiplayer();
	commandMap["network"] = new NetworkMultiplayer();
	commandMap["single"] = new SinglePlayer();
	commandMap["help"] = new HelpCommand();
}

CommandManager::~CommandManager() {
	map<string, Command *>::iterator it;
	for (it = commandMap.begin(); it!=commandMap.end(); it++) {
		delete it->second;
	}
}

void CommandManager::executeCommand(string command, Game &game) {
	Command *commandObj = commandMap[command];
	commandObj->execute(game);
}

bool CommandManager::isCommandExist(string command) {
	if (commandMap.find(command) == commandMap.end()) {
		return false;
	}
	return true;
}
