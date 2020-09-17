/*
 * Player.cpp
 *
 *  Created on: Jan 3, 2018
 *      Author: naveh
 */

#include "../include/Player.h"

void Player::getMove(vector<Point> availableMoves) {
	int xinput, yinput;
	char comma;
	char buffer[256];
	printAvailableMoves(availableMoves);
	while (true) {
		cout << "Please enter your move <x>,<y> (e.g. 4,5):" << endl;
		cin.getline(buffer, 256);
		istringstream iss(buffer);
		iss >> xinput >> comma >> yinput;
		Point move(xinput, yinput);
		for (size_t i = 0; i < availableMoves.size(); i++) {
			if (move == availableMoves.at(i)) {
				x = xinput;
				y = yinput;
				return;
			}
		}
		cout << "Move not available." << endl;
	}
}

void Player::printAvailableMoves(vector<Point> availableMoves) {
	// Prints all available moves:
	cout << "You got " << availableMoves.size() << " available Moves: " << endl;
	for (size_t i = 0; i < availableMoves.size(); i++) {
		cout << availableMoves.at(i);
		if (i < availableMoves.size() - 1) {
			cout << ", ";
		}
	}
	cout << endl;
}
