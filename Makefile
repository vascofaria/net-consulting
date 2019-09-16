CFLAGS= -std=c++11 -g

OBJECT1= main.o lib/Graph.o lib/Tarjan.o lib/NetBreaks.o

project-file: $(OBJECT1)
	(cd lib; make; cd ..)
	g++ $(CFLAGS) -o NetConsulting $(OBJECT1) 

main.o: main.cpp lib/Graph.h lib/Tarjan.h  lib/NetBreaks.h lib/Net.h
	g++ $(CFLAGS) -c main.cpp

clean:
	rm *.o
	(cd lib; make clean;)