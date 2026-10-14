// =====================================================================
//  AdminMenu.h  -  everything an ADMIN and a SUPER ADMIN can do in the app
// =====================================================================
//  Admin::showMenu() and SuperAdmin::showMenu() show the options. Each
//  option is one small "screen" function below.
//
//  Use cases here: Manage Users and Listings, reports,
//                  UC-02 5a (settle pending refunds), UC-03 (remove any trip)
// =====================================================================
#ifndef ADMINMENU_H
#define ADMINMENU_H

#include "BookingSystem.h"
#include "Input.h"

// [Abstraction] the system finds users through the Searchable interface
inline void searchUsersScreen(BookingSystem& system, const Admin& admin) {
    string keyword = readLine("Search for a name or email: ");
    if (keyword == "") {
        cout << "Type something to search for.\n";
        return;
    }
    vector<User*> found = system.searchUsers(keyword);
    if (found.empty()) cout << "No users found for '" << keyword << "'.\n";
    else admin.viewAllUsers(found);
}

inline void adminRemoveTripScreen(BookingSystem& system, const Admin& admin) {
    Trip* trip = system.findTrip(readLine("Trip ID to remove (like TRP-2): "));
    if (trip == nullptr) {
        cout << "No trip with that ID.\n";
        return;
    }
    admin.removeTrip(*trip);   // the admin may remove ANY trip (UC-03, secondary actor)
}

// UC-02 alternate flow 5a: settle every refund that failed earlier
inline void settleRefundsScreen(BookingSystem& system, const Admin& admin) {
    int settled = 0;
    for (Booking* b : system.getBookings()) {
        if (b->getPayment().getStatus() == PENDING) {
            admin.settlePendingRefund(b->getPayment(), system.getGateway());
            settled++;
        }
    }
    if (settled == 0) cout << "No pending refunds.\n";
}

// Tools for testing the alternate flows that are hard to reach otherwise:
//   - a failing payment gateway (UC-02 5a: refund fails)
//   - a later "today" (UC-02 1a: cancelling after the trip date)
inline void testingToolsScreen(BookingSystem& system) {
    PaymentGateway& gateway = system.getGateway();
    cout << "\n--- TESTING TOOLS ---\n"
         << "1. Turn payment gateway failure " << (gateway.isFailing() ? "OFF" : "ON")
         << "  (now " << (gateway.isFailing() ? "ON" : "OFF") << ")\n"
         << "2. Change today's date  (now " << system.getToday() << ")\n"
         << "0. Back\n";
    int choice = readInt("Choose: ");
    if (choice == 1) {
        gateway.setFailMode(!gateway.isFailing());
        cout << "Payment gateway failure is now " << (gateway.isFailing() ? "ON" : "OFF") << ".\n";
    } else if (choice == 2) {
        string date = readLine("New date (YYYY-MM-DD): ");
        if (looksLikeDate(date)) {
            system.setToday(date);
            cout << "Today is now " << date << ".\n";
        } else {
            cout << "That does not look like a date. Nothing changed.\n";
        }
    }
}

// [Function overriding] Admin's version of User::showMenu()
inline void Admin::showMenu(BookingSystem& system) {
    while (true) {
        cout << "\n--- ADMIN MENU (" << getName() << ") ---\n"
             << "1. All users\n"
             << "2. Search users\n"
             << "3. All bookings\n"
             << "4. Trip report (seats sold, money collected)\n"
             << "5. Remove a trip\n"
             << "6. Settle pending refunds\n"
             << "7. Testing tools\n"
             << "0. Log out\n";
        int choice = readInt("Choose: ");
        switch (choice) {
            case 1: viewAllUsers(system.getUsers()); break;
            case 2: searchUsersScreen(system, *this); break;
            case 3: viewAllBookings(system.getBookings()); break;
            case 4: tripReport(system.getTrips(), system.getBookings()); break;
            case 5: adminRemoveTripScreen(system, *this); break;
            case 6: settleRefundsScreen(system, *this); break;
            case 7: testingToolsScreen(system); break;
            case 0: return;
            default: cout << "No such option.\n";
        }
    }
}

// [Function overriding] SuperAdmin's version of showMenu().
// It REUSES the parent's menu by calling Admin::showMenu() with the scope operator ::
inline void SuperAdmin::showMenu(BookingSystem& system) {
    while (true) {
        cout << "\n--- SUPER ADMIN MENU (" << getName() << ") ---\n"
             << "1. Admin menu\n"
             << "2. System stats (asks for your password again)\n"
             << "0. Log out\n";
        int choice = readInt("Choose: ");
        if (choice == 1) Admin::showMenu(system);
        else if (choice == 2) viewSystemStats(readLine("Password: "));
        else if (choice == 0) return;
        else cout << "No such option.\n";
    }
}

#endif
