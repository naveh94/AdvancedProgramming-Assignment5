/*
 * JoinCommand.h
 *
 *  Created on: Jan 4, 2018
 *      Author: naveh
 */

#ifndef INCLUDE_COMMANDS_JOINCOMMAND_H_
#define INCLUDE_COMMANDS_JOINCOMMAND_H_

#include "Command.h"
#include "../GameList.h"

class JoinCommand: public Command {
public:
	JoinCommand() {};
	virtual void *execute(vector<string> args, int socket = 0) {
		GameList *gl = GameList::getInstance();
		if (gl->joinGame(args.at(0), socket)) {
			return (void *) 1;
		}
		return (void *) -1;
	}
};

#endif /* INCLUDE_COMMANDS_JOINCOMMAND_H_ */
