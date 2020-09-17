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
	string getIP() const { return ip; }


private:
	int port;
	string ip;
};

#endif /* INCLUDE_READCONFIG_H_ */
