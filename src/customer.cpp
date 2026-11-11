// customer.cpp
// The customer program: login, see adventures, book, cancel, profile.
// Build: g++ -std=c++17 customer.cpp -o customer

#include "BookingSystem.h"
#include "Input.h"

// Asks for email and password until they are right. Returns the customer's ID.
string loginScreen(BookingSystem& app) {
    cout << "\n===== CUSTOMER LOGIN =====\n";
    while (true) {
        string email = readLine("Email (0 = exit) : ");
        if (email == "0") {
            cout << "Goodbye!\n";
            exit(0);
        }
        string password = readLine("Password         : ");
        try {
            Customer c = app.loginCustomer(email, password);
            cout << "\nWelcome, " << c.getName() << "!\n";
            return c.getId();
        } catch (runtime_error& e) {
            cout << e.what() << ". Try again.\n\n";
        }
    }
}

// Asks for tickets (name and age of each person) and books the adventure
void bookScreen(BookingSystem& app, string customerId, Adventure adventure) {
    int max = Booking::MAX_TICKETS;   // static member: same for every booking
    int count = readIntInRange("How many tickets? (1-" + to_string(max) + "): ", 1, max);

    vector<Ticket> tickets;
    for (int i = 1; i <= count; i++) {
        cout << "Person " << i << ":\n";
        Ticket t;
        t.name = readLine("  Name : ");
        t.age = readIntInRange("  Age  : ", 1, 120);
        tickets.push_back(t);
    }

    try {
        Booking b = app.book(customerId, adventure.getId(), tickets);
        cout << "\nBooked! " << b.getTicketCount() << " ticket(s) for "
             << adventure.getName() << ". Total: Rs. " << b.getTotalPrice() << "\n";
    } catch (runtime_error& e) {
        cout << "\nBooking failed: " << e.what() << "\n";
    }
}

// Shows all adventures. The user can open one and book it.
void showAdventures(BookingSystem& app, string customerId) {
    vector<Adventure> list = app.getAdventures();

    cout << "\n===== ALL ADVENTURES =====\n";
    for (int i = 0; i < (int)list.size(); i++) {
        cout << (i + 1) << ". " << list[i].getName()
             << " | " << list[i].getLocation()
             << " | " << list[i].getDate()
             << " | Rs. " << list[i].getPrice()
             << " | Seats left: " << list[i].getSeatsLeft() << "\n";
    }

    int choice = readIntInRange("\nOpen adventure number (0 = back): ", 0, list.size());
    if (choice == 0) return;

    Adventure chosen = list[choice - 1];
    cout << "\n";
    cout << chosen;   // uses the overloaded << operator

    int answer = readIntInRange("\nBook this? (1 = Yes, 0 = No): ", 0, 1);
    if (answer == 1) {
        bookScreen(app, customerId, chosen);
    }
}

// Shows all bookings of this customer (cancelled ones too)
void myBookings(BookingSystem& app, string customerId) {
    vector<Booking> list = app.getBookingsOfCustomer(customerId);

    cout << "\n===== MY BOOKINGS =====\n";
    if (list.size() == 0) {
        cout << "No bookings yet.\n";
        return;
    }
    for (int i = 0; i < (int)list.size(); i++) {
        Adventure a = app.getAdventure(list[i].getAdventureId());
        cout << "\n" << (i + 1) << ". " << a.getName() << " (" << a.getDate() << ")\n";
        cout << list[i];
    }
}

// Lists only the BOOKED bookings and cancels the chosen one
void cancelScreen(BookingSystem& app, string customerId) {
    // true = only the bookings that are still BOOKED
    vector<Booking> active = app.getBookingsOfCustomer(customerId, true);

    cout << "\n===== CANCEL A BOOKING =====\n";
    if (active.size() == 0) {
        cout << "No bookings to cancel.\n";
        return;
    }
    for (int i = 0; i < (int)active.size(); i++) {
        Adventure a = app.getAdventure(active[i].getAdventureId());
        cout << (i + 1) << ". " << a.getName() << " (" << a.getDate() << ") - "
             << active[i].getTicketCount() << " ticket(s), Rs. "
             << active[i].getTotalPrice() << "\n";
    }

    int choice = readIntInRange("Cancel booking number (0 = back): ", 0, active.size());
    if (choice == 0) return;

    Booking chosen = active[choice - 1];
    try {
        app.cancelBooking(chosen.getId(), customerId);   // customer version: checks it is theirs
        cout << "Cancelled. Refunded Rs. " << chosen.getTotalPrice() << "\n";
    } catch (runtime_error& e) {
        cout << "Could not cancel: " << e.what() << "\n";
    }
}

void viewProfile(BookingSystem& app, string customerId) {
    cout << "\n===== MY PROFILE =====\n";
    app.getCustomer(customerId).showProfile();
}

// Changes one field at a time: name, gender, age or mobile
void editProfile(BookingSystem& app, string customerId) {
    while (true) {
        Customer c = app.getCustomer(customerId);   // fresh copy each time

        cout << "\n===== EDIT PROFILE =====\n";
        cout << "1. Name   (" << c.getName() << ")\n";
        cout << "2. Gender (" << c.getGender() << ")\n";
        cout << "3. Age    (" << c.getAge() << ")\n";
        cout << "4. Mobile (" << c.getMobile() << ")\n";
        cout << "0. Back\n";
        int choice = readIntInRange("Choose: ", 0, 4);
        if (choice == 0) return;

        // Start from the current values and change only the chosen one
        string name = c.getName();
        string gender = c.getGender();
        int age = c.getAge();
        string mobile = c.getMobile();

        if (choice == 1) name = readLine("New name: ");
        if (choice == 2) gender = chooseGender();
        if (choice == 3) age = readIntInRange("New age: ", 1, 120);
        if (choice == 4) mobile = readLine("New mobile: ");

        try {
            app.updateCustomer(customerId, name, c.getEmail(), gender, age, mobile);
            cout << "Saved.\n";
        } catch (runtime_error& e) {
            cout << "Could not save: " << e.what() << "\n";
        }
    }
}

// The main menu after login. Returns when the user logs out.
void customerMenu(BookingSystem& app, string customerId) {
    while (true) {
        cout << "\n===== CUSTOMER MENU =====\n";
        cout << "1. Show adventures\n";
        cout << "2. My bookings\n";
        cout << "3. Cancel a booking\n";
        cout << "4. View profile\n";
        cout << "5. Edit profile\n";
        cout << "0. Logout\n";
        int choice = readIntInRange("Choose: ", 0, 5);

        if (choice == 1) showAdventures(app, customerId);
        if (choice == 2) myBookings(app, customerId);
        if (choice == 3) cancelScreen(app, customerId);
        if (choice == 4) viewProfile(app, customerId);
        if (choice == 5) editProfile(app, customerId);
        if (choice == 0) {
            cout << "Logged out.\n";
            return;
        }
    }
}

int main() {
    try {
        BookingSystem app;   // reads the shared data from the data folder

        // After logout, go back to the login screen
        while (true) {
            string customerId = loginScreen(app);
            customerMenu(app, customerId);
        }
    } catch (runtime_error& e) {
        // A problem with the data files, e.g. the data folder was not found
        cout << "\nError: " << e.what() << "\n";
        return 1;
    } catch (exception& e) {
        // Any other error we did not expect (multiple catch: the most specific comes first)
        cout << "\nUnexpected error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
