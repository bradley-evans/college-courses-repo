#include "HashTable.h"
#include "WordEntry.h"

/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable (int s) {
    // I guess we'll use the default size
    this->hashTable = new list<WordEntry>[s];
    this->size = s;
	
}


/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to 
*  ensure array index doesn't go out of bounds
*/
int HashTable::computeHash(const string &s) {
    int hashVal = 0;

    for(unsigned i = 0; i<s.length();  i++) {
        hashVal = 37*hashVal+s[i];
    }
    hashVal %= this->size;
    if(hashVal<0) {
        hashVal += size;
    }
   return hashVal;
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void HashTable::put(const string &s, int score) {
    int hash = computeHash(s);
    list<WordEntry> *currList = &hashTable[hash];
    list<WordEntry>::iterator it;
    
    
    // iterate through the list and see if s is there
    // if it is, run addNewAppearance()
    for (it=currList->begin(); it!=currList->end(); it++) {
        if (it->getWord() == s) {
            it->addNewAppearance(score);
            //cout << "added a new appearance ";
            return;
        }
    }
    //cout << "adding a new entry for " << s << endl;
    WordEntry newEntry(s,score);
    currList->push_back(newEntry);
}

/* getAverage
*  input: string word 
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/

double HashTable::getAverage(const string &s) {
    int hash = computeHash(s);
    list<WordEntry> *currList = &hashTable[hash];
    list<WordEntry>::iterator it;
    
    for (it=currList->begin(); it!=currList->end(); it++) {
        if (it->getWord() == s) {
            cout << s << " has an average value " << it->getAverage() << endl;
            return it->getAverage();
        }
    }
    return 2.0;

}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(const string &s) {
    int hash = computeHash(s);
    list<WordEntry> *currList = &hashTable[hash];
    list<WordEntry>::iterator it;
    for (it=currList->begin(); it!=currList->end(); it++) {
        if (it->getWord() == s) {
            return true;
        }
    }
    return false;
}

