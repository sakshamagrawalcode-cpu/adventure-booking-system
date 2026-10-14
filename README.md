# Adventure Booking System

OOPS course project, 3rd semester, IIIT Vadodara.

**Team ID:** [3]

| Name | Roll Number |
|---|---|
| Saksham | 20251501153 |
| Naitik | 20251501133 |
| Prerna | 20251501135 |
| Kush | 20251501176 |
| Abhay | 20251502033 |


A booking app for adventure trips. Travelers browse trips, book seats, pay
through a payment gateway and get a confirmation email. Adventure providers
list their own trips and see who booked them. An admin watches over all of it.
Seat counts update automatically on every booking and cancellation.

## How to run

Needs g++ (C++17). From the project folder:

| Program | What it is | Build and run (Windows PowerShell) |
|---|---|---|
| **The app** | The real booking system with menus | `g++ -std=c++17 src\main.cpp -o app.exe` then `.\app.exe` |
| **The demo** | Shows every OOP topic of the syllabus, one by one | `g++ -std=c++17 src\demo.cpp -o demo.exe` then `.\demo.exe` |

(On Linux/Mac use `src/main.cpp` and `./app`.)

**Sample accounts** (the app starts with these, and the date is fixed at 2026-10-15):

| Kind of user | Email | Password |
|---|---|---|
| Traveler | aarav.sharma@gmail.com | aarav@123 |
| Adventure provider | ops@himalayantrails.in | rohit@123 |
| Traveler + provider | karan.negi@spitiexpeditions.in | karan@123 |
| Admin | sneha.iyer@trekmate.in | sneha@123 |
| Super admin | vikram.mehta@trekmate.in | vikram@123 |

## What each kind of user can do

| User | Menu options |
|---|---|
| Traveler | browse trips, search trips, see a trip, book a trip, cancel a booking, my bookings, my profile |
| Adventure provider | my trips, create a trip, edit price/dates (booked travelers get an email), remove a trip, see who booked |
| Traveler + provider | picks the traveler menu or the provider menu |
| Admin | all users, search users, all bookings, trip report, remove any trip, settle pending refunds, testing tools |
| Super admin | the admin menu + system stats |

Anyone can also **register** as a new traveler from the main menu.

## Files

```
problem-statement.md          the problem, in plain words

src/main.cpp                  the app: starts the system and the main menu
src/demo.cpp                  the demo: every OOP topic, in 18 numbered sections

src/User.h                    abstract base class for all users
src/Traveler.h                books and cancels trips
src/AdventureProvider.h       creates, edits and removes trips
src/Admin.h                   views users/bookings, reports, removes trips, settles refunds
src/SuperAdmin.h              platform owner (multilevel inheritance)
src/TravelerProvider.h        lists AND books trips (multiple inheritance, diamond)
src/Trip.h                    a trip and its seats (operator overloading)
src/Booking.h                 a booking (also holds Traveler's booking functions)
src/Payment.h                 one payment for a booking (data conversion)
src/PaymentGateway.h          simulated payment gateway
src/Receipt.h                 receipt made from a booking (class -> class conversion)
src/Searchable.h              interface for anything that can be searched
src/BookingSystem.h           keeps all users, trips and bookings

src/StartMenu.h               welcome, log in, register
src/TravelerMenu.h            the traveler's menu
src/ProviderMenu.h            the provider's menu
src/AdminMenu.h               the admin's and super admin's menus
src/Input.h                   safe helpers to read what the user types

docs/syllabus-coverage.md     where every syllabus topic is in the code  <- start here
docs/test-cases.md            33 test cases, all passing
docs/noun-analysis.md         noun-verb analysis used to find the classes
docs/crc-cards.md             CRC card for each class
docs/use-cases.md             three full use case specifications
docs/use-case-diagram.puml    use case diagram (PlantUML source + .jpeg)
docs/class-diagram.puml       class diagram (PlantUML source + .png)
docs/object-diagram.puml      object diagram (PlantUML source + .png)
docs/sequence-diagram.puml    sequence diagram for UC-01 (PlantUML source + .png)
tests/run_tests.py            optional: runs all test cases automatically (needs Python)
```

## Class family

```
                 User  (abstract, follows Searchable)
        __________|______________
       |          |              |
   Traveler  AdventureProvider  Admin
       |__________|              |
            |                SuperAdmin
     TravelerProvider
```

`Traveler` and `AdventureProvider` inherit `User` virtually, so `TravelerProvider`
has only one `User` part (the diamond problem is solved).

## Progress against the project plan

| Weeks | Plan | Status |
|---|---|---|
| W1 | Plan the project, understand the data | ✅ problem statement, use cases, noun analysis, CRC cards, UML |
| W1–W2 | Main classes with private data | ✅ User, Trip, Booking, Payment, PaymentGateway |
| W2 | Basic booking and cancelling | ✅ UC-01, UC-02 with all alternate flows |
| W3–W4 | Inheritance + different rules for different users | ✅ 5 kinds of user; booking limit 6 vs 15 seats |
| W5–W6 | Menu, search, reports, an interface | ✅ menus for every user, `Searchable`, trip report, stats |
| W7 | Test all features | ✅ 33 test cases in `docs/test-cases.md`, all passing |
| W8 | Report and presentation | ⏳ next |
