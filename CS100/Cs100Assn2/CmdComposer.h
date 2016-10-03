#ifndef CMDCOMPOSER_H
#define CMDCOMPOSER_H
#include "BaseCmd.h"
#include "Cmd.h"
#include "Connector.h"
#include <sstream>
#include <vector>
#include <string.h>

using namespace std;

class CmdComposer {
    public:
        CmdComposer() { };
        BaseCmd* compose(istringstream &ss, BaseCmd* head = 0) {
            string tstr;
            vector<string> v;
            int conType = -1; //default no connector
            while (ss >> tstr) {
                if(tstr.at(tstr.size() - 1) == ';') {
                    conType = next; //semicolon
                    v.push_back(tstr.substr(0, tstr.size() - 1));
                    break;
                }
                else if(strcmp(tstr.c_str(), "||") == 0) {
                    conType = failure; 
                    break;
                }
                else if(strcmp(tstr.c_str(), "&&") == 0) {
                    conType = success;
                    break;
                } 
                
                v.push_back(tstr);
                
            }
            char** args = new char*[v.size() + 1];
            //dynamically allocate mem
            for (int i = 0; i < v.size(); ++i) {
                args[i] = new char[v.at(i).size() + 1];
                strcpy(args[i], v.at(i).c_str());
            }
            args[v.size()] = 0;
            
            BaseCmd* tempCmd = new Cmd(args);
            
            if(head == 0) {
                head = tempCmd;
            }
            else {
                head->addRight((tempCmd));
            }
            if(conType == -1) {
                return head;
            }
            else {
                BaseCmd* newCon = new Connector((ConType)conType);
                newCon->addLeft(head);
                head = newCon;
                return compose(ss, head);
            }
        };
};

#endif