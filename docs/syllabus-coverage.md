# Syllabus Coverage — CS201 OOPD

**Team ID:** 3 · Saksham (20251501153) · Naitik (20251501133) · Prerna (20251501135) · Kush (20251501176) · Abhay (20251502033)

Where each topic of the course syllabus is in our code.

- **Yes**: used in the code; the "Where" column says where.
- **Partly**: only part of the topic is used.
- **No**: not in this version. All of these are collected in the [last section](#not-in-this-version).

To find something in VS Code, press `Ctrl+Shift+F` and search for the function or word in the "Where" column.

---

## Module 1 — Introduction, classes and objects

| Topic | In code? | Where |
|---|---|---|
| Principles of OOD | Yes | See [Theory](#theory) |
| Programming paradigms | Yes | See [Theory](#theory) |
| Benefits and applications of OOD&P | Yes | See [Theory](#theory) |
| Classes and objects | Yes | Every `.h` file in `src/` defines a class. Objects are created in `BookingSystem::loadSampleData()` |
| Access qualifiers | Partly | `private` and `public` in every class. `protected` is not used |
| Instance creation | Yes | `BookingSystem app;` in each `main()`; `Customer(...)`, `Provider(...)`, `Admin(...)` in `loadSampleData()`; `Booking b(...)` in `BookingSystem::book()` |
| Constructors | Yes | Every class has one |
| Parameterized constructors | Yes | `User(id, name, email, password)`, `Customer(...)`, `Adventure(...)`, `Booking(...)` |
| Overloaded constructors | Yes | `Adventure` has two constructors. The second one also sets `seatsLeft` (used by `load()` when reading `adventures.txt`) and first runs the other one with `: Adventure(...)` |
| Constructors with default arguments | No | — |
| Copy constructors | Yes | `Booking(const Booking& other)` in `Booking.h`. It runs every time a booking is copied, e.g. when `getAllBookings()` returns a `vector<Booking>` |
| Static class members | Yes | Static data member: `static const int MAX_TICKETS = 20;` in `Booking` (used as `Booking::MAX_TICKETS`). Static member functions: `isValidEmail()`, `isValidMobile()`, `isValidDate()` in `BookingSystem` |
| Static objects | No | — |

## Module 2 — Functions and operators

| Topic | In code? | Where |
|---|---|---|
| Function prototyping | No | Every function is written above the code that uses it, so no separate prototypes are needed |
| Function components | Yes | Every function has a return type, a name, parameters and a body, e.g. `int readIntInRange(string prompt, int min, int max)` in `Input.h` |
| Passing parameters | Partly | By value: `string` parameters, e.g. `readLine(string prompt)`. By reference: `BookingSystem& app` in every menu function. By pointer: not used |
| Inline functions | Partly | Every function written inside a class body is inline automatically (e.g. all the getters). The `inline` keyword itself is not used |
| Default arguments | Yes | `getBookingsOfCustomer(string customerId, bool onlyActive = false)`, and the same in `getBookingsOfAdventure()` and `getAllBookings()`. `cancelScreen()` calls it with `true` |
| Overloaded functions | Yes | `cancelBooking(bookingId)` (admin) and `cancelBooking(bookingId, customerId)` (customer, checks the booking is theirs) in `BookingSystem.h`; also the two `Adventure` constructors |
| Array of objects | Partly | `vector<Customer>`, `vector<Adventure>`, `vector<Booking>` in `BookingSystem.h` and `vector<Ticket>` in `Booking.h` (a vector is an array that can grow). A plain array like `Adventure list[4]` is not used |
| Pointers to objects | Yes | `vector<User*>` returned by `searchUsers()`; `results[i]->showProfile()` in `searchScreen()` in `admin.cpp` |
| Dynamic allocation operators (`new`, `delete`) | No | `vector` manages the memory, so `new` and `delete` are not needed |
| Dynamic objects | No | — |
| Operator overloading | Yes | `<<` for `Adventure` and `Booking`; `=` for `Booking` |
| Overloading a unary and a binary operator | Partly | Binary: `<<` (`cout << booking`) and `=` (`b1 = b2`). No unary operator is overloaded |
| Overloading an operator using a friend function | Yes | `friend ostream& operator<<(ostream& out, const Adventure& a)` in `Adventure.h`, and the same in `Booking.h` |
| Stream operator overloading (`<<`, `>>`) | Partly | `<<` for `Adventure` and `Booking`: `cout << chosen;` in `customer.cpp`. `>>` is not overloaded |
| Data conversion | No | Only conversions between basic types: `stoi()` (text to int), `to_string()` (int to text) and `(int)` |

## Module 3 — Inheritance

| Topic | In code? | Where |
|---|---|---|
| Defining derived classes | Yes | `class Customer : public User` (also `Provider`, `Admin`) in `User.h` |
| Single inheritance | Yes | `Customer`, `Provider` and `Admin` each have one parent, `User` |
| Protected data with private inheritance | No | Only `public` inheritance is used |
| Multiple inheritance | No | — |
| Multi-level inheritance | No | — |
| Hierarchical inheritance | Yes | One parent, three children: `User` → `Customer`, `Provider`, `Admin` |
| Hybrid inheritance | No | — |
| Multi-path inheritance | No | — |
| Constructors in derived and base class | Yes | `Customer(...) : User(id, name, email, password)` runs `User`'s constructor first |
| Abstract classes | Yes | `User` has `virtual string getRole() = 0;` and `virtual void showProfile() = 0;`, so no plain `User` can be made |
| Virtual functions and dynamic polymorphism | Yes | `searchScreen()` in `admin.cpp` calls `showProfile()` through a `User*`; the `Customer` or `Provider` version runs |
| Virtual destructor | Yes | `virtual ~User() {}` in `User.h` |

## Module 4 — Exception handling

| Topic | In code? | Where |
|---|---|---|
| Principle of exception handling | Yes | A rule that fails does not return an error code; it throws, and the menu decides what to show |
| Exception handling mechanism (`try`, `throw`, `catch`) | Yes | `throw runtime_error(...)` in `Adventure::bookSeats()`, `Booking::cancel()` and `BookingSystem` (also when a data file is damaged or can't be written). `try` / `catch` in every `loginScreen()` and in every screen that changes data (`bookScreen()`, `cancelScreen()`, the add and edit screens, `changePasswordScreen()`) |
| Multiple catch | Yes | `main()` in each program: `catch (runtime_error& e)` (e.g. data folder not found) and then `catch (exception& e)` (anything else, e.g. a damaged number in a data file) |
| Nested try | Partly | A menu's `try` (e.g. in `bookScreen()`) runs while `main()`'s `try` is active, so errors not caught by the menu reach `main()`. No `try` is written inside another `try` in the same function |
| Re-throwing the exception | No | — |

## Taught in class — Multithreading

| Topic | In code? | Where |
|---|---|---|
| Creating threads | No | — |
| Extending a Thread class / implementing Runnable | No | — |
| Thread life cycle and thread methods | No | — |
| Thread synchronization | No | — |

## UML

| Topic | In code? | Where |
|---|---|---|
| Building blocks of UML (things, relationships, diagrams) | Yes | All diagrams in `docs/` |
| Structural modeling | Yes | [Class diagram](class-diagram.md), [object diagram](object-diagram.md) |
| Behavioral modeling | Yes | [Use case diagram](use-case-diagram.md), [sequence diagram](sequence-diagram.md) |
| Use case diagram: actors, system boundary, «include» | Yes | [use-case-diagram.md](use-case-diagram.md) |
| Class diagram: visibility, inheritance, composition, association, multiplicity | Yes | [class-diagram.md](class-diagram.md) |
| Object diagram | Yes | [object-diagram.md](object-diagram.md) |
| Sequence diagram: calls, returns, `loop`, `alt` | Yes | [sequence-diagram.md](sequence-diagram.md) |

## Extra topics in the code

| Topic | Where |
|---|---|
| Encapsulation | Data is `private` and changes only through functions. `seatsLeft` changes only through `bookSeats()` and `releaseSeats()`. There is no `getPassword()`: a password can only be checked with `checkPassword()` |
| `this` pointer | `this->name = name;` in the constructors and setters |
| Function overriding with `override` | `getRole()` and `showProfile()` in `Customer`, `Provider` and `Admin` |
| Struct | `Ticket` in `Booking.h` |
| Friend class | `friend class BookingSystem;` in `User`: only `BookingSystem` can call the private `getPassword()`, to save the password in `customers.txt` |
| File handling | `load()` reads the files with `ifstream` and `getline()`; `save()` writes them with `ofstream`; `splitLine()` uses `stringstream` |
| Delegating constructor | The second `Adventure` constructor starts with `: Adventure(...)`, running the first one |
| Composition | A `Booking` holds a `vector<Ticket>`; `BookingSystem` holds all users, adventures and bookings |
| Returning a reference | `Customer& findCustomer(string id)` in `BookingSystem.h` returns the real object, not a copy |
| `#pragma once` | Top of every `.h` file, so it is read only once |

---

## Theory

### Programming paradigms
- **Procedural** (like C): the program is a list of functions, and the data sits outside them.
  If the seat count were a global variable, any function could change it by mistake.
- **Object-oriented** (C++): the program is made of objects, and each object keeps its data
  and the functions that work on that data together. In our project the seat count lives
  inside `Adventure` and can only change through `bookSeats()` and `releaseSeats()`.

### Principles of object-oriented design, and where our project follows them
- **Abstraction:** `User` says what every account can do (`checkPassword()`, `getRole()`,
  `showProfile()`) without saying how. The menus call `BookingSystem` functions like `book()`
  without knowing how the checks are done inside.
- **Encapsulation:** data is private and changed only through functions. A password can be
  checked but never read.
- **Inheritance:** the data every account has is written once in `User` and reused by
  `Customer`, `Provider` and `Admin`.
- **Polymorphism:** one call, `showProfile()`, prints a customer's or a provider's profile
  depending on the object.
- **One job per class:** each class has one clear responsibility (see the [CRC cards](crc-cards.md)).

### Benefits and applications of OOP
**Benefits we got in this project**
- *Reuse:* `Customer`, `Provider` and `Admin` share `User`'s code instead of repeating it.
- *Safety:* private data can't be changed by mistake from outside the class.
- *Easy to understand:* classes match real things: customer, adventure, booking, ticket.
- *Easy to extend:* a new kind of user is a new child class of `User`. A database later would
  change only `BookingSystem`, because the menus only call its functions.

**Applications of OOP:** booking systems like ours, banking software, games, GUI apps, simulations.

---

## Not in this version

These syllabus topics are not used in the code:

- **Module 1:** `protected` access, constructors with default arguments, static objects
- **Module 2:** function prototypes, passing by pointer, the `inline` keyword, plain arrays of objects, `new` / `delete`, dynamic objects, overloading a unary operator, overloading `>>`, data conversion between basic types and classes
- **Module 3:** protected data with private inheritance, multiple, multi-level, hybrid and multi-path inheritance
- **Module 4:** a `try` written inside another `try`, re-throwing
- **Multithreading:** all topics
