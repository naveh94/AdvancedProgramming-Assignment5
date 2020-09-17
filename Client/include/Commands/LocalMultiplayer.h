/*
 * LocalMultiplayer.h
 *
 *  Created on: Jan 1, 2018
 *      Author: naveh
 */

#ifndef INCLUDE_COMMANDS_LOCALMULTIPLAYER_H_
#define INCLUDE_COMMANDS_LOCALMULTIPLAYER_H_


#include "Command.h"

class LocalMultiplayer: public Command {
public:
	virtual void execute(Game &game) {
		Player p(NULL);
		game.playSession(p,p);
	}
};


#endif /* INCLUDE_COMMANDS_LOCALMULTIPLAYER_H_ */
