#include <iostream>
#include "BaseCmd.h"
#include "CmdComposer.h"
#include <sstream>
#include <unistd.h>

using namespace std;


int main() {
    CmdComposer composer;
    char u[40];
    char h[40];
    for (int i = 0; i < 40; ++i) {
        u[i] = 0;
        h[i] = 0;
    }
    gethostname(h, 40);
    getlogin_r(u, 40);

    //main loop
    while (true) {
        cout << u << "@" << h << "$ ";
        string str;
        getline(cin, str);
        istringstream ss(str);
        BaseCmd* bc = composer.compose(ss);
        bc->execute();
        delete bc;
    }
}