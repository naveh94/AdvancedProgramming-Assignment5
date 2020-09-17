/*
 * PrintListCommand.h
 *
 *  Created on: Jan 4, 2018
 *      Author: naveh
 */

#ifndef INCLUDE_COMMANDS_PRINTLISTCOMMAND_H_
#define INCLUDE_COMMANDS_PRINTLISTCOMMAND_H_

#include "Command.h"
#include "../GameList.h"

class PrintListCommand: public Command {
public:
	PrintListCommand() {};
	virtual void *execute(vector<string> args, int socket = 0) {
		GameList *gl = GameList::getInstance();
		gl->printWaitingGames(socket);
		return (void *) 1;
	}
};

#endif /* INCLUDE_COMMANDS_PRINTLISTCOMMAND_H_ */
