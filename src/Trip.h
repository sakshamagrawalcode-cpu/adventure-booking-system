#ifndef TRIP_H
#define TRIP_H

#include <iostream>
#include <string>
using namespace std;

enum FitnessLevel { LOW, MODERATE, HIGH };
enum TripStatus { DRAFT, PENDING_APPROVAL, PUBLISHED, CLOSED };

inline string toString(FitnessLevel f) {
    if (f == LOW) return "LOW";
    if (f == MODERATE) return "MODERATE";
    return "HIGH";
}

inline string toString(TripStatus s) {
    if (s == DRAFT) return "DRAFT";
    if (s == PENDING_APPROVAL) return "PENDING_APPROVAL";
    if (s == PUBLISHED) return "PUBLISHED";
    return "CLOSED";
}

class Trip {
private:
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

    // [Static variable] counts trips created, also used to generate tripId
    static int tripCount;

    bool hasCapacityFor(int count) const {
        return count > 0 && count <= availableSlots;
    }

    void assignNewId() {
        tripCount++;
        tripId = "TRP-" + to_string(tripCount);
    }

public:
    // Default constructor: used when trip details are read with operator>>
    Trip()
        : price(0), maxCapacity(0), availableSlots(0), minAge(0),
          requiredFitness(LOW), status(DRAFT) {
        assignNewId();
    }

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

    // Used when a trip is removed: kept as CLOSED, not erased (record stays)
    void close() { status = CLOSED; }

    // UC-03 alternate flow 2a: seats are reserved only by CONFIRMED bookings,
    // so if any seat is taken, the trip has confirmed bookings
    bool canBeRemoved() const { return availableSlots == maxCapacity; }

    int getAvailableSlots() const { return availableSlots; }
    double getPrice() const { return price; }
    string getTitle() const { return title; }
    string getTripId() const { return tripId; }
    string getStartDate() const { return startDate; }

    // [Static function]
    static int getTripCount() {
        return tripCount;
    }

    // [Stream operator overloading using friend function] - output and input
    friend ostream& operator<<(ostream& out, const Trip& t);
    friend istream& operator>>(istream& in, Trip& t);
};

inline int Trip::tripCount = 0;

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

// Input order: title, location (one line each), then
// price startDate endDate maxCapacity minAge fitness(0/1/2)
inline istream& operator>>(istream& in, Trip& t) {
    getline(in >> ws, t.title);
    getline(in >> ws, t.location);
    int fit;
    in >> t.price >> t.startDate >> t.endDate >> t.maxCapacity >> t.minAge >> fit;
    if (fit < 0 || fit > 2) fit = 0;   // anything other than 0/1/2 becomes LOW
    t.requiredFitness = static_cast<FitnessLevel>(fit);
    t.availableSlots = t.maxCapacity;
    return in;
}

#endif
