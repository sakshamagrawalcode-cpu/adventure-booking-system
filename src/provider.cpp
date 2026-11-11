// provider.cpp
// The provider program: see, add and edit your adventures, and see who booked them.
// Build: g++ -std=c++17 provider.cpp -o provider

#include "BookingSystem.h"
#include "Input.h"

// Asks for email and password until they are right. Returns the provider's ID.
string loginScreen(BookingSystem& app) {
    cout << "\n===== PROVIDER LOGIN =====\n";
    while (true) {
        string email = readLine("Email    : ");
        string password = readLine("Password : ");
        try {
            Provider p = app.loginProvider(email, password);
            cout << "\nWelcome, " << p.getName() << " (" << p.getCompanyName() << ")!\n";
            return p.getId();
        } catch (runtime_error& e) {
            cout << e.what() << ". Try again.\n\n";
        }
    }
}

// Lets the provider pick a difficulty from a list
string chooseDifficulty() {
    cout << "1. Easy\n2. Moderate\n3. Hard\n";
    int choice = readIntInRange("Difficulty: ", 1, 3);
    if (choice == 1) return "Easy";
    if (choice == 2) return "Moderate";
    return "Hard";
}

// Prints this provider's adventures as a numbered list and returns them
vector<Adventure> printMyAdventures(BookingSystem& app, string providerId) {
    vector<Adventure> list = app.getAdventuresOfProvider(providerId);
    if (list.size() == 0) {
        cout << "You have no adventures yet.\n";
    }
    for (int i = 0; i < (int)list.size(); i++) {
        cout << (i + 1) << ". " << list[i].getName()
             << " | " << list[i].getDate()
             << " | Rs. " << list[i].getPrice()
             << " | Seats left: " << list[i].getSeatsLeft()
             << " of " << list[i].getTotalSeats() << "\n";
    }
    return list;
}

void myAdventures(BookingSystem& app, string providerId) {
    cout << "\n===== MY ADVENTURES =====\n";
    printMyAdventures(app, providerId);
}

// Asks for all details and lists a new adventure
void addAdventureScreen(BookingSystem& app, string providerId) {
    cout << "\n===== ADD ADVENTURE =====\n";
    string name = readLine("Name        : ");
    string location = readLine("Location    : ");
    string description = readLine("Description : ");
    string difficulty = chooseDifficulty();
    int minAge = readIntInRange("Min age     : ", 1, 120);
    string date = readLine("Date (DD-MM-YYYY): ");
    int price = readIntInRange("Price per person (Rs.): ", 1, 1000000);
    int seats = readIntInRange("Seats       : ", 1, 1000);

    try {
        app.addAdventure(providerId, name, location, description,
                         difficulty, minAge, date, price, seats);
        cout << "Adventure added.\n";
    } catch (runtime_error& e) {
        cout << "Could not add: " << e.what() << "\n";
    }
}

// Pick one of your adventures, then change one field at a time (not seats)
void editAdventureScreen(BookingSystem& app, string providerId) {
    cout << "\n===== EDIT ADVENTURE =====\n";
    vector<Adventure> list = printMyAdventures(app, providerId);
    if (list.size() == 0) return;

    int pick = readIntInRange("Edit adventure number (0 = back): ", 0, list.size());
    if (pick == 0) return;
    string adventureId = list[pick - 1].getId();

    while (true) {
        Adventure a = app.getAdventure(adventureId);   // fresh copy each time

        cout << "\nEditing: " << a.getName() << "\n";
        cout << "1. Name        (" << a.getName() << ")\n";
        cout << "2. Location    (" << a.getLocation() << ")\n";
        cout << "3. Description\n";
        cout << "4. Difficulty  (" << a.getDifficulty() << ")\n";
        cout << "5. Min age     (" << a.getMinAge() << ")\n";
        cout << "6. Date        (" << a.getDate() << ")\n";
        cout << "7. Price       (Rs. " << a.getPrice() << ")\n";
        cout << "0. Back\n";
        int choice = readIntInRange("Choose: ", 0, 7);
        if (choice == 0) return;

        // Start from the current values and change only the chosen one
        string name = a.getName();
        string location = a.getLocation();
        string description = a.getDescription();
        string difficulty = a.getDifficulty();
        int minAge = a.getMinAge();
        string date = a.getDate();
        int price = a.getPrice();

        if (choice == 1) name = readLine("New name: ");
        if (choice == 2) location = readLine("New location: ");
        if (choice == 3) description = readLine("New description: ");
        if (choice == 4) difficulty = chooseDifficulty();
        if (choice == 5) minAge = readIntInRange("New min age: ", 1, 120);
        if (choice == 6) date = readLine("New date (DD-MM-YYYY): ");
        if (choice == 7) price = readIntInRange("New price (Rs.): ", 1, 1000000);

        try {
            app.updateAdventure(adventureId, name, location, description,
                                difficulty, minAge, date, price);
            cout << "Saved.\n";
        } catch (runtime_error& e) {
            cout << "Could not save: " << e.what() << "\n";
        }
    }
}

// Pick one of your adventures and see who booked it (active bookings only)
void bookersScreen(BookingSystem& app, string providerId) {
    cout << "\n===== WHO BOOKED =====\n";
    vector<Adventure> list = printMyAdventures(app, providerId);
    if (list.size() == 0) return;

    int pick = readIntInRange("Adventure number (0 = back): ", 0, list.size());
    if (pick == 0) return;
    Adventure a = list[pick - 1];

    vector<Booking> bookings = app.getBookingsOfAdventure(a.getId());
    cout << "\nBookings for " << a.getName() << ":\n";

    int shown = 0;
    for (int i = 0; i < (int)bookings.size(); i++) {
        if (bookings[i].isCancelled()) continue;   // skip cancelled ones

        Customer c = app.getCustomer(bookings[i].getCustomerId());
        shown++;
        cout << "\n" << shown << ". " << c.getName() << "\n";
        cout << "   Gender : " << c.getGender() << "\n";
        cout << "   Mobile : " << c.getMobile() << "\n";
        cout << "   Email  : " << c.getEmail() << "\n";
    }
    if (shown == 0) {
        cout << "No bookings yet.\n";
    }
}

// Shows this provider's own profile
void viewProfile(BookingSystem& app, string providerId) {
    cout << "\n===== MY PROFILE =====\n";
    app.getProvider(providerId).showProfile();
}

// The main menu after login. Returns when the provider logs out.
void providerMenu(BookingSystem& app, string providerId) {
    while (true) {
        cout << "\n===== PROVIDER MENU =====\n";
        cout << "1. My adventures\n";
        cout << "2. Add adventure\n";
        cout << "3. Edit adventure\n";
        cout << "4. Who booked\n";
        cout << "5. View profile\n";
        cout << "0. Logout\n";
        int choice = readIntInRange("Choose: ", 0, 5);

        if (choice == 1) myAdventures(app, providerId);
        if (choice == 2) addAdventureScreen(app, providerId);
        if (choice == 3) editAdventureScreen(app, providerId);
        if (choice == 4) bookersScreen(app, providerId);
        if (choice == 5) viewProfile(app, providerId);
        if (choice == 0) {
            cout << "Logged out.\n";
            return;
        }
    }
}

int main() {
    BookingSystem app;   // holds all the sample data

    // After logout, go back to the login screen
    while (true) {
        string providerId = loginScreen(app);
        providerMenu(app, providerId);
    }
    return 0;
}
