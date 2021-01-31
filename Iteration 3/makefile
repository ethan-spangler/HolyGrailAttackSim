hw6: ClientDriver.o Helper.o ThreadManager.o Castle.o Knight.o LoggerClient.o Helper.o SafeQueue.o
	g++ ClientDriver.o Helper.o ThreadManager.o Castle.o Knight.o LoggerClient.o Helper.o SafeQueue.o -o hw6

ClientDriver.o: ClientDriver.cpp Helper.h ThreadManager.h
	g++ -c ClientDriver.cpp

Helper.o: Helper.cpp Helper.h Castle.h Knight.h LoggerClient.have
	g++ -c Helper.cpp

LoggerClient.o: LoggerClient.cpp LoggerClient.h ThreadManager.h Helper.h LogMessage.h
	g++ -c LoggerClient.cpp

ThreadManager.o: ThreadManager.cpp ThreadManager.h SafeQueue.h AttackMessage.h Castle.h LoggerClient.h
	g++ -c ThreadManager.cpp

SafeQueue.o: SafeQueue.cpp SafeQueue.h AttackMessage.h
	g++ -c SafeQueue.cpp

Knight.o: Knight.cpp Knight.h ThreadManager.h AttackMessage.h
	g++ -c Knight.cpp

Castle.o: Castle.cpp Castle.h Knight.h ThreadManager.h AttackMessage.h
	g++ -c Castle.cpp

Helper.o: Helper.cpp Helper.h Castle.h Knight.h LoggerClient.h
	g++ -c Helper.cpp
