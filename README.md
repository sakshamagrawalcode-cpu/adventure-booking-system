# Adventure Booking System

OOPS course project, 3rd semester, IIIT Vadodara.

**Team ID:** 3

| Name | Roll Number |
|---|---|
| Saksham | 20251501153 |
| Naitik | 20251501133 |
| Prerna | 20251501135 |
| Kush | 20251501176 |
| Abhay | 20251502033 |

A simple C++ console project that works like a small adventure booking website.
It has three separate programs: **customer**, **provider** and **admin**.
Each one starts with an email and password login.

All three programs share the same data, kept in text files in the `data` folder.
A booking made in the customer program shows up at once in the provider and admin
programs, and nothing is lost when a program closes. On the very first run the files
don't exist yet, so the programs create them with the sample data.

## Features

### Customer (`src/customer.cpp`)
- Login with email and password (asks again if wrong; capitals in the email don't matter)
- See all adventures, open one and book it
  - choose how many tickets, then the name and age of each person
  - checks seats left and every person's minimum age
  - shows the total price (price x tickets)
- My bookings (cancelled ones are marked CANCELLED)
- Cancel a booking (whole booking only, full refund)
- View and edit profile: name, gender, age, mobile
- Logout, or exit from the login screen

### Provider (`src/provider.cpp`)
- Login
- My adventures, with seats left
- Add an adventure: name, location, description, difficulty, minimum age, date, price, seats
- Edit an adventure (every field except seats)
- Who booked: gender, name, mobile and email of each customer (cancelled bookings are hidden)
- View profile
- Logout, or exit from the login screen

### Admin (`src/admin.cpp`)
- Login
- All customers and all providers (passwords are never shown)
- Search users by name (part of the name, capitals ignored)
- All bookings, with the full profile of who booked
- Seats left for every adventure
- Cancel any booking
- Edit any customer or provider (every field, email too)
- Set a new password for any user
- Logout, or exit from the login screen

## Rules the program checks
- Wrong email or password: asks again
- Not enough seats: booking fails ("Only 2 seats left")
- A person younger than the minimum age: booking fails
- At most 20 tickets in one booking
- A customer can cancel only their own bookings, and a booking can't be cancelled twice
- Email must contain `@` and must not be used by another account
- Mobile must be exactly 10 digits
- Date must be in the form `DD-MM-YYYY`, e.g. `20-12-2026`
- Typed numbers must be in range (age 1-120, tickets 1-20, menu choices, ...)
- Text can't be empty and can't contain `|` (it separates the values in the data files)

## Project structure
```
.
├── README.md
├── problem-statement.md      the problem, in plain words
├── .gitignore
├── data/                     the shared data files (created on the first run)
├── docs/
│   ├── use-cases.md          written use cases, UC-01 to UC-04
│   ├── crc-cards.md          a CRC card for every class
│   ├── noun-analysis.md      how the classes were found
│   ├── test-cases.md         every test, with its result
│   ├── syllabus-coverage.md  where each syllabus topic is in the code
│   ├── use-case-diagram.md / .png
│   ├── class-diagram.md / .png
│   ├── object-diagram.md / .png
│   └── sequence-diagram.md / .png
└── src/
    ├── User.h            User (abstract) + Customer, Provider, Admin
    ├── Adventure.h       one adventure and its seats
    ├── Booking.h         Ticket (one person) + Booking
    ├── BookingSystem.h   all the rules, and reading/writing the data files
    ├── Input.h           safe input helpers: readLine, readInt, readIntInRange, chooseGender
    ├── customer.cpp      customer program
    ├── provider.cpp      provider program
    └── admin.cpp         admin program
```

## Architecture
```
customer.cpp ─┐                      ┌─▶ Customer, Provider, Admin (all are a User)
provider.cpp ─┼──▶ BookingSystem ────┼─▶ Adventure
admin.cpp ────┘    all the rules     ├─▶ Booking, Ticket
                                     └─▶ data/*.txt  (load before every action,
                                                      save after every change)
```
- The three programs only show menus, read input and print results.
- `BookingSystem` checks every rule. The programs never change data directly; they call
  `BookingSystem` functions such as `book()` or `cancelBooking()`.
- Every `BookingSystem` function first reads the latest data from the files (`load()`),
  and every function that changes something writes the files again (`save()`). That is how
  the three programs see each other's changes.
- When a rule is broken, the code throws a `runtime_error` with a message. The program
  catches it and prints the message, for example `Booking failed: Only 2 seats left`.

## Data files
Each line is one object, with its values separated by `|`:

| File | One line looks like |
|---|---|
| `customers.txt` | `C1\|Rahul Mehta\|rahul@example.com\|rahul123\|Male\|20\|9123400001` |
| `providers.txt` | `P1\|Amit Sharma\|amit@example.com\|amit123\|9876500001\|Himalayan Treks` |
| `admins.txt` | `AD1\|Saksham\|admin@example.com\|admin123` |
| `adventures.txt` | `A1\|P1\|Kedarkantha Winter Trek\|Uttarakhand\|...\|Moderate\|12\|20-12-2026\|9500\|10\|8` |
| `bookings.txt` | `B5\|C1\|A1\|19000\|BOOKED` |
| `tickets.txt` | `B5\|Rahul Mehta\|20` |

**To start again from the sample data**, delete the `.txt` files in `data/`.

## How to build and run
You need a C++17 compiler (g++). Open a terminal in the `src` folder
(the programs look for the data in `../data/`, so they must be started from `src`):

```
g++ -std=c++17 customer.cpp -o customer
g++ -std=c++17 provider.cpp -o provider
g++ -std=c++17 admin.cpp -o admin
```

Run on Windows: `.\customer.exe`, `.\provider.exe`, `.\admin.exe`
Run on Linux or macOS: `./customer`, `./provider`, `./admin`

You can keep all three open at the same time in three terminals.
After logout, a program goes back to the login screen. Type `0` as the email to exit.

## Sample logins
| Role | Name | Email | Password |
|---|---|---|---|
| Admin | Saksham | admin@example.com | admin123 |
| Provider | Amit Sharma (Himalayan Treks) | amit@example.com | amit123 |
| Provider | Neha Verma (Rishikesh Rapids) | neha@example.com | neha123 |
| Customer | Rahul Mehta, age 20 | rahul@example.com | rahul123 |
| Customer | Priya Patel, age 22 | priya@example.com | priya123 |
| Customer | Arjun Rao, age 16 | arjun@example.com | arjun123 |

## Sample adventures
| Adventure | Provider | Date | Price per person | Min age | Seats |
|---|---|---|---|---|---|
| Kedarkantha Winter Trek | Himalayan Treks | 20-12-2026 | Rs. 9500 | 12 | 10 (2 booked by Rahul at the start) |
| Hampta Pass Trek | Himalayan Treks | 15-06-2027 | Rs. 11000 | 14 | 8 |
| River Rafting (16 km) | Rishikesh Rapids | 05-01-2027 | Rs. 1500 | 14 | 12 |
| Bungee Jumping | Rishikesh Rapids | 10-01-2027 | Rs. 3500 | 18 | 6 |

To see the age check, log in as Arjun (16) and try to book Bungee Jumping (minimum age 18).

## OOP concepts used
| Concept | Where |
|---|---|
| Class and object | Every `.h` file. The sample objects are made in `BookingSystem::loadSampleData()` |
| Encapsulation | Data is `private` and changes only through functions. `seatsLeft` changes only through `bookSeats()` and `releaseSeats()` |
| Constructor, overloaded constructor | Every class. `Adventure` has two: one sets all seats free, the other also sets `seatsLeft` (used when reading the data file) |
| Copy constructor | `Booking(const Booking& other)` in `Booking.h` |
| Static members | `Booking::MAX_TICKETS` (one value for the whole class); `isValidEmail()`, `isValidMobile()`, `isValidDate()` are static functions in `BookingSystem` |
| Inheritance | `Customer`, `Provider` and `Admin` inherit from `User` (`User.h`) |
| Abstract class | `User` has pure virtual functions (`= 0`), so a plain `User` can't be created |
| Function overriding | Each child writes its own `getRole()` and `showProfile()`, marked `override` |
| Run-time polymorphism | Admin search (`searchScreen()` in `admin.cpp`) gets a `vector<User*>` and calls `showProfile()` on each; customers and providers each run their own version |
| Function overloading | `cancelBooking(bookingId)` for the admin, `cancelBooking(bookingId, customerId)` for a customer |
| Default arguments | `getBookingsOfCustomer(customerId, onlyActive = false)`, also `getBookingsOfAdventure()` and `getAllBookings()` |
| Operator overloading, friend function | `operator<<` for `Adventure` and `Booking` (`cout << adventure;`) is a friend function; `Booking` also overloads `=` |
| Friend class | `BookingSystem` is a friend of `User`, so only it can read a password (to save it) |
| Composition | A `Booking` contains a `vector<Ticket>`. `BookingSystem` owns all users, adventures and bookings |
| Exception handling | `throw runtime_error(...)` in `Adventure`, `Booking` and `BookingSystem`; `try` / `catch` in the three programs |
| Multiple catch | `main()` in each program: `catch (runtime_error&)` first, then `catch (exception&)` |
| File handling | `load()` and `save()` in `BookingSystem` use `ifstream` and `ofstream` |
| Struct | `Ticket` in `Booking.h` |
| References | `BookingSystem& app` in every menu function, so they all work on the same object |

## Documents
| Document | What it has |
|---|---|
| [Problem statement](problem-statement.md) | The problem and what we built |
| [Use cases](docs/use-cases.md) | UC-01 Book Adventure, UC-02 Cancel Booking, UC-03 Manage Adventures, UC-04 Manage Users |
| [CRC cards](docs/crc-cards.md) | Responsibilities and collaborators of every class |
| [Noun analysis](docs/noun-analysis.md) | How the classes and functions were found from the use cases |
| [Test cases](docs/test-cases.md) | Every test with its steps, expected output and result |
| [Syllabus coverage](docs/syllabus-coverage.md) | Where each syllabus topic is in the code, and which ones are not |

## Diagrams
- [Use case diagram](docs/use-case-diagram.md)
- [Class diagram](docs/class-diagram.md)
- [Object diagram](docs/object-diagram.md)
- [Sequence diagram: booking an adventure](docs/sequence-diagram.md)

Each diagram has a `.png` picture (open it directly, or put it in a report) and a `.md`
file with the same picture plus its Mermaid source code. GitHub also draws the Mermaid code
as a picture. In VS Code, open a `.md` file and press `Ctrl+Shift+V` to see it.

## Limits of this basic version
- Passwords are stored as plain text. Real systems store a hash instead.
- The date's format is checked, but not whether it is in the past.
- There is no sign-up: new accounts can only be added to the data files by hand.
- If two programs save at the very same moment, one change can overwrite the other.
  A real system uses a database to prevent this.
