// Jason Zellmer
// Bradley Evans

#include <iostream>
#include <string>
using namespace std;

#include "Character.h"
#include "Elf.h"

/* Elf

   Stores the elf's family name as a string.

   The elf does not attack elf's from its own family.

   The damage done by the elf is the percentage of the elf's health 
   remaining (health / MAX_HEALTH) multiplied by the elf's attack strength.



class Elf : public Character {
   private:
      string surname;
   public:
   
*/

// Elf::Elf() {
//    type = WARRIOR;
//    name = "";
//    health = 0.0;
//    attackStrength = 0.0;
//    surname = "";
// }


Elf::Elf(const string &name, 
       double health, 
       double attackStrength,
       string surname)
 : Character(ELF, name, health, attackStrength), surname(surname) {}
 
 
string Elf::getSurname() {
   return surname;
}


void Elf::setSurname(const string & s) {
   surname = s;
   return;
}



/* 

Elf attack() function:

   The elf does not attack elf's from its own family.

   The damage done by the elf is the percentage of the elf's health 
   remaining (health / MAX_HEALTH) multiplied by the elf's attack strength.

   private:
      string surname;

   enum CharType {WARRIOR, ELF, WIZARD};
   const double MAX_HEALTH = 100.0;
   
Find family name:
   
   In order to access the Elf data field surname using the Character 
   reference passed in to the attack function, you will need to dynamic cast 
   the Character reference to an Elf reference.

   Here's an example of dynamic casting a Character reference named opponent 
   to an Elf reference named opp:

      Elf &opp = dynamic_cast<Elf &>(opponent);

   
*/
void Elf::attack(Character &opponent) {
   
   
   if (opponent.getType() == ELF) {
      // cout << "Type is ELF." << endl;
      // find allegiance
      Elf &opp = dynamic_cast<Elf &>(opponent);
      
      if (getSurname() == opp.getSurname() ) {
         cout << "Elf " << getName() << " does not attack Elf " << opponent.getName() << "." << endl;
         cout << "They are both members of the " << getSurname() << " family." << endl;
         // Elf Raegron does not attack Elf Cereasstar.
         // They are both members of the Sylvarian family.
      }
      else {
         
         cout << "Elf " << getName() << " shoots an arrow at " << opponent.getName() << " --- TWANG!!" << endl;
         cout << opponent.getName() << " takes " << ((health / MAX_HEALTH) * attackStrength) << " damage." << endl;
         opponent.setHealth( opponent.getHealth() - ((health / MAX_HEALTH) * attackStrength) );
      }
      
      
   }
   else {
      
      cout << "Elf " << getName() << " shoots an arrow at " << opponent.getName() << " --- TWANG!!" << endl;
      cout << opponent.getName() << " takes " << ((health / MAX_HEALTH) * attackStrength) << " damage." << endl;
      opponent.setHealth( opponent.getHealth() - ((health / MAX_HEALTH) * attackStrength) );
      
      // // FIXME: remove later !!!!!!!!!!!!!!!!!!!!!!!!!1
      // cout << "getHealth() = " << getHealth() << endl;
      // cout << "(getHealth() / MAX_HEALTH) = " << (getHealth() / MAX_HEALTH) << endl;
      // cout << "attackStrength = " << attackStrength << endl;
      // cout << "((getHealth() / MAX_HEALTH) * attackStrength) = " << ((getHealth() / MAX_HEALTH) * attackStrength) << endl;
      
   }


   
   return;
}
