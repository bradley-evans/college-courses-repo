// Jason Zellmer
// Bradley Evans

#ifndef WIZARD_H
#define WIZARD_H

#include "Character.h"
#include <string>
using namespace std;

/* Wizard

   Stores the wizard's rank as an int.

   When a wizard attacks another wizard, the damage done is the wizard's 
   attack strength multiplied by the ratio of the attacking wizard's rank 
   over the defending wizard's rank.

   The damage done to non-wizards is just the attack strength. The wizard's 
   health is not taken into consideration.

*/

class Wizard : public Character {
   private:
      int rank;
   public:
      // Wizard();
      Wizard(const string &name, 
              double health, 
              double attackStrength,
              int rank);
      int getRank();
      void setRank(int rnk);
      void attack(Character &opponent);
    
};
#endif