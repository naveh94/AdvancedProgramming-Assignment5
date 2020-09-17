/*
 * CommandManager.h
 *
 *  Created on: Jan 1, 2018
 *      Author: naveh
 */

#ifndef INCLUDE_COMMANDMANAGER_H_
#define INCLUDE_COMMANDMANAGER_H_

#include <map>
#include "Commands/Command.h"
#include "Commands/LocalMultiplayer.h"
#include "Commands/NetworkMultiplayer.h"
#include "Commands/SinglePlayer.h"
#include "Commands/HelpCommand.h"

class CommandManager {
public:
	CommandManager();
	~CommandManager();
	void executeCommand(string command, Game &game);
	bool isCommandExist(string command);
private:
	map<string, Command *> commandMap;
};

#endif /* INCLUDE_COMMANDMANAGER_H_ */
