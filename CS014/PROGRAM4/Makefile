main.exe: main.o HashTable.o WordEntry.o
	g++ -Wall -Werror main.o HashTable.o WordEntry.o -o main.exe 
	./main.exe
	
main.o: main.cpp HashTable.cpp HashTable.h WordEntry.cpp WordEntry.h
	g++ -Wall -Werror -c main.cpp HashTable.cpp WordEntry.cpp
	
HashTable.o: HashTable.cpp HashTable.h WordEntry.cpp WordEntry.h
	g++ -Wall -Werror -c HashTable.cpp

WordEntry.o: WordEntry.cpp WordEntry.h
	g++ -Wall -Werror -c WordEntry.cpp

clean:
	rm *.o *.exe *.dot *.jpg