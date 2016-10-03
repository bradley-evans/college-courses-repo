// Jason Zellmer
// Bradley Evans

#ifndef WARRIOR_H
#define WARRIOR_H

#include <string>
#include "Character.h"
using namespace std;

/* Warrior

   Stores the warrior's allegiance as a string.

   The warrior does not attack warriors that have the same allegiance.

   The damage done by the warrior is the percentage of the warrior's health 
   remaining (health / MAX_HEALTH) multiplied by the warrior's attack strength.

*/

class Warrior : public Character {
   private:
      string allegiance;
   public:
      // Warrior();
      Warrior(const string &name, 
              double health, 
              double attackStrength,
              string allegiance);
      string getAllegiance();
      void setAllegiance(const string & s);
      void attack(Character &opponent);
    
};
#endif