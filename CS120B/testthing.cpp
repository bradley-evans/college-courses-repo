#include <iostream>
#include <string>

using namespace std;

int MAX = 10;
bool alwaystrue = true;

int main() {
    char key[10]  = "secretkey";
    string plaintext = "!aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    string ciphertext;
    string decrypted;
    bool end = false;
    int j;
    
    j=0;
    while (!end) {
        for (int i=0;i<10;i++) {
            if (plaintext[j] == '\0') { end = true; break; }
            ciphertext[i] = plaintext[j] ^ key[i];
            //cout << "ct: " << ciphertext[i] << " pt: " << plaintext[i] << endl;
            j++;
        }
    }
    ciphertext[j] = '\0';
    end = false; j=0;
    
    
    for (int i=0;i<10;i++) {
        decrypted[i] = ciphertext[i] ^ key[i];
        cout << "dt: " << decrypted[i] << " pt: " << plaintext[i] << endl;
    }
    decrypted[9] = '\0';
    cout << "original: " << plaintext << endl;
    cout << "ciphertext: " << ciphertext << endl;
    cout << "decrypted: " << decrypted << endl;
}