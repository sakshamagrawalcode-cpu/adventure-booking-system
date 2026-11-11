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

    // Prints status, tickets and total (the menu prints the adventure name)
    void show() {
        cout << "Status  : " << status << "\n";
        cout << "Tickets : " << getTicketCount() << "\n";
        for (int i = 0; i < getTicketCount(); i++) {
            cout << "   " << (i + 1) << ". " << tickets[i].name
                 << " (age " << tickets[i].age << ")\n";
        }
        cout << "Total   : Rs. " << totalPrice << "\n";
    }
};
