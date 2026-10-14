// =====================================================================
//  ProviderMenu.h  -  everything an ADVENTURE PROVIDER can do in the app
// =====================================================================
//  AdventureProvider::showMenu() shows the options. Each option is one
//  small "screen" function below it.
//
//  Use cases here: UC-03 Manage Trips (add, edit, remove),
//                  View Trip Bookings, Notify Booked Travelers
// =====================================================================
#ifndef PROVIDERMENU_H
#define PROVIDERMENU_H

#include "BookingSystem.h"
#include "Input.h"

// Asks for a trip ID and gives back the trip ONLY if this provider created it
inline Trip* askForMyTrip(BookingSystem& system, const AdventureProvider& provider) {
    Trip* trip = system.findTrip(readLine("Trip ID (like TRP-2): "));
    if (trip == nullptr || trip->getProviderId() != provider.getUserId()) {
        cout << "You have no trip with that ID.\n";
        return nullptr;
    }
    return trip;
}

inline void myTripsScreen(BookingSystem& system, const AdventureProvider& provider) {
    vector<Trip*> mine = system.tripsOf(provider);
    if (mine.empty()) {
        cout << "You have no trips yet.\n";
        return;
    }
    cout << "Your trips:\n";
    for (Trip* t : mine) t->printRow();
}

// UC-03 main flow: fill in the details -> check them (4a) -> publish
inline void createTripScreen(BookingSystem& system, AdventureProvider& provider) {
    cout << "\n--- CREATE A NEW TRIP ---\n";
    string title = readLine("Trip name: ");
    string location = readLine("Place: ");
    double price = readDouble("Price per seat (Rs.): ");
    string start = readLine("Start date (YYYY-MM-DD): ");
    string end = readLine("End date (YYYY-MM-DD): ");
    int seats = readInt("Total seats: ");
    int minAge = readInt("Minimum age: ");
    int fitness = readInt("Fitness needed (0 = LOW, 1 = MODERATE, 2 = HIGH): ");
    if (fitness < 0 || fitness > 2) {
        cout << "Not saved: fitness must be 0, 1 or 2.\n";
        return;
    }

    // [Returning objects from functions] createTrip() gives back a Trip object
    Trip trip = provider.createTrip(title, location, price, start, end, seats, minAge,
                                    static_cast<FitnessLevel>(fitness));

    // Step 4 / alternate flow 4a: check every detail before saving
    string problem = trip.checkDetails(system.getToday());
    if (problem != "") {
        cout << "Not saved: " << problem << "\n";
        return;
    }

    provider.publishTrip(trip);          // step 6: the trip goes live
    Trip* saved = system.addTrip(trip);
    cout << "Saved! " << saved->getTripId() << " is now live for travelers.\n";
}

// UC-03 edit: change the price or the dates of one of my trips
inline void editTripScreen(BookingSystem& system, AdventureProvider& provider) {
    Trip* trip = askForMyTrip(system, provider);
    if (trip == nullptr) return;
    if (trip->getStatus() == CLOSED) {
        cout << "This trip was removed, so it can not be edited.\n";
        return;
    }

    cout << "1. Change the price\n2. Change the dates\n";
    int what = readInt("Choose: ");
    if (what != 1 && what != 2) {
        cout << "No such option.\n";
        return;
    }

    // Try the change on a COPY first. Only if the copy passes the checks
    // is the real trip changed.
    Trip changed = *trip;
    double newPrice = 0;
    string newStart, newEnd;
    if (what == 1) {
        newPrice = readDouble("New price per seat (Rs.): ");
        changed.changePrice(newPrice);
    } else {
        newStart = readLine("New start date (YYYY-MM-DD): ");
        newEnd = readLine("New end date (YYYY-MM-DD): ");
        changed.changeDates(newStart, newEnd);
    }
    string problem = changed.checkDetails(system.getToday());
    if (problem != "") {
        cout << "Not saved: " << problem << "\n";
        return;
    }

    // Alternate flow 3a: people have already paid -> warn first
    int booked = system.countConfirmedBookings(*trip);
    if (booked > 0) {
        cout << "Warning: this trip has " << booked << " confirmed booking(s). "
             << "Those travelers will be emailed about the change.\n";
        if (!askYesNo("Save the change anyway?")) {
            cout << "Nothing changed.\n";
            return;
        }
    }

    stringstream message;   // builds the email text, just like cout builds output
    if (what == 1) {
        trip->changePrice(newPrice);
        message << trip->getTitle() << ": the price is now Rs. " << newPrice
                << " per seat (you keep the price you already paid).";
    } else {
        trip->changeDates(newStart, newEnd);
        message << trip->getTitle() << ": the new dates are " << newStart << " to " << newEnd << ".";
    }
    cout << "Saved.\n";
    system.notifyTravelers(*trip, message.str());   // 3a: email every booked traveler
}

// UC-03 remove (alternate flow 2a is checked inside removeTrip)
inline void removeTripScreen(BookingSystem& system, AdventureProvider& provider) {
    Trip* trip = askForMyTrip(system, provider);
    if (trip == nullptr) return;
    if (askYesNo("Remove '" + trip->getTitle() + "'?")) {
        provider.removeTrip(*trip);
    } else {
        cout << "Nothing changed.\n";
    }
}

// View Trip Bookings: who booked one of my trips
inline void tripBookingsScreen(BookingSystem& system, const AdventureProvider& provider) {
    Trip* trip = askForMyTrip(system, provider);
    if (trip == nullptr) return;
    vector<Booking*> list = system.bookingsForTrip(*trip);
    if (list.empty()) {
        cout << "No bookings for " << trip->getTitle() << " yet.\n";
        return;
    }
    cout << "Bookings for " << trip->getTitle() << ":\n";
    for (Booking* b : list) {
        cout << "  " << b->getBookingId() << " | " << b->getTraveler()->getName()
             << " | " << b->getTraveler()->getEmail() << " | seats " << b->getSeatsBooked()
             << " | " << toString(b->getStatus()) << "\n";
    }
}

// [Function overriding] AdventureProvider's version of User::showMenu()
inline void AdventureProvider::showMenu(BookingSystem& system) {
    while (true) {
        cout << "\n--- PROVIDER MENU (" << getAgencyName() << ") ---\n"
             << "1. My trips\n"
             << "2. Create a new trip\n"
             << "3. Edit a trip (price or dates)\n"
             << "4. Remove a trip\n"
             << "5. See who booked a trip\n"
             << "0. Log out\n";
        int choice = readInt("Choose: ");
        switch (choice) {
            case 1: myTripsScreen(system, *this); break;
            case 2: createTripScreen(system, *this); break;
            case 3: editTripScreen(system, *this); break;
            case 4: removeTripScreen(system, *this); break;
            case 5: tripBookingsScreen(system, *this); break;
            case 0: return;
            default: cout << "No such option.\n";
        }
    }
}

#endif
