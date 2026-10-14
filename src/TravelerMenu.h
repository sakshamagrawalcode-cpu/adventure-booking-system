// =====================================================================
//  TravelerMenu.h  -  everything a TRAVELER can do in the app
// =====================================================================
//  Traveler::showMenu() shows the options. Each option is one small
//  "screen" function below it, so every piece is short and easy to read.
//
//  Use cases here: Browse Adventures, UC-01 Book Adventure,
//                  UC-02 Cancel Booking, View My Bookings
// =====================================================================
#ifndef TRAVELERMENU_H
#define TRAVELERMENU_H

#include "BookingSystem.h"
#include "Receipt.h"
#include "Input.h"

// Prints a list of trips, or a message when the list is empty
inline void printTrips(const vector<Trip*>& list, const string& emptyMessage) {
    if (list.empty()) {
        cout << emptyMessage << "\n";
        return;
    }
    for (Trip* t : list) t->printRow();
}

inline void browseTripsScreen(BookingSystem& system) {
    cout << "Open trips:\n";
    printTrips(system.openTrips(), "No trips are open right now.");
}

// [Abstraction] the system finds trips through the Searchable interface
inline void searchTripsScreen(BookingSystem& system) {
    string keyword = readLine("Search for a place or trip name: ");
    if (keyword == "") {
        cout << "Type something to search for.\n";
        return;
    }
    printTrips(system.searchTrips(keyword), "No trips found for '" + keyword + "'.");
}

inline void tripDetailsScreen(BookingSystem& system) {
    Trip* trip = system.findTrip(readLine("Trip ID (like TRP-2): "));
    if (trip == nullptr) {
        cout << "No trip with that ID.\n";
        return;
    }
    cout << *trip;   // [Stream operator overloading]
}

// UC-01 Book Adventure: pick trip -> seats -> card -> pay -> booking + receipt
inline void bookTripScreen(BookingSystem& system, Traveler& traveler) {
    Trip* trip = system.findTrip(readLine("Trip ID to book (like TRP-2): "));
    if (trip == nullptr) {
        cout << "No trip with that ID.\n";
        return;
    }
    if (!system.isOpenForBooking(*trip)) return;

    // Steps 2-4: show the trip, ask for seats, check them before asking for money
    cout << trip->getTitle() << " - Rs. " << trip->getPrice() << " per seat, "
         << trip->getAvailableSlots() << " seat(s) left.\n";
    int seats = readInt("How many seats? ");
    if (!traveler.canBook(*trip, seats)) return;   // 4a: not enough seats / over the limit

    // Steps 5-6: payment details (checked by the simulated gateway)
    cout << "Total to pay: Rs. " << trip->getPrice() * seats << "\n";
    string cardNo = readLine("Card number (16 digits): ");
    string expiry = readLine("Card expiry (MM/YY): ");

    // Steps 7-9: book, email, show the booking ID
    Booking* booking = system.bookTrip(traveler, *trip, seats, cardNo, expiry);
    if (booking == nullptr) return;   // 6a: the payment failed, nothing was saved
    cout << *booking;

    // [Data conversion: class -> class] the Booking becomes a Receipt
    Receipt receipt = *booking;
    cout << receipt;
}

// UC-02 Cancel Booking
inline void cancelBookingScreen(BookingSystem& system, Traveler& traveler) {
    traveler.viewMyBookings(true);    // show what can be cancelled
    Booking* booking = system.findBooking(readLine("Booking ID to cancel (like BK-1): "));
    if (booking == nullptr || booking->getTraveler() != &traveler) {
        cout << "You have no booking with that ID.\n";
        return;
    }
    // Steps 2-3: ask to confirm. Alternate flow 3a: the traveler changes their mind.
    if (!askYesNo("Cancel " + booking->getBookingId() + " for " + booking->getTrip()->getTitle() + "?")) {
        cout << "Nothing changed. " << booking->getBookingId() << " is still "
             << toString(booking->getStatus()) << ".\n";
        return;
    }
    system.cancelBooking(traveler, *booking);   // steps 4-7, alternate flows 1a and 5a
}

inline void myBookingsScreen(Traveler& traveler) {
    if (askYesNo("Show only CONFIRMED bookings?")) {
        traveler.viewMyBookings(true);
    } else {
        traveler.viewMyBookings();   // [Default arguments in functions] onlyConfirmed = false
    }
}

inline void profileScreen(Traveler& traveler) {
    cout << traveler;   // [Stream operator overloading]
    if (!askYesNo("Update your name or phone?")) return;
    string newName = readLine("New name (press Enter to keep it): ");
    string newPhone = readLine("New phone (press Enter to keep it): ");
    traveler.updateProfile(newName, newPhone);
    cout << "Profile saved.\n";
}

// [Function overriding] Traveler's version of User::showMenu()
inline void Traveler::showMenu(BookingSystem& system) {
    while (true) {
        cout << "\n--- TRAVELER MENU (" << getName() << ") ---\n"
             << "1. Browse open trips\n"
             << "2. Search trips\n"
             << "3. See one trip's details\n"
             << "4. Book a trip\n"
             << "5. Cancel a booking\n"
             << "6. My bookings\n"
             << "7. My profile\n"
             << "0. Log out\n";
        int choice = readInt("Choose: ");
        switch (choice) {
            case 1: browseTripsScreen(system); break;
            case 2: searchTripsScreen(system); break;
            case 3: tripDetailsScreen(system); break;
            case 4: bookTripScreen(system, *this); break;
            case 5: cancelBookingScreen(system, *this); break;
            case 6: myBookingsScreen(*this); break;
            case 7: profileScreen(*this); break;
            case 0: return;
            default: cout << "No such option.\n";
        }
    }
}

#endif
