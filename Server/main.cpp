/*
 * main.cpp
 *
 *  Created on: Dec 11, 2017
 *      Author: naveh
 */
#include "include/Server.h"
#include <iostream>
#include <stdlib.h>
#include "include/ReadConfig.h"
using namespace std;

int main() {
	int port;
	try {
		ReadConfig config("conf.txt");
		port = config.getPort();
	} catch(char* msg) {
		cout << "Error: " << msg << endl;
		return 1;
	}
	Server server(port);
	try {
		server.start();
		cout << "Enter exit to stop server " << endl;
		string str;
		while (true) {
			cin >> str;
			if (str == "exit") {
				server.stop();
				return 0;
			}
		}
	} catch (const char *msg) {
		cout << "Cannot start server. Reason: " << msg << endl;
		return -1;
	}
	return 0;
}
