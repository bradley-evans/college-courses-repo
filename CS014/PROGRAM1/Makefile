main.exe: main.o WordLadder.o
	g++ -Wall -Werror main.o WordLadder.o -o main.exe
	cp -f dictionary.txt dictionary.txt
	./main.exe < test.txt
	cp -f dictionary.txt dictionary.txt
	./main.exe < test.1.txt
	cp -f dictionary.txt dictionary.txt
	./main.exe < test.2.txt
	
main.o: main.cpp WordLadder.cpp WordLadder.h
	g++ -Wall -Werror -c main.cpp WordLadder.cpp
	
WordLadder.o: WordLadder.cpp WordLadder.h
	g++ -Wall -Werror -c WordLadder.cpp

clean:
	rm *.o *.exe output.txt outa.txt outb.txt outc.txt