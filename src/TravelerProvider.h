// =====================================================================
//  TravelerProvider.h  -  someone who LISTS trips AND BOOKS trips
// =====================================================================
//  Example: a trek leader who runs his own treks, and also books other
//  companies' trips for his group.
//  Menu: StartMenu.h (lets them pick the traveler or the provider menu)
//
//  OOP topics in this file:
//    [Multiple inheritance]  two parents: Traveler and AdventureProvider
//    [Multipath inheritance] User is reached by two paths
//    [Diamond problem]       ...which would give TWO User parts
//    [Virtual inheritance]   ...but the parents use 'virtual public User',
//                            so there is only ONE User part
//    [Hybrid inheritance]    hierarchical (User -> 3 children) + multiple (this class)
//    [Ambiguity in multiple inheritance]  both parents have getRole() and showMenu()
//    [Constructor execution order]  User, Traveler, AdventureProvider, TravelerProvider
//    [Function overriding]  maxSeatsPerBooking() - a bigger limit for group leaders
//    [final]
// =====================================================================
#ifndef TRAVELERPROVIDER_H
#define TRAVELERPROVIDER_H

#include "Traveler.h"
#include "AdventureProvider.h"

// [Diamond problem] - the shape of this family:
//
//                 User
//            _____|_____
//           |           |
//       Traveler    AdventureProvider     <- both: virtual public User
//           |___________|
//                 |
//          TravelerProvider
//
// Without 'virtual', TravelerProvider would hold TWO copies of User
// (two names, two emails, counted twice), and getName() would be ambiguous.
class TravelerProvider final : public Traveler, public AdventureProvider {
public:
    TravelerProvider(string id, string n, string e, string pass, string ph,
                     Traveler::EmergencyContact contact, string dob, string blood,
                     FitnessLevel fit, string agency, string license, string cert,
                     double rating, bool verified)
        // [Virtual inheritance] rule: the LAST class in the chain builds the
        // shared User part itself. That is why User(...) is called here.
        : User(id, n, e, pass, ph),
          // The User(...) calls inside these two parent constructors are now SKIPPED,
          // so the User part is built only ONCE.
          Traveler(id, n, e, pass, ph, contact, dob, blood, fit),
          AdventureProvider(id, n, e, pass, ph, agency, license, cert, rating, verified) {
        traceConstructor("TravelerProvider");
    }

    // [Ambiguity in multiple inheritance] Traveler AND AdventureProvider both
    // have their own getRole(). If we did not write getRole() here, the compiler
    // could not choose between them and would give an error.
    // The scope operator ::  picks one parent's version on purpose.
    string getRole() const override {
        return Traveler::getRole() + " + " + AdventureProvider::getRole();
    }

    // Same ambiguity for showMenu(): this menu lets the user pick which
    // parent's menu to open. Body: StartMenu.h
    void showMenu(BookingSystem& system) override;

    // [Function overriding] a group leader books for the whole group,
    // so the limit is bigger than a normal traveler's 6 seats
    int maxSeatsPerBooking() const override { return 15; }

    // The same ambiguity happens with cout:  cout << karan;  is an ERROR,
    // because both parents have their own operator<<.
};

#endif
