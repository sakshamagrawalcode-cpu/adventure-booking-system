// =====================================================================
//  Traveler.h  -  a person who BOOKS trips
// =====================================================================
//  Parent: User.   Child: TravelerProvider (see TravelerProvider.h)
//
//  OOP topics in this file:
//    [Single inheritance]  Traveler -> User
//    [Virtual inheritance] 'virtual public User' (needed by TravelerProvider)
//    [Constructors in inheritance]  [Function overriding]
//    [Nested class]  EmergencyContact
//    [Default arguments in constructor]  EmergencyContact(string n = "", string p = "")
//    [Composition]  the EmergencyContact object lives inside the Traveler
//    [Aggregation]  keeps pointers to its bookings, but does not own them
//    [Function prototype]  bookTrip(), cancelBooking(), viewMyBookings()
//    [Default arguments in functions]  viewMyBookings(bool onlyConfirmed = false)
//    [Returning objects from functions]  getEmergencyContact()
// =====================================================================
#ifndef TRAVELER_H
#define TRAVELER_H

#include <vector>
#include "User.h"
#include "Trip.h"

// Forward declarations: Traveler only stores POINTERS to these,
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
    // The Traveler does NOT own them (main() deletes them); it only keeps a list.
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

    // [Function prototype] only the DECLARATION is here. The bodies are written
    // at the bottom of Booking.h, because they create and use Booking objects,
    // and the full Booking class is only known there.
    Booking* bookTrip(Trip& trip, int seats, const PaymentGateway& gateway,
                      const string& cardNo, const string& expiry,
                      const string& today);                          // UC-01 Book Adventure
    bool cancelBooking(Booking* booking, const PaymentGateway& gateway,
                       const string& today);                         // UC-02 Cancel Booking

    // [Default arguments in functions]
    //   viewMyBookings()      -> shows ALL bookings      (onlyConfirmed = false)
    //   viewMyBookings(true)  -> shows only CONFIRMED ones
    void viewMyBookings(bool onlyConfirmed = false) const;

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
