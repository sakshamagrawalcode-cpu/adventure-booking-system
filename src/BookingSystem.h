// BookingSystem.h
// Holds all data and all rules of the system.
// The data is sample data kept in vectors (memory), so every change
// is lost when the program closes.
// The menus never change data directly: they only call these functions.

#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>
#include "User.h"
#include "Adventure.h"
#include "Booking.h"
using namespace std;

class BookingSystem {
private:
    vector<Customer> customers;
    vector<Provider> providers;
    vector<Admin> admins;
    vector<Adventure> adventures;
    vector<Booking> bookings;
    int nextIdNumber = 1;   // used to make new IDs like "A1", "B2"

    // ---------- private helpers ----------

    // Makes a new unique ID, e.g. newId("B") -> "B7"
    string newId(string prefix) {
        string id = prefix + to_string(nextIdNumber);
        nextIdNumber++;
        return id;
    }

    // Returns the text in small letters, e.g. "RaHul" -> "rahul"
    string toLowerText(string text) {
        for (int i = 0; i < (int)text.size(); i++) {
            text[i] = tolower(text[i]);
        }
        return text;
    }

    // The find functions return the REAL object (note the &),
    // so the rules can change it. They throw if the ID is not found.
    Customer& findCustomer(string id) {
        for (int i = 0; i < (int)customers.size(); i++) {
            if (customers[i].getId() == id) return customers[i];
        }
        throw runtime_error("Customer not found");
    }

    Provider& findProvider(string id) {
        for (int i = 0; i < (int)providers.size(); i++) {
            if (providers[i].getId() == id) return providers[i];
        }
        throw runtime_error("Provider not found");
    }

    Adventure& findAdventure(string id) {
        for (int i = 0; i < (int)adventures.size(); i++) {
            if (adventures[i].getId() == id) return adventures[i];
        }
        throw runtime_error("Adventure not found");
    }

    Booking& findBooking(string id) {
        for (int i = 0; i < (int)bookings.size(); i++) {
            if (bookings[i].getId() == id) return bookings[i];
        }
        throw runtime_error("Booking not found");
    }

    // Returns true if another account (not userId) already uses this email
    bool emailUsedByOther(string email, string userId) {
        for (int i = 0; i < (int)customers.size(); i++) {
            if (customers[i].getEmail() == email && customers[i].getId() != userId) return true;
        }
        for (int i = 0; i < (int)providers.size(); i++) {
            if (providers[i].getEmail() == email && providers[i].getId() != userId) return true;
        }
        for (int i = 0; i < (int)admins.size(); i++) {
            if (admins[i].getEmail() == email && admins[i].getId() != userId) return true;
        }
        return false;
    }

    // Simple check: an email must contain '@'
    bool isValidEmail(string email) {
        return email.find('@') != string::npos;
    }

    // Simple check: a mobile number must be exactly 10 digits
    bool isValidMobile(string mobile) {
        if (mobile.size() != 10) {
            return false;
        }
        for (int i = 0; i < (int)mobile.size(); i++) {
            if (mobile[i] < '0' || mobile[i] > '9') {
                return false;
            }
        }
        return true;
    }

    // Fills the vectors with sample data
    void loadSampleData() {
        admins.push_back(Admin("AD1", "Saksham", "admin@example.com", "admin123"));

        providers.push_back(Provider("P1", "Amit Sharma", "amit@example.com", "amit123",
                                     "9876500001", "Himalayan Treks"));
        providers.push_back(Provider("P2", "Neha Verma", "neha@example.com", "neha123",
                                     "9876500002", "Rishikesh Rapids"));

        customers.push_back(Customer("C1", "Rahul Mehta", "rahul@example.com", "rahul123",
                                     "Male", 20, "9123400001"));
        customers.push_back(Customer("C2", "Priya Patel", "priya@example.com", "priya123",
                                     "Female", 22, "9123400002"));
        customers.push_back(Customer("C3", "Arjun Rao", "arjun@example.com", "arjun123",
                                     "Male", 16, "9123400003"));

        addAdventure("P1", "Kedarkantha Winter Trek", "Uttarakhand",
                     "A 6-day snow trek through pine forests to a 12,500 ft summit.",
                     "Moderate", 12, "20-12-2026", 9500, 10);
        addAdventure("P1", "Hampta Pass Trek", "Himachal Pradesh",
                     "A 5-day crossing from green Kullu valley to the dry Spiti side.",
                     "Moderate", 14, "15-06-2027", 11000, 8);
        addAdventure("P2", "River Rafting (16 km)", "Rishikesh",
                     "Rafting on the Ganga with grade 3 rapids and a trained guide.",
                     "Easy", 14, "05-01-2027", 1500, 12);
        addAdventure("P2", "Bungee Jumping", "Rishikesh",
                     "A jump from an 83 m platform with full safety gear.",
                     "Hard", 18, "10-01-2027", 3500, 6);

        // One booking at the start, so the lists are not empty
        vector<Ticket> tickets = { {"Rahul Mehta", 20}, {"Aman Mehta", 24} };
        book("C1", adventures[0].getId(), tickets);
    }

public:
    // Constructor: loads the sample data
    BookingSystem() {
        loadSampleData();
    }

    // ================= LOGIN =================

    Customer loginCustomer(string email, string password) {
        for (int i = 0; i < (int)customers.size(); i++) {
            if (customers[i].getEmail() == email && customers[i].checkPassword(password)) {
                return customers[i];
            }
        }
        throw runtime_error("Wrong email or password");
    }

    Provider loginProvider(string email, string password) {
        for (int i = 0; i < (int)providers.size(); i++) {
            if (providers[i].getEmail() == email && providers[i].checkPassword(password)) {
                return providers[i];
            }
        }
        throw runtime_error("Wrong email or password");
    }

    Admin loginAdmin(string email, string password) {
        for (int i = 0; i < (int)admins.size(); i++) {
            if (admins[i].getEmail() == email && admins[i].checkPassword(password)) {
                return admins[i];
            }
        }
        throw runtime_error("Wrong email or password");
    }

    // ================= ADVENTURES =================

    vector<Adventure> getAdventures() {
        return adventures;
    }

    vector<Adventure> getAdventuresOfProvider(string providerId) {
        vector<Adventure> result;
        for (int i = 0; i < (int)adventures.size(); i++) {
            if (adventures[i].getProviderId() == providerId) {
                result.push_back(adventures[i]);
            }
        }
        return result;
    }

    Adventure getAdventure(string id) {
        return findAdventure(id);
    }

    void addAdventure(string providerId, string name, string location,
                      string description, string difficulty, int minAge,
                      string date, int price, int seats) {
        findProvider(providerId);   // throws if this provider does not exist
        adventures.push_back(Adventure(newId("A"), providerId, name, location,
                                       description, difficulty, minAge, date, price, seats));
    }

    // Edits everything except seats
    void updateAdventure(string id, string name, string location,
                         string description, string difficulty, int minAge,
                         string date, int price) {
        Adventure& a = findAdventure(id);
        a.setName(name);
        a.setLocation(location);
        a.setDescription(description);
        a.setDifficulty(difficulty);
        a.setMinAge(minAge);
        a.setDate(date);
        a.setPrice(price);
    }

    // ================= BOOKINGS =================

    // Checks ages and seats, then saves the booking and returns it
    Booking book(string customerId, string adventureId, vector<Ticket> tickets) {
        findCustomer(customerId);                 // throws if not found
        Adventure& a = findAdventure(adventureId);

        if (tickets.size() == 0) {
            throw runtime_error("At least one ticket is needed");
        }

        // 1. Every person must meet the minimum age
        for (int i = 0; i < (int)tickets.size(); i++) {
            if (!a.isAgeAllowed(tickets[i].age)) {
                throw runtime_error(tickets[i].name + " is below the minimum age "
                                    + to_string(a.getMinAge()));
            }
        }

        // 2. Take the seats (throws if not enough)
        a.bookSeats(tickets.size());

        // 3. Save the booking
        int total = a.getPrice() * tickets.size();
        Booking b(newId("B"), customerId, adventureId, tickets, total);
        bookings.push_back(b);
        return b;
    }

    vector<Booking> getBookingsOfCustomer(string customerId) {
        vector<Booking> result;
        for (int i = 0; i < (int)bookings.size(); i++) {
            if (bookings[i].getCustomerId() == customerId) {
                result.push_back(bookings[i]);
            }
        }
        return result;
    }

    vector<Booking> getBookingsOfAdventure(string adventureId) {
        vector<Booking> result;
        for (int i = 0; i < (int)bookings.size(); i++) {
            if (bookings[i].getAdventureId() == adventureId) {
                result.push_back(bookings[i]);
            }
        }
        return result;
    }

    vector<Booking> getAllBookings() {
        return bookings;
    }

    // Marks the booking cancelled and gives its seats back
    void cancelBooking(string bookingId) {
        Booking& b = findBooking(bookingId);
        b.cancel();   // throws if already cancelled
        findAdventure(b.getAdventureId()).releaseSeats(b.getTicketCount());
    }

    // ================= USERS =================

    Customer getCustomer(string id) { return findCustomer(id); }
    Provider getProvider(string id) { return findProvider(id); }

    vector<Customer> getCustomers() { return customers; }
    vector<Provider> getProviders() { return providers; }
    vector<Admin>    getAdmins()    { return admins; }

    void updateCustomer(string id, string name, string email,
                        string gender, int age, string mobile) {
        if (!isValidEmail(email)) {
            throw runtime_error("Email must contain @");
        }
        if (!isValidMobile(mobile)) {
            throw runtime_error("Mobile must be exactly 10 digits");
        }
        if (emailUsedByOther(email, id)) {
            throw runtime_error("Email already in use");
        }
        Customer& c = findCustomer(id);
        c.setName(name);
        c.setEmail(email);
        c.setGender(gender);
        c.setAge(age);
        c.setMobile(mobile);
    }

    void updateProvider(string id, string name, string email,
                        string mobile, string companyName) {
        if (!isValidEmail(email)) {
            throw runtime_error("Email must contain @");
        }
        if (!isValidMobile(mobile)) {
            throw runtime_error("Mobile must be exactly 10 digits");
        }
        if (emailUsedByOther(email, id)) {
            throw runtime_error("Email already in use");
        }
        Provider& p = findProvider(id);
        p.setName(name);
        p.setEmail(email);
        p.setMobile(mobile);
        p.setCompanyName(companyName);
    }

    // Sets a new password for any user (customer, provider or admin)
    void changePassword(string userId, string newPassword) {
        for (int i = 0; i < (int)customers.size(); i++) {
            if (customers[i].getId() == userId) { customers[i].setPassword(newPassword); return; }
        }
        for (int i = 0; i < (int)providers.size(); i++) {
            if (providers[i].getId() == userId) { providers[i].setPassword(newPassword); return; }
        }
        for (int i = 0; i < (int)admins.size(); i++) {
            if (admins[i].getId() == userId) { admins[i].setPassword(newPassword); return; }
        }
        throw runtime_error("User not found");
    }

    // Customers and providers whose name contains the text (capitals ignored).
    // Returns User* pointers, so each result can call its own showProfile().
    vector<User*> searchUsers(string text) {
        vector<User*> result;
        string word = toLowerText(text);
        for (int i = 0; i < (int)customers.size(); i++) {
            if (toLowerText(customers[i].getName()).find(word) != string::npos) {
                result.push_back(&customers[i]);
            }
        }
        for (int i = 0; i < (int)providers.size(); i++) {
            if (toLowerText(providers[i].getName()).find(word) != string::npos) {
                result.push_back(&providers[i]);
            }
        }
        return result;
    }
};
