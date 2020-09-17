/*
 * NetworkMultiplayer.h
 *
 *  Created on: Jan 1, 2018
 *      Author: naveh
 */

#ifndef INCLUDE_COMMANDS_NETWORKMULTIPLAYER_H_
#define INCLUDE_COMMANDS_NETWORKMULTIPLAYER_H_


#include "Command.h"

class NetworkMultiplayer: public Command {
public:
	virtual void execute(Game &game) {
		game.playNetMultiplayer();
	}
};

#endif /* INCLUDE_COMMANDS_NETWORKMULTIPLAYER_H_ */
