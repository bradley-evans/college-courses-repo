// Jason Zellmer
// Bradley Evans

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <list>

#include "Character.h"
#include "Warrior.h"
#include "Elf.h"
#include "Wizard.h"

using namespace std;

void populateList (list<Character *> &p1, list<Character *> &p2) {
    int random;
    const double MAX_HEALTH = 100.0;
    list<Character *>::iterator list_iterator;
    
    srand(time(0));
    
    cout << "Keeping it simple and creating a team of size 4." << endl;
    
    // add a wizard
    cout << "Adding a Wizard to Player 1's team." << endl;
    p1.push_back(new Wizard("P1Wizard", MAX_HEALTH, 5, 10));
    
    // add an elf
    cout << "Adding an Elf to Player 1's team." << endl;
    p1.push_back(new Elf("P1Elf", MAX_HEALTH, 3, "Sylvarian"));
    
    // add a warrior
    cout << "Adding a Warrior to Player 1's team." << endl;
    p1.push_back(new Warrior("P1Warrior", MAX_HEALTH, 5, "King George"));
    
    // then add random stuff
    cout << "Adding a random character type to Player 1's team... ";
    random = rand()%3;
    switch(random) {
        case 1:
            cout << "Selected a Warrior!" << endl;
            p1.push_back(new Warrior("P1WarriorRandom", MAX_HEALTH, 5, "Random"));
            break;
        case 2:
            cout << "Selected an Elf!" << endl;
            p1.push_back(new Elf("P1ElfRandom", MAX_HEALTH, 3, "Random"));
            break;
        case 0:
            cout << "Selected a Wizard!" << endl;
            p1.push_back(new Wizard("P1WizardRandom", MAX_HEALTH, 5, 10));
            break;
    }
    // now do player 2
    // add a wizard
    cout << "Adding a Wizard to Player 1's team." << endl;
    p2.push_back(new Wizard("P2Wizard", MAX_HEALTH, 5, 10));
    
    // add an elf
    cout << "Adding an Elf to Player 1's team." << endl;
    p2.push_back(new Elf("P2Elf", MAX_HEALTH, 3, "Sylvarian"));
    
    // add a warrior
    cout << "Adding a Warrior to Player 1's team." << endl;
    p2.push_back(new Warrior("P2Warrior", MAX_HEALTH, 5, "King George"));
    
    // then add random stuff
    cout << "Adding a random character type to Player 1's team... ";
    random = rand()%3;
    switch(random) {
        case 1:
            cout << "Selected a Warrior!" << endl;
            p2.push_back(new Warrior("P2WarriorRandom", MAX_HEALTH, 5, "Random"));
            break;
        case 2:
            cout << "Selected an Elf!" << endl;
            p2.push_back(new Elf("P2ElfRandom", MAX_HEALTH, 3, "Random"));
            break;
        case 0:
            cout << "Selected a Wizard!" << endl;
            p2.push_back(new Wizard("P2WizardRandom", MAX_HEALTH, 5, 10));
            break;
    }
}

int main() {
    
    bool exitCond = false;
    int i = 1;
    int random;
    srand(time(0));

    // make a list of characters for player 1
    list<Character *> player1;
    // make a list of characters for player 2
    list<Character *> player2;
    // populate the lists with characters
    populateList(player1,player2);
    
    // create an iterator that selects each player's character for the round
    list<Character *>::iterator p1select, p2select;
    
    
    
    // -- game loop --
    cout << endl << "Begin fight sequence." << endl;
    while (!exitCond) {
        cout << "   Round " << i << endl;
        //select a random character
        random = rand()%player1.size();
        p1select = player1.begin();
        for (i=0;i<random;i++) {
            p1select++;
        }
        random = rand()%player2.size();
        p2select = player2.begin();
        for (i=0;i<random;i++) {
            p2select++;
        }
        //run attacks
        //(*p1select)->attack(&p2select);
        
    }

}
