#Naveh Marchoom 312275746 Ex4
a.out: main.o Block.o Board.o Game.o Point.o AI.o Client.o CommandManager.o Player.o ReadConfig.o
	g++ main.o Block.o Board.o Game.o Point.o AI.o Client.o CommandManager.o Player.o ReadConfig.o
	
Block.o: src/Block.cpp include/Block.h
	g++ -c src/Block.cpp

Board.o: src/Board.cpp include/Board.h include/Block.h
	g++ -c src/Board.cpp

Game.o: src/Game.cpp include/Game.h include/Board.h include/Point.h include/AI.h
	g++ -c src/Game.cpp

Point.o: src/Point.cpp include/Point.h
	g++ -c src/Point.cpp

AI.o : src/AI.cpp include/AI.h include/Game.h include/Client.h
	g++ -c src/AI.cpp

Client.o : src/Client.cpp include/Client.h include/Point.h
	g++ -c src/Client.cpp

CommandManager.o : src/CommandManager.cpp include/CommandManager.h include/Commands/Command.h include/Commands/HelpCommand.h include/Commands/LocalMultiplayer.h include/Commands/NetworkMultiplayer.h include/Commands/SinglePlayer.h
	g++ -c src/CommandManager.cpp

Player.o : src/Player.cpp include/Player.h include/Point.h include/MoveGetter.h
	g++ -c src/Player.cpp

ReadConfig.o : src/ReadConfig.cpp include/ReadConfig.h
	g++ -c src/ReadConfig.cpp

main.o: main.cpp include/Game.h
	g++ -c main.cpp
