/*
 * Command.h
 *
 *  Created on: Jan 1, 2018
 *      Author: naveh
 */

#ifndef INCLUDE_COMMAND_H_
#define INCLUDE_COMMAND_H_

#include <vector>
#include <string>
#include "../Game.h"
#include "../Player.h"
#include "../AI.h"

using namespace std;

class Command {
public:
	virtual void execute(Game &game) = 0;
	virtual ~Command() {}
};


#endif /* INCLUDE_COMMAND_H_ */
