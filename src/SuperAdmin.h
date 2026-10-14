// =====================================================================
//  SuperAdmin.h  -  the owner of the whole platform
// =====================================================================
//  Can do everything an Admin can, plus see system-wide statistics.
//  Menu: AdminMenu.h
//
//  OOP topics in this file:
//    [Multilevel inheritance]  User -> Admin -> SuperAdmin
//    [Constructors in inheritance]  order: User, then Admin, then SuperAdmin
//    [Protected member]  uses validatePassword() from User (its grandparent)
//    [Function overriding]  getRole()
//    [final]  no class can inherit from SuperAdmin
// =====================================================================
#ifndef SUPERADMIN_H
#define SUPERADMIN_H

#include "Admin.h"
#include "Trip.h"
#include "Booking.h"
#include "Payment.h"

// [Multilevel inheritance]
//     User            (grandparent)
//      |
//     Admin           (parent)
//      |
//     SuperAdmin      (child)
//
// [final] nobody can inherit from SuperAdmin. This line would be an error:
//     class OwnerAssistant : public SuperAdmin { };
class SuperAdmin final : public Admin {
private:
    string companyName;

public:
    // [Constructors in inheritance] SuperAdmin calls Admin(...),
    // and Admin calls User(...). So they run in the order User -> Admin -> SuperAdmin.
    SuperAdmin(string id, string n, string e, string pass, string ph, string company)
        : Admin(id, n, e, pass, ph), companyName(company) {
        traceConstructor("SuperAdmin");
    }

    // [Function overriding]
    string getRole() const override { return "SuperAdmin"; }

    // [Function overriding] the super admin's own menu. Body: AdminMenu.h
    void showMenu(BookingSystem& system) override;

    // Asks for the password again before showing the numbers.
    // [Protected member] validatePassword() is protected in User, so a child
    // (even a grandchild like SuperAdmin) can call it, but outside code cannot.
    void viewSystemStats(const string& password) const {
        if (!validatePassword(password)) {
            cout << "Wrong password. Stats not shown.\n";
            return;
        }
        // [Static member function] each class keeps its own count
        cout << companyName << " - system stats:\n"
             << "  Users alive    : " << User::getTotalUsers() << "\n"
             << "  Trips created  : " << Trip::getTripCount() << "\n"
             << "  Bookings made  : " << Booking::getBookingCount() << "\n"
             << "  Payments tried : " << Payment::getPaymentCount() << "\n";
    }
};

#endif
