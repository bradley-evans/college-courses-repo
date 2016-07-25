#include "Heap.h"

using namespace std;
// Private Functions

void Heap::swap(PrintJob* job1, PrintJob* job2) {
        
  int priority_temp;
  int jobNumber_temp;
  int numPages_temp;
  
  priority_temp = job1->priority;
  jobNumber_temp = job1->jobNumber;
  numPages_temp = job1->numPages;
  job1->priority = job2->priority;
  job1->jobNumber = job2->jobNumber;
  job1->numPages = job2->numPages;
  job2->priority = priority_temp;
  job2->jobNumber = jobNumber_temp;
  job2->numPages = numPages_temp;
  
  return;
  
}

void Heap::trickleDown(int i) 
{
  if (i >= numItems) 
  {
    return;
  }
  else if (2*i + 1 < numItems && 2*i + 2 < numItems)
  {
    if (arr[2*i + 1]->priority > arr[2*i + 2]->priority) 
    {
      // left child is larger than right child
      if (arr[2*i + 1]->priority > arr[i]->priority) 
      {
        swap(arr[2*i + 1], arr[i]);
        trickleDown(2*i + 1);
      }
    }
    else 
    {
      // right child is bigger than left child
      if (arr[2*i + 2]->priority > arr[i]->priority) 
      {
        swap(arr[2*i + 2], arr[i]);
        trickleDown(2*i + 2);
      }
    }
  }
  else return;
}

/*This function is called by dequeue function
to move the new root down the heap to the 
appropriare location.*/
void Heap::trickleUp(int i) {
  if (i==0) {
    //this is the root node
    return;
  }
  if ( arr[(i-1)/2]->priority < arr[i]->priority ) {
    // swap and run trickleDown recursively
    swap(arr[(i-1)/2], arr[i]);
    trickleUp((i-1)/2);
  }
  
}

//You can include additional private helper functions here




// Public Functions

/*Initializes an empty PrintJob.*/
Heap::Heap() {
  numItems = 0;
}

/*Inserts a Heap to the heap without
violating max-heap properties.*/
/* 
void enqueueHeap ( itemtype item )
  if heap not full
    if heap empty
      arr[numNodes] = item
      ++numNodes
    else
      x = numNodes
      while (x > 0 && arr[(x-1)/2] > item)
        arr[x] = arr[(x-1)/2]
        x = (x-1)/2
      arr[x] = item
      ++numNodes 
*/
void Heap::enqueue ( PrintJob* printJ) {
  if (numItems < MAX_HEAP_SIZE)
  {
    if (numItems == 0)
    {
      arr[numItems] = printJ;
      ++numItems;
    }
    else
    {
      arr[numItems] = printJ;
      trickleUp(numItems);
      ++numItems;
    }
  }
}

/*Removes the node with highest priority from the heap. 
Follow the algorithm on priority-queue slides. */
void Heap::dequeue () {
  if (arr[0] != 0 && numItems != 0) {
    if (0 == numItems - 1)
    {
      cout << "Testing..." << endl;
      arr[0]->priority = 0;
      arr[0]->numPages = 0;
      arr[0]->jobNumber = 0;  // I think trickle down is going out of range
      delete arr[0];          // bc when i dq in the else below....  
      arr[0] = 0;
      --numItems;
    }
    else
    {
      // cout << "ARR PRIORITY AT NUMITEMS - 1 IS: " << arr[numItems-1]->priority << endl;
      swap(arr[0], arr[numItems - 1]);
      delete arr[numItems - 1];
      arr[numItems - 1] = 0; // ... when I don't set this to 0, i get random
      numItems--;             // garbage values for priority, job, etc 
      trickleDown(0);         // when i dq and cant dq past that
    }
  }
}

/*Returns the node with highest priority.*/
PrintJob* Heap::highest ( ) 
{
  if (arr[0])
  {
    return arr[0];
  }
  else return 0;
}

/*Prints the PrintJob with highest priority in the following format:
Priority: priority, Job Number: jobNum, Number of Pages: numPages
(Add a new line at the end.)*/
void Heap::print ( ) {
  if (arr[0] != 0) {
  cout << "Priority: " << arr[0]->priority << ", Job Number: " 
  << arr[0]->jobNumber << ", Number of Pages: " << arr[0]->numPages << endl;
  }
  
}
