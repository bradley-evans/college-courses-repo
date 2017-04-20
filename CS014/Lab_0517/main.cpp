
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm> 
using namespace std;
//Bradley Evans, Pedro De La Cueva

const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds



int genRandInt(int low, int high) {
    srand(clock());
    return low + rand() % (high - low + 1);
}
void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
        
    }
}

int Partition(int *numbers, int i, int k) {
   int l = 0;
   int h = 0;
   int midpoint = 0;
   int pivot = 0;
   int temp = 0;
   bool done = false;
   
   /* Pick middle element as pivot */
   midpoint = i + (k - i) / 2;
   pivot = numbers[midpoint];
   
   l = i;
   h = k;
   
   while (!done) {
      
      /* Increment l while numbers[l] < pivot */
      while (numbers[l] < pivot) {
         ++l;
      }
      
      /* Decrement h while pivot < numbers[h] */
      while (pivot < numbers[h]) {
         --h;
      }
      
      /* If there are zero or one elements remaining,
       all numbers are partitioned. Return h */
      if (l >= h) {
         done = true;
      }
      else {
         /* Swap numbers[l] and numbers[h],
          update l and h */
         temp = numbers[l];
         numbers[l] = numbers[h];
         numbers[h] = temp;
         
         ++l;
         --h;
      }
   }
   
   return h;
}

void quicksort_midpoint(int *numbers, int i, int k) {
   int j = 0;
   
   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }
   
   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   j = Partition(numbers, i, k);
   
   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   quicksort_midpoint(numbers, i, j);
   quicksort_midpoint(numbers, j + 1, k);
   
   return;
}

int middleValue(int i, int mid, int k)
{
    if(i >= mid && i <= k)
    {
        return i;
    }
    else if(i <= mid && i >= k)
    {
        return i;
    }
    else if(k >=i && k <= mid)
    {
        return k;
    }
    else if(k <= i && k >= mid)
    {
        return k;
    }
    else
    {
        return mid;
    }
}
int median_partition(int *numbers,int i, int k) {
    
     int l = 0;
   int h = 0;
   int midpoint = 0;
   int pivot = 0;
   int temp = 0;
   bool done = false;
   
   /* Pick middle element as pivot */
   midpoint = i + (k - i) / 2;
   pivot = middleValue(numbers[i], numbers[midpoint] ,numbers[k]);
   
   l = i;
   h = k;
   
   while (!done) {
      
      /* Increment l while numbers[l] < pivot */
      while (numbers[l] < pivot) {
         ++l;
      }
      
      /* Decrement h while pivot < numbers[h] */
      while (pivot < numbers[h]) {
         --h;
      }
      
      /* If there are zero or one elements remaining,
       all numbers are partitioned. Return h */
      if (l >= h) {
         done = true;
      }
      else {
         /* Swap numbers[l] and numbers[h],
          update l and h */
         temp = numbers[l];
         numbers[l] = numbers[h];
         numbers[h] = temp;
         
         ++l;
         --h;
      }
   }
   
   return h;
}

void quicksort_medianOfThree(int *numbers, int i, int k){
     int j = 0;
   
  /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
  if (i >= k) {
      return;
  }
   
  /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
  j = median_partition(numbers, i, k);
   
  /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
  quicksort_medianOfThree(numbers, i, j);
  quicksort_medianOfThree(numbers, j + 1, k);
   
  return;
}
void insertionsort (int *numbers) {
    int i, j, temp;
    for (i = 1; i < NUMBERS_SIZE; ++i) {
        j = i;
        // Insert numbers[i] into sorted part 
        // stopping once numbers[i] in correct position
        while (j > 0 && numbers[j] < numbers[j - 1]) {
             
          // Swap numbers[j] and numbers[j - 1]
          temp = numbers[j];
          numbers[j] = numbers[j - 1];
          numbers[j - 1] = temp;
          --j;
        }
    }
}

void mergesort(*int arr, int start, int end) {
    if (end-start == 0) {
        return;
    }
    m = (end-start)/2 + start;
    
    mergesort[arr,0,m];
    mergesort[arr,m+1,size];
    
    int i=start; j=start, k=m+1, temp=0;
    int arr2[NUMBERS_SIZE] = arr;
    
    while i <= m and j <= n,
        
        arr[i++] = (arr[j] < arr2[k]) ? arr[j++] : arr2[i++];
    while i <= m,
        a[k++] = b[i++]
        
    }
    
}


int main() {
    int i = 0, elapsedTime = 0;
    int arr1[NUMBERS_SIZE], arr2[NUMBERS_SIZE], arr3[NUMBERS_SIZE];
    int *arrptr;
    clock_t Start, End;
    
    fillArrays(arr1,arr2,arr3);
    
    cout << "This program will only display the first 100 elements of each" << endl
            << NUMBERS_SIZE << " array." << endl;
    cout << "Unsorted: ";
    for(i = 0; i < 100; ++i) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    
    cout << "Sorting via Quicksort Midpoint: ";
    arrptr = arr1;
    Start = clock();
    quicksort_midpoint(arrptr, 0, NUMBERS_SIZE-1);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout << "[ Time Elapsed: " << elapsedTime << " ms ] " << endl;
    for(i = 0; i < 100; ++i) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    cout << "Sorting via Quicksort, Median of Three: ";
    arrptr = arr2;
    Start = clock();
    quicksort_medianOfThree(arrptr, 0, NUMBERS_SIZE-1);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout << "[ Time Elapsed: " << elapsedTime << " ms ] " << endl;
    for(i = 0; i < 100; ++i) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    
    cout << "Sorting via Insertion Sort: ";
    arrptr = arr3;
    Start = clock();
    insertionsort(arr3);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout << "[ Time Elapsed: " << elapsedTime << " ms ] " << endl;
    for(i = 0; i < 100; ++i) {
        cout << arr3[i] << " ";
    }
    cout << endl << endl;
    
    cout << "Executing sorts on pre-sorted arrays: " << endl;
    cout << "Sorting via Quicksort Midpoint: ";
    arrptr = arr1;
    Start = clock();
    quicksort_midpoint(arrptr, 0, NUMBERS_SIZE-1);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout << "[ Time Elapsed: " << elapsedTime << " ms ] " << endl;
    cout << "Sorting via Quicksort, Median of Three: ";
    arrptr = arr2;
    Start = clock();
    quicksort_medianOfThree(arrptr, 0, NUMBERS_SIZE-1);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout << "[ Time Elapsed: " << elapsedTime << " ms ] " << endl;
    cout << "Sorting via Insertion Sort: ";
    arrptr = arr3;
    Start = clock();
    insertionsort(arr3);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout << "[ Time Elapsed: " << elapsedTime << " ms ] "<< endl;
    cout << endl;
   
   return 0;
}