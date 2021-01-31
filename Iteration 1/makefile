hw2: main.o Log.o Knight.o Castle.o Helper.o
	g++ main.o Log.o Knight.o Castle.o Helper.o -o hw2

main.o: main.cpp Log.h Helper.h Castle.h Knight.h
	g++ -c main.cpp

Log.o: Log.cpp Log.h
	g++ -c Log.cpp

Knight.o: Knight.cpp Knight.h Helper.h
	g++ -c Knight.cpp

Castle.o: Castle.cpp Castle.h
	g++ -c Castle.cpp

Helper.o: Helper.cpp Helper.h
	g++ -c Helper.cpp