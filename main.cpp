#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> // all_of function | sort function 
#include <cctype>

using namespace std;

const int MAX_PASSWORDS = 1000; // liczba haseł
const int MAX_PASSWORD_LENGTH = 100; // długość hasła

bool containsConsecutiveASCII(const string& str) {
    for (size_t i = 0; i < str.length() - 3; ++i) {
        if (isascii(str[i]) && isascii(str[i + 1]) && isascii(str[i + 2]) && isascii(str[i + 3])) {
            if ((str[i + 1] - str[i] == 1) && (str[i + 2] - str[i + 1] == 1) && (str[i + 3] - str[i + 2] == 1)) {
                return true;
            }
        }
    }
    return false;
}


bool containsDigit(const string& str) {
    for (char c : str) {
        if (isdigit(c)) {
            return true;
        }
    }
    return false;
}

bool containsLowercase(const string& str) {
    for (char c : str) {
        if (islower(c)) {
            return true;
        }
    }
    return false;
}

bool containsUppercase(const string& str) {
    for (char c : str) {
        if (isupper(c)) {
            return true;
        }
    }
    return false;
}

void countPasswords(const string passwords[], int numPasswords, int passwordCount[], bool passwordsUsedByMultipleUsers[], int& passwordsOnlyDigits, int& usersWithConsecutiveASCII, int& passwordsMatchingCriteria) {
    cout << "--------------" << endl;
    cout << "4.1" << endl;
    cout << passwordsOnlyDigits << endl;
    cout << "--------------" << endl;
    cout << "4.2" << endl;
    for (int i = 0; i < numPasswords; ++i) {
        if (passwordsUsedByMultipleUsers[i]) {
            cout << passwords[i] << endl;
        }
    }
    cout << "--------------" << endl;
    cout << "4.3" << endl;
    cout << usersWithConsecutiveASCII << endl;
    cout << "--------------" << endl;
    cout << "4.4" << endl;
    cout << passwordsMatchingCriteria << endl;
    cout << "--------------" << endl;
}



int main() {
    ifstream file("hasla.txt");

    string passwords[MAX_PASSWORDS]; // hasła
    int passwordCount[MAX_PASSWORDS] = {0}; // wystapienia hasla
    bool passwordsUsedByMultipleUsers[MAX_PASSWORDS] = {false}; // hasła używane przez +2 użytkowników
    int passwordsOnlyDigits = 0; // haseła składających z cyfr
    int usersWithConsecutiveASCII = 0; // hasła użytkownikow z kodami ASCII
    int passwordsMatchingCriteria = 0; //  haseła spełniających wszystkie warunki

    string line;
    int numPasswords = 0; 

    while (getline(file, line)) {
        bool found = false;
        for (int i = 0; i < numPasswords; ++i) {
            if (line == passwords[i]) {
                found = true;
                passwordCount[i]++;
                if (passwordCount[i] == 2) {
                    passwordsUsedByMultipleUsers[i] = true;
                }
                break;
            }
        }
        if (!found) {
            passwords[numPasswords] = line;
            passwordCount[numPasswords]++;
            numPasswords++;
        }
        if (containsConsecutiveASCII(line)) {
            usersWithConsecutiveASCII++;
        }
        if (all_of(line.begin(), line.end(), [](unsigned char c) { return isdigit(c); })) {
            passwordsOnlyDigits++;
        }
        if (containsDigit(line) && containsLowercase(line) && containsUppercase(line)) {
            passwordsMatchingCriteria++;
        }
    }

    file.close();

    countPasswords(passwords, numPasswords, passwordCount, passwordsUsedByMultipleUsers, passwordsOnlyDigits, usersWithConsecutiveASCII, passwordsMatchingCriteria);
    // Globalna funkcja do wynikow

    return 0;
}
