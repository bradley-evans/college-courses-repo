main.exe: main.o Base.o container.o strategy.o
	g++ main.o Base.o container.o strategy.o -o main.exe
	./main.exe
	
main.o: main.cpp Base.cpp Base.h container.h container.cpp strategy.h strategy.cpp
	g++ -c main.cpp Base.cpp container.cpp strategy.cpp
	
Base.o: Base.cpp Base.h
	g++ -c Base.cpp
	
container.o: container.cpp container.h
	g++ -c container.cpp

strategy.o: strategy.cpp strategy.h
	g++ -c strategy.cpp
clean:
	rm *.o *.exe