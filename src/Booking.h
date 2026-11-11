// Booking.h
// Ticket: one person on a booking.
// Booking: one booking made by a customer for one adventure.

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

// One person going on the adventure
struct Ticket {
    string name;
    int age;
};

class Booking {
public:
    // Static data member: one value shared by the whole class, not one per object
    static const int MAX_TICKETS = 20;

private:
    string id;
    string customerId;     // who booked
    string adventureId;    // which adventure
    vector<Ticket> tickets;
    int totalPrice;        // saved at booking time
    string status;         // "BOOKED" or "CANCELLED"

public:
    // Constructor: every new booking starts as "BOOKED"
    Booking(string id, string customerId, string adventureId,
            vector<Ticket> tickets, int totalPrice) {
        this->id = id;
        this->customerId = customerId;
        this->adventureId = adventureId;
        this->tickets = tickets;
        this->totalPrice = totalPrice;
        this->status = "BOOKED";
    }

    // Copy constructor: makes a new Booking with the same values as another one.
    // It runs every time a booking is copied, e.g. when a vector<Booking> is returned.
    // (C++ would make the same one automatically; it is written here to show how it works.)
    Booking(const Booking& other) {
        id = other.id;
        customerId = other.customerId;
        adventureId = other.adventureId;
        tickets = other.tickets;
        totalPrice = other.totalPrice;
        status = other.status;
    }

    // Copy assignment (b1 = b2): needed because we wrote our own copy constructor
    Booking& operator=(const Booking& other) {
        id = other.id;
        customerId = other.customerId;
        adventureId = other.adventureId;
        tickets = other.tickets;
        totalPrice = other.totalPrice;
        status = other.status;
        return *this;
    }

    // Getters
    string getId()            { return id; }
    string getCustomerId()    { return customerId; }
    string getAdventureId()   { return adventureId; }
    vector<Ticket> getTickets() { return tickets; }
    int    getTotalPrice()    { return totalPrice; }
    string getStatus()        { return status; }

    // Number of tickets = number of seats this booking takes
    int getTicketCount() {
        return tickets.size();
    }

    bool isCancelled() {
        return status == "CANCELLED";
    }

    // Cancels the booking. Throws an error if it is already cancelled.
    void cancel() {
        if (isCancelled()) {
            throw runtime_error("Booking is already cancelled");
        }
        status = "CANCELLED";
    }

    // Stream operator overloading: prints status, tickets and total with  cout << booking;
    // (the menu prints the adventure name). It is a friend, so it reads private data.
    friend ostream& operator<<(ostream& out, const Booking& b) {
        out << "Status  : " << b.status << "\n";
        out << "Tickets : " << b.tickets.size() << "\n";
        for (int i = 0; i < (int)b.tickets.size(); i++) {
            out << "   " << (i + 1) << ". " << b.tickets[i].name
                << " (age " << b.tickets[i].age << ")\n";
        }
        out << "Total   : Rs. " << b.totalPrice << "\n";
        return out;
    }
};
