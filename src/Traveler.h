#ifndef TRAVELER_H
#define TRAVELER_H

#include <vector>
#include "User.h"
#include "Trip.h"

// Forward declarations: Traveler only stores POINTERS to these,
// so the full class is not needed here.
// bookTrip(), cancelBooking() and viewMyBookings() are written at the
// bottom of Booking.h, because they need the full Booking class.
class Booking;
class PaymentGateway;

// [final] no class can inherit from Traveler
// [Virtual base class] "virtual public User" -> only ONE User part is kept,
// even if a class later inherits User through two paths
class Traveler final : virtual public User {
public:
    // [Nested class] EmergencyContact only makes sense inside Traveler.
    // Outside, it is written as Traveler::EmergencyContact
    class EmergencyContact {
    private:
        string name;
        string phone;

    public:
        EmergencyContact(string n = "", string p = "") : name(n), phone(p) {}

        string getName() const { return name; }
        string getPhone() const { return phone; }
    };

private:
    EmergencyContact emergencyContact;
    string dateOfBirth;
    string bloodGroup;
    FitnessLevel fitnessLevel;

    // [Pointer to objects] list of this traveler's bookings (not owned)
    vector<Booking*> myBookings;

public:
    // With a virtual base class, the most-derived class (Traveler) calls User's constructor
    Traveler(string id, string n, string e, string pass, string ph,
             EmergencyContact contact, string dob, string blood, FitnessLevel fit)
        : User(id, n, e, pass, ph), emergencyContact(contact),
          dateOfBirth(dob), bloodGroup(blood), fitnessLevel(fit) {}

    EmergencyContact getEmergencyContact() const { return emergencyContact; }
    FitnessLevel getFitnessLevel() const { return fitnessLevel; }

    // [Virtual function] overrides User::getRole()
    string getRole() const override {
        return "Traveler";
    }

    // UC-01 Book Adventure - returns nullptr if no booking is made
    Booking* bookTrip(Trip& trip, int seats, const PaymentGateway& gateway,
                      const string& cardNo, const string& expiry, const string& today);

    // UC-02 Cancel Booking
    bool cancelBooking(Booking* booking, const PaymentGateway& gateway, const string& today);

    void viewMyBookings() const;

    // [Stream operator overloading using friend function]
    friend ostream& operator<<(ostream& out, const Traveler& t);
};

inline ostream& operator<<(ostream& out, const Traveler& t) {
    out << static_cast<const User&>(t);   // reuse User's operator<< for base part
    out << "DOB     : " << t.dateOfBirth << "\n"
        << "Blood   : " << t.bloodGroup << "\n"
        << "Fitness : " << toString(t.fitnessLevel) << "\n"
        << "Emergency Contact : " << t.emergencyContact.getName()
        << " (" << t.emergencyContact.getPhone() << ")\n";
    return out;
}

#endif
