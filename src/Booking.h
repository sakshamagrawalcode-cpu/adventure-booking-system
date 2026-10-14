#ifndef BOOKING_H
#define BOOKING_H

#include "Trip.h"
#include "Traveler.h"
#include "Payment.h"

enum BookingStatus { CONFIRMED, CANCELLED };

inline string toString(BookingStatus s) {
    if (s == CONFIRMED) return "CONFIRMED";
    return "CANCELLED";
}

class Booking {
private:
    string bookingId;
    string bookingDate;
    int seatsBooked;
    double totalCost;
    BookingStatus status;

    // [Pointer to objects] Booking does not own the Traveler or the Trip,
    // it only points to them (association in the class diagram)
    Traveler* traveler;
    Trip* trip;

    // Composition: the Payment lives inside the Booking (Booking *-- Payment)
    Payment payment;

    // [Static variable] counts bookings, also used to generate bookingId
    static int bookingCount;

    // Email Service is an outside system, so the email is only simulated
    void triggerEmail(const string& message) const {
        cout << "[Email to " << traveler->getEmail() << "] " << message << "\n";
    }

public:
    // A Booking is created only AFTER the payment succeeds (UC-01 step 7),
    // so every new booking starts as CONFIRMED.
    Booking(Traveler* traveler, Trip* trip, int seatsBooked,
            string bookingDate, const Payment& payment)
        : payment(payment) {
        // [this pointer] parameter names are the same as the data members
        this->traveler = traveler;
        this->trip = trip;
        this->seatsBooked = seatsBooked;
        this->bookingDate = bookingDate;

        bookingCount++;
        bookingId = "BK-" + to_string(bookingCount);

        this->trip->reserveSlots(seatsBooked);   // seats left go down
        totalCost = calculateTotalCost();
        status = CONFIRMED;
        triggerEmail("Booking " + bookingId + " confirmed for " + this->trip->getTitle());
    }

    // [Pointer to objects] arrow operator: trip->getPrice()
    double calculateTotalCost() const {
        return trip->getPrice() * seatsBooked;
    }

    // UC-02 Cancel Booking. Dates are "YYYY-MM-DD", so string compare works.
    bool cancel(const PaymentGateway& gateway, const string& today) {
        if (status == CANCELLED) {
            cout << bookingId << " is already cancelled.\n";
            return false;
        }
        if (today > trip->getStartDate()) {                  // 1a
            cout << "Trip date has passed. " << bookingId << " cannot be cancelled.\n";
            return false;
        }

        status = CANCELLED;                                  // step 4
        trip->releaseSlots(seatsBooked);                     // seats go back

        if (payment.processRefund(gateway) == REFUNDED) {    // step 5
            triggerEmail("Booking " + bookingId + " cancelled. Refund done.");
        } else {                                             // 5a
            triggerEmail("Booking " + bookingId + " cancelled. Refund PENDING, admin will settle it.");
        }
        return true;
    }

    string getBookingId() const { return bookingId; }
    BookingStatus getStatus() const { return status; }
    int getSeatsBooked() const { return seatsBooked; }
    double getTotalCost() const { return totalCost; }
    Traveler* getTraveler() const { return traveler; }
    Trip* getTrip() const { return trip; }
    Payment& getPayment() { return payment; }

    // [Static function]
    static int getBookingCount() {
        return bookingCount;
    }

    // [Stream operator overloading using friend function]
    friend ostream& operator<<(ostream& out, const Booking& b);
};

inline int Booking::bookingCount = 0;

inline ostream& operator<<(ostream& out, const Booking& b) {
    out << "Booking ID : " << b.bookingId << "\n"
        << "Traveler   : " << b.traveler->getName() << "\n"
        << "Trip       : " << b.trip->getTitle() << " (" << b.trip->getTripId() << ")\n"
        << "Seats      : " << b.seatsBooked << "\n"
        << "Total      : Rs. " << b.totalCost << "\n"
        << "Date       : " << b.bookingDate << "\n"
        << "Status     : " << toString(b.status) << "\n"
        << "Payment    : " << b.payment << "\n";
    return out;
}

// ------------------------------------------------------------------
// Traveler's booking functions are written HERE, not in Traveler.h,
// because they create and use Booking objects. The full Booking class
// is only known after the definition above. (Traveler.h has only
// "class Booking;" - a forward declaration.)
// ------------------------------------------------------------------

// UC-01 Book Adventure. Returns nullptr when no booking is made (4a / 6a).
// The Booking is made with new -> main.cpp must delete it.
inline Booking* Traveler::bookTrip(Trip& trip, int seats, const PaymentGateway& gateway,
                                   const string& cardNo, const string& expiry,
                                   const string& today) {
    // Step 4 / 4a: check that many seats are still free
    if (seats <= 0) {
        cout << "Number of seats must be at least 1.\n";
        return nullptr;
    }
    if (seats > trip.getAvailableSlots()) {
        cout << "Only " << trip.getAvailableSlots() << " seat(s) left. Enter a smaller number.\n";
        return nullptr;
    }

    // Steps 5-6: pay first
    Payment payment(trip.getPrice() * seats, today);
    if (payment.processPayment(gateway, cardNo, expiry) != SUCCESS) {
        cout << "Payment failed. Nothing saved, seats unchanged.\n";   // 6a
        return nullptr;
    }

    // Step 7: only now is the booking created.
    // [this pointer] 'this' = address of the Traveler who called bookTrip()
    Booking* booking = new Booking(this, &trip, seats, today, payment);
    myBookings.push_back(booking);
    return booking;
}

// UC-02 Cancel Booking
inline bool Traveler::cancelBooking(Booking* booking, const PaymentGateway& gateway,
                                    const string& today) {
    // [this pointer] a traveler can cancel only their OWN booking
    if (booking == nullptr || booking->getTraveler() != this) {
        cout << "This booking does not belong to " << getName() << ".\n";
        return false;
    }
    return booking->cancel(gateway, today);
}

inline void Traveler::viewMyBookings() const {
    cout << getName() << " has " << myBookings.size() << " booking(s):\n";
    for (Booking* b : myBookings) {
        cout << "  " << b->getBookingId() << " | " << b->getTrip()->getTitle()
             << " | seats " << b->getSeatsBooked()
             << " | " << toString(b->getStatus()) << "\n";
    }
}

#endif
