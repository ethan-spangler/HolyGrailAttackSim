LogServer: ServerDriver.o LoggerServer.o
	g++ ServerDriver.o LoggerServer.o -o LogServer

ServerDriver.o: ServerDriver.cpp LoggerServer.h LogMessage.h
	g++ -c ServerDriver.cpp

LoggerServer.o: LoggerServer.cpp LoggerServer.h LogMessage.h
	g++ -c ServerDriver.cpp	