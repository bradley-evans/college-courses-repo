main.exe: main.o AVLTree.o Node.o
	g++ -Wall -Werror main.o AVLTree.o Node.o -o main.exe 
	./main.exe < testharness
	
main.o: main.cpp AVLTree.cpp AVLTree.h Node.cpp Node.h
	g++ -Wall -Werror -c main.cpp AVLTree.cpp Node.cpp
	
AVLTree.o: AVLTree.cpp AVLTree.h Node.cpp Node.h
	g++ -Wall -Werror -c AVLTree.cpp

Node.o: Node.cpp Node.h
	g++ -Wall -Werror -c Node.cpp

clean:
	rm *.o *.exe