// =====================================================================
//  Admin.h  -  watches over the whole platform
// =====================================================================
//  Parent: User.   Child: SuperAdmin (see SuperAdmin.h)
//  Menu:   AdminMenu.h
//
//  OOP topics in this file:
//    [Hierarchical inheritance]  User -> Traveler / AdventureProvider / Admin
//    [Constructors in inheritance]  [Function overriding]
//    [Base-class pointers to derived objects]  [Dynamic binding]  viewAllUsers()
//    [Pointers to objects]  viewAllBookings()
//    [Friend class]  removeTrip() and tripReport() read Trip's private data
// =====================================================================
#ifndef ADMIN_H
#define ADMIN_H

#include <vector>
#include "User.h"
#include "Trip.h"
#include "Booking.h"

// Normal (not virtual) inheritance: Admin is not part of the diamond,
// only Traveler and AdventureProvider are (see TravelerProvider.h).
class Admin : public User {
public:
    // [Constructors in inheritance] the User part is built FIRST by calling User(...)
    Admin(string id, string n, string e, string pass, string ph)
        : User(id, n, e, pass, ph) {
        traceConstructor("Admin");
    }

    // [Function overriding] fills in User's pure virtual getRole()
    string getRole() const override { return "Admin"; }

    // [Function overriding] the admin's own menu. Body: AdminMenu.h
    void showMenu(BookingSystem& system) override;

    // [Base-class pointers to derived objects] every element is a User*,
    // but each one points to a Traveler / AdventureProvider / Admin / ... object.
    // [Dynamic binding] getRole() is virtual, so the version of the REAL
    // object's class runs - decided while the program runs, not while compiling.
    void viewAllUsers(const vector<User*>& users) const {
        for (User* u : users) {
            cout << "  " << u->getUserId() << " | " << u->getName()
                 << " | " << u->getEmail() << " | " << u->getRole() << "\n";
        }
    }

    // [Pointers to objects] a list of Booking pointers
    void viewAllBookings(const vector<Booking*>& bookings) const {
        if (bookings.empty()) cout << "  (no bookings yet)\n";
        for (Booking* b : bookings) {
            cout << "  " << b->getBookingId()
                 << " | " << b->getTraveler()->getName()
                 << " | " << b->getTrip()->getTitle()
                 << " | seats " << b->getSeatsBooked()
                 << " | " << toString(b->getStatus())
                 << " | payment " << toString(b->getPayment().getStatus()) << "\n";
        }
    }

    // Report: for every trip, how many seats are sold and how much money came in.
    // [Friend class] reads Trip's PRIVATE members (title, status, maxCapacity,
    // availableSlots) directly, because Trip wrote 'friend class Admin'.
    void tripReport(const vector<Trip*>& trips, const vector<Booking*>& bookings) const {
        for (Trip* t : trips) {
            double money = 0;
            for (Booking* b : bookings) {
                if (b->getTrip() == t && b->getStatus() == CONFIRMED) money += b->getTotalCost();
            }
            cout << "  " << t->tripId << " | " << t->title << " | " << toString(t->status)
                 << " | seats sold " << (t->maxCapacity - t->availableSlots) << " of " << t->maxCapacity
                 << " | money collected Rs. " << money << "\n";
        }
    }

    // UC-03 Manage Trips (admin as secondary actor), alternate flow 2a.
    // [Friend class] uses Trip's private members to show the exact seat count.
    bool removeTrip(Trip& trip) const {
        if (trip.status == CLOSED) {
            cout << "'" << trip.title << "' is already removed.\n";
            return false;
        }
        if (!trip.canBeRemoved()) {
            cout << "Cannot remove '" << trip.title << "': "
                 << (trip.maxCapacity - trip.availableSlots) << " seat(s) are booked.\n";
            return false;
        }
        trip.close();
        cout << "'" << trip.title << "' removed (status " << toString(trip.status) << ").\n";
        return true;
    }

    // UC-02 alternate flow 5a: the admin settles a refund that failed earlier
    bool settlePendingRefund(Payment& payment, const PaymentGateway& gateway) const {
        if (payment.getStatus() != PENDING) {
            cout << "No pending refund on " << payment.getPaymentId() << ".\n";
            return false;
        }
        payment.processRefund(gateway);
        cout << "Refund for " << payment.getPaymentId() << " is now "
             << toString(payment.getStatus()) << ".\n";
        return payment.getStatus() == REFUNDED;
    }
};

#endif
