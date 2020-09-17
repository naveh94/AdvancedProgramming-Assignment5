/*
 * ReadConfig.cpp
 *
 *  Created on: Dec 25, 2017
 *      Author: naveh
 */

#include "../include/ReadConfig.h"


ReadConfig::ReadConfig(string fileName) {
	string line, port_str, ip_str;
	int port_num;
	ifstream config(fileName.c_str());
	if (!config.is_open()) {
		throw "Can't open file.";
	}
	config >> port_num;
	config >> ip_str;
	config.close();
	port = port_num;
	ip = ip_str;
	return;
}


