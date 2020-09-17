/*
 * ExitCommand.h
 *
 *  Created on: Jan 3, 2018
 *      Author: naveh
 */

#ifndef COMMANDS_EXITCOMMAND_H_
#define COMMANDS_EXITCOMMAND_H_


#include "Command.h"

class ExitCommand: public Command {
public:
	ExitCommand() {}
	virtual void *execute(vector<string> args, int socket = 0) {
	return (void *) 0;
	}
};


#endif /* COMMANDS_EXITCOMMAND_H_ */
