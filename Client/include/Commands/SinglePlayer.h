/*
 * SinglePlayer.h
 *
 *  Created on: Jan 1, 2018
 *      Author: naveh
 */

#ifndef INCLUDE_COMMANDS_SINGLEPLAYER_H_
#define INCLUDE_COMMANDS_SINGLEPLAYER_H_

#include "Command.h"

class SinglePlayer: public Command {
public:
	virtual void execute(Game &game) {
		Player p(NULL);
		AI ai((void *) &game);
		game.playSession(p, ai);
	}
};

#endif /* INCLUDE_COMMANDS_SINGLEPLAYER_H_ */
