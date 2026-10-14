# Syllabus Coverage — CS201 OOPD (till mid-sem)

Where every syllabus topic is in our code, and where you can see it run.

**How to use this page**

- **Find it in the code:** every topic is marked with a tag like `[Friend class]`.
  In VS Code press `Ctrl+Shift+F` and search for the tag.
- **See it run:** the project has two programs.
  - `src/demo.cpp` — shows every topic one by one, in 18 numbered sections.
    Build with `g++ -std=c++17 src/demo.cpp -o demo`.
    The "Demo section" column below is the section number in its output.
  - `src/main.cpp` — the real booking app with menus. The last part of this page
    shows where the same topics are used inside the app.

---

## Module 1 — OOP Fundamentals

| Topic | Where in the code | Demo section |
|---|---|---|
| OOP fundamentals | The whole project: each real thing (traveler, trip, booking, payment) is a class | — |
| Programming paradigms | See [Theory](#theory) below | — |
| Principles of OOD | See [Theory](#theory) below | — |
| Benefits and applications of OOP | See [Theory](#theory) below | — |
| Classes and objects | Every class has its own `.h` file in `src/`; objects are made in `demo.cpp` and `BookingSystem.h` | 1 |
| Access specifiers | `User.h` — `private`, `protected` and `public` are explained at the top of the class | 1 |
| Object creation | `demo.cpp` section 1: `himalayanTrails`, `aarav`, `sneha` | 1 |
| Constructors | Every class has one | 2 |
| Default constructor | `Trip()` in `Trip.h` | 2 |
| Parameterized constructor | `User(...)`, `Trip(...)`, `Traveler(...)`, ... | 2 |
| Constructor overloading | `Trip` has two: `Trip()` and `Trip(title, location, ...)` | 2 |
| Copy constructor | `User(const User& other)` in `User.h` — runs for `Traveler aaravCopy = aarav;` | 2 |
| Default arguments in constructors | `EmergencyContact(string n = "", string p = "")` in `Traveler.h`; `Payment(double amount, string timestamp = "N/A")` in `Payment.h` | 2, 8 |
| Static data members | `User::totalUsers`, `Trip::tripCount`, `Booking::bookingCount`, `Payment::paymentCount` | 1, 18 |
| Static member functions | `User::getTotalUsers()`, `Trip::getTripCount()`, `Booking::getBookingCount()`, `Payment::getPaymentCount()` | 1, 9, 18 |
| Static objects | `getGateway()` at the bottom of `demo.cpp` — one `PaymentGateway` made once and reused | 3 |

## Module 2 — Functions and Operators

| Topic | Where in the code | Demo section |
|---|---|---|
| Function prototypes and components | Top of `demo.cpp` (5 prototypes, bodies after `main()`); `Traveler.h` declares `bookTrip()`, `cancelBooking()`, `viewMyBookings()` and their bodies are at the bottom of `Booking.h`; every class declares `showMenu()` and its body is in a menu file | — |
| Parameter passing | `addSeatByValue(Trip t)`, `addSeatByReference(Trip& t)`, `addSeatByPointer(Trip* t)` in `demo.cpp` | 7 |
| Inline functions | `toString()` in `Trip.h`, `Booking.h`, `PaymentGateway.h`; the helpers in `Input.h`; every function written inside a class body | 11 |
| Default arguments in functions | `viewMyBookings(bool onlyConfirmed = false)` in `Traveler.h` | 16 |
| Function overloading | Four `toString()` functions with different parameter types | 11 |
| Array of objects | `Trip catalogue[3]` in `demo.cpp` | 6 |
| Pointers to objects | `Trip* tripPtr`, `Booking* b1`, the arrow operator `->` | 13, 17 |
| Dynamic memory allocation | `new Booking(...)` inside `Traveler::bookTrip()` (`Booking.h`); every user and trip in `BookingSystem.h` | 13 |
| Dynamic objects (`new` and `delete`) | Freed with `delete b1; delete b2;` at the end of `demo.cpp`; in the app, `~BookingSystem()` deletes everything | 13, 18 |
| Returning objects from functions | `AdventureProvider::createTrip()` returns a `Trip`; `Traveler::getEmergencyContact()` returns an `EmergencyContact` | 2, 5 |
| Friend functions | `operator<<` in every class can read private data | 4 |
| Friend classes | `friend class Admin;` in `Trip.h`, used by `Admin::removeTrip()` and `Admin::tripReport()` | 15, 17 |
| Operator overloading | `Trip.h` (`++`, `<`, `==`, `<<`, `>>`) | 6, 7 |
| Unary operator overloading | `Trip& operator++()` — `++trip` adds one seat | 7 |
| Binary operator overloading | `trip1 < trip2` (compares price), `trip1 == trip2` (same trip ID) | 6 |
| Member vs friend operator overloading | `operator<` is a **member** (left side is `this`, one parameter); `operator==` is a **friend** (both sides are parameters) | 6 |
| Stream operator overloading (`<<` and `>>`) | `operator<<` in every class; `operator>>` in `Trip.h` | 4 |
| Data conversion: basic type → class | `Payment advance = 2000.0;` works because of `Payment(double amount, ...)` | 8 |
| Data conversion: class → basic type | `double amount = advance;` works because of `operator double()` in `Payment.h` | 8 |
| Data conversion: class → class | `Receipt receipt = *b1;` works because of `Receipt(const Booking& b)` in `Receipt.h` | 14 |

## Module 3 — Inheritance and Polymorphism

| Topic | Where in the code | Demo section |
|---|---|---|
| Base and derived classes | `User` is the base; every other user class is derived from it | 11 |
| Single inheritance | `Traveler : User`, `AdventureProvider : User`, `Admin : User` | — |
| Protected members | `validatePassword()` and `traceConstructor()` in `User.h`, used by `SuperAdmin::viewSystemStats()` | 9 |
| Multilevel inheritance | `User → Admin → SuperAdmin` (`SuperAdmin.h`) | 9 |
| Multiple inheritance | `TravelerProvider : Traveler, AdventureProvider` (`TravelerProvider.h`) | 10 |
| Ambiguity in multiple inheritance | Both parents have `getRole()` and `showMenu()`; `TravelerProvider` writes its own and uses `Traveler::...` / `AdventureProvider::...` | 10 |
| Hierarchical inheritance | `User → Traveler / AdventureProvider / Admin` | 11 |
| Hybrid inheritance | The whole family: hierarchical + multilevel + multiple | 9, 10 |
| Multipath inheritance | `TravelerProvider` reaches `User` by two paths | 10 |
| Diamond problem | `TravelerProvider.h` — the diamond is drawn in the comment | 10 |
| Virtual inheritance | `virtual public User` in `Traveler.h` and `AdventureProvider.h` — `User`'s constructor runs only once | 10 |
| Constructors in inheritance | Every child calls its parent's constructor; `TravelerProvider` must call `User(...)` itself | 9, 10 |
| Constructor execution order | Printed while creating `vikram` (User → Admin → SuperAdmin) and `karan` (User → Traveler → AdventureProvider → TravelerProvider) | 9, 10 |
| Function overriding | `getRole()`, `showMenu()` in every child class; `maxSeatsPerBooking()` in `TravelerProvider` | 11 |
| Polymorphism | One call gives the right result for each kind of user: `getRole()`, `showMenu()`, `maxSeatsPerBooking()` | 11 |
| Compile-time polymorphism | Function overloading (`toString`) and operator overloading | 11 |
| Run-time polymorphism | Virtual functions called through a `User*` or `Traveler*` | 11 |
| Virtual functions | `getRole()`, `showMenu()`, `maxSeatsPerBooking()`, the virtual destructor in `User.h` | 11 |
| Base-class pointers and derived objects | `vector<User*> users = { &aarav, &himalayanTrails, &sneha, &vikram, &karan }` | 11 |
| Dynamic binding | `Admin::viewAllUsers()` — which `getRole()` runs is decided while the program runs | 11 |
| Pure virtual functions | `getRole() = 0` and `showMenu() = 0` in `User.h`; `matches() = 0` in `Searchable.h` | 11 |
| Abstract classes | `User` (no plain `User` object can be made); `Searchable` is an abstract class with only pure virtual functions — an **interface** | 11 |

## UML and Design

| Topic | Where |
|---|---|
| Unified Modeling Language (UML) | `docs/` folder — `.puml` is the source, `.png`/`.jpeg` is the picture |
| Class diagrams | `docs/class-diagram.puml` / `.png` — matches the code in `src/` |
| Class names, attributes and operations | Every box in the class diagram |
| Visibility symbols | `-` private, `#` protected, `+` public. (`~` package is not used: C++ has no package access.) |
| UML relationships | All shown in the class diagram |
| Association | `Booking --> Trip` ("for") |
| Multiplicity | `1` and `0..*` on the lines, e.g. one Traveler makes 0..* Bookings |
| Generalization / inheritance | Lines with hollow triangles, e.g. `User <|-- Traveler`; dashed ones for the interface, `Searchable <|.. Trip` |
| Dependency | Dashed arrows: `Payment ..> PaymentGateway`, `Receipt ..> Booking`, `AdventureProvider ..> Trip` «create», `Admin ..> Trip` «friend» |
| Aggregation | Hollow diamond: `Traveler o-- Booking` (keeps pointers, does not own them) |
| Composition | Filled diamond: `BookingSystem *-- User / Trip / Booking / PaymentGateway`, `Booking *-- Payment`, `Traveler *-- EmergencyContact` |
| Use case diagrams | `docs/use-case-diagram.puml` / `.jpeg`, written out in `docs/use-cases.md` |
| Actors and system boundaries | Use case diagram: Traveler, Adventure Provider, Admin + Payment Gateway, Email Service; the rectangle is the system boundary |
| Sequence diagrams | `docs/sequence-diagram.puml` / `.png` — UC-01 Book Adventure, step by step |
| Object diagrams | `docs/object-diagram.puml` / `.png` — Rohan books the River Rafting trip |

## Extra topics in the code (not in the list above)

| Topic | Where | Demo section |
|---|---|---|
| Encapsulation | Private data with public functions — `User` password, `Trip` seats | 1 |
| `this` pointer | `PaymentGateway`, `Payment` and `Booking` constructors; `bookTrip()` passes `this` | 13 |
| Nested class | `Traveler::EmergencyContact` | 5 |
| Object slicing | `Admin slicedAdmin = vikram;` | 12 |
| `final` | `SuperAdmin` and `TravelerProvider` | 12 |
| Interface | `Searchable.h`, followed by `Trip` and `User` | 11 |
| Virtual destructor | `virtual ~User()` — lets `~BookingSystem()` delete any kind of user through a `User*` | — |
| Destructor | The copy made in section 2 is destroyed at the closing `}`; `~BookingSystem()` | 2 |

---

## The same topics inside the real app (`main.cpp`)

| What happens in the app | Topic | Where |
|---|---|---|
| After login, `user->showMenu(system)` opens a different menu for each kind of user | Run-time polymorphism, dynamic binding, pure virtual function | `StartMenu.h` (`loginScreen`) |
| A traveler may book 6 seats at once, a traveler+provider 15 | Virtual function, function overriding | `Traveler::maxSeatsPerBooking()`, `TravelerProvider.h` |
| Search trips (traveler) and search users (admin) use the same `matches()` | Abstraction, interface | `Searchable.h`, `BookingSystem::searchTrips()` / `searchUsers()` |
| The traveler+provider menu picks which parent's menu to open | Ambiguity in multiple inheritance, scope operator `::` | `TravelerProvider::showMenu()` in `StartMenu.h` |
| The super admin menu reuses the admin menu | Multilevel inheritance, calling the parent's function | `SuperAdmin::showMenu()` in `AdminMenu.h` |
| The system keeps every user, trip and booking and deletes them at the end | Composition, dynamic memory, destructor, base-class pointers | `BookingSystem.h` |
| After a booking, a receipt is printed | Data conversion: class → class | `bookTripScreen()` in `TravelerMenu.h` |
| Trip report with seats sold and money collected | Friend class | `Admin::tripReport()` |
| "My bookings": all, or only confirmed | Default arguments in functions | `myBookingsScreen()` in `TravelerMenu.h` |
| Editing a trip is checked on a copy first | Copy of an object, encapsulation | `editTripScreen()` in `ProviderMenu.h` |

---

## Theory

### Programming paradigms

- **Procedural** (like C): the program is a list of functions, and the data sits outside them.
  If the seat count were a global variable, *any* function could change it by mistake.
- **Object-oriented** (C++): the program is made of objects, and each object keeps its data
  *and* the functions that work on that data together. In our project the seat count lives
  inside `Trip` and can only change through `reserveSlots()` and `releaseSlots()`.

### Principles of object-oriented design — and how our project follows them

- **Abstraction:** `User` shows only what every user can do (`login()`, `getRole()`, `showMenu()`)
  and hides the details; `Searchable` says only "it can be matched".
- **Encapsulation:** data is private and changed only through functions (`Trip` seats, `User` password).
- **Inheritance:** the common user data is written once in `User` and reused by every kind of user.
- **Polymorphism:** one call, like `showMenu()`, does the right thing for each kind of user.
- **One job per class:** each class has a clear responsibility (see `docs/crc-cards.md`).

### Benefits and applications of OOP

**Benefits we got in this project**
- *Reuse:* `SuperAdmin` and `TravelerProvider` were added without rewriting any user code.
- *Safety:* private data cannot be changed by mistake from outside the class.
- *Easy to understand:* classes match real things — traveler, trip, booking, payment.
- *Easy to extend:* a new kind of user is just a new child class of `User` with its own `showMenu()`.

**Applications of OOP:** booking systems like ours, banking software, games, GUI apps, simulations.
