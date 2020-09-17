/*
 * Server.cpp
 *
 *  Created on: Dec 11, 2017
 *      Author: naveh
 */

#include "../include/Server.h"

using namespace std;
#define MAX_CONNECTED_CLIENTS 10
#define MAX_COMMAND_LEN 20

static void *acceptClients(void *);
static void *handleClient(void *);

Server::Server(int port) : port(port), serverSocket(0), serverThreadId(0) {
	cout << "Server" << endl;
}

void Server::start() {
	// Create a socket point:
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		throw "Error opening socket";
	}

	// Assign a local address:
	struct sockaddr_in serverAddress;
	bzero((void *)&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(port);
	if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
		throw "Error on binding";
	}

	// Start listening:
	listen(serverSocket, MAX_CONNECTED_CLIENTS);
	pthread_create(&serverThreadId, NULL, &acceptClients, (void *)serverSocket);
}

static void * acceptClients(void * socket) {
	long serverSocket = (long)socket;

	// Define client socket structure:
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen;

	while (true) {
		cout << "Waiting for client connection..." << endl;

		// Accept first player:
		int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);

		cout << "Client 1 connected!" << endl;
		if (clientSocket == -1) {
			throw "Error on accept";
		}

		pthread_t threadId;
		pthread_create(&threadId, NULL, &handleClient, (void *)clientSocket);
	}
}

static void * handleClient(void * socket) {
	long clientSocket = (long)socket;
	char commandStr[MAX_COMMAND_LEN];

	long not_stopped = 1;

	while (not_stopped) {
		// Read the command from the socket
		int n = read(clientSocket, commandStr, MAX_COMMAND_LEN);
		if (n == -1) {
			cout << "Error reading command" << endl;
			return NULL;
		}
		cout << "Command recieved:" << commandStr << endl;

		// Split the command string to the command name and the arguments:
		string str(commandStr);
		istringstream iss(str);
		string command;
		iss >> command;
		vector<string> args;
		while (iss) {
			string arg;
			iss >> arg;
			args.push_back(arg);
		}
		try {
			not_stopped = (long)CommandManager::getInstance()->executeCommand(command, args, clientSocket);
		} catch (const char * msg) {
			cout << "Error committing command. Reason:" << msg << endl;
		}
	}
	close(clientSocket);
	return NULL;
}

void Server::stop() {
	pthread_cancel(serverThreadId);
	close(serverSocket);
	cout << "Server Stopped" << endl;
}
