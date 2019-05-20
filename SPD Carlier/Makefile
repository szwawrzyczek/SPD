CXXFLAGS = -pedantic -Wall -std=c++1z

__START__: Carlier.exe
	./Carlier.exe

Carlier.exe: main.o Carlier.o 
	g++ -o Carlier.exe main.o Carlier.o 

main.o: main.cpp 	
	g++ -c ${CXXFLAGS} main.cpp

Carlier.o: Carlier.cpp Carlier.hpp
	g++ -c ${CXXFLAGS} Carlier.cpp 

clean:
	rm -f *.o *.exe