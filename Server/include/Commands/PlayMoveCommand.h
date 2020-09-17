/*
 * PlayMoveCommand.h
 *
 *  Created on: Jan 4, 2018
 *      Author: naveh
 */

#ifndef INCLUDE_COMMANDS_PLAYMOVECOMMAND_H_
#define INCLUDE_COMMANDS_PLAYMOVECOMMAND_H_

#include "Command.h"
#include "../GameList.h"

class PlayMoveCommand: public Command {
public:
	PlayMoveCommand() {};
	virtual void *execute(vector<string> args, int socket = 0) {
		GameList *gl = GameList::getInstance();
		int x, y;
		istringstream issx(args[0]);
		issx >> x;
		istringstream issy(args[1]);
		issy >> y;
		try {
			gl->sendMove(Point(x,y), socket);
		} catch(const char * msg) {
			cout << "Error:" << msg << endl;
			return (void *) -1;
		}
		return (void *) 1;
	}
};

#endif /* INCLUDE_COMMANDS_PLAYMOVECOMMAND_H_ */
