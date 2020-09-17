/*
 * ReadConfig.h
 *
 *  Created on: Dec 25, 2017
 *      Author: naveh
 */

#ifndef INCLUDE_READCONFIG_H_
#define INCLUDE_READCONFIG_H_

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ReadConfig {
public:
	ReadConfig(string fileName);
	int getPort() const { return port; }


private:
	int port;
};

#endif /* INCLUDE_READCONFIG_H_ */
