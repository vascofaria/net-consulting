CFLAGS= -std=c++11 -g

Graph.o: Graph.cpp Graph.h Net.h
	g++ $(CFLAGS) -c Graph.cpp

Tarjan.o: Tarjan.cpp Tarjan.h Graph.h Net.h
	g++ $(CFLAGS) -c Tarjan.cpp

NetBreaks.o: NetBreaks.cpp NetBreaks.h Net.h Graph.h Tarjan.h
	g++ $(CFLAGS) -c NetBreaks.cpp

clean:
	rm *.o