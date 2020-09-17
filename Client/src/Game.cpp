#include "../include/Game.h"

#include "../include/AI.h"

Game::Game()
{
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    board = new Board(width,height);
    board->setMark(width / 2 , height / 2 + 1, BLACK_PLAYER);
    board->setMark(width / 2 + 1, height / 2, BLACK_PLAYER);
    board->setMark(width / 2 , height / 2, WHITE_PLAYER);
    board->setMark(width / 2  + 1, height / 2 + 1, WHITE_PLAYER);
    current_turn = BLACK_PLAYER;
    this->available_moves.reserve(width * height);
}

Game::Game(Game &src)
{
    board = new Board(src.getBoard());
    current_turn = src.getTurn();
    this->available_moves.reserve(board->getWidth() * board->getHeight());
}

Game::~Game()
{
}

ostream &operator <<(ostream &out, const Game &game)
{
    out << *game.board;
    return out;
}

int Game::checkMove(Point p) {
	int sum = 0,temp;
	if (this->board->getMark(p.getX(), p.getY()) != BLANK) {
		return 0;
	}
	string directions[8] = {"n", "ne", "e", "se", "s", "sw", "w", "nw" };
	for (int i = 0; i < 8; i++) {
		temp = checkDirection(p, directions[i], false);
		if (temp > 0) {
			sum += temp;
		}
	}
	return sum;
}

int Game::checkDirection(Point p, string dir, bool flip) {
	Point pdir = p.goDirection(dir);
	char mark = board->getMark(pdir.getX(),pdir.getY());
	if (mark == BLANK || mark == BORDER)
	{
		return -99;
	}
	int flippables = 0;
	if (mark != current_turn)
	{
		flippables = 1 + checkDirection(pdir, dir, flip);
	}
	if ((flippables > 0) && flip)
	{
		board->setMark(pdir.getX(), pdir.getY(), current_turn);
	}
	return flippables;
}

int Game::updateAvailableMoves()
{
    vector<Point> temp_v;
    int temp_max = 0, temp;
    for (int i = 1; i < this->board->getHeight() + 1; i++) {
        for (int j = 1; j < this->board->getWidth() + 1; j++) {
        	Point move(i,j);
        	temp = checkMove(move);
            if (temp) {
                if (temp > temp_max) {
                    temp_max = temp;
                }
			temp_v.push_back(move);
            }
        }
    }
    available_moves = temp_v;
    return temp_max;
}

bool Game::playTurn(Point move, bool print)
{
	if (checkMove(move) == 0) {
		return false;
	}
    if (print) {
		cout << "Player " << board->markToChar(this->current_turn) << " played:";
		cout << move << endl;
    }

    this->board->setMark(move.getX(), move.getY(), current_turn);

    string directions[8] = {"n", "ne", "e", "se", "s", "sw", "w", "nw"};
	for (int i = 0; i < 8; i++) {
		checkDirection(move, directions[i], true);
	}
    return true;
}

int Game::playSession(MoveGetter &player1, MoveGetter &player2) {
	bool player1_got_moves = true;
	bool player2_got_moves = true;

	while (true) {
		printBoard();
		updateAvailableMoves(); // Update available moves vector.

		// If no moves available for both players:
		if (!player1_got_moves && !player2_got_moves) {
			break;
		}

		// If no moves available for current player, start counting players without turns
		// and switch to the other player.
		if (available_moves.size() == 0) {
			if (current_turn == BLACK_PLAYER) {
				player1_got_moves = false;
			} else {
				player2_got_moves = false;
			}
			cout << "You got no available moves." << endl;
			switchTurn();
			continue;
		}
		// If there are available moves for one of the players, reset counter.

		if (current_turn == BLACK_PLAYER) {
			player1.getMove(available_moves);
			Point move = player1.sendMove();
			player1_got_moves = true;
			playTurn(move, true);
		} else {
			player2.getMove(available_moves);
			Point move = player2.sendMove();
			player2_got_moves = true;
			playTurn(move, true);
		}

		this->switchTurn();
	}
	cout << "No moves left for both players. Game Over!" << endl;
	return gameOver();
}


int Game::playNetMultiplayer() {
	// 1. Connect to server:
	string ip;
	int port;
	try {
		ReadConfig config("conf.txt");
		ip = config.getIP();
		port = config.getPort();
	} catch(const char *msg) {
		cout << "Error: " << msg << endl;
		return -1;
	}
	Client client(ip.c_str(), port);
	try {
		client.connectToServer();
	} catch (const char *msg) {
		cout << "Failed to connect to server. Reason: " << msg << endl;
		return -1;
	}

	int choice = 0;
	// 2. Get command from player (start game, get list, join game):
	while (true) {
		cout << "Please enter the number of your choice:" << endl
				<< "1 - Create a new game on the server." << endl
				<< "2 - Join an existing game on the server from a list" << endl
				<< "3 - Return to main menu" << endl;
		cin >> choice;
		if (choice < 1 || choice > 3) {
			cout << "Not an available choice." << endl;
		} else {
			break;
		}
	}

	// If player want to start a new game on server:
	if (choice == 1) {
		string name;
		int result;
		cout << "Please enter the name for the new game:" << endl;
		while (true) {
			cin >> name;
			try {
				result = client.startGame(name);
			} catch(const char *msg) {
				cout << "Failed starting game. Reason: " << msg << endl;
				return -1;
			}
			if (result == 0) {
				break;
			} else {
				cout << "Name already exists. Please choose another:" << endl;
			}
		}
	} else if (choice == 2) {
		string name;
		int result;
		cout << "List of games currently on the server:" << endl;
		client.getListOfGames();
		cout << "Choose the name of the server you want to join:" << endl;
		while (true) {
			cin >> name;
			try {
				result = client.joinGame(name);
			} catch(const char *msg) {
				cout << "Failed joining game. Reason: " << msg << endl;
				return -1;
			}
			if (result == 0) {
				break;
			} else {
				cout << "This server doesn't accept players. Please choose another:" << endl;
			}
		}
	} else {
		return 0;
	}

    // 3. Set player turn according to his choice (player1 if created game, player2 if joined):
	int playerTurn = (choice == 1) ? BLACK_PLAYER : WHITE_PLAYER;
	current_turn = BLACK_PLAYER;

	// wait for game to start:
	client.recieveTurnAnnouncement();

	// 4. Start the game:
    int turns_without_moves = 0;
    while (true) {
    	printBoard();
		updateAvailableMoves();

		// If it's been 2 turns without a move already, the game is over.
		// Tell server we are done, and finish the game.
		if (turns_without_moves >= 2) {
			client.closeGame();
		}

        // If this is current player turn:
        if (current_turn == playerTurn) {
			// If no moves available, skip your turn; (assume both players are on same game)
			if (available_moves.size() == 0) {
				turns_without_moves++;
				cout << "You got no available moves." << endl;
				switchTurn();
				continue;
			}
			turns_without_moves = 0;
			Player p(NULL);
			p.getMove(available_moves);
			Point move = p.sendMove();
			try {
				client.sendMove(move);
			} catch (const char *msg) {
				cout << "Error on sending move to server. Reason: " << msg << endl;
				try {
					client.closeGame();
				} catch (const char * msg2) {
					cout << "Error closing the game. Reason: " << msg2 << endl;
				}
				return -1;
			}
			playTurn(move, true);

        } else {
        	if (available_moves.size() == 0) {
				// If opponent have no available moves, don't wait for receiving a move.
        		turns_without_moves++;
        		switchTurn();
				continue;
        	}
        	turns_without_moves = 0;
        	Point move;
        	try {
				move = client.recieveMove();
        	} catch (const char *msg) {
        		cout << "Error recieving move from server. Reason: " << msg << endl;
        		try {
					client.closeGame();
        		} catch (const char * msg2) {
        			cout << "Error closing the game. Reason: " << msg2 << endl;
        		}
        		return -1;
        	}
        	playTurn(move, true);
        }
		switchTurn();
    }
    cout << "No moves left for both players. Game Over!" << endl;
    try {
		client.closeGame();
	} catch (const char * msg2) {
		cout << "Error closing the game. Reason: " << msg2 << endl;
	}
    return gameOver();
}

int Game::gameOver()
{
    int player_x_score = getCurrentScore(BLACK_PLAYER);
    int player_o_score = getCurrentScore(WHITE_PLAYER);
    if (player_o_score > player_x_score)
    {
        cout << "Player O wins with a score of " << player_o_score << "!" << endl;
        return WHITE_PLAYER;
    }
    if (player_x_score > player_o_score)
    {
        cout << "Player X wins with a score of " << player_x_score << "!" << endl;
        return BLACK_PLAYER;
    }
    cout << "The game ends with a tie with a score of " << player_o_score << "." << endl;
    return 0;
}

int Game::getCurrentScore(int player) {
    int white_player_coins = 0, black_player_coins = 0, white_player_score, black_player_score;
    for (int i = 1; i <= board->getHeight(); i++)
    {
        for (int j = 1; j <= board->getWidth(); j++)
        {
            if (board->getMark(i,j) == WHITE_PLAYER)
            {
                white_player_coins++;
            }
            if (board->getMark(i,j)== BLACK_PLAYER)
            {
                black_player_coins++;
            }
        }
    }
    black_player_score = black_player_coins - white_player_coins;
    white_player_score = white_player_coins - black_player_coins;
    // If given player is Black Player, returns his score, else returns white player score.
    return (player == BLACK_PLAYER) ? black_player_score : white_player_score;
}

void Game::printBoard() {
	cout << "Current turn: " << this->board->markToChar(this->current_turn) << endl;
	cout << "Current board:" << endl << *this << endl;
}
