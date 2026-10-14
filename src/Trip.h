// =====================================================================
//  Trip.h  -  one adventure trip (e.g. "Hampta Pass Trek") and its seats
// =====================================================================
//  Created by an AdventureProvider. Booked through a Booking.
//
//  OOP topics in this file:
//    [Encapsulation]  [Default constructor]  [Parameterized constructor]
//    [Constructor overloading]  [Static data member]  [Static member function]
//    [Inline function]  [Function overloading]
//    [Unary operator overloading]   ++trip
//    [Binary operator overloading]  trip1 < trip2 (member), trip1 == trip2 (friend)
//    [Friend function]  [Stream operator overloading]  <<  >>
//    [Friend class]  Admin
// =====================================================================
#ifndef TRIP_H
#define TRIP_H

#include <iostream>
#include <string>
using namespace std;

enum FitnessLevel { LOW, MODERATE, HIGH };
enum TripStatus { DRAFT, PUBLISHED, CLOSED };

// [Inline function] 'inline' tells the compiler it may paste the body where
// the function is called. (Functions written INSIDE a class are inline automatically.)
//
// [Function overloading] the SAME name toString(), DIFFERENT parameter types.
// The compiler picks the right one while compiling -> [Compile-time polymorphism].
// (More toString() versions are in Booking.h and PaymentGateway.h.)
inline string toString(FitnessLevel f) {
    if (f == LOW) return "LOW";
    if (f == MODERATE) return "MODERATE";
    return "HIGH";
}

inline string toString(TripStatus s) {
    if (s == DRAFT) return "DRAFT";
    if (s == PUBLISHED) return "PUBLISHED";
    return "CLOSED";
}

class Trip {
private:
    // [Encapsulation] seat numbers are private. They change ONLY through
    // reserveSlots() / releaseSlots(), so they can never go wrong.
    string tripId;
    string title;
    string location;
    double price;
    string startDate;
    string endDate;
    int maxCapacity;
    int availableSlots;
    int minAge;
    FitnessLevel requiredFitness;
    TripStatus status;

    // [Static data member] counts trips created; also used to make the trip ID
    static int tripCount;

    bool hasCapacityFor(int count) const {
        return count > 0 && count <= availableSlots;
    }

    void assignNewId() {
        tripCount++;
        tripId = "TRP-" + to_string(tripCount);
    }

public:
    // [Default constructor] takes no arguments.
    // Used when the details are filled in later with  cin >> trip
    Trip()
        : price(0), maxCapacity(0), availableSlots(0), minAge(0),
          requiredFitness(LOW), status(DRAFT) {
        assignNewId();
    }

    // [Parameterized constructor]
    // [Constructor overloading] Trip has TWO constructors with different parameters
    Trip(string t, string loc, double p, string start, string end,
         int cap, int age, FitnessLevel fit)
        : title(t), location(loc), price(p), startDate(start), endDate(end),
          maxCapacity(cap), availableSlots(cap), minAge(age),
          requiredFitness(fit), status(DRAFT) {
        assignNewId();
    }

    bool reserveSlots(int count) {
        if (!hasCapacityFor(count)) return false;
        availableSlots -= count;
        return true;
    }

    void releaseSlots(int count) {
        availableSlots += count;
        if (availableSlots > maxCapacity) availableSlots = maxCapacity;
    }

    void publish() { status = PUBLISHED; }

    // UC-03 alternate flow 2a: seats are taken only by CONFIRMED bookings,
    // so "all seats free" means "no confirmed bookings" -> safe to remove
    bool canBeRemoved() const { return availableSlots == maxCapacity; }

    string getTripId() const { return tripId; }
    string getTitle() const { return title; }
    double getPrice() const { return price; }
    string getStartDate() const { return startDate; }
    int getAvailableSlots() const { return availableSlots; }

    // [Static member function]
    static int getTripCount() { return tripCount; }

    // [Unary operator overloading] written as a MEMBER function with no parameter.
    //   ++trip   adds ONE more seat to the trip
    Trip& operator++() {
        maxCapacity++;
        availableSlots++;
        return *this;
    }

    // [Binary operator overloading] as a MEMBER function:
    //   in  a < b   'a' is the object that calls it (this), 'b' is the parameter.
    //   Compares trips by price.
    bool operator<(const Trip& other) const {
        return price < other.price;
    }

    // [Binary operator overloading] as a FRIEND function:
    //   in  a == b   BOTH a and b are parameters (a friend has no 'this').
    //   Two trips are equal when they have the same trip ID.
    friend bool operator==(const Trip& a, const Trip& b);

    // [Friend function] + [Stream operator overloading]  output and input
    friend ostream& operator<<(ostream& out, const Trip& t);
    friend istream& operator>>(istream& in, Trip& t);

    // [Friend class] ALL functions of Admin may use Trip's private members.
    // (Admin::removeTrip() changes 'status' directly - see Admin.h)
    friend class Admin;
};

inline int Trip::tripCount = 0;

inline bool operator==(const Trip& a, const Trip& b) {
    return a.tripId == b.tripId;
}

inline ostream& operator<<(ostream& out, const Trip& t) {
    out << "Trip ID   : " << t.tripId << "\n"
        << "Title     : " << t.title << "\n"
        << "Location  : " << t.location << "\n"
        << "Price     : Rs. " << t.price << "\n"
        << "Dates     : " << t.startDate << " to " << t.endDate << "\n"
        << "Slots     : " << t.availableSlots << " / " << t.maxCapacity << "\n"
        << "Min Age   : " << t.minAge << "\n"
        << "Fitness   : " << toString(t.requiredFitness) << "\n"
        << "Status    : " << toString(t.status) << "\n";
    return out;
}

// Input order: title (one line), location (one line), then
//              price startDate endDate maxCapacity minAge fitness(0/1/2)
inline istream& operator>>(istream& in, Trip& t) {
    getline(in >> ws, t.title);      // 'ws' skips leftover spaces/newlines,
    getline(in >> ws, t.location);   // getline reads a whole line (titles have spaces)
    int fit;
    in >> t.price >> t.startDate >> t.endDate >> t.maxCapacity >> t.minAge >> fit;
    if (fit < 0 || fit > 2) fit = 0;                   // anything other than 0/1/2 becomes LOW
    t.requiredFitness = static_cast<FitnessLevel>(fit); // number 0/1/2 -> LOW/MODERATE/HIGH
    t.availableSlots = t.maxCapacity;
    return in;
}

#endif
