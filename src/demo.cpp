// =====================================================================
//  demo.cpp  -  shows every OOP topic of the syllabus, one by one
// =====================================================================
//  (To USE the booking system with menus, run main.cpp instead.)
//
//  This program runs in 4 parts:
//    PART A  Module 1 : classes, objects, constructors, static     (sections 1-3)
//    PART B  Module 2 : functions and operators                    (sections 4-8)
//    PART C  Module 3 : inheritance and polymorphism               (sections 9-12)
//    PART D  The real system: use cases UC-01, UC-02, UC-03        (sections 13-18)
//
//  Every OOP topic is marked with a tag like  [Friend class]  so you can
//  search for it in any file. docs/syllabus-coverage.md lists all of them.
//
//  Run:   g++ -std=c++17 src/demo.cpp -o demo      then      ./demo
// =====================================================================

#include <iostream>
#include <sstream>
#include "StartMenu.h"   // brings in every class (and the menu code the classes need)
using namespace std;

// ---------------------------------------------------------------------
// [Function prototype] tells the compiler about a function BEFORE it is used.
// Its parts:   return type   name   (parameter list)   ;
// The full bodies (the definitions) are written AFTER main().
// ---------------------------------------------------------------------
void printTitle(const string& title);
PaymentGateway& getGateway();
void addSeatByValue(Trip t);
void addSeatByReference(Trip& t);
void addSeatByPointer(Trip* t);

int main() {
    // =================================================================
    //  PART A  -  MODULE 1: classes, objects, constructors, static
    // =================================================================

    printTitle("1. Classes, objects, encapsulation, static members");

    // [Static member function] called with the CLASS name - no object exists yet
    cout << "Users before creating any object: " << User::getTotalUsers() << "\n";

    // [Object creation] each line below makes one object of a class
    AdventureProvider himalayanTrails("U-1004", "Rohit Thapa", "ops@himalayantrails.in",
                                      "rohit@123", "+91-98110-44521",
                                      "Himalayan Trails Pvt Ltd", "HP/ADV/2025/0871",
                                      "ATOAI Certified", 4.6, true);
    Traveler::EmergencyContact aaravContact("Meera Sharma", "+91-99300-27780");
    Traveler aarav("U-2031", "Aarav Sharma", "aarav.sharma@gmail.com",
                   "aarav@123", "+91-99300-27781",
                   aaravContact, "2004-03-22", "B+", MODERATE);
    Admin sneha("U-1001", "Sneha Iyer", "sneha.iyer@trekmate.in",
                "sneha@123", "+91-98200-11001");

    // [Static data member] totalUsers is ONE number shared by all objects
    cout << "Users after creating 3 objects  : " << User::getTotalUsers() << "\n";

    // [Encapsulation] the password is private; only login() can check it
    // cout << aarav.password;      // ERROR: 'password' is private
    cout << "Login with right password : "
         << (aarav.login("aarav.sharma@gmail.com", "aarav@123") ? "success" : "failed") << "\n";
    cout << "Login with wrong password : "
         << (aarav.login("aarav.sharma@gmail.com", "1234") ? "success" : "failed") << "\n";


    printTitle("2. Constructors: parameterized, default, default arguments, copy");

    // [Parameterized constructor] + [Returning objects from functions]:
    // createTrip() builds a Trip with the parameterized constructor and returns the object
    Trip hamptaPass = himalayanTrails.createTrip("Hampta Pass Trek", "Manali, Himachal Pradesh",
                                                 4500, "2026-09-12", "2026-09-17", 20, 18, MODERATE);
    // [Default constructor] no arguments; the details are read later with >> (section 4)
    Trip chadar;
    // [Constructor overloading] the two trips above used two different Trip constructors
    cout << hamptaPass.getTripId() << " - parameterized constructor: " << hamptaPass.getTitle() << "\n";
    cout << chadar.getTripId() << " - default constructor: title is still empty\n";

    // [Default arguments in constructor] EmergencyContact(string n = "", string p = "")
    Traveler::EmergencyContact noContact;   // both arguments left out
    cout << "EmergencyContact with no arguments -> name = \"" << noContact.getName() << "\"\n";

    // [Copy constructor] User(const User& other) runs when aarav is copied
    {
        Traveler aaravCopy = aarav;
        cout << "Copied " << aaravCopy.getName() << ". Users now: " << User::getTotalUsers() << "\n";
    }   // aaravCopy is destroyed at this }  ->  the [Destructor] lowers the count again
    cout << "Copy destroyed. Users now: " << User::getTotalUsers() << "\n";


    printTitle("3. Static object");

    // getGateway() keeps ONE PaymentGateway as a [Static object]: it is made the
    // first time the function runs, and the SAME object is given back every time.
    PaymentGateway& gateway = getGateway();
    PaymentGateway& gatewayAgain = getGateway();
    cout << "1st call gives the object at " << &gateway << "\n";
    cout << "2nd call gives the object at " << &gatewayAgain << "   (same object)\n";


    // =================================================================
    //  PART B  -  MODULE 2: functions and operators
    // =================================================================

    printTitle("4. Friend functions: operator<< and operator>>");

    // [Stream operator overloading] each class has operator<< as a [Friend function],
    // so  cout << object  can print its private details
    himalayanTrails.publishTrip(hamptaPass);
    cout << "--- Provider ---\n" << himalayanTrails;
    cout << "--- Traveler ---\n" << aarav;
    cout << "--- Trip ---\n" << hamptaPass;

    // operator>> fills the empty 'chadar' trip from input.
    // A stringstream is used here so nobody has to type during the demo.
    istringstream input("Chadar Frozen River Trek\n"
                        "Leh, Ladakh\n"
                        "18500 2027-01-10 2027-01-18 15 21 2\n");
    input >> chadar;
    cout << "--- Trip read with >> ---\n" << chadar;


    printTitle("5. Nested class");

    // EmergencyContact is a class INSIDE Traveler, so its full name is Traveler::EmergencyContact
    Traveler::EmergencyContact contact = aarav.getEmergencyContact();
    cout << "Aarav's emergency contact: " << contact.getName() << ", " << contact.getPhone() << "\n";


    printTitle("6. Array of objects + binary operators < and ==");

    // [Array of objects] three Trip OBJECTS stored in one array
    Trip catalogue[3] = {
        Trip("Rishikesh River Rafting", "Rishikesh, Uttarakhand", 1500,
             "2026-09-20", "2026-09-20", 10, 14, LOW),
        Trip("Kedarkantha Winter Trek", "Uttarkashi, Uttarakhand", 8500,
             "2026-12-10", "2026-12-15", 15, 16, MODERATE),
        Trip("Bir Billing Paragliding", "Bir, Himachal Pradesh", 3000,
             "2026-10-25", "2026-10-25", 6, 18, LOW)
    };
    for (int i = 0; i < 3; i++) {
        cout << "  catalogue[" << i << "]  " << catalogue[i].getTripId() << "  "
             << catalogue[i].getTitle() << " - Rs. " << catalogue[i].getPrice() << "\n";
    }

    // [Binary operator overloading] member version:  a < b  compares prices
    Trip cheapest = catalogue[0];
    for (int i = 1; i < 3; i++) {
        if (catalogue[i] < cheapest) cheapest = catalogue[i];
    }
    cout << "Cheapest trip (found with <): " << cheapest.getTitle() << "\n";

    // [Binary operator overloading] friend version:  a == b  checks for the same trip ID
    cout << "cheapest == catalogue[0] ? " << (cheapest == catalogue[0] ? "yes" : "no") << "\n";
    cout << "cheapest == catalogue[1] ? " << (cheapest == catalogue[1] ? "yes" : "no") << "\n";


    printTitle("7. Unary operator ++ and parameter passing");

    cout << "Rafting seats at start         : " << catalogue[0].getAvailableSlots() << "\n";
    ++catalogue[0];   // [Unary operator overloading] adds one seat
    cout << "After ++catalogue[0]           : " << catalogue[0].getAvailableSlots() << "\n";

    // [Parameter passing] three ways to give an object to a function
    addSeatByValue(catalogue[0]);
    cout << "After addSeatByValue(trip)     : " << catalogue[0].getAvailableSlots()
         << "   (no change - the function got a COPY)\n";
    addSeatByReference(catalogue[0]);
    cout << "After addSeatByReference(trip) : " << catalogue[0].getAvailableSlots()
         << "   (changed - the function got the ORIGINAL)\n";
    addSeatByPointer(&catalogue[0]);
    cout << "After addSeatByPointer(&trip)  : " << catalogue[0].getAvailableSlots()
         << "   (changed - the function got its ADDRESS)\n";


    printTitle("8. Data conversion: basic type <-> class");

    // [Data conversion: basic -> class] a double becomes a Payment object,
    // because Payment has the constructor  Payment(double amount, string timestamp = "N/A")
    Payment advance = 2000.0;
    advance.processPayment(gateway, "4111111111111111", "12/28");
    cout << "Payment made from 2000.0 : " << advance << "\n";

    // [Data conversion: class -> basic] a Payment becomes a double,
    // because Payment has  operator double()
    double amount = advance;
    cout << "Same payment as a double : " << amount << "\n";


    // =================================================================
    //  PART C  -  MODULE 3: inheritance and polymorphism
    // =================================================================

    printTitle("9. Multilevel inheritance + protected members + constructor order");

    // [Multilevel inheritance]  User -> Admin -> SuperAdmin
    // [Constructor execution order] the base part is built FIRST, the child LAST
    cout << "Creating vikram (a SuperAdmin):\n";
    User::setShowConstructorCalls(true);
    SuperAdmin vikram("U-1000", "Vikram Mehta", "vikram.mehta@trekmate.in",
                      "vikram@123", "+91-98200-10000", "TrekMate Pvt Ltd");
    User::setShowConstructorCalls(false);

    // [Protected member] viewSystemStats() uses validatePassword(), which is
    // protected in User. SuperAdmin (a grandchild of User) can use it; main() cannot:
    // vikram.validatePassword("vikram@123");     // ERROR: it is protected
    vikram.viewSystemStats("wrong-password");
    vikram.viewSystemStats("vikram@123");


    printTitle("10. Multiple, multipath and hybrid inheritance (diamond problem)");

    //                 User
    //            _____|_____
    //           |           |
    //       Traveler    AdventureProvider     <- both: virtual public User
    //           |___________|
    //                 |
    //          TravelerProvider               <- [Multiple inheritance]
    int usersBefore = User::getTotalUsers();
    cout << "Creating karan (a TravelerProvider):\n";
    User::setShowConstructorCalls(true);
    TravelerProvider karan("U-3050", "Karan Negi", "karan.negi@spitiexpeditions.in",
                           "karan@123", "+91-94180-55210",
                           Traveler::EmergencyContact("Pooja Negi", "+91-94180-55211"),
                           "1995-06-14", "O+", HIGH,
                           "Spiti Expeditions", "HP/ADV/2024/0412", "IMF Certified", 4.8, true);
    User::setShowConstructorCalls(false);

    // [Virtual inheritance] the User constructor ran only ONCE (see above),
    // so karan is counted once and has only one name - the diamond problem is solved.
    cout << "Users added: " << User::getTotalUsers() - usersBefore
         << ", name: " << karan.getName() << "\n";

    // [Ambiguity in multiple inheritance] both parents have getRole().
    // The scope operator :: picks one of them on purpose.
    cout << "karan.Traveler::getRole()          = " << karan.Traveler::getRole() << "\n";
    cout << "karan.AdventureProvider::getRole() = " << karan.AdventureProvider::getRole() << "\n";
    cout << "karan.getRole() (its own version)  = " << karan.getRole() << "\n";
    // cout << karan;    // ERROR: ambiguous - Traveler's << or AdventureProvider's << ?


    printTitle("11. Abstract class, virtual functions, base-class pointers");

    // [Abstract class] User has [Pure virtual function]s (getRole() = 0 and
    // showMenu() = 0), so a plain User object can NOT be made:
    // User someone("U-1", "x", "x", "x", "x");     // ERROR: User is abstract

    // [Base-class pointers to derived objects] every pointer is a User*,
    // but each one points to a different kind of user
    vector<User*> users = { &aarav, &himalayanTrails, &sneha, &vikram, &karan };
    // users[0]->getFitnessLevel();    // ERROR: a User* can only see User's functions

    // [Run-time polymorphism] / [Dynamic binding]: getRole() is virtual, so each
    // object's OWN version runs. Which one is decided while the program RUNS.
    cout << "Admin's list of all users:\n";
    sneha.viewAllUsers(users);

    // [Compile-time polymorphism] the other kind: overloaded functions and operators
    // are chosen while COMPILING, from the argument types.
    cout << "toString(MODERATE) = " << toString(MODERATE)
         << ",  toString(PUBLISHED) = " << toString(PUBLISHED) << "\n";

    // [Virtual functions] a RULE that changes by type: maxSeatsPerBooking()
    // is virtual, so each traveler's own limit is used
    vector<Traveler*> travelers = { &aarav, &karan };
    for (Traveler* t : travelers) {
        cout << t->getName() << " (" << t->getRole() << ") may book up to "
             << t->maxSeatsPerBooking() << " seats at once\n";
    }

    // [Interface] Trip and User both follow Searchable, so ONE kind of pointer
    // can search both. [Abstraction]: the code only knows "it can be matched".
    vector<Searchable*> things = { &hamptaPass, &aarav };
    cout << "Does each thing match \"manali\"? ";
    for (Searchable* item : things) cout << (item->matches("manali") ? "yes " : "no ");
    cout << "\n";

    // operator<< is a friend function, NOT virtual, so through a User* it
    // prints only the User part (no DOB, blood group, ...)
    cout << "cout << *users[0] prints only the User part:\n" << *users[0];


    printTitle("12. Object slicing and final");

    // [Object slicing] copying a child object INTO a parent object keeps only
    // the parent part. The child's extra data and its own getRole() are cut off.
    Admin slicedAdmin = vikram;
    cout << "sizeof(vikram)      = " << sizeof(vikram) << " bytes\n";
    cout << "sizeof(slicedAdmin) = " << sizeof(slicedAdmin) << " bytes   (companyName was cut off)\n";
    cout << "vikram.getRole()      = " << vikram.getRole() << "\n";
    cout << "slicedAdmin.getRole() = " << slicedAdmin.getRole()
         << "   (copied by value -> SuperAdmin part lost)\n";
    User* vikramPtr = &vikram;
    cout << "vikramPtr->getRole()  = " << vikramPtr->getRole() << "   (pointer -> no slicing)\n";

    // [final] SuperAdmin and TravelerProvider are marked final, so this is an ERROR:
    // class OwnerAssistant : public SuperAdmin { };
    cout << "SuperAdmin and TravelerProvider are 'final': no class can inherit from them.\n";


    // =================================================================
    //  PART D  -  the real system: use cases UC-01, UC-02, UC-03
    // =================================================================

    printTitle("13. UC-01 Book Adventure");

    string today = "2026-08-19";

    // [Pointers to objects] tripPtr holds the ADDRESS of hamptaPass; -> reaches its members
    Trip* tripPtr = &hamptaPass;
    cout << tripPtr->getTitle() << " - seats left: " << tripPtr->getAvailableSlots() << "\n\n";

    // Main flow: 2 seats, payment succeeds.
    // [Dynamic memory allocation] bookTrip() makes the Booking with 'new' and returns its address
    Booking* b1 = aarav.bookTrip(hamptaPass, 2, gateway, "4111111111111111", "12/28", today);
    cout << *b1;
    cout << "Seats left now: " << tripPtr->getAvailableSlots() << "\n\n";

    // [this pointer] inside bookTrip(), 'this' was aarav's address, and the booking saved it
    cout << "&aarav            = " << &aarav << "\n";
    cout << "b1->getTraveler() = " << b1->getTraveler() << "   (same address)\n\n";

    cout << "4a - asking for more seats than are left:\n";
    Booking* tooMany = aarav.bookTrip(hamptaPass, 25, gateway, "4111111111111111", "12/28", today);
    cout << "Returned pointer is " << (tooMany == nullptr ? "nullptr" : "not null") << "\n\n";

    cout << "6a - payment fails (invalid card number):\n";
    Booking* badCard = aarav.bookTrip(hamptaPass, 1, gateway, "1234", "12/28", today);
    cout << "Returned pointer is " << (badCard == nullptr ? "nullptr" : "not null")
         << ", seats left: " << tripPtr->getAvailableSlots() << "\n\n";

    cout << "A second booking (1 seat):\n";
    Booking* b2 = aarav.bookTrip(hamptaPass, 1, gateway, "4111111111111111", "12/28", today);
    aarav.viewMyBookings();


    printTitle("14. Data conversion: class -> class (Booking -> Receipt)");

    // Receipt has the constructor Receipt(const Booking&), so a Booking can become a Receipt
    Receipt receipt = *b1;
    cout << receipt;


    printTitle("15. UC-03 Admin tries to remove a trip that has bookings");

    // [Friend class] removeTrip() reads Trip's private data directly (see Admin.h)
    sneha.removeTrip(hamptaPass);   // alternate flow 2a: blocked


    printTitle("16. UC-02 Cancel Booking");

    cout << "1a - trying to cancel after the trip date:\n";
    aarav.cancelBooking(b1, gateway, "2026-09-20");

    cout << "\nMain flow - refund succeeds:\n";
    aarav.cancelBooking(b1, gateway, today);
    cout << "Seats left now: " << tripPtr->getAvailableSlots() << "\n\n";

    // [Default arguments in functions] viewMyBookings(bool onlyConfirmed = false)
    aarav.viewMyBookings();        // argument left out -> false -> ALL bookings
    aarav.viewMyBookings(true);    // only the CONFIRMED ones

    cout << "\n5a - refund fails, marked PENDING:\n";
    gateway.setFailMode(true);
    aarav.cancelBooking(b2, gateway, today);
    gateway.setFailMode(false);


    printTitle("17. Admin settles the pending refund, then removes the trip");

    // [Pointers to objects] a list of Booking pointers
    vector<Booking*> allBookings = { b1, b2 };
    sneha.viewAllBookings(allBookings);
    sneha.settlePendingRefund(b2->getPayment(), gateway);
    sneha.removeTrip(hamptaPass);   // no confirmed bookings now -> allowed


    printTitle("18. End of program");

    vikram.viewSystemStats("vikram@123");

    // [Dynamic memory allocation] the bookings were made with 'new',
    // so they must be freed with 'delete'. Every other object is destroyed
    // automatically when main() ends (destructors run in reverse order).
    delete b1;
    delete b2;
    cout << "Bookings deleted. Done.\n";

    return 0;
}

// ---------------------------------------------------------------------
// Definitions of the functions whose [Function prototype]s are above main()
// ---------------------------------------------------------------------

void printTitle(const string& title) {
    cout << "\n===== " << title << " =====\n";
}

// [Static object] a 'static' object inside a function is created only ONCE
// (on the first call) and lives until the program ends. Every call returns
// a reference to that same object.
PaymentGateway& getGateway() {
    static PaymentGateway gateway("SimulatedGateway");
    return gateway;
}

// [Parameter passing]
void addSeatByValue(Trip t) {       // pass by value: t is a COPY, the original is not touched
    ++t;
}

void addSeatByReference(Trip& t) {  // pass by reference: t IS the original object
    ++t;
}

void addSeatByPointer(Trip* t) {    // pass by pointer: t holds the original's address
    ++(*t);
}
