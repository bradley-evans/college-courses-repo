main.exe: main.o Jug.o
	g++ -Wall -Werror main.o Jug.o -o main.exe 
	./main.exe < testharness

main.o: main.cpp Jug.cpp Jug.h
	g++ -Wall -Werror -c main.cpp Jug.cpp

Jug.o: Jug.cpp Jug.h
	g++ -Wall -Werror -c Jug.cpp
	
clean:
	rm *.o *.exe *.dot *.jpg