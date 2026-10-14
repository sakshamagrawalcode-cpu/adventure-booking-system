// =====================================================================
//  AdventureProvider.h  -  a company that CREATES and lists trips
// =====================================================================
//  Parent: User.   Child: TravelerProvider (see TravelerProvider.h)
//  Menu:   ProviderMenu.h
//
//  OOP topics in this file:
//    [Single inheritance]  AdventureProvider -> User
//    [Virtual inheritance] 'virtual public User' (needed by TravelerProvider)
//    [Constructors in inheritance]  [Function overriding]
//    [Returning objects from functions]  createTrip() returns a Trip object
//    [Friend function]  [Stream operator overloading]
// =====================================================================
#ifndef ADVENTUREPROVIDER_H
#define ADVENTUREPROVIDER_H

#include "User.h"
#include "Trip.h"

// [Virtual inheritance] same reason as Traveler: TravelerProvider has both
// Traveler and AdventureProvider as parents, and must get only ONE User part.
class AdventureProvider : virtual public User {
private:
    string agencyName;
    string licenseNumber;
    string certification;
    double rating;
    bool isVerified;

public:
    // [Constructors in inheritance] the User part is built FIRST by calling User(...)
    AdventureProvider(string id, string n, string e, string pass, string ph,
                      string agency, string license, string cert,
                      double r, bool verified)
        : User(id, n, e, pass, ph), agencyName(agency), licenseNumber(license),
          certification(cert), rating(r), isVerified(verified) {
        traceConstructor("AdventureProvider");
    }

    // [Returning objects from functions] builds a Trip inside the function
    // and gives the whole object back to the caller
    Trip createTrip(string title, string location, double price,
                    string start, string end, int cap, int minAge, FitnessLevel fit) {
        Trip trip(title, location, price, start, end, cap, minAge, fit);
        trip.setProviderId(getUserId());   // remember who created it
        return trip;
    }

    void publishTrip(Trip& t) { t.publish(); }

    // UC-03: the provider removes one of their own trips (the menu checks it is theirs).
    // Alternate flow 2a: blocked while there are confirmed bookings,
    // so no traveler loses a trip silently.
    bool removeTrip(Trip& trip) {
        if (trip.getStatus() == CLOSED) {
            cout << "This trip is already removed.\n";
            return false;
        }
        if (!trip.canBeRemoved()) {
            cout << "Cannot remove '" << trip.getTitle()
                 << "': it has confirmed bookings. Deal with those bookings first.\n";
            return false;
        }
        trip.close();
        cout << "'" << trip.getTitle() << "' removed (status CLOSED).\n";
        return true;
    }

    string getAgencyName() const { return agencyName; }

    // [Function overriding] fills in User's pure virtual getRole()
    string getRole() const override { return "AdventureProvider"; }

    // [Function overriding] the provider's own menu. Body: ProviderMenu.h
    void showMenu(BookingSystem& system) override;

    // [Friend function] + [Stream operator overloading]
    friend ostream& operator<<(ostream& out, const AdventureProvider& p);
};

inline ostream& operator<<(ostream& out, const AdventureProvider& p) {
    out << static_cast<const User&>(p);   // print the User part first, using User's <<
    out << "Agency  : " << p.agencyName << "\n"
        << "License : " << p.licenseNumber << "\n"
        << "Cert.   : " << p.certification << "\n"
        << "Rating  : " << p.rating << "\n"
        << "Verified: " << (p.isVerified ? "Yes" : "No") << "\n";
    return out;
}

#endif
