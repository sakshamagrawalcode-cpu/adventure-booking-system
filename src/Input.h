// Input.h
// Helper functions for reading what the user types.
// Everything is read with getline (never cin >>), so lines never get mixed up.

#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

// Prints the prompt and reads one whole line. Repeats if the line is empty.
string readLine(string prompt) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) {
            // Input has ended (e.g. input came from a file that ran out)
            cout << "\nInput ended. Exiting.\n";
            exit(0);
        }
        if (line != "") {
            return line;
        }
        cout << "This cannot be empty.\n";
    }
}

// Returns true if the text is only digits (0-9), with 1 to 9 digits.
// (More than 9 digits could be too big for an int.)
bool isNumber(string text) {
    if (text.size() == 0 || text.size() > 9) {
        return false;
    }
    for (int i = 0; i < (int)text.size(); i++) {
        if (text[i] < '0' || text[i] > '9') {
            return false;
        }
    }
    return true;
}

// Repeats until the user types a whole number. Returns it as an int.
int readInt(string prompt) {
    while (true) {
        string line = readLine(prompt);
        if (isNumber(line)) {
            return stoi(line);   // stoi turns text like "42" into the number 42
        }
        cout << "Please enter a whole number.\n";
    }
}

// Repeats until the user types a number between min and max.
int readIntInRange(string prompt, int min, int max) {
    while (true) {
        int number = readInt(prompt);
        if (number >= min && number <= max) {
            return number;
        }
        cout << "Please enter a number from " << min << " to " << max << ".\n";
    }
}

// Lets the user pick a gender from a list, so there are no spelling mistakes
string chooseGender() {
    cout << "1. Male\n2. Female\n3. Other\n";
    int choice = readIntInRange("Gender: ", 1, 3);
    if (choice == 1) return "Male";
    if (choice == 2) return "Female";
    return "Other";
}
