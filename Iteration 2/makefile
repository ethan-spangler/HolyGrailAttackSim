hw4: main.o Log.o Knight.o Castle.o Helper.o PipeManager.o
	g++ main.o Log.o Knight.o Castle.o Helper.o PipeManager.o -o hw4

main.o: main.cpp Log.h Helper.h Castle.h Knight.h PipeManager.h
	g++ -c main.cpp

Log.o: Log.cpp Log.h PipeManager.h Helper.h
	g++ -c Log.cpp

Knight.o: Knight.cpp Knight.h PipeManager.h Helper.h
	g++ -c Knight.cpp

Castle.o: Castle.cpp Castle.h Knight.h PipeManager.h Helper.h
	g++ -c Castle.cpp

Helper.o: Helper.cpp Helper.h
	g++ -c Helper.cpp
	
PipeManager.o: PipeManager.cpp PipeManager.h AttackMessage.h
	g++ -c PipeManager.cpp