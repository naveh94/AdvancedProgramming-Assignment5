/*
 * StartGame.h
 *
 *  Created on: Jan 2, 2018
 *      Author: naveh
 */

#ifndef INCLUDE_COMMANDS_STARTCOMMAND_H_
#define INCLUDE_COMMANDS_STARTCOMMAND_H_

#include "Command.h"
#include "../GameList.h"


class StartCommand: public Command {
public:
	StartCommand() {}
	virtual void *execute(vector<string> args, int socket = 0) {
		GameList *gl = GameList::getInstance();
		if (gl->createNewGame(args.at(0), socket)) {
			return (void *) 1;
		}
		return (void *)-1;
	}
};

#endif /* INCLUDE_COMMANDS_STARTCOMMAND_H_ */
