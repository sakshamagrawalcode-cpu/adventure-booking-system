// =====================================================================
//  main.cpp  -  the Adventure Booking System app (menu driven)
// =====================================================================
//  Run this to USE the system.
//  (demo.cpp is a separate program that shows every OOP topic one by one.)
//
//  Run:   g++ -std=c++17 src/main.cpp -o app      then      ./app
//
//  How it works:
//    1. BookingSystem keeps every user, trip and booking.
//    2. You log in with an email and password (or register first).
//    3. user->showMenu() opens the menu for YOUR kind of user.
//       That one call opens a different menu for a Traveler, a Provider,
//       an Admin, ...  ->  [Run-time polymorphism]
// =====================================================================

#include "StartMenu.h"   // brings in every class and every menu

int main() {
    // A fixed "today", so every run behaves the same and the test cases
    // give the same results. (Admin -> Testing tools can change it.)
    BookingSystem system("2026-10-15");
    system.loadSampleData();

    printWelcome(system);
    while (true) {
        cout << "\n===== MAIN MENU =====\n"
             << "1. Log in\n"
             << "2. Register as a new traveler\n"
             << "0. Exit\n";
        int choice = readInt("Choose: ");
        if (choice == 1) loginScreen(system);
        else if (choice == 2) registerScreen(system);
        else if (choice == 0) break;
        else cout << "No such option.\n";
    }
    cout << "Goodbye!\n";
    return 0;
}
