/*
 * HelpCommand.h
 *
 *  Created on: Jan 1, 2018
 *      Author: naveh
 */

#ifndef INCLUDE_COMMANDS_HELPCOMMAND_H_
#define INCLUDE_COMMANDS_HELPCOMMAND_H_


#include "Command.h"

class HelpCommand: public Command {
public:
	virtual void execute(Game &game) {
		cout << "'single' - Start a single player game against an AI" << endl;
		cout << "'local' - start a multiplayer game against another user on the same computer" << endl;
		cout << "'network' - start a multiplayer game against another user on another computer" << endl;
		cout << "'exit' - exit the game." << endl;
		cout << "'help' - show this list of commands again" << endl;
	}
};


#endif /* INCLUDE_COMMANDS_HELPCOMMAND_H_ */
