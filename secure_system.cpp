#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

string hashPassword(string password, string salt) {
    string combined = password + salt;
    unsigned long hash = 5381;
    for (char c : combined) {
        hash = ((hash << 5) + hash) + c;
    }
    return to_string(hash);
}

string generateSalt() {
    string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    string salt = "";
    srand(time(0) + rand());
    for (int i = 0; i < 16; i++) {
        salt += chars[rand() % chars.length()];
    }
    return salt;
}

void registerUser() {
    string username, password;
    cout << "\n--- REGISTER ---" << endl;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    string salt = generateSalt();
    string hash = hashPassword(password, salt);
    ofstream file("users.txt", ios::app);
    file << username << ":" << salt << ":" << hash << endl;
    file.close();
    cout << "User registered SUCCESSFULLY!" << endl;
    cout << "Stored in database: " << username << ":" << salt << ":" << hash << endl;
    cout << "Notice: Your real password is NOT stored anywhere!" << endl;
}

void loginUser() {
    string username, password;
    cout << "\n--- LOGIN ---" << endl;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    ifstream file("users.txt");
    string line;
    bool found = false;
    while (getline(file, line)) {
        int pos1 = line.find(":");
        int pos2 = line.find(":", pos1 + 1);
        string storedUser = line.substr(0, pos1);
        string storedSalt = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string storedHash = line.substr(pos2 + 1);
        if (storedUser == username) {
            found = true;
            string testHash = hashPassword(password, storedSalt);
            if (testHash == storedHash) {
                cout << "LOGIN SUCCESS! Welcome " << username << endl;
            } else {
                cout << "LOGIN FAILED! Wrong password." << endl;
            }
            break;
        }
    }
    if (!found) cout << "User not found!" << endl;
    file.close();
}

int main() {
    int choice;
    do {
        cout << "\n===== SECURE PASSWORD STORAGE SYSTEM =====" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose: ";
        cin >> choice;
        if (choice == 1) registerUser();
        else if (choice == 2) loginUser();
    } while (choice != 0);
    return 0;
}