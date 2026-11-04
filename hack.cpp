#include <iostream>
#include <string>
using namespace std;
int main() {
    string password;
    cout << "=== STACY'S PASSWORD AUDITOR ===" << endl;
    cout << "Enter password to audit: ";
    cin  >> password;

    int score = 0;
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;

    if(password.length() >= 8) score++;
    else cout << "[WEAK] Too short! Minimum 8 chars" << endl;
    for (char c : password) {
        if (isupper(c)) hasUpper = true;
        if (islower(c)) hasLower= true;
        if (isdigit(c)) hasDigit = true;
        if (!isalnum(c)) hasSpecial = true;
    }
    if(hasUpper) score++; else cout << "[TIP] Add UPPERCASE letter" << endl;
    if (hasLower) score++; else cout << "[TIP] Add lowercase letter" << endl;
    if (hasDigit) score++; else cout << "[TIP] Add a number" <<endl;
    if (hasSpecial) score++; else cout << "[TIP] Add special char !@#$" << endl;

    cout << "\n--- RESULT ---" << endl;
    cout << "Score: " << score << "/5" << endl;

    if (score == 5) cout << "STATUS: STRONG - Hacker proof!" << endl;
    else if (score >=3) cout << "STATUS: MEDIUM - could be cracked" << endl;
    else cout << "STATUS: WEAK - Crack in 2 seconds!" << endl;
    return 0;
}


        
    
