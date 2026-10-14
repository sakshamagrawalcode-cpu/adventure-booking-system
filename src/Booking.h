// =====================================================================
//  Booking.h  -  one booking: a traveler + a trip + seats + a payment
// =====================================================================
//  Made in UC-01 (Book Adventure), cancelled in UC-02 (Cancel Booking).
//
//  This file ALSO has the bodies of Traveler's booking functions
//  (bookTrip, cancelBooking, viewMyBookings) at the bottom - see why there.
//
//  OOP topics in this file:
//    [Pointers to objects]  arrow operator  trip->getPrice()
//    [this pointer]  [Composition]  Booking owns its Payment
//    [Dynamic memory allocation]  new Booking(...)
//    [Static data member]  [Static member function]
//    [Inline function]  [Function overloading]  toString()
//    [Friend function]  [Stream operator overloading]
//    [Function prototype]  (definitions of Traveler's functions)
// =====================================================================
#ifndef BOOKING_H
#define BOOKING_H

#include "Trip.h"
#include "Traveler.h"
#include "Payment.h"

enum BookingStatus { CONFIRMED, CANCELLED };

// [Inline function] + [Function overloading] another toString() version
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

    // [Pointers to objects] the Booking does NOT own the Traveler or the Trip,
    // it only points to them (association in the class diagram)
    Traveler* traveler;
    Trip* trip;

    // [Composition] the Payment object lives INSIDE the Booking (Booking *-- Payment)
    Payment payment;

    // [Static data member] counts bookings; also used to make the booking ID
    static int bookingCount;

    // The Email Service is an outside system, so the email is only printed
    void triggerEmail(const string& message) const {
        cout << "[Email to " << traveler->getEmail() << "] " << message << "\n";
    }

public:
    // A Booking is made only AFTER the payment succeeds (UC-01 step 7),
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

    // [Pointers to objects] arrow operator:  trip->getPrice()
    double calculateTotalCost() const {
        return trip->getPrice() * seatsBooked;
    }

    // UC-02 Cancel Booking. Dates are "YYYY-MM-DD", so comparing strings works.
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

    // [Static member function]
    static int getBookingCount() { return bookingCount; }

    // [Friend function] + [Stream operator overloading]
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

// ---------------------------------------------------------------------
// Traveler's booking functions are written HERE, not in Traveler.h.
// Traveler.h has only their [Function prototype]s, because these bodies
// create and use Booking objects, and the full Booking class is only
// known after the definition above.
// ---------------------------------------------------------------------

// UC-01 Book Adventure. Returns nullptr when no booking is made (4a / 6a).
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
    // [Dynamic memory allocation] 'new' makes the Booking on the heap and gives
    // back its address. It stays alive until someone calls 'delete' (main() does).
    // [this pointer] 'this' = the address of the Traveler who called bookTrip()
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

// [Default arguments in functions] the default value (= false) is written ONLY
// in the declaration inside Traveler.h, never again here in the definition.
inline void Traveler::viewMyBookings(bool onlyConfirmed) const {
    cout << getName() << "'s " << (onlyConfirmed ? "CONFIRMED " : "") << "bookings:\n";
    for (Booking* b : myBookings) {          // for each booking pointer in the list
        if (onlyConfirmed && b->getStatus() != CONFIRMED) continue;
        cout << "  " << b->getBookingId() << " | " << b->getTrip()->getTitle()
             << " | seats " << b->getSeatsBooked()
             << " | " << toString(b->getStatus()) << "\n";
    }
}

#endif
