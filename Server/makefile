#Naveh Marchoom 312275746 Ex5
a.out: main.o Server.o ReadConfig.o CommandManager.o GameInfo.o GameList.o Point.o
	g++ main.o Server.o ReadConfig.o CommandManager.o GameInfo.o GameList.o Point.o -pthread
	
Server.o : src/Server.cpp include/Server.h include/Point.h
	g++ -c src/Server.cpp -pthread

ReadConfig.o : src/ReadConfig.cpp include/ReadConfig.h
	g++ -c src/ReadConfig.cpp -pthread

CommandManager.o : src/CommandManager.cpp include/CommandManager.h include/Commands/CloseCommand.h include/Commands/Command.h include/Commands/ExitCommand.h include/Commands/JoinCommand.h include/Commands/PlayMoveCommand.h include/Commands/PrintListCommand.h include/Commands/StartCommand.h
	g++ -c src/CommandManager.cpp -pthread

GameInfo.o : src/GameInfo.cpp include/GameInfo.h include/Point.h
	g++ -c src/GameInfo.cpp -pthread

GameList.o : src/GameList.cpp include/GameList.h include/GameInfo.h
	g++ -c src/GameList.cpp -pthread

Point.o : src/Point.cpp include/Point.h
	g++ -c src/Point.cpp -pthread

main.o: main.cpp include/Server.h
	g++ -c main.cpp -pthread
