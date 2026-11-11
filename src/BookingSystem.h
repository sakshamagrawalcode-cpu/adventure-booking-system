// BookingSystem.h
// Holds all data and all rules of the system.
//
// The data is kept in text files in the data folder (../data/ seen from src),
// so all three programs share it and nothing is lost when a program closes:
//  - every public function first calls load() to read the latest data,
//  - every function that changes something calls save() at the end.
// On the very first run there are no files yet, so the sample data is used and saved.
//
// The menus never change data directly: they only call these functions.

#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
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
    int nextIdNumber = 1;   // used to make new IDs like "A6", "B7"

    // Where the data files are, seen from the src folder
    string dataFolder = "../data/";

    // ================= small helpers =================

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

    // Returns true if another account (not userId) already uses this email.
    // Capitals are ignored: "Rahul@Example.com" is the same as "rahul@example.com".
    bool emailUsedByOther(string email, string userId) {
        string e = toLowerText(email);
        for (int i = 0; i < (int)customers.size(); i++) {
            if (toLowerText(customers[i].getEmail()) == e && customers[i].getId() != userId) return true;
        }
        for (int i = 0; i < (int)providers.size(); i++) {
            if (toLowerText(providers[i].getEmail()) == e && providers[i].getId() != userId) return true;
        }
        for (int i = 0; i < (int)admins.size(); i++) {
            if (toLowerText(admins[i].getEmail()) == e && admins[i].getId() != userId) return true;
        }
        return false;
    }

    // ================= simple checks (static member functions) =================
    // They are static because they don't use any object's data:
    // they only look at the value they are given.

    // An email must contain '@'
    static bool isValidEmail(string email) {
        return email.find('@') != string::npos;
    }

    // A mobile number must be exactly 10 digits
    static bool isValidMobile(string mobile) {
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

    // A date must look like DD-MM-YYYY, with day 1-31 and month 1-12
    static bool isValidDate(string date) {
        if (date.size() != 10 || date[2] != '-' || date[5] != '-') {
            return false;
        }
        for (int i = 0; i < 10; i++) {
            if (i == 2 || i == 5) continue;   // skip the two '-'
            if (date[i] < '0' || date[i] > '9') {
                return false;
            }
        }
        int day = stoi(date.substr(0, 2));
        int month = stoi(date.substr(3, 2));
        return day >= 1 && day <= 31 && month >= 1 && month <= 12;
    }

    // ================= sample data =================

    // Fills the vectors with the sample data (used only on the very first run)
    void loadSampleData() {
        customers.clear();
        providers.clear();
        admins.clear();
        adventures.clear();
        bookings.clear();

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

        adventures.push_back(Adventure("A1", "P1", "Kedarkantha Winter Trek", "Uttarakhand",
                     "A 6-day snow trek through pine forests to a 12,500 ft summit.",
                     "Moderate", 12, "20-12-2026", 9500, 10));
        adventures.push_back(Adventure("A2", "P1", "Hampta Pass Trek", "Himachal Pradesh",
                     "A 5-day crossing from green Kullu valley to the dry Spiti side.",
                     "Moderate", 14, "15-06-2027", 11000, 8));
        adventures.push_back(Adventure("A3", "P2", "River Rafting (16 km)", "Rishikesh",
                     "Rafting on the Ganga with grade 3 rapids and a trained guide.",
                     "Easy", 14, "05-01-2027", 1500, 12));
        adventures.push_back(Adventure("A4", "P2", "Bungee Jumping", "Rishikesh",
                     "A jump from an 83 m platform with full safety gear.",
                     "Hard", 18, "10-01-2027", 3500, 6));

        // One booking at the start, so the lists are not empty
        vector<Ticket> tickets = { {"Rahul Mehta", 20}, {"Aman Mehta", 24} };
        adventures[0].bookSeats(tickets.size());
        bookings.push_back(Booking("B5", "C1", "A1", tickets,
                                   adventures[0].getPrice() * tickets.size()));

        nextIdNumber = 6;
    }

    // ================= reading and writing the data files =================
    // Each line of a file is one object. Its values are separated by '|', e.g.
    //   C1|Rahul Mehta|rahul@example.com|rahul123|Male|20|9123400001

    // Splits "a|b|c" into {"a", "b", "c"}
    vector<string> splitLine(string line) {
        if (line.size() > 0 && line[line.size() - 1] == '\r') {
            line.pop_back();   // remove a Windows line ending, if any
        }
        vector<string> parts;
        string part;
        stringstream ss(line);
        while (getline(ss, part, '|')) {
            parts.push_back(part);
        }
        return parts;
    }

    // Throws if a line does not have the expected number of values
    void checkParts(vector<string>& parts, int expected, string fileName) {
        if ((int)parts.size() != expected) {
            throw runtime_error("The data file " + fileName + " is damaged");
        }
    }

    // Reads all data from the files into the vectors.
    // If the files don't exist yet (first run), uses the sample data and saves it.
    void load() {
        ifstream check(dataFolder + "customers.txt");
        if (!check) {
            loadSampleData();
            save();
            return;
        }
        check.close();

        customers.clear();
        providers.clear();
        admins.clear();
        adventures.clear();
        bookings.clear();
        string line;

        ifstream customerFile(dataFolder + "customers.txt");
        while (getline(customerFile, line)) {
            if (line == "" || line == "\r") continue;
            vector<string> p = splitLine(line);
            checkParts(p, 7, "customers.txt");
            customers.push_back(Customer(p[0], p[1], p[2], p[3], p[4], stoi(p[5]), p[6]));
        }

        ifstream providerFile(dataFolder + "providers.txt");
        while (getline(providerFile, line)) {
            if (line == "" || line == "\r") continue;
            vector<string> p = splitLine(line);
            checkParts(p, 6, "providers.txt");
            providers.push_back(Provider(p[0], p[1], p[2], p[3], p[4], p[5]));
        }

        ifstream adminFile(dataFolder + "admins.txt");
        while (getline(adminFile, line)) {
            if (line == "" || line == "\r") continue;
            vector<string> p = splitLine(line);
            checkParts(p, 4, "admins.txt");
            admins.push_back(Admin(p[0], p[1], p[2], p[3]));
        }

        ifstream adventureFile(dataFolder + "adventures.txt");
        while (getline(adventureFile, line)) {
            if (line == "" || line == "\r") continue;
            vector<string> p = splitLine(line);
            checkParts(p, 11, "adventures.txt");
            // the overloaded constructor, which also sets seatsLeft
            adventures.push_back(Adventure(p[0], p[1], p[2], p[3], p[4], p[5], stoi(p[6]),
                                           p[7], stoi(p[8]), stoi(p[9]), stoi(p[10])));
        }

        // tickets.txt: bookingId|name|age  (one line per ticket)
        vector<string> ticketBookingIds;
        vector<Ticket> allTickets;
        ifstream ticketFile(dataFolder + "tickets.txt");
        while (getline(ticketFile, line)) {
            if (line == "" || line == "\r") continue;
            vector<string> p = splitLine(line);
            checkParts(p, 3, "tickets.txt");
            ticketBookingIds.push_back(p[0]);
            allTickets.push_back(Ticket{p[1], stoi(p[2])});
        }

        // bookings.txt: id|customerId|adventureId|totalPrice|status
        ifstream bookingFile(dataFolder + "bookings.txt");
        while (getline(bookingFile, line)) {
            if (line == "" || line == "\r") continue;
            vector<string> p = splitLine(line);
            checkParts(p, 5, "bookings.txt");

            // collect this booking's tickets
            vector<Ticket> tickets;
            for (int i = 0; i < (int)allTickets.size(); i++) {
                if (ticketBookingIds[i] == p[0]) {
                    tickets.push_back(allTickets[i]);
                }
            }
            Booking b(p[0], p[1], p[2], tickets, stoi(p[3]));
            if (p[4] == "CANCELLED") {
                b.cancel();
            }
            bookings.push_back(b);
        }

        // The next new ID number is one more than the biggest one used so far
        nextIdNumber = 1;
        for (int i = 0; i < (int)adventures.size(); i++) {
            int n = stoi(adventures[i].getId().substr(1));   // "A12" -> 12
            if (n >= nextIdNumber) nextIdNumber = n + 1;
        }
        for (int i = 0; i < (int)bookings.size(); i++) {
            int n = stoi(bookings[i].getId().substr(1));     // "B7" -> 7
            if (n >= nextIdNumber) nextIdNumber = n + 1;
        }
    }

    // Opens a data file for writing. Throws if the data folder can't be found.
    ofstream openForWriting(string fileName) {
        ofstream file(dataFolder + fileName);
        if (!file) {
            throw runtime_error("Can't write " + dataFolder + fileName +
                                ". Run the program from the src folder.");
        }
        return file;
    }

    // Writes all the vectors into the files (each file is rewritten fully)
    void save() {
        ofstream customerFile = openForWriting("customers.txt");
        for (int i = 0; i < (int)customers.size(); i++) {
            Customer& c = customers[i];
            customerFile << c.getId() << "|" << c.getName() << "|" << c.getEmail() << "|"
                         << c.getPassword() << "|" << c.getGender() << "|" << c.getAge() << "|"
                         << c.getMobile() << "\n";
        }

        ofstream providerFile = openForWriting("providers.txt");
        for (int i = 0; i < (int)providers.size(); i++) {
            Provider& p = providers[i];
            providerFile << p.getId() << "|" << p.getName() << "|" << p.getEmail() << "|"
                         << p.getPassword() << "|" << p.getMobile() << "|"
                         << p.getCompanyName() << "\n";
        }

        ofstream adminFile = openForWriting("admins.txt");
        for (int i = 0; i < (int)admins.size(); i++) {
            Admin& a = admins[i];
            adminFile << a.getId() << "|" << a.getName() << "|" << a.getEmail() << "|"
                      << a.getPassword() << "\n";
        }

        ofstream adventureFile = openForWriting("adventures.txt");
        for (int i = 0; i < (int)adventures.size(); i++) {
            Adventure& a = adventures[i];
            adventureFile << a.getId() << "|" << a.getProviderId() << "|" << a.getName() << "|"
                          << a.getLocation() << "|" << a.getDescription() << "|"
                          << a.getDifficulty() << "|" << a.getMinAge() << "|" << a.getDate() << "|"
                          << a.getPrice() << "|" << a.getTotalSeats() << "|"
                          << a.getSeatsLeft() << "\n";
        }

        ofstream bookingFile = openForWriting("bookings.txt");
        ofstream ticketFile = openForWriting("tickets.txt");
        for (int i = 0; i < (int)bookings.size(); i++) {
            Booking& b = bookings[i];
            bookingFile << b.getId() << "|" << b.getCustomerId() << "|" << b.getAdventureId()
                        << "|" << b.getTotalPrice() << "|" << b.getStatus() << "\n";
            vector<Ticket> tickets = b.getTickets();
            for (int t = 0; t < (int)tickets.size(); t++) {
                ticketFile << b.getId() << "|" << tickets[t].name << "|" << tickets[t].age << "\n";
            }
        }
    }

public:
    // Constructor: reads the data files (or creates them with the sample data)
    BookingSystem() {
        load();
    }

    // ================= LOGIN =================
    // Capitals in the email are ignored.

    Customer loginCustomer(string email, string password) {
        load();
        for (int i = 0; i < (int)customers.size(); i++) {
            if (toLowerText(customers[i].getEmail()) == toLowerText(email)
                && customers[i].checkPassword(password)) {
                return customers[i];
            }
        }
        throw runtime_error("Wrong email or password");
    }

    Provider loginProvider(string email, string password) {
        load();
        for (int i = 0; i < (int)providers.size(); i++) {
            if (toLowerText(providers[i].getEmail()) == toLowerText(email)
                && providers[i].checkPassword(password)) {
                return providers[i];
            }
        }
        throw runtime_error("Wrong email or password");
    }

    Admin loginAdmin(string email, string password) {
        load();
        for (int i = 0; i < (int)admins.size(); i++) {
            if (toLowerText(admins[i].getEmail()) == toLowerText(email)
                && admins[i].checkPassword(password)) {
                return admins[i];
            }
        }
        throw runtime_error("Wrong email or password");
    }

    // ================= ADVENTURES =================

    vector<Adventure> getAdventures() {
        load();
        return adventures;
    }

    vector<Adventure> getAdventuresOfProvider(string providerId) {
        load();
        vector<Adventure> result;
        for (int i = 0; i < (int)adventures.size(); i++) {
            if (adventures[i].getProviderId() == providerId) {
                result.push_back(adventures[i]);
            }
        }
        return result;
    }

    Adventure getAdventure(string id) {
        load();
        return findAdventure(id);
    }

    void addAdventure(string providerId, string name, string location,
                      string description, string difficulty, int minAge,
                      string date, int price, int seats) {
        load();
        findProvider(providerId);   // throws if this provider does not exist
        if (!isValidDate(date)) {
            throw runtime_error("Date must be like 20-12-2026 (DD-MM-YYYY)");
        }
        adventures.push_back(Adventure(newId("A"), providerId, name, location,
                                       description, difficulty, minAge, date, price, seats));
        save();
    }

    // Edits everything except seats
    void updateAdventure(string id, string name, string location,
                         string description, string difficulty, int minAge,
                         string date, int price) {
        load();
        if (!isValidDate(date)) {
            throw runtime_error("Date must be like 20-12-2026 (DD-MM-YYYY)");
        }
        Adventure& a = findAdventure(id);
        a.setName(name);
        a.setLocation(location);
        a.setDescription(description);
        a.setDifficulty(difficulty);
        a.setMinAge(minAge);
        a.setDate(date);
        a.setPrice(price);
        save();
    }

    // ================= BOOKINGS =================

    // Checks ages and seats, then saves the booking and returns it
    Booking book(string customerId, string adventureId, vector<Ticket> tickets) {
        load();
        findCustomer(customerId);                 // throws if not found
        Adventure& a = findAdventure(adventureId);

        if (tickets.size() == 0) {
            throw runtime_error("At least one ticket is needed");
        }
        if ((int)tickets.size() > Booking::MAX_TICKETS) {
            throw runtime_error("At most " + to_string(Booking::MAX_TICKETS) + " tickets per booking");
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
        save();
        return b;
    }

    // Default argument: getBookingsOfCustomer("C1") gives all bookings,
    // getBookingsOfCustomer("C1", true) gives only the ones still BOOKED.
    vector<Booking> getBookingsOfCustomer(string customerId, bool onlyActive = false) {
        load();
        vector<Booking> result;
        for (int i = 0; i < (int)bookings.size(); i++) {
            if (bookings[i].getCustomerId() != customerId) continue;
            if (onlyActive && bookings[i].isCancelled()) continue;
            result.push_back(bookings[i]);
        }
        return result;
    }

    vector<Booking> getBookingsOfAdventure(string adventureId, bool onlyActive = false) {
        load();
        vector<Booking> result;
        for (int i = 0; i < (int)bookings.size(); i++) {
            if (bookings[i].getAdventureId() != adventureId) continue;
            if (onlyActive && bookings[i].isCancelled()) continue;
            result.push_back(bookings[i]);
        }
        return result;
    }

    vector<Booking> getAllBookings(bool onlyActive = false) {
        load();
        vector<Booking> result;
        for (int i = 0; i < (int)bookings.size(); i++) {
            if (onlyActive && bookings[i].isCancelled()) continue;
            result.push_back(bookings[i]);
        }
        return result;
    }

    // Admin version: cancels any booking and gives its seats back
    void cancelBooking(string bookingId) {
        load();
        Booking& b = findBooking(bookingId);
        b.cancel();   // throws if already cancelled
        findAdventure(b.getAdventureId()).releaseSeats(b.getTicketCount());
        save();
    }

    // Function overloading: the customer version also checks that the booking is theirs
    void cancelBooking(string bookingId, string customerId) {
        load();
        if (findBooking(bookingId).getCustomerId() != customerId) {
            throw runtime_error("This booking is not yours");
        }
        cancelBooking(bookingId);
    }

    // ================= USERS =================

    Customer getCustomer(string id) { load(); return findCustomer(id); }
    Provider getProvider(string id) { load(); return findProvider(id); }

    vector<Customer> getCustomers() { load(); return customers; }
    vector<Provider> getProviders() { load(); return providers; }
    vector<Admin>    getAdmins()    { load(); return admins; }

    void updateCustomer(string id, string name, string email,
                        string gender, int age, string mobile) {
        load();
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
        save();
    }

    void updateProvider(string id, string name, string email,
                        string mobile, string companyName) {
        load();
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
        save();
    }

    // Sets a new password for any user (customer, provider or admin)
    void changePassword(string userId, string newPassword) {
        load();
        for (int i = 0; i < (int)customers.size(); i++) {
            if (customers[i].getId() == userId) { customers[i].setPassword(newPassword); save(); return; }
        }
        for (int i = 0; i < (int)providers.size(); i++) {
            if (providers[i].getId() == userId) { providers[i].setPassword(newPassword); save(); return; }
        }
        for (int i = 0; i < (int)admins.size(); i++) {
            if (admins[i].getId() == userId) { admins[i].setPassword(newPassword); save(); return; }
        }
        throw runtime_error("User not found");
    }

    // Customers and providers whose name contains the text (capitals ignored).
    // Returns User* pointers, so each result can call its own showProfile().
    // (The pointers are valid until the next call to a BookingSystem function.)
    vector<User*> searchUsers(string text) {
        load();
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
