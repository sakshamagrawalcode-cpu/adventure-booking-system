#ifndef ADVENTUREPROVIDER_H
#define ADVENTUREPROVIDER_H

#include "User.h"
#include "Trip.h"

// [final] no class can inherit from AdventureProvider
// [Virtual base class] only ONE User part, same as Traveler
class AdventureProvider final : virtual public User {
private:
    string agencyName;
    string licenseNumber;
    string certification;
    double rating;
    bool isVerified;

public:
    AdventureProvider(string id, string n, string e, string pass, string ph,
                      string agency, string license, string cert,
                      double r, bool verified)
        : User(id, n, e, pass, ph), agencyName(agency), licenseNumber(license),
          certification(cert), rating(r), isVerified(verified) {}

    Trip createTrip(string title, string location, double price,
                    string start, string end, int cap, int minAge, FitnessLevel fit) {
        return Trip(title, location, price, start, end, cap, minAge, fit);
    }

    void publishTrip(Trip& t) {
        t.publish();
    }

    // [Virtual function] overrides User::getRole()
    string getRole() const override {
        return "AdventureProvider";
    }

    // [Stream operator overloading using friend function]
    friend ostream& operator<<(ostream& out, const AdventureProvider& p);
};

inline ostream& operator<<(ostream& out, const AdventureProvider& p) {
    out << static_cast<const User&>(p);
    out << "Agency  : " << p.agencyName << "\n"
        << "License : " << p.licenseNumber << "\n"
        << "Cert.   : " << p.certification << "\n"
        << "Rating  : " << p.rating << "\n"
        << "Verified: " << (p.isVerified ? "Yes" : "No") << "\n";
    return out;
}

#endif
