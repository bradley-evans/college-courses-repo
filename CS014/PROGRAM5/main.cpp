/*
Program by: Bradley Evans, 861236473
bevan006

June 2nd, 2016
*/

#include <iostream>
#include <string>
#include "Jug.h"

using namespace std;

int main() {
   string solution;
   Jug head(3, 5, 4, 1, 2, 3, 4, 5, 6);
   if (head.solve(solution) != 1) {
      cout << "Error 3" << endl;
   }
   cout << solution << endl << endl;
   
   
   Jug head2( 3, 5, 4, 1, 1, 1, 1, 1, 2);         
   if(head2.solve(solution) != 1) {
      cout << "Error 3" << endl;
   }
   cout << solution << endl;
}


/* helper function definitions */