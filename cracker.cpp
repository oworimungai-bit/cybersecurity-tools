#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string hashPassword(string password, string salt) {
    string combined = password + salt;
    unsigned long hash = 5381;
    for (char c : combined) {
        hash = ((hash << 5) + hash) + c;
    }
    return to_string(hash);
}

int main() {
    cout << "=== PROJECT 2: Password Cracker by Owori ===" << endl;
    cout << "Trying to crack users.txt..." << endl << endl;

    // Common passwords hackers try first
    vector<string> wordlist = {"123456", "password", "123456789", "qwerty", "12345", "12345678", "admin", "letmein", "welcome", "monkey", "dragon", "123123", "password1", "1234", "1234567", "Mungai", "mungai", "owori", "kenya", "nairobi"};

    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        // Format is username:salt:hash
        int p1 = line.find(':');
        int p2 = line.find(':', p1 + 1);
        string user = line.substr(0, p1);
        string salt = line.substr(p1 + 1, p2 - p1 - 1);
        string targetHash = line.substr(p2 + 1);

        cout << "Cracking user: " << user << " Salt: " << salt << endl;
        bool found = false;
        for (string guess : wordlist) {
            if (hashPassword(guess, salt) == targetHash) {
                cout << ">>> CRACKED! Password for " << user << " is: " << guess << endl;
                found = true;
                break;
            }
        }
        if (!found) cout << "Not found in wordlist - password is STRONG!" << endl << endl;
    }
    return 0;
}