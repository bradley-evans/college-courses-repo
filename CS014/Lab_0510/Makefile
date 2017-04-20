main.exe: main.o Heap.o PrintJob.o
	g++ -Wall -Werror main.o Heap.o PrintJob.o -o main.exe 
	./main.exe
	
main.o: main.cpp Heap.cpp Heap.h PrintJob.cpp PrintJob.h
	g++ -Wall -Werror -c main.cpp Heap.cpp PrintJob.cpp
	
Heap.o: Heap.cpp Heap.h PrintJob.cpp PrintJob.h
	g++ -Wall -Werror -c Heap.cpp

PrintJob.o: PrintJob.cpp PrintJob.h
	g++ -Wall -Werror -c PrintJob.cpp

clean:
	rm *.o *.exe