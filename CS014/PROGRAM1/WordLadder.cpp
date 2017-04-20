#include "WordLadder.h"

WordLadder::WordLadder(const string &file) {
    string word;
    ifstream infile;
    infile.open(file.c_str());
    if (infile.is_open()) {
        while (!infile.eof()) {
            getline(infile,word);
            if (word.size() != 5) {
                cout << "Warning: Word longer than 5 characters detected in dictionary." << endl;
            }
            dict.push_back(word.c_str());
        }
        infile.close();
        return;
    } else {
        cout << "Error opening input file." << endl;
        return;
    }
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
    
    cout << "Finding word ladder from " << start << " to " << end << ": ";
    ofstream outfile;
    outfile.open(outputFile.c_str());
    if (!outfile.is_open()) {
        cout << "Opening output file failed." << endl;
        return;
    }
    // set up the stuff
    queue< stack<string> > queue;
    stack< string > stack;
    string word;
    list<string>::iterator it;
    bool startgood = false, endgood = false;
    
    // initial validity tests
    for (it=dict.begin();it!=dict.end();++it) {
        if (*it == start) {
            startgood = true;
        }
        if (*it == end) {
            endgood = true;
        }
    }
    if (!startgood || !endgood) {
        cout << "Starting or ending word was not found in the dictionary." << endl;
        return;
    }
    if (start == end) {
        outfile << start;
        return;
    }
    stack.push(start);
    queue.push(stack);
   
    // find the first word, delete it
    dict.remove(start);
    while(!queue.empty()) {
        // get the word off of the top of the front stack
        word = queue.front().top();
        for (it=dict.begin();it!=dict.end();++it) {
            // wordcompare will decide if the word is off by one from the dictionary word.
            if (wordcompare(word,*it)) {
                if (*it == end) {
                    // if the off by one word is the last word 
                    // the ladder contains the entire stack -- output and return.
                    queue.front().push(end);
                    //print the stack
                    printstack(queue.front(),outfile);
                    //cout << "Operations: " << opers << endl << endl;
                    return;
                } 
                // otherwise, create a copy of the front stack and push the
                // off by one word from dictionary
                stack = queue.front();
                stack.push(*it);
                queue.push(stack);
                it = dict.erase(it);
                // decrement iterator by one to correct for the advanced iterator
                // returned by the std::list::erase function
                it--;
            }
        }
        queue.pop();
    }
    // if a word ladder is not found, then do this
    if (outfile.is_open()) {
        outfile << "No Word Ladder Found!!";
        cout << "No Word Ladder Found!!";
    }
}

bool WordLadder::wordcompare(string word, string dictword) {
    int hits = 0;
    for (int i=0; i<5; i++) {
        if (word[i] == dictword[i]) { hits++; }
    }
    if (hits == 4) {
        return true;
    } else {
        return false;
    }
}

void WordLadder::printstack(stack<string> stack, ofstream &outfile) {
    
    int i = 0;
    vector<string> ladder;
    while (!stack.empty()) {
        ladder.push_back(stack.top());
        stack.pop();
        i++;
    }
    
    if (outfile.is_open()) {
        while (i!=0) {
            i--;
            outfile << ladder.at(i);
            cout << ladder.at(i);
            if (i!=0) {
                outfile << " ";
                cout << " ";
            }
        }
        cout << endl;
    }
    // if (outfile.is_open()) {
    //     while (!stack.empty()) {
            
    //         outfile << stack.top();
    //         cout << stack.top();
    //         stack.pop();
    //         if (!stack.empty()) {
    //             outfile << " ";
    //             cout << " ";
    //         }
    //     }
    // }
    //cout << endl;
}