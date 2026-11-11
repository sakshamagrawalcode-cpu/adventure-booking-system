// Adventure.h
// One adventure that a provider lists and customers book.

#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Adventure {
private:
    string id;
    string providerId;     // which provider owns this adventure
    string name;
    string location;
    string description;
    string difficulty;     // e.g. "Easy", "Moderate", "Hard"
    int minAge;
    string date;           // plain text, e.g. "20-12-2026"
    int price;             // per person, in rupees
    int totalSeats;
    int seatsLeft;

public:
    // Constructor: at the start, all seats are free
    Adventure(string id, string providerId, string name, string location,
              string description, string difficulty, int minAge,
              string date, int price, int totalSeats) {
        this->id = id;
        this->providerId = providerId;
        this->name = name;
        this->location = location;
        this->description = description;
        this->difficulty = difficulty;
        this->minAge = minAge;
        this->date = date;
        this->price = price;
        this->totalSeats = totalSeats;
        this->seatsLeft = totalSeats;
    }

    // Getters
    string getId()          { return id; }
    string getProviderId()  { return providerId; }
    string getName()        { return name; }
    string getLocation()    { return location; }
    string getDescription() { return description; }
    string getDifficulty()  { return difficulty; }
    int    getMinAge()      { return minAge; }
    string getDate()        { return date; }
    int    getPrice()       { return price; }
    int    getTotalSeats()  { return totalSeats; }
    int    getSeatsLeft()   { return seatsLeft; }

    // Setters for "edit adventure" (no setters for seats: seats can't be edited)
    void setName(string name)               { this->name = name; }
    void setLocation(string location)       { this->location = location; }
    void setDescription(string description) { this->description = description; }
    void setDifficulty(string difficulty)   { this->difficulty = difficulty; }
    void setMinAge(int minAge)              { this->minAge = minAge; }
    void setDate(string date)               { this->date = date; }
    void setPrice(int price)                { this->price = price; }

    // Returns true if a person of this age may join
    bool isAgeAllowed(int age) {
        return age >= minAge;
    }

    // Takes n seats. Throws an error if there are not enough.
    void bookSeats(int n) {
        if (n > seatsLeft) {
            throw runtime_error("Only " + to_string(seatsLeft) + " seats left");
        }
        seatsLeft = seatsLeft - n;
    }

    // Gives n seats back (used when a booking is cancelled)
    void releaseSeats(int n) {
        seatsLeft = seatsLeft + n;
    }

    // Prints all details
    void show() {
        cout << "Name        : " << name << "\n";
        cout << "Location    : " << location << "\n";
        cout << "Date        : " << date << "\n";
        cout << "Difficulty  : " << difficulty << "\n";
        cout << "Min age     : " << minAge << "\n";
        cout << "Price       : Rs. " << price << " per person\n";
        cout << "Seats left  : " << seatsLeft << " of " << totalSeats << "\n";
        cout << "About       : " << description << "\n";
    }
};
