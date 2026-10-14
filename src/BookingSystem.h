// =====================================================================
//  BookingSystem.h  -  keeps ALL users, trips and bookings in one place
// =====================================================================
//  The menus (TravelerMenu.h, ProviderMenu.h, AdminMenu.h, StartMenu.h)
//  ask this class for data and tell it what to do.
//
//  OOP topics in this file:
//    [Composition]  the system owns its PaymentGateway, users, trips, bookings
//    [Dynamic memory allocation]  every user, trip and booking is made with new
//    [Destructor]  deletes everything the system made
//    [Abstraction]  searchTrips() / searchUsers() only use Searchable::matches()
//    [Base-class pointers to derived objects]  vector<User*> holds every kind of user
// =====================================================================
#ifndef BOOKINGSYSTEM_H
#define BOOKINGSYSTEM_H

#include <vector>
#include "User.h"
#include "Trip.h"
#include "Traveler.h"
#include "AdventureProvider.h"
#include "Admin.h"
#include "SuperAdmin.h"
#include "TravelerProvider.h"
#include "Booking.h"
#include "Payment.h"
#include "PaymentGateway.h"

class BookingSystem {
private:
    string today;                // the date the system thinks it is (YYYY-MM-DD)
    PaymentGateway gateway;      // [Composition] the system has exactly one gateway

    // [Dynamic memory allocation] every object in these lists was made with new,
    // so the system must delete them (see the destructor)
    vector<User*> users;         // [Base-class pointers] Traveler, Admin, ... all as User*
    vector<Trip*> trips;
    vector<Booking*> bookings;

    int nextUserNumber;          // used to make IDs for new travelers: U-5001, U-5002, ...

public:
    BookingSystem(string todayDate)
        : today(todayDate), gateway("SimulatedGateway"), nextUserNumber(5001) {}

    // [Destructor] frees every object the system made with new.
    // [Virtual destructor] in User makes 'delete u' remove the WHOLE child object.
    ~BookingSystem() {
        for (Booking* b : bookings) delete b;
        for (Trip* t : trips) delete t;
        for (User* u : users) delete u;
    }

    // The system holds pointers it must delete, so it must never be copied
    // (two copies would delete the same objects twice).
    BookingSystem(const BookingSystem&) = delete;
    BookingSystem& operator=(const BookingSystem&) = delete;

    string getToday() const { return today; }
    void setToday(const string& date) { today = date; }
    PaymentGateway& getGateway() { return gateway; }
    const vector<User*>& getUsers() const { return users; }
    const vector<Trip*>& getTrips() const { return trips; }
    const vector<Booking*>& getBookings() const { return bookings; }

    // ------------------------------ USERS ------------------------------

    void addUser(User* user) { users.push_back(user); }

    // Returns the user with this email and password, or nullptr
    User* login(const string& email, const string& password) const {
        for (User* u : users) {
            if (u->login(email, password)) return u;
        }
        return nullptr;
    }

    bool emailTaken(const string& email) const {
        for (User* u : users) {
            if (u->getEmail() == email) return true;
        }
        return false;
    }

    // Register checks. Returns "" when everything is fine, otherwise WHAT is wrong.
    string checkNewTraveler(const string& name, const string& email, const string& password,
                            const string& dob, int fitness) const {
        if (name == "") return "Name can not be empty.";
        if (email.find('@') == string::npos) return "Email must have an @ in it.";
        if (emailTaken(email)) return "This email is already registered.";
        if (password.length() < 4) return "Password must be at least 4 characters.";
        if (!looksLikeDate(dob)) return "Date of birth must look like YYYY-MM-DD.";
        if (fitness < 0 || fitness > 2) return "Fitness must be 0, 1 or 2.";
        return "";
    }

    Traveler* registerTraveler(const string& name, const string& email, const string& password,
                               const string& phone, Traveler::EmergencyContact contact,
                               const string& dob, const string& blood, FitnessLevel fitness) {
        string id = "U-" + to_string(nextUserNumber);
        nextUserNumber++;
        Traveler* traveler = new Traveler(id, name, email, password, phone,
                                          contact, dob, blood, fitness);
        users.push_back(traveler);
        return traveler;
    }

    // [Abstraction] only calls matches() from the Searchable interface
    vector<User*> searchUsers(const string& keyword) const {
        vector<User*> found;
        for (User* u : users) {
            if (u->matches(keyword)) found.push_back(u);
        }
        return found;
    }

    // ------------------------------ TRIPS ------------------------------

    // Stores a copy of the trip and returns where it is kept
    Trip* addTrip(const Trip& trip) {
        Trip* saved = new Trip(trip);
        trips.push_back(saved);
        return saved;
    }

    Trip* findTrip(const string& tripId) const {
        for (Trip* t : trips) {
            if (t->getTripId() == tripId) return t;
        }
        return nullptr;
    }

    // A trip can be booked if it is PUBLISHED and has not started yet
    bool isOpen(const Trip& trip) const {
        return trip.getStatus() == PUBLISHED && trip.getStartDate() > today;
    }

    // Same check, but tells the user WHY a trip can not be booked
    bool isOpenForBooking(const Trip& trip) const {
        if (trip.getStatus() != PUBLISHED) {
            cout << "This trip is not open for booking (status " << toString(trip.getStatus()) << ").\n";
            return false;
        }
        if (trip.getStartDate() <= today) {
            cout << "This trip has already started.\n";
            return false;
        }
        return true;
    }

    vector<Trip*> openTrips() const {
        vector<Trip*> open;
        for (Trip* t : trips) {
            if (isOpen(*t)) open.push_back(t);
        }
        return open;
    }

    // [Abstraction] only calls matches() from the Searchable interface
    vector<Trip*> searchTrips(const string& keyword) const {
        vector<Trip*> found;
        for (Trip* t : trips) {
            if (isOpen(*t) && t->matches(keyword)) found.push_back(t);
        }
        return found;
    }

    vector<Trip*> tripsOf(const AdventureProvider& provider) const {
        vector<Trip*> mine;
        for (Trip* t : trips) {
            if (t->getProviderId() == provider.getUserId()) mine.push_back(t);
        }
        return mine;
    }

    // ----------------------------- BOOKINGS ----------------------------

    // UC-01 Book Adventure. Returns the new booking, or nullptr if it failed.
    Booking* bookTrip(Traveler& traveler, Trip& trip, int seats,
                      const string& cardNo, const string& expiry) {
        if (!isOpenForBooking(trip)) return nullptr;
        Booking* booking = traveler.bookTrip(trip, seats, gateway, cardNo, expiry, today);
        if (booking != nullptr) bookings.push_back(booking);   // the system owns it now
        return booking;
    }

    // UC-02 Cancel Booking
    bool cancelBooking(Traveler& traveler, Booking& booking) {
        return traveler.cancelBooking(&booking, gateway, today);
    }

    Booking* findBooking(const string& bookingId) const {
        for (Booking* b : bookings) {
            if (b->getBookingId() == bookingId) return b;
        }
        return nullptr;
    }

    vector<Booking*> bookingsForTrip(const Trip& trip) const {
        vector<Booking*> list;
        for (Booking* b : bookings) {
            if (b->getTrip() == &trip) list.push_back(b);
        }
        return list;
    }

    int countConfirmedBookings(const Trip& trip) const {
        int count = 0;
        for (Booking* b : bookings) {
            if (b->getTrip() == &trip && b->getStatus() == CONFIRMED) count++;
        }
        return count;
    }

    // UC-03 alternate flow 3a: email every traveler with a CONFIRMED booking
    // (the Email Service is outside our system, so the email is only printed)
    void notifyTravelers(const Trip& trip, const string& message) const {
        for (Booking* b : bookings) {
            if (b->getTrip() == &trip && b->getStatus() == CONFIRMED) {
                cout << "[Email to " << b->getTraveler()->getEmail() << "] " << message << "\n";
            }
        }
    }

    // --------------------------- SAMPLE DATA ---------------------------

    // Creates a trip for a provider, publishes it and stores it
    void addPublishedTrip(AdventureProvider& provider, string title, string location,
                          double price, string start, string end,
                          int seats, int minAge, FitnessLevel fitness) {
        Trip trip = provider.createTrip(title, location, price, start, end, seats, minAge, fitness);
        provider.publishTrip(trip);
        addTrip(trip);
    }

    // Some users and trips, so the app can be used straight away
    void loadSampleData() {
        SuperAdmin* vikram = new SuperAdmin("U-1000", "Vikram Mehta", "vikram.mehta@trekmate.in",
                                            "vikram@123", "+91-98200-10000", "TrekMate Pvt Ltd");
        Admin* sneha = new Admin("U-1001", "Sneha Iyer", "sneha.iyer@trekmate.in",
                                 "sneha@123", "+91-98200-11001");
        AdventureProvider* rohit = new AdventureProvider(
            "U-1004", "Rohit Thapa", "ops@himalayantrails.in", "rohit@123", "+91-98110-44521",
            "Himalayan Trails Pvt Ltd", "HP/ADV/2025/0871", "ATOAI Certified", 4.6, true);
        TravelerProvider* karan = new TravelerProvider(
            "U-3050", "Karan Negi", "karan.negi@spitiexpeditions.in", "karan@123", "+91-94180-55210",
            Traveler::EmergencyContact("Pooja Negi", "+91-94180-55211"), "1995-06-14", "O+", HIGH,
            "Spiti Expeditions", "HP/ADV/2024/0412", "IMF Certified", 4.8, true);
        Traveler* aarav = new Traveler(
            "U-2031", "Aarav Sharma", "aarav.sharma@gmail.com", "aarav@123", "+91-99300-27781",
            Traveler::EmergencyContact("Meera Sharma", "+91-99300-27780"), "2004-03-22", "B+", MODERATE);

        addUser(vikram);
        addUser(sneha);
        addUser(rohit);
        addUser(karan);
        addUser(aarav);

        addPublishedTrip(*rohit, "Rishikesh River Rafting", "Rishikesh, Uttarakhand", 1500,
                         "2026-10-25", "2026-10-25", 10, 14, LOW);
        addPublishedTrip(*rohit, "Hampta Pass Trek", "Manali, Himachal Pradesh", 4500,
                         "2026-11-12", "2026-11-17", 20, 18, MODERATE);
        addPublishedTrip(*rohit, "Kedarkantha Winter Trek", "Uttarkashi, Uttarakhand", 8500,
                         "2026-12-10", "2026-12-15", 15, 16, MODERATE);
        addPublishedTrip(*rohit, "Chadar Frozen River Trek", "Leh, Ladakh", 18500,
                         "2027-01-10", "2027-01-18", 15, 21, HIGH);
        addPublishedTrip(*karan, "Bir Billing Paragliding", "Bir, Himachal Pradesh", 3000,
                         "2026-11-01", "2026-11-01", 6, 18, LOW);
        addPublishedTrip(*karan, "Spiti Valley Winter Expedition", "Kaza, Himachal Pradesh", 12000,
                         "2027-02-05", "2027-02-12", 10, 18, HIGH);
    }
};

#endif
