/*
 * CloseCommand.h
 *
 *  Created on: Jan 4, 2018
 *      Author: naveh
 */

#ifndef INCLUDE_COMMANDS_CLOSECOMMAND_H_
#define INCLUDE_COMMANDS_CLOSECOMMAND_H_

#include "Command.h"
#include "../GameList.h"

class CloseCommand: public Command {
public:
	CloseCommand() {};
	virtual void *execute(vector<string> args, int socket = 0) {
		GameList *gl = GameList::getInstance();
		gl->removeGame(args.at(0), socket);
		return (void *) 0;
	}
};

#endif /* INCLUDE_COMMANDS_CLOSECOMMAND_H_ */
