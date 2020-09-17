/*
 * CommandManager.h
 *
 *  Created on: Jan 3, 2018
 *      Author: naveh
 */

#ifndef COMMANDMANAGER_H_
#define COMMANDMANAGER_H_

#include <pthread.h>
#include <map>

#include "Commands/Command.h"
#include "Commands/ExitCommand.h"
#include "Commands/StartCommand.h"
#include "Commands/PrintListCommand.h"
#include "Commands/CloseCommand.h"
#include "Commands/JoinCommand.h"
#include "Commands/PlayMoveCommand.h"


class CommandManager {
public:
	static CommandManager* getInstance();
	void * executeCommand(string command, vector<string> args, int socket = 0);

private:
	CommandManager();
	CommandManager(const CommandManager &);
	~CommandManager();
	static CommandManager* instance;
	static pthread_mutex_t lock;

	map<string, Command *> commandsMap;
};

#endif /* COMMANDMANAGER_H_ */
