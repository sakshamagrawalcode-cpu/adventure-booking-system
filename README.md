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

## Files

```
problem-statement.md          the problem, in plain words
docs/syllabus-coverage.md     where every syllabus topic is in the code  <- start here
docs/noun-analysis.md         noun-verb analysis used to find the classes
docs/crc-cards.md             CRC card for each class
docs/use-cases.md             three full use case specifications
docs/use-case-diagram.puml    use case diagram (PlantUML source + .jpeg)
docs/class-diagram.puml       class diagram (PlantUML source + .png)
docs/object-diagram.puml      object diagram (PlantUML source + .png)
docs/sequence-diagram.puml    sequence diagram for UC-01 (PlantUML source + .png)
src/main.cpp                  runs every OOP topic, then every use case
src/User.h                    abstract base class for all users
src/Traveler.h                books and cancels trips
src/AdventureProvider.h       creates and publishes trips
src/Admin.h                   views users/bookings, removes trips, settles refunds
src/SuperAdmin.h              platform owner (multilevel inheritance)
src/TravelerProvider.h        lists AND books trips (multiple inheritance, diamond)
src/Trip.h                    a trip and its seats (operator overloading)
src/Booking.h                 a booking (also holds Traveler's booking functions)
src/Payment.h                 one payment for a booking (data conversion)
src/PaymentGateway.h          simulated payment gateway
src/Receipt.h                 receipt made from a booking (class -> class conversion)
```

## Class family

```
                 User  (abstract)
        __________|______________
       |          |              |
   Traveler  AdventureProvider  Admin
       |__________|              |
            |                SuperAdmin
     TravelerProvider
```

`Traveler` and `AdventureProvider` inherit `User` virtually, so `TravelerProvider`
has only one `User` part (the diamond problem is solved).

## How to run

Needs g++ (C++17). From the project folder:

```
g++ -std=c++17 src/main.cpp -o app
./app
```

On Windows PowerShell use `src\main.cpp` and `.\app.exe`.

The output is split into 18 numbered sections. `docs/syllabus-coverage.md`
says which section shows which topic.
