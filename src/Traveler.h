// =====================================================================
//  Traveler.h  -  a person who BOOKS trips
// =====================================================================
//  Parent: User.   Child: TravelerProvider (see TravelerProvider.h)
//  Menu:   TravelerMenu.h
//
//  OOP topics in this file:
//    [Single inheritance]  Traveler -> User
//    [Virtual inheritance] 'virtual public User' (needed by TravelerProvider)
//    [Constructors in inheritance]  [Function overriding]
//    [Virtual functions]  maxSeatsPerBooking() - a rule that changes by user type
//    [Nested class]  EmergencyContact
//    [Default arguments in constructor]  EmergencyContact(string n = "", string p = "")
//    [Composition]  the EmergencyContact object lives inside the Traveler
//    [Aggregation]  keeps pointers to its bookings, but does not own them
//    [Function prototype]  bookTrip(), cancelBooking(), viewMyBookings(), showMenu()
//    [Default arguments in functions]  viewMyBookings(bool onlyConfirmed = false)
//    [Returning objects from functions]  getEmergencyContact()
// =====================================================================
#ifndef TRAVELER_H
#define TRAVELER_H

#include <vector>
#include "User.h"
#include "Trip.h"

// Forward declarations: Traveler only uses POINTERS / references to these,
// so the full classes are not needed in this file.
class Booking;
class PaymentGateway;

// [Virtual inheritance] "virtual public User" means: if a later class gets User
// through TWO parents, it still keeps only ONE User part. (See TravelerProvider.h)
class Traveler : virtual public User {
public:
    // [Nested class] a class inside a class. It only makes sense for a Traveler,
    // so outside it is written as  Traveler::EmergencyContact
    class EmergencyContact {
    private:
        string name;
        string phone;

    public:
        // [Default arguments in constructor] both values can be left out:
        //   EmergencyContact c;   ->  name = "", phone = ""
        EmergencyContact(string n = "", string p = "") : name(n), phone(p) {}

        string getName() const { return name; }
        string getPhone() const { return phone; }
    };

private:
    EmergencyContact emergencyContact;   // [Composition] lives and dies with the Traveler
    string dateOfBirth;
    string bloodGroup;
    FitnessLevel fitnessLevel;

    // [Aggregation] pointers to this traveler's bookings.
    // The Traveler does NOT own them (the BookingSystem deletes them); it only keeps a list.
    vector<Booking*> myBookings;

public:
    // [Constructors in inheritance] the User part is built FIRST by calling User(...)
    Traveler(string id, string n, string e, string pass, string ph,
             EmergencyContact contact, string dob, string blood, FitnessLevel fit)
        : User(id, n, e, pass, ph), emergencyContact(contact),
          dateOfBirth(dob), bloodGroup(blood), fitnessLevel(fit) {
        traceConstructor("Traveler");
    }

    // [Returning objects from functions] gives back a copy of the contact object
    EmergencyContact getEmergencyContact() const { return emergencyContact; }
    FitnessLevel getFitnessLevel() const { return fitnessLevel; }

    // [Function overriding] fills in User's pure virtual getRole()
    string getRole() const override { return "Traveler"; }

    // [Virtual functions] a RULE that is different for different kinds of traveler.
    // A normal traveler may book at most 6 seats at once.
    // TravelerProvider overrides this (a group leader may book more).
    virtual int maxSeatsPerBooking() const { return 6; }

    // UC-01 step 4 / alternate flow 4a: can this traveler book that many seats?
    // Prints the reason when the answer is no.
    bool canBook(const Trip& trip, int seats) const {
        if (seats < 1) {
            cout << "Number of seats must be at least 1.\n";
            return false;
        }
        if (seats > trip.getAvailableSlots()) {
            cout << "Only " << trip.getAvailableSlots() << " seat(s) left. Enter a smaller number.\n";
            return false;
        }
        // [Run-time polymorphism] maxSeatsPerBooking() is virtual, so for a
        // TravelerProvider its own (bigger) limit is used here
        if (seats > maxSeatsPerBooking()) {
            cout << "A " << getRole() << " can book at most " << maxSeatsPerBooking()
                 << " seats at once.\n";
            return false;
        }
        return true;
    }

    // [Function prototype] only the DECLARATIONS are here. The bodies of these
    // three are at the bottom of Booking.h, because they create and use Booking
    // objects, and the full Booking class is only known there.
    Booking* bookTrip(Trip& trip, int seats, const PaymentGateway& gateway,
                      const string& cardNo, const string& expiry,
                      const string& today);                          // UC-01 Book Adventure
    bool cancelBooking(Booking* booking, const PaymentGateway& gateway,
                       const string& today);                         // UC-02 Cancel Booking

    // [Default arguments in functions]
    //   viewMyBookings()      -> shows ALL bookings      (onlyConfirmed = false)
    //   viewMyBookings(true)  -> shows only CONFIRMED ones
    void viewMyBookings(bool onlyConfirmed = false) const;

    // [Function overriding] the traveler's own menu. Body: TravelerMenu.h
    void showMenu(BookingSystem& system) override;

    // [Friend function] + [Stream operator overloading]
    friend ostream& operator<<(ostream& out, const Traveler& t);
};

inline ostream& operator<<(ostream& out, const Traveler& t) {
    out << static_cast<const User&>(t);   // print the User part first, using User's <<
    out << "DOB     : " << t.dateOfBirth << "\n"
        << "Blood   : " << t.bloodGroup << "\n"
        << "Fitness : " << toString(t.fitnessLevel) << "\n"
        << "Emergency Contact : " << t.emergencyContact.getName()
        << " (" << t.emergencyContact.getPhone() << ")\n";
    return out;
}

#endif
