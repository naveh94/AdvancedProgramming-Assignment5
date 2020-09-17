/*
 * Client.cpp
 *
 *  Created on: Dec 11, 2017
 *      Author: naveh
 */

#include "../include/Client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

Client::Client(const char *serverIP, int serverPort) : serverIP(serverIP),
		serverPort(serverPort), clientSocket(0) {
	cout << "Client" << endl;
	cout << "IP: " << serverIP << " port:" << serverPort << endl;
}

void Client::connectToServer() {
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1) {
		throw "Error opening socket";
	}

	struct in_addr address;
	if (!inet_aton(serverIP, &address)) {
		throw "Can't parse IP address.";
	}

	struct hostent *server;
	server = gethostbyaddr((const void *)&address, sizeof(address), AF_INET);
	if (server == NULL) {
		throw "Host is unreachable";
	}

	struct sockaddr_in serverAddress;
	bzero((char *)&address, sizeof(address));

	serverAddress.sin_family = AF_INET;
	memcpy((char *)&serverAddress.sin_addr.s_addr, (char *)server->h_addr, server->h_length);

	serverAddress.sin_port = htons(serverPort);

	if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
		throw "Error connecting to server";
	}
	cout << "Connected to server.";
}

void Client::getListOfGames() {
	const char * command = "list_games";
	const char * endofstream = "eos";
	char buffer[MAX_COMMAND_LEN];
	int n = write(clientSocket, command, MAX_COMMAND_LEN);
	if (n == -1) {
		throw "Error sending 'list_games' command to server";
	}
	n = read(clientSocket, buffer, MAX_COMMAND_LEN);
	if (n == -1) {
		throw "Error reading list of games from server";
	}
	while (strcmp(buffer,endofstream) != 0) {
		cout << buffer << endl;
		n = read(clientSocket, buffer, MAX_COMMAND_LEN);
		if (n == -1) {
			throw "Error reading list of games from server";
		}
	}
}

void Client::closeGame() {
	ostringstream oss;
	oss << "close " << gameName;
	string comm = oss.str();
	const char * command = comm.c_str();
	int n = write(clientSocket, command, MAX_COMMAND_LEN);
	if (n == -1) {
		throw "Error closing the game.";
	}
}

int Client::startGame(string name) {
	ostringstream oss;
	int result;
	oss << "start " << name;
	string comm = oss.str();
	const char * command = comm.c_str();
	cout << "Sending: " << command << endl;
	int n = write(clientSocket, command, MAX_COMMAND_LEN);
	if (n == -1) {
		throw "Error sending start command to server";
	}
	n = read(clientSocket, &result, sizeof(result));
	if (n == -1) {
		throw "Error recieving result from server";
	}
	if (result == -1) {
		return -1;
	}
	gameName = name;
	return 0;
}

int Client::joinGame(string name) {
	ostringstream oss;
	int result;
	oss << "join " << name;
	string comm = oss.str();
	const char * command = comm.c_str();
	int n = write(clientSocket, command, MAX_COMMAND_LEN);
	if (n == -1) {
		throw "Error sending start command to server";
	}
	n = read(clientSocket, &result, sizeof(result));
	if (n == -1) {
		throw "Error recieving result from server";
	}
	if (result == -1) {
		return -1;
	}
	gameName = name;
	return 0;
}

void Client::sendMove(Point move) {
	int x = move.getX(), y = move.getY(), acceptance = -1;
	ostringstream oss;
	oss << "play " << x << " " << y;
	string comm = oss.str();
	const char * command = comm.c_str();
	int n = write(clientSocket, command, MAX_COMMAND_LEN);
	if (n == -1) {
		throw "Error writing x to server";
	}
	n = read(clientSocket, &acceptance, sizeof(int));
	if (n == -1) {
		throw "Error reading acceptance from server";
	}
	if (acceptance != 0) {
		throw "Error accepting move on server";
	}
}

Point Client::recieveMove() {
	int x, y;
	char command[MAX_COMMAND_LEN];
	int n = read(clientSocket, command, MAX_COMMAND_LEN);
	if (n == -1) {
		throw "Error reading move from server";
	}
	istringstream iss(command);
	iss >> x >> y;
	return Point(x, y);
}

int Client::recieveTurnAnnouncement() {
	int announce, n;
	n = read(clientSocket, &announce, sizeof(announce));
	if (n == -1) {
		throw "Error reading turn from server";
	}
	return announce;
}
