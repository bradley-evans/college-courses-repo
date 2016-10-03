// Jason Zellmer
// Bradley Evans

#include <iostream>
using namespace std;

#include "Character.h"

/*
enum CharType {WARRIOR, ELF, WIZARD};

const double MAX_HEALTH = 100.0;

class Character {
 protected:
    CharType type;
    string name;
    double health;
    double attackStrength;

 public:
 
*/

// Character::Character() {
//    type = WARRIOR;
//    name = "";
//    health = 0.0;
//    attackStrength = 0.0;
// }


Character::Character(CharType type, 
   const string &name, 
   double health, 
   double attackStrength)
   : type(type), name(name), health(health), attackStrength(attackStrength) {}


CharType Character::getType() const {
   return type;
}


const string & Character::getName() const {
   return name;
}


/* 
   Returns the whole number of the health value (static_cast to int). 
*/
int Character::getHealth() const {
   return static_cast<int>(health);
}


void Character::setHealth(double h) {
   health = h;
   return;
}


/* 
   Returns true if getHealth() returns an integer greater than 0, otherwise 
   false 
*/
bool Character::isAlive() const {
   if (this->getHealth() > 0) {
      return true;
   }
   else {
      return false;
   }
}

// // The following is a pure virtual function, so we don't "have to" implement
// // it for the base case, but we'll have to for any derived cases. Also, it 
// // only has to have virtual in the declaration and not in the definition if 
// // it is defined
// // virtual void Character::attack(Character &) = 0;
