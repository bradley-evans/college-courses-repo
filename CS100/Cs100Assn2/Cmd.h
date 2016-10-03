#ifndef CMD_H
#define CMD_H
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "BaseCmd.h"

using namespace std;

class Cmd : public BaseCmd {
    private: 
        char** args;
    public:
        Cmd() { };
        Cmd(char ** arg) : args(arg) { };
        int execute() {
            if (strcmp(args[0], "exit") == 0) {
                exit(0);
            }
            int procID, status;
            procID = fork();
            
            if(procID == 0) {
                int i = execvp(args[0], args);
                exit(i);
            }
            int waitID = wait(&status);
            return status;
        };
        void addLeft(BaseCmd* l) {};
        void addRight(BaseCmd* r) {};
        ~Cmd() {
            int argNum = 0;
            while (args[argNum] != 0) {
                delete[] args[argNum];
                argNum++;
            }
            delete[] args;
            
        };
};
#endif
