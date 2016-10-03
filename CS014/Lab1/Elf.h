// Jason Zellmer
// Bradley Evans

#ifndef ELF_H
#define ELF_H

#include "Character.h"

/* Elf

   Stores the elf's family name as a string.

   The elf does not attack elf's from its own family.

   The damage done by the elf is the percentage of the elf's health 
   remaining (health / MAX_HEALTH) multiplied by the elf's attack strength.

*/

class Elf : public Character {
   private:
      string surname;
   public:
      // Elf();
      Elf(const string &name, 
              double health, 
              double attackStrength,
              string surname);
      string getSurname();
      void setSurname(const string & s);
      void attack(Character &opponent);
    
};
#endif