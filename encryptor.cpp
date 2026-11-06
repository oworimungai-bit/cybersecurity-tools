#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Simple XOR encryption - same function encrypts AND decrypts
string xorCrypt(string data, string password) {
    string result = data;
    for (int i = 0; i < data.size(); i++) {
        result[i] = data[i] ^ password[i % password.size()];
    }
    return result;
}

int main() {
    string mode, inputFile, outputFile, password;
    
    cout << "=== File Encryptor / Decryptor ===" << endl;
    cout << "1 = Encrypt, 2 = Decrypt" << endl;
    cout << "Choose mode (1/2): ";
    cin >> mode;
    cin.ignore();

    cout << "Enter input file name (e.g. secret.txt): ";
    getline(cin, inputFile);

    cout << "Enter output file name (e.g. secret.enc): ";
    getline(cin, outputFile);

    cout << "Enter password: ";
    getline(cin, password);

    // Read file
    ifstream in(inputFile, ios::binary);
    if (!in) {
        cout << "Error: Cannot open " << inputFile << endl;
        return 1;
    }
    string data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    // Encrypt / Decrypt
    string result = xorCrypt(data, password);

    // Write file
    ofstream out(outputFile, ios::binary);
    out << result;
    out.close();

    if (mode == "1") {
        cout << "SUCCESS: " << inputFile << " encrypted to " << outputFile << endl;
    } else {
        cout << "SUCCESS: " << inputFile << " decrypted to " << outputFile << endl;
    }
    cout << "Password used: " << password << " (keep it safe!)" << endl;

    return 0;
}