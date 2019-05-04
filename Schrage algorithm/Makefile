CXXFLAGS = -pedantic -Wall -std=c++1z

__START__: Schrage_algorithm.exe
	./Schrage_algorithm.exe

Schrage_algorithm.exe: main.o Schrage_algorithm.o Task.o
	g++ -o Schrage_algorithm.exe main.o Schrage_algorithm.o Task.o

main.o: main.cpp 	
	g++ -c ${CXXFLAGS} main.cpp

Schrage_algorithm.o: Schrage_algorithm.cpp Schrage_algorithm.hpp
	g++ -c ${CXXFLAGS} Schrage_algorithm.cpp 

Task.o: Task.cpp Task.hpp
	g++ -c ${CXXFLAGS} Task.cpp 

clean:
	rm -f *.o *.exe