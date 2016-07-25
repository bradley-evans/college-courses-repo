main.exe: main.o Tree.o Node.o
	g++ -Wall -Werror main.o Tree.o Node.o -o main.exe 
	./main.exe < testharness.txt
	
main.o: main.cpp Tree.cpp Tree.h Node.cpp Node.h
	g++ -Wall -Werror -c main.cpp Tree.cpp Node.cpp
	
Tree.o: Tree.cpp Tree.h Node.cpp Node.h
	g++ -Wall -Werror -c Tree.cpp

Node.o: Node.cpp Node.h
	g++ -Wall -Werror -c Node.cpp

clean:
	rm *.o *.exe *.dot *.jpg