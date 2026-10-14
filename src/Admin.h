#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Trip.h"
#include "Booking.h"

// [Virtual base class] only ONE User part, same as Traveler and AdventureProvider
class Admin : virtual public User {
public:
    Admin(string id, string n, string e, string pass, string ph)
        : User(id, n, e, pass, ph) {}

    // [Virtual function] overrides User::getRole()
    string getRole() const override {
        return "Admin";
    }

    // [Pointer to derived classes] users[] is an array of User*,
    // but each pointer points to a Traveler / AdventureProvider / Admin object.
    // getRole() is virtual, so the child's version runs for each one.
    void viewAllUsers(User* users[], int count) const {
        for (int i = 0; i < count; i++) {
            cout << "  " << users[i]->getUserId() << " | " << users[i]->getName()
                 << " | " << users[i]->getRole() << "\n";
        }
    }

    // [Pointer to objects] array of Booking*
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

    // UC-03 (admin as secondary actor), alternate flow 2a
    bool removeTrip(Trip& trip) const {
        if (!trip.canBeRemoved()) {
            cout << "Cannot remove '" << trip.getTitle() << "': it has confirmed bookings.\n";
            return false;
        }
        trip.close();
        cout << "'" << trip.getTitle() << "' removed (status CLOSED).\n";
        return true;
    }

    // UC-02 alternate flow 5a: admin settles a refund that failed earlier
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
