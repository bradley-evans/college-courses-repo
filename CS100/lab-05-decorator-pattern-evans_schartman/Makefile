main.exe: main.o Decorator.o Base.o
	g++ main.o Decorator.o Base.o -o main.exe
	./main.exe
	
main.o: main.cpp Decorator.cpp Decorator.h Base.h Base.cpp
	g++ -c main.cpp Decorator.cpp Base.cpp 
	
Decorator.o: Decorator.cpp Decorator.h
	g++ -c Decorator.cpp
	
Base.o: Base.cpp Base.h
	g++ -c Base.cpp

clean:
	rm *.o *.exe