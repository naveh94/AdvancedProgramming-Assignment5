/*
 * ReadConfig.cpp
 *
 *  Created on: Dec 25, 2017
 *      Author: naveh
 */

#include "../include/ReadConfig.h"


ReadConfig::ReadConfig(string fileName) {
	int port_num;
	ifstream config(fileName.c_str());
	if (!config.is_open()) {
		throw "Can't open file.";
	}
	config >> port_num;
	config.close();
	port = port_num;
}


