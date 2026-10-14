// =====================================================================
//  Searchable.h  -  an INTERFACE for anything that can be searched
// =====================================================================
//  Trip and User both follow this interface, so the system searches
//  trips and users in the same way: by calling matches(keyword).
//
//  OOP topics in this file:
//    [Abstraction]  [Interface]  [Pure virtual function]
// =====================================================================
#ifndef SEARCHABLE_H
#define SEARCHABLE_H

#include <string>
#include <cctype>
using namespace std;

// [Interface] a class that has ONLY pure virtual functions.
// It says WHAT a class must be able to do, not HOW.
// [Abstraction] the search code only needs to know "it can be matched",
// not whether it is a Trip or a User.
class Searchable {
public:
    // [Pure virtual function] each class decides what "matches" means for it
    virtual bool matches(const string& keyword) const = 0;

    virtual ~Searchable() {}
};

// true if 'word' is somewhere inside 'text', ignoring capital letters
// (so "manali" matches "Manali, Himachal Pradesh")
inline bool containsIgnoreCase(string text, string word) {
    for (char& c : text) c = tolower(c);
    for (char& c : word) c = tolower(c);
    return text.find(word) != string::npos;
}

#endif
