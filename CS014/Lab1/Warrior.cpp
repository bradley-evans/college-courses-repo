// Jason Zellmer
// Bradley Evans

#include <iostream>
#include <string>
using namespace std;

#include "Character.h"
#include "Warrior.h"

/* Warrior

   Stores the warrior's allegiance as a string.

   The warrior does not attack warriors that have the same allegiance.

   The damage done by the warrior is the percentage of the warrior's health 
   remaining (health / MAX_HEALTH) multiplied by the warrior's attack strength.



class Warrior : public Character {
   private:
      string allegiance;
   public:
   
*/

// Warrior::Warrior() {
//    type = WARRIOR;
//    name = "";
//    health = 0.0;
//    attackStrength = 0.0;
//    allegiance = "";
// }


Warrior::Warrior(const string &name, 
       double health, 
       double attackStrength,
       string allegiance)
 : Character(WARRIOR, name, health, attackStrength), allegiance(allegiance) {}
        

string Warrior::getAllegiance() {
   return allegiance;
}


void Warrior::setAllegiance(const string & s) {
   allegiance = s;
   return;
}


/* 

Warrior attack() function:

   The warrior does not attack warriors that have the same allegiance.

   The damage done by the warrior is the percentage of the warrior's health 
   remaining (health / MAX_HEALTH) multiplied by the warrior's attack strength.

   private:
      string allegiance;
   
   enum CharType {WARRIOR, ELF, WIZARD};
   const double MAX_HEALTH = 100.0;
   
Find allgeiance:
   
   In order to access the Warrior data field allegiance using the Character 
   reference passed in to the attack function, you will need to dynamic cast 
   the Character reference to a Warrior reference.

   Here's an example of dynamic casting a Character reference named opponent 
   to a Warrior reference named opp:

      Warrior &opp = dynamic_cast<Warrior &>(opponent);

*/
void Warrior::attack(Character &opponent) {
   
   
   if (opponent.getType() == WARRIOR) {
      // cout << "Type is WARRIOR." << endl;
      // find allegiance
      Warrior &opp = dynamic_cast<Warrior &>(opponent);
      
      if (getAllegiance() == opp.getAllegiance() ) {
         cout << "Warrior " << getName() << " does not attack Warrior " << opponent.getName() << "." << endl;
         cout << "They share an allegiance with " << getAllegiance() << "." << endl;
         // Warrior Jane does not attack Warrior Arthur.
         // They share an allegiance with King George.
      }
      else {
         
         cout << "Warrior " << getName() << " attacks " << opponent.getName() << " --- SLASH!!" << endl;
         cout << opponent.getName() << " takes " << ((health / MAX_HEALTH) * attackStrength) << " damage." << endl;
         opponent.setHealth( opponent.getHealth() - ((health / MAX_HEALTH) * attackStrength) );
      }
      
      
   }
   else {
      
      cout << "Warrior " << getName() << " attacks " << opponent.getName() << " --- SLASH!!" << endl;
      cout << opponent.getName() << " takes " << ((health / MAX_HEALTH) * attackStrength) << " damage." << endl;
      opponent.setHealth( opponent.getHealth() - ((health / MAX_HEALTH) * attackStrength) );
      
      // // FIXME: remove later !!!!!!!!!!!!!!!!!!!!!!!!!1
      // cout << "health = " << health << endl;
      // cout << "(getHealth() / MAX_HEALTH) = " << (health / MAX_HEALTH) << endl;
      // cout << "attackStrength = " << attackStrength << endl;
      // cout << "((getHealth() / MAX_HEALTH) * attackStrength) = " << ((health / MAX_HEALTH) * attackStrength) << endl;
      
   }
   
   
   
   
   
   
   return;
}