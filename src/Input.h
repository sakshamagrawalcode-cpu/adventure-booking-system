// =====================================================================
//  Input.h  -  small helpers to read what the user types, safely
// =====================================================================
//  If the user types something wrong (letters instead of a number),
//  they are simply asked again.
//
//  If the input ENDS (for example when the input comes from a file),
//  the helpers return 0 or "". Every menu treats 0 as "go back",
//  so the program always finishes cleanly instead of looping forever.
// =====================================================================
#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Reads one whole line (it may have spaces, like "Hampta Pass Trek")
inline string readLine(const string& prompt) {
    cout << prompt;
    string line;
    if (!getline(cin, line)) return "";       // no more input
    return line;
}

// Reads a whole number. Asks again until a real number is typed.
inline int readInt(const string& prompt) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) return 0;    // no more input -> behave like "0 = back"
        stringstream ss(line);
        int number;
        char extra;
        if (ss >> number && !(ss >> extra)) return number;   // exactly one number, nothing else
        cout << "Please type a whole number.\n";
    }
}

// Reads a number that may have a decimal point, like 4500 or 4500.50
inline double readDouble(const string& prompt) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) return 0;
        stringstream ss(line);
        double number;
        char extra;
        if (ss >> number && !(ss >> extra)) return number;
        cout << "Please type a number.\n";
    }
}

// Asks a yes/no question. Only "y" or "Y" counts as yes.
inline bool askYesNo(const string& question) {
    string answer = readLine(question + " (y/n): ");
    return answer == "y" || answer == "Y";
}

#endif
