// =====================================================================
//  StartMenu.h  -  the first screens: welcome, log in, register
// =====================================================================
//  Including this ONE file brings in every class and every menu.
//
//  Use cases here: Register / Login
//  OOP topic: [Run-time polymorphism] after login, user->showMenu() opens
//             a DIFFERENT menu for each kind of user.
// =====================================================================
#ifndef STARTMENU_H
#define STARTMENU_H

#include "BookingSystem.h"
#include "TravelerMenu.h"
#include "ProviderMenu.h"
#include "AdminMenu.h"
#include "Input.h"

inline void printWelcome(const BookingSystem& system) {
    cout << "==============================================================\n"
         << "  ADVENTURE BOOKING SYSTEM            (today is " << system.getToday() << ")\n"
         << "==============================================================\n"
         << "Sample accounts you can log in with:\n"
         << "  Traveler            aarav.sharma@gmail.com          aarav@123\n"
         << "  Provider            ops@himalayantrails.in          rohit@123\n"
         << "  Traveler+Provider   karan.negi@spitiexpeditions.in  karan@123\n"
         << "  Admin               sneha.iyer@trekmate.in          sneha@123\n"
         << "  Super admin         vikram.mehta@trekmate.in        vikram@123\n";
}

inline void loginScreen(BookingSystem& system) {
    string email = readLine("Email: ");
    string password = readLine("Password: ");
    User* user = system.login(email, password);
    if (user == nullptr) {
        cout << "Wrong email or password.\n";
        return;
    }
    cout << "Welcome, " << user->getName() << " (" << user->getRole() << ")\n";

    // [Run-time polymorphism] / [Dynamic binding]: 'user' is a User*, but
    // showMenu() is virtual, so the menu of the REAL object opens -
    // Traveler, AdventureProvider, Admin, SuperAdmin or TravelerProvider.
    user->showMenu(system);
}

inline void registerScreen(BookingSystem& system) {
    cout << "\n--- REGISTER AS A NEW TRAVELER ---\n";
    string name = readLine("Full name: ");
    string email = readLine("Email: ");
    string password = readLine("Password (at least 4 characters): ");
    string phone = readLine("Phone: ");
    string dob = readLine("Date of birth (YYYY-MM-DD): ");
    string blood = readLine("Blood group: ");
    int fitness = readInt("Fitness (0 = LOW, 1 = MODERATE, 2 = HIGH): ");
    string contactName = readLine("Emergency contact name: ");
    string contactPhone = readLine("Emergency contact phone: ");

    string problem = system.checkNewTraveler(name, email, password, dob, fitness);
    if (problem != "") {
        cout << "Not registered: " << problem << "\n";
        return;
    }
    Traveler* traveler = system.registerTraveler(
        name, email, password, phone, Traveler::EmergencyContact(contactName, contactPhone),
        dob, blood, static_cast<FitnessLevel>(fitness));
    cout << "Registered! Your user ID is " << traveler->getUserId() << ". You can log in now.\n";
}

// [Ambiguity in multiple inheritance] TravelerProvider has TWO parents that
// both have showMenu(). This menu lets the user pick one, and the scope
// operator :: says exactly which parent's menu to open.
inline void TravelerProvider::showMenu(BookingSystem& system) {
    while (true) {
        cout << "\n--- " << getName() << ": you are a traveler AND a provider ---\n"
             << "1. Traveler menu\n"
             << "2. Provider menu\n"
             << "0. Log out\n";
        int choice = readInt("Choose: ");
        if (choice == 1) Traveler::showMenu(system);
        else if (choice == 2) AdventureProvider::showMenu(system);
        else if (choice == 0) return;
        else cout << "No such option.\n";
    }
}

#endif
