#include <iostream>
#include <list>
#include <cstdlib>
#include <string>
#include "evans_functions.h"
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