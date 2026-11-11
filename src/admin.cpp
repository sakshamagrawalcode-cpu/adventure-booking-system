// admin.cpp
// The admin program: see and manage all users, bookings and seats.
// Build: g++ -std=c++17 admin.cpp -o admin

#include "BookingSystem.h"
#include "Input.h"

// Asks for email and password until they are right
void loginScreen(BookingSystem& app) {
    cout << "\n===== ADMIN LOGIN =====\n";
    while (true) {
        string email = readLine("Email (0 = exit) : ");
        if (email == "0") {
            cout << "Goodbye!\n";
            exit(0);
        }
        string password = readLine("Password         : ");
        try {
            Admin a = app.loginAdmin(email, password);
            cout << "\nWelcome, " << a.getName() << "!\n";
            return;
        } catch (runtime_error& e) {
            cout << e.what() << ". Try again.\n\n";
        }
    }
}

// ---------------------------------------------------------------
// Pick helpers: show a numbered list and return the chosen user's ID.
// They return "" (empty text) if the admin chooses 0 (back).
// ---------------------------------------------------------------

string pickCustomer(BookingSystem& app) {
    vector<Customer> list = app.getCustomers();
    for (int i = 0; i < (int)list.size(); i++) {
        cout << (i + 1) << ". " << list[i].getName() << " (" << list[i].getEmail() << ")\n";
    }
    int choice = readIntInRange("Customer number (0 = back): ", 0, list.size());
    if (choice == 0) return "";
    return list[choice - 1].getId();
}

string pickProvider(BookingSystem& app) {
    vector<Provider> list = app.getProviders();
    for (int i = 0; i < (int)list.size(); i++) {
        cout << (i + 1) << ". " << list[i].getName() << " - " << list[i].getCompanyName()
             << " (" << list[i].getEmail() << ")\n";
    }
    int choice = readIntInRange("Provider number (0 = back): ", 0, list.size());
    if (choice == 0) return "";
    return list[choice - 1].getId();
}

string pickAdmin(BookingSystem& app) {
    vector<Admin> list = app.getAdmins();
    for (int i = 0; i < (int)list.size(); i++) {
        cout << (i + 1) << ". " << list[i].getName() << " (" << list[i].getEmail() << ")\n";
    }
    int choice = readIntInRange("Admin number (0 = back): ", 0, list.size());
    if (choice == 0) return "";
    return list[choice - 1].getId();
}

// ---------------------------------------------------------------
// Screens
// ---------------------------------------------------------------

// Shows every customer's profile (passwords are never shown)
void showAllCustomers(BookingSystem& app) {
    vector<Customer> list = app.getCustomers();
    cout << "\n===== ALL CUSTOMERS =====\n";
    for (int i = 0; i < (int)list.size(); i++) {
        cout << "\nCustomer " << (i + 1) << "\n";
        list[i].showProfile();
    }
}

// Shows every provider's profile (passwords are never shown)
void showAllProviders(BookingSystem& app) {
    vector<Provider> list = app.getProviders();
    cout << "\n===== ALL PROVIDERS =====\n";
    for (int i = 0; i < (int)list.size(); i++) {
        cout << "\nProvider " << (i + 1) << "\n";
        list[i].showProfile();
    }
}

// Finds customers and providers by name (part of the name, capitals ignored).
// Each result is a User*. Calling showProfile() on it runs the Customer
// version or the Provider version: this is polymorphism.
void searchScreen(BookingSystem& app) {
    cout << "\n===== SEARCH USERS =====\n";
    string text = readLine("Name (or part of it): ");
    vector<User*> results = app.searchUsers(text);

    if (results.size() == 0) {
        cout << "No user found.\n";
        return;
    }
    for (int i = 0; i < (int)results.size(); i++) {
        cout << "\n" << (i + 1) << ". " << results[i]->getRole() << "\n";
        results[i]->showProfile();
    }
}

// Shows every booking: which adventure, who booked it (full profile) and the tickets
void showAllBookings(BookingSystem& app) {
    vector<Booking> list = app.getAllBookings();

    cout << "\n===== ALL BOOKINGS =====\n";
    if (list.size() == 0) {
        cout << "No bookings yet.\n";
        return;
    }
    for (int i = 0; i < (int)list.size(); i++) {
        Adventure a = app.getAdventure(list[i].getAdventureId());
        Customer c = app.getCustomer(list[i].getCustomerId());

        cout << "\n" << (i + 1) << ". " << a.getName() << " (" << a.getDate() << ")\n";
        cout << "-- Booked by --\n";
        c.showProfile();
        cout << "-- Booking --\n";
        cout << list[i];
    }
}

// Shows seats left for every adventure
void showSeats(BookingSystem& app) {
    vector<Adventure> list = app.getAdventures();

    cout << "\n===== SEATS LEFT =====\n";
    for (int i = 0; i < (int)list.size(); i++) {
        Provider p = app.getProvider(list[i].getProviderId());
        cout << (i + 1) << ". " << list[i].getName()
             << " | " << list[i].getDate()
             << " | " << p.getCompanyName()
             << " | Seats left: " << list[i].getSeatsLeft()
             << " of " << list[i].getTotalSeats() << "\n";
    }
}

// Lists the BOOKED bookings of every customer and cancels the chosen one
void cancelAnyBooking(BookingSystem& app) {
    // true = only the bookings that are still BOOKED
    vector<Booking> active = app.getAllBookings(true);

    cout << "\n===== CANCEL A BOOKING =====\n";
    if (active.size() == 0) {
        cout << "No bookings to cancel.\n";
        return;
    }
    for (int i = 0; i < (int)active.size(); i++) {
        Adventure a = app.getAdventure(active[i].getAdventureId());
        Customer c = app.getCustomer(active[i].getCustomerId());
        cout << (i + 1) << ". " << a.getName() << " (" << a.getDate() << ") - "
             << c.getName() << " - " << active[i].getTicketCount()
             << " ticket(s), Rs. " << active[i].getTotalPrice() << "\n";
    }

    int choice = readIntInRange("Cancel booking number (0 = back): ", 0, active.size());
    if (choice == 0) return;

    Booking chosen = active[choice - 1];
    try {
        app.cancelBooking(chosen.getId());
        cout << "Cancelled. Refunded Rs. " << chosen.getTotalPrice() << "\n";
    } catch (runtime_error& e) {
        cout << "Could not cancel: " << e.what() << "\n";
    }
}

// Changes one field of a customer at a time (admin can change every field)
void editCustomer(BookingSystem& app, string customerId) {
    while (true) {
        Customer c = app.getCustomer(customerId);   // fresh copy each time

        cout << "\nEditing customer: " << c.getName() << "\n";
        cout << "1. Name   (" << c.getName() << ")\n";
        cout << "2. Email  (" << c.getEmail() << ")\n";
        cout << "3. Gender (" << c.getGender() << ")\n";
        cout << "4. Age    (" << c.getAge() << ")\n";
        cout << "5. Mobile (" << c.getMobile() << ")\n";
        cout << "0. Back\n";
        int choice = readIntInRange("Choose: ", 0, 5);
        if (choice == 0) return;

        // Start from the current values and change only the chosen one
        string name = c.getName();
        string email = c.getEmail();
        string gender = c.getGender();
        int age = c.getAge();
        string mobile = c.getMobile();

        if (choice == 1) name = readLine("New name: ");
        if (choice == 2) email = readLine("New email: ");
        if (choice == 3) gender = chooseGender();
        if (choice == 4) age = readIntInRange("New age: ", 1, 120);
        if (choice == 5) mobile = readLine("New mobile (10 digits): ");

        try {
            app.updateCustomer(customerId, name, email, gender, age, mobile);
            cout << "Saved.\n";
        } catch (runtime_error& e) {
            cout << "Could not save: " << e.what() << "\n";
        }
    }
}

// Changes one field of a provider at a time (admin can change every field)
void editProvider(BookingSystem& app, string providerId) {
    while (true) {
        Provider p = app.getProvider(providerId);   // fresh copy each time

        cout << "\nEditing provider: " << p.getName() << "\n";
        cout << "1. Name    (" << p.getName() << ")\n";
        cout << "2. Email   (" << p.getEmail() << ")\n";
        cout << "3. Mobile  (" << p.getMobile() << ")\n";
        cout << "4. Company (" << p.getCompanyName() << ")\n";
        cout << "0. Back\n";
        int choice = readIntInRange("Choose: ", 0, 4);
        if (choice == 0) return;

        // Start from the current values and change only the chosen one
        string name = p.getName();
        string email = p.getEmail();
        string mobile = p.getMobile();
        string company = p.getCompanyName();

        if (choice == 1) name = readLine("New name: ");
        if (choice == 2) email = readLine("New email: ");
        if (choice == 3) mobile = readLine("New mobile (10 digits): ");
        if (choice == 4) company = readLine("New company name: ");

        try {
            app.updateProvider(providerId, name, email, mobile, company);
            cout << "Saved.\n";
        } catch (runtime_error& e) {
            cout << "Could not save: " << e.what() << "\n";
        }
    }
}

// Picks a customer or a provider, then opens the matching edit screen
void editUserScreen(BookingSystem& app) {
    cout << "\n===== EDIT A USER =====\n";
    cout << "1. Customer\n2. Provider\n0. Back\n";
    int type = readIntInRange("Choose: ", 0, 2);

    if (type == 1) {
        string id = pickCustomer(app);
        if (id != "") editCustomer(app, id);
    }
    if (type == 2) {
        string id = pickProvider(app);
        if (id != "") editProvider(app, id);
    }
}

// Sets a new password for any user. The old password is never shown.
void changePasswordScreen(BookingSystem& app) {
    cout << "\n===== CHANGE A PASSWORD =====\n";
    cout << "1. Customer\n2. Provider\n3. Admin\n0. Back\n";
    int type = readIntInRange("Choose: ", 0, 3);
    if (type == 0) return;

    string id = "";
    if (type == 1) id = pickCustomer(app);
    if (type == 2) id = pickProvider(app);
    if (type == 3) id = pickAdmin(app);
    if (id == "") return;

    string newPassword = readLine("New password: ");
    try {
        app.changePassword(id, newPassword);
        cout << "Password changed.\n";
    } catch (runtime_error& e) {
        cout << "Could not change: " << e.what() << "\n";
    }
}

// The main menu after login. Returns when the admin logs out.
void adminMenu(BookingSystem& app) {
    while (true) {
        cout << "\n===== ADMIN MENU =====\n";
        cout << "1. All customers\n";
        cout << "2. All providers\n";
        cout << "3. Search users by name\n";
        cout << "4. All bookings\n";
        cout << "5. Seats left\n";
        cout << "6. Cancel a booking\n";
        cout << "7. Edit a user\n";
        cout << "8. Change a password\n";
        cout << "0. Logout\n";
        int choice = readIntInRange("Choose: ", 0, 8);

        if (choice == 1) showAllCustomers(app);
        if (choice == 2) showAllProviders(app);
        if (choice == 3) searchScreen(app);
        if (choice == 4) showAllBookings(app);
        if (choice == 5) showSeats(app);
        if (choice == 6) cancelAnyBooking(app);
        if (choice == 7) editUserScreen(app);
        if (choice == 8) changePasswordScreen(app);
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
            loginScreen(app);
            adminMenu(app);
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
