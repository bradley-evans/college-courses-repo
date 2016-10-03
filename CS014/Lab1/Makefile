main.exe: main.o Character.o Warrior.o Elf.o Wizard.o
	g++ -Wall -Werror main.o Character.o Warrior.o Elf.o Wizard.o -o main.exe 
	./main.exe
	
main.o: main.cpp Character.cpp Character.h Elf.cpp Elf.h Wizard.cpp Wizard.h Warrior.cpp Warrior.h
	g++ -Wall -Werror -c main.cpp Character.cpp Elf.cpp Wizard.cpp Warrior.cpp
	
Character.o: Character.cpp Character.h
	g++ -Wall -c Character.cpp

Warrior.o: Warrior.cpp Warrior.h Character.cpp Character.h
	g++ -Wall -c Warrior.cpp

Wizard.o: Wizard.cpp Wizard.h Character.cpp Character.h
	g++ -Wall -c Wizard.cpp

Elf.o: Elf.cpp Elf.h Character.cpp Character.h
	g++ -Wall -c Elf.cpp

clean:
	rm *.o *.exe