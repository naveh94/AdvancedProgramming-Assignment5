/*
 * Command.h
 *
 *  Created on: Jan 3, 2018
 *      Author: naveh
 */

#ifndef COMMANDS_COMMAND_H_
#define COMMANDS_COMMAND_H_

#include <vector>
#include <string>

using namespace std;

class Command {
public:
	virtual void *execute(vector<string> args, int socket = 0) = 0;
	virtual ~Command() {}
};

#endif /* COMMANDS_COMMAND_H_ */
