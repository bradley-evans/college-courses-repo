// Tiffany Vuong & Bradley Evans
#ifndef __PRINTJOB_H
#define __PRINTJOB_H

using namespace std;

class PrintJob {
friend class Heap;
private:
  int priority;
  int jobNumber;
  int numPages;

public:
  PrintJob ( int, int, int);
  int getPriority ( );
  int getJobNumber ( );
  int getPages ( );
  //You can add additional functions here
};
#endif