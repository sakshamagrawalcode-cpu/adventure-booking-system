// =====================================================================
//  Receipt.h  -  a short receipt the traveler gets after booking
// =====================================================================
//  OOP topics in this file:
//    [Data conversion: class -> class]  Booking -> Receipt
//    [Friend function]  [Stream operator overloading]
// =====================================================================
#ifndef RECEIPT_H
#define RECEIPT_H

#include "Booking.h"

class Receipt {
private:
    string bookingId;
    string travelerName;
    string tripTitle;
    int seats;
    double amountPaid;

public:
    // [Data conversion: class -> class] a constructor that takes an object of
    // ANOTHER class. Because of it, a Booking can be turned into a Receipt:
    //     Receipt r = booking;
    Receipt(const Booking& b)
        : bookingId(b.getBookingId()),
          travelerName(b.getTraveler()->getName()),
          tripTitle(b.getTrip()->getTitle()),
          seats(b.getSeatsBooked()),
          amountPaid(b.getTotalCost()) {}

    // [Friend function] + [Stream operator overloading]
    friend ostream& operator<<(ostream& out, const Receipt& r);
};

inline ostream& operator<<(ostream& out, const Receipt& r) {
    out << "+------------- RECEIPT -------------+\n"
        << "  Booking : " << r.bookingId << "\n"
        << "  Name    : " << r.travelerName << "\n"
        << "  Trip    : " << r.tripTitle << "\n"
        << "  Seats   : " << r.seats << "\n"
        << "  Paid    : Rs. " << r.amountPaid << "\n"
        << "+-----------------------------------+\n";
    return out;
}

#endif
