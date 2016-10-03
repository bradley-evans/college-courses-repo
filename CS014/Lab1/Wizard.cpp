// Jason Zellmer
// Bradley Evans

#include <iostream>
#include <string>
using namespace std;

#include "Character.h"
#include "Wizard.h"

/* Wizard

   Stores the wizard's rank as an int.

   When a wizard attacks another wizard, the damage done is the wizard's 
   attack strength multiplied by the ratio of the attacking wizard's rank 
   over the defending wizard's rank.

   The damage done to non-wizards is just the attack strength. The wizard's 
   health is not taken into consideration.



class Wizard : public Character {
   private:
      int rank;
   public:
   
*/
// Wizard::Wizard() {
//    type = WARRIOR;
//    name = "";
//    health = 0.0;
//    attackStrength = 0.0;
//    rank = 0;
// }

Wizard::Wizard(const string &name, 
       double health, 
       double attackStrength,
       int rank)
 : Character(WIZARD, name, health, attackStrength), rank(rank) {}
              
              
int Wizard::getRank() {
   return rank;
}


void Wizard::setRank(int rnk) {
   rank = rnk;
   return;
}



/* 

Wizard attack() function:

   When a wizard attacks another wizard, the damage done is the wizard's 
   attack strength multiplied by the ratio of the attacking wizard's rank 
   over the defending wizard's rank.

   The damage done to non-wizards is just the attack strength. The wizard's 
   health is not taken into consideration.

   private:
      int rank;

   enum CharType {WARRIOR, ELF, WIZARD};
   const double MAX_HEALTH = 100.0;
   
Find rank
   
   In order to access the Wizard data field surname using the Character 
   reference passed in to the attack function, you will need to dynamic cast 
   the Character reference to a Wizard reference.

   Here's an example of dynamic casting a Character reference named opponent 
   to a Wizard reference named opp:

      Wizard &opp = dynamic_cast<Wizard &>(opponent);

   
*/
void Wizard::attack(Character &opponent) {
   

   if (opponent.getType() == WIZARD) {
      
      // cout << "Type is WIZARD." << endl;
      // find allegiance
      Wizard &opp = dynamic_cast<Wizard &>(opponent);
      
      cout << "Wizard " << getName() << " attacks " << opponent.getName() << " --- POOF!!" << endl;
      cout << opponent.getName() << " takes " << ( attackStrength * ( static_cast<double>(getRank()) / opp.getRank() )) << " damage." << endl;
      opponent.setHealth( opponent.getHealth() - ( attackStrength * ( static_cast<double>(getRank()) / opp.getRank() ))  );
      // Wizard Merlin attacks Adali --- POOF!!
      // Adali takes 6.25 damage.
      
      // // FIXME: remove below later !!!!!!!!!!!!!!!!!
      // cout << "ratio: " << static_cast<double>( getRank() / opp.getRank() );
      
   }
   else {
      
      cout << "Wizard " << getName() << " attacks " << opponent.getName() << " --- POOF!!" << endl;
      cout << opponent.getName() << " takes " << attackStrength << " damage." << endl;
      opponent.setHealth( opponent.getHealth() - attackStrength );
      
   }

   
   return;
}
    