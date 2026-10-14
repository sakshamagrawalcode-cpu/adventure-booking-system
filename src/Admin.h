// =====================================================================
//  Admin.h  -  watches over the whole platform
// =====================================================================
//  Parent: User.   Child: SuperAdmin (see SuperAdmin.h)
//
//  OOP topics in this file:
//    [Hierarchical inheritance]  User -> Traveler / AdventureProvider / Admin
//    [Constructors in inheritance]  [Function overriding]
//    [Base-class pointers to derived objects]  [Dynamic binding]  viewAllUsers()
//    [Pointers to objects]  viewAllBookings()
//    [Friend class]  removeTrip() changes Trip's private data directly
// =====================================================================
#ifndef ADMIN_H
#define ADMIN_H

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

    // [Base-class pointers to derived objects] users[] is an array of User*,
    // but each pointer points to a Traveler / AdventureProvider / Admin / ... object.
    // [Dynamic binding] getRole() is virtual, so the version of the REAL
    // object's class runs - decided while the program runs, not while compiling.
    void viewAllUsers(User* users[], int count) const {
        for (int i = 0; i < count; i++) {
            cout << "  " << users[i]->getUserId() << " | " << users[i]->getName()
                 << " | " << users[i]->getRole() << "\n";
        }
    }

    // [Pointers to objects] an array of Booking*
    void viewAllBookings(Booking* bookings[], int count) const {
        for (int i = 0; i < count; i++) {
            if (bookings[i] == nullptr) continue;
            cout << "  " << bookings[i]->getBookingId()
                 << " | " << bookings[i]->getTraveler()->getName()
                 << " | " << bookings[i]->getTrip()->getTitle()
                 << " | " << toString(bookings[i]->getStatus())
                 << " | payment " << toString(bookings[i]->getPayment().getStatus()) << "\n";
        }
    }

    // UC-03 Manage Trips (admin as secondary actor), alternate flow 2a.
    // [Friend class] Trip wrote 'friend class Admin', so Admin can read and change
    // Trip's PRIVATE members (trip.title, trip.status) directly. Other classes cannot.
    bool removeTrip(Trip& trip) const {
        if (!trip.canBeRemoved()) {
            cout << "Cannot remove '" << trip.title << "': it has confirmed bookings.\n";
            return false;
        }
        trip.status = CLOSED;   // kept as CLOSED, not erased, so the record stays
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
