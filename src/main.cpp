#include <iostream>
#include <sstream>
#include "User.h"
#include "Trip.h"
#include "Traveler.h"
#include "AdventureProvider.h"
#include "Admin.h"
#include "Booking.h"
#include "Payment.h"
#include "PaymentGateway.h"
using namespace std;

// Takes User BY VALUE -> any Traveler passed here gets sliced
void printAsUser(User u) {
    cout << u;
}

// [final] Uncommenting this gives a compile error:
// "cannot derive from 'final' base 'Traveler'"
// class PremiumTraveler : public Traveler { };

// [Virtual base class] Without 'virtual', a class like
//     class X : public Traveler, public Admin { };
// would contain TWO User parts (two userIds, counted twice in totalUsers),
// and x.getName() would be ambiguous. With 'virtual public User' it gets ONE.
// (Traveler is final, so this exact class cannot be written in our project.)

int main() {
    cout << "===== 1. Static variable + static function =====\n";
    cout << "Users before creating any object: " << User::getTotalUsers() << "\n";
    cout << "Trips before creating any object: " << Trip::getTripCount() << "\n\n";

    AdventureProvider himalayanTrails("U-1004", "Rohit Thapa", "ops@himalayantrails.in",
                                      "rohit@123", "+91-98110-44521",
                                      "Himalayan Trails Pvt Ltd", "HP/ADV/2025/0871",
                                      "ATOAI Certified", 4.6, true);

    // [Nested class] object created using Outer::Inner
    Traveler::EmergencyContact aaravContact("Meera Sharma", "+91-99300-27780");

    Traveler aarav("U-2031", "Aarav Sharma", "aarav.sharma@gmail.com",
                   "aarav@123", "+91-99300-27781",
                   aaravContact, "2004-03-22", "B+", MODERATE);

    cout << "Users after creating 2 objects: " << User::getTotalUsers() << "\n\n";

    cout << "===== 2. operator<< (friend) =====\n";
    cout << "--- Provider ---\n" << himalayanTrails << "\n";
    cout << "--- Traveler ---\n" << aarav << "\n";

    cout << "===== 3. Nested class =====\n";
    Traveler::EmergencyContact c = aarav.getEmergencyContact();
    cout << "Aarav's emergency contact: " << c.getName() << ", " << c.getPhone() << "\n\n";

    cout << "===== 4. Trip + operator>> (friend) =====\n";
    Trip hamptaPass = himalayanTrails.createTrip("Hampta Pass Trek", "Manali, Himachal Pradesh",
                                                 4500, "2026-09-12", "2026-09-17", 20, 18, MODERATE);
    himalayanTrails.publishTrip(hamptaPass);
    cout << hamptaPass << "\n";

    // Same input a user would type; stringstream is used so the demo runs without typing
    istringstream input("Chadar Frozen River Trek\n"
                        "Leh, Ladakh\n"
                        "18500 2027-01-10 2027-01-18 15 21 2\n");
    Trip chadar;
    input >> chadar;
    cout << "Trip read using >> :\n" << chadar << "\n";
    cout << "Total trips created (static): " << Trip::getTripCount() << "\n\n";

    cout << "===== 5. Object slicing =====\n";
    User slicedUser = aarav;   // only the User part of aarav is copied
    cout << "sizeof(aarav)      = " << sizeof(aarav) << " bytes\n";
    cout << "sizeof(slicedUser) = " << sizeof(slicedUser) << " bytes\n";
    cout << "Printing slicedUser (DOB, blood group, emergency contact are lost):\n";
    cout << slicedUser << "\n";

    cout << "Passing aarav by value to printAsUser(User u):\n";
    printAsUser(aarav);
    cout << "\n";

    cout << "===== 6. final =====\n";
    cout << "Traveler and AdventureProvider are declared 'final'.\n";
    cout << "See the commented PremiumTraveler class above main().\n\n";

    cout << "===== 7. Virtual function + pointer to derived classes =====\n";
    Admin sneha("U-1001", "Sneha Iyer", "sneha.iyer@trekmate.in",
                "sneha@123", "+91-98200-11001");

    // [Pointer to derived classes] base-class pointers pointing to child objects
    User* users[] = { &aarav, &himalayanTrails, &sneha };
    cout << "Admin view of all users (getRole() is virtual, child version runs):\n";
    sneha.viewAllUsers(users, 3);

    // users[0]->getFitnessLevel();   // compile error: a User* only sees User's members

    cout << "\nslicedUser.getRole() = " << slicedUser.getRole()
         << "   (copied by value -> Traveler part lost, so User's version runs)\n";
    cout << "users[0]->getRole() = " << users[0]->getRole()
         << "   (pointer -> no slicing, Traveler's version runs)\n\n";

    cout << "operator<< is a friend function, it cannot be virtual.\n"
         << "So *users[0] prints only the User part:\n" << *users[0] << "\n";

    cout << "===== 8. Virtual base class =====\n";
    cout << "Traveler, AdventureProvider and Admin inherit 'virtual public User'.\n";
    cout << "See the comment above main() for the two-parents case.\n\n";

    cout << "===== 9. UC-01 Book Adventure (pointer to objects + this pointer) =====\n";
    string today = "2026-08-19";
    PaymentGateway gateway("SimulatedGateway");

    // [Pointer to objects] pointer to an existing object, members used with ->
    Trip* tripPtr = &hamptaPass;
    cout << tripPtr->getTitle() << " seats left: " << tripPtr->getAvailableSlots() << "\n";

    // Main flow: 2 seats, payment succeeds
    Booking* b1 = aarav.bookTrip(hamptaPass, 2, gateway, "4111111111111111", "12/28", today);
    cout << *b1;
    cout << "Seats left now: " << tripPtr->getAvailableSlots() << "\n\n";

    // [this pointer] bookTrip() passed 'this' into the Booking
    cout << "&aarav                = " << &aarav << "\n";
    cout << "b1->getTraveler()     = " << b1->getTraveler() << "   (same address)\n\n";

    cout << "4a - asking for more seats than are left:\n";
    Booking* bFail1 = aarav.bookTrip(hamptaPass, 25, gateway, "4111111111111111", "12/28", today);
    cout << "Returned pointer is " << (bFail1 == nullptr ? "nullptr" : "not null") << "\n\n";

    cout << "6a - payment fails (invalid card number):\n";
    Booking* bFail2 = aarav.bookTrip(hamptaPass, 1, gateway, "1234", "12/28", today);
    cout << "Returned pointer is " << (bFail2 == nullptr ? "nullptr" : "not null")
         << ", seats left: " << tripPtr->getAvailableSlots() << "\n\n";

    Booking* b2 = aarav.bookTrip(hamptaPass, 1, gateway, "4111111111111111", "12/28", today);
    aarav.viewMyBookings();
    cout << "\n";

    cout << "===== 10. UC-03 Admin tries to remove a trip with bookings =====\n";
    sneha.removeTrip(hamptaPass);   // 2a: blocked
    cout << "\n";

    cout << "===== 11. UC-02 Cancel Booking =====\n";
    cout << "1a - trying to cancel after the trip date:\n";
    aarav.cancelBooking(b1, gateway, "2026-09-20");

    cout << "\nMain flow - refund succeeds:\n";
    aarav.cancelBooking(b1, gateway, today);
    cout << "Seats left now: " << tripPtr->getAvailableSlots() << "\n\n";

    cout << "5a - refund fails, marked PENDING:\n";
    gateway.setFailMode(true);
    aarav.cancelBooking(b2, gateway, today);
    gateway.setFailMode(false);

    Booking* allBookings[] = { b1, b2 };
    cout << "\nAdmin view of all bookings:\n";
    sneha.viewAllBookings(allBookings, 2);

    cout << "\nAdmin settles the pending refund:\n";
    sneha.settlePendingRefund(b2->getPayment(), gateway);
    cout << "\n";

    cout << "===== 12. UC-03 Remove trip again (no confirmed bookings now) =====\n";
    sneha.removeTrip(hamptaPass);
    cout << "\n";

    cout << "Bookings created (static) : " << Booking::getBookingCount() << "\n";
    cout << "Payment attempts (static) : " << Payment::getPaymentCount() << "\n";

    // [Pointer to objects] bookings were made with new, so they must be deleted
    delete b1;
    delete b2;

    cout << "Users alive at end of main (aarav, himalayanTrails, sneha, slicedUser): "
         << User::getTotalUsers() << "\n";

    return 0;
}
