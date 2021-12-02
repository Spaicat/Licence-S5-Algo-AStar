all: main.out

main.out: main.o graphe.o sommet.o
	g++ -g -W -Wall main.o graphe.o sommet.o -o main.out

main.o: main.cpp graphe.h sommet.h
	g++ -g -W -Wall -c main.cpp

graphe.o: graphe.h graphe.cpp sommet.h
	g++ -g -W -Wall -c graphe.cpp -o graphe.o

sommet.o: sommet.h sommet.cpp
	g++ -g -W -Wall -c sommet.cpp

clean:
	rm *.o

veryclean: clean
	rm *.out