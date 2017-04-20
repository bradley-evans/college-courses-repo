main.exe: main.o Graph.o
	g++ -Wall -Werror main.o Graph.o -o main.exe 
	./main.exe input1
	./main.exe input2
	./main.exe input3
	
main.o: main.cpp Graph.cpp Graph.h Vertex.h
	g++ -Wall -Werror -c main.cpp Graph.cpp
	
Graph.o: Graph.cpp Graph.h Vertex.h
	g++ -Wall -Werror -c Graph.cpp

clean:
	rm *.o *.exe