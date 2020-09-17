/**
 * @name: Naveh Marchoom
 * @exercise: Ex3
 * @ID: 312275746
 */

#include <iostream>
#include "include/Game.h"
#include "include/CommandManager.h"

using namespace std;

int main()
{
    string command;
    Game game;
    CommandManager comm;
    comm.executeCommand("help", game);
    while (true) {
		cout << "Please enter a command:" << endl;
        cin >> command;
        if (command.compare("exit") == 0) {
        	break;
        }
        if (comm.isCommandExist(command)) {
        	cin.ignore(); // Clear the buffer.
        	comm.executeCommand(command, game);
        } else {
        	cout << "Unrecognized Command." << endl;
        }
    }
	cout << "Goodbye!" << endl;
    return 0;
}
