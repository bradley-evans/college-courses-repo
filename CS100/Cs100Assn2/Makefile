main.exe: main.o BaseCmd.o CmdComposer.o Cmd.o
	g++ main.o BaseCmd.o CmdComposer.o Cmd.o -o main.exe
	./main.exe
	
main.o: main.cpp BaseCmd.cpp BaseCmd.h CmdComposer.h CmdComposer.cpp Cmd.h Cmd.cpp Connector.h Connector.cpp
	g++ -c main.cpp BaseCmd.cpp CmdComposer.cpp Cmd.cpp Connector.cpp
	
BaseCmd.o: BaseCmd.cpp BaseCmd.h
	g++ -c BaseCmd.cpp
	
CmdComposer.o: CmdComposer.cpp CmdComposer.h
	g++ -c CmdComposer.cpp

Cmd.o: Cmd.cpp Cmd.h
	g++ -c Cmd.cpp
	
Connector.o: Connector.cpp Connector.h
	g++ -c Cmd.cpp

clean:
	rm *.o *.exe
