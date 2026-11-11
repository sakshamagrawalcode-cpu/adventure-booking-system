# Adventure Booking System

A simple C++ console project that works like a small adventure booking website.
It has three separate programs: **customer**, **provider** and **admin**.
Each one starts with an email and password login.

All data is sample data written in the code (`src/BookingSystem.h`). It lives in
memory, so changes are lost when a program closes, and each program has its own
copy: a booking made in the customer program does not appear in the admin program.

## Features

### Customer (`src/customer.cpp`)
- Login with email and password (asks again if wrong)
- See all adventures, open one and book it
  - choose how many tickets, then the name and age of each person
  - checks seats left and every person's minimum age
  - shows the total price (price x tickets)
- My bookings (cancelled ones are marked CANCELLED)
- Cancel a booking (whole booking only, full refund)
- View and edit profile: name, gender, age, mobile
- Logout

### Provider (`src/provider.cpp`)
- Login
- My adventures, with seats left
- Add an adventure: name, location, description, difficulty, minimum age, date, price, seats
- Edit an adventure (every field except seats)
- Who booked: gender, name, mobile and email of each customer (cancelled bookings are hidden)
- View profile
- Logout

### Admin (`src/admin.cpp`)
- Login
- All customers and all providers (passwords are never shown)
- Search users by name (part of the name, capitals ignored)
- All bookings, with the full profile of who booked
- Seats left for every adventure
- Cancel any booking
- Edit any customer or provider (every field, email too)
- Set a new password for any user
- Logout

## Rules the program checks
- Wrong email or password: asks again
- Not enough seats: booking fails ("Only 2 seats left")
- A person younger than the minimum age: booking fails
- A booking can't be cancelled twice
- Email must contain `@` and must not be used by another account
- Mobile must be exactly 10 digits
- Typed numbers must be in range (age 1-120, tickets 1-20, menu choices, ...)
- Text can't be left empty

## Project structure
```
.
├── README.md
├── .gitignore
├── docs/
│   ├── use-case-diagram.md
│   ├── class-diagram.md
│   └── sequence-diagram.md
└── src/
    ├── User.h            User (abstract) + Customer, Provider, Admin
    ├── Adventure.h       one adventure and its seats
    ├── Booking.h         Ticket (one person) + Booking
    ├── BookingSystem.h   all data (sample data) and all rules
    ├── Input.h           safe input helpers: readLine, readInt, readIntInRange, chooseGender
    ├── customer.cpp      customer program
    ├── provider.cpp      provider program
    └── admin.cpp         admin program
```

## Architecture
```
customer.cpp ─┐
provider.cpp ─┼──▶ BookingSystem ──▶ Customer, Provider, Admin (all are a User)
admin.cpp ────┘    all data,          Adventure
                   all rules          Booking, Ticket
```
- The three programs only show menus, read input and print results.
- `BookingSystem` holds all the data and checks every rule. The programs never change
  data directly; they call `BookingSystem` functions such as `book()` or `cancelBooking()`.
- When a rule is broken, the code throws a `runtime_error` with a message. The program
  catches it and prints the message, for example `Booking failed: Only 2 seats left`.

## How to build and run
You need a C++17 compiler (g++). Open a terminal in the `src` folder:

```
g++ -std=c++17 customer.cpp -o customer
g++ -std=c++17 provider.cpp -o provider
g++ -std=c++17 admin.cpp -o admin
```

Run on Windows: `.\customer.exe`, `.\provider.exe`, `.\admin.exe`
Run on Linux or macOS: `./customer`, `./provider`, `./admin`

After logout, the program goes back to the login screen. To close it, press `Ctrl+C`.

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
| Class and object | Every `.h` file. Objects are created in `BookingSystem::loadSampleData()` |
| Encapsulation | Data is `private` and changes only through functions. `seatsLeft` changes only through `bookSeats()` and `releaseSeats()`. A password can be checked with `checkPassword()` but never read |
| Constructor | Every class. For example, `Adventure(...)` sets `seatsLeft = totalSeats` |
| Inheritance | `Customer`, `Provider` and `Admin` inherit from `User` (`User.h`) |
| Abstract class | `User` has pure virtual functions (`= 0`), so a plain `User` can't be created |
| Function overriding | Each child writes its own `getRole()` and `showProfile()`, marked `override` |
| Run-time polymorphism | Admin search (`searchScreen()` in `admin.cpp`) gets a `vector<User*>` and calls `showProfile()` on each; customers and providers each run their own version |
| Composition | A `Booking` contains a `vector<Ticket>`. `BookingSystem` owns all users, adventures and bookings |
| Exception handling | `throw runtime_error(...)` in `Adventure`, `Booking` and `BookingSystem`; `try` / `catch` in the three programs |
| Struct | `Ticket` in `Booking.h` |
| References | `BookingSystem& app` in every menu function, so they all work on the same data |

## Diagrams
- [Use case diagram](docs/use-case-diagram.md)
- [Class diagram](docs/class-diagram.md)
- [Sequence diagram: booking an adventure](docs/sequence-diagram.md)

The diagrams are written in Mermaid. GitHub shows them as pictures automatically.
In VS Code, install the **Markdown Preview Mermaid Support** extension, open a diagram
file and press `Ctrl+Shift+V`.

## Limits of this basic version
- Data is in memory only: it resets when a program closes, and the three programs don't share it.
- Passwords are stored as plain text. Real systems store a hash instead.
- The date is plain text and isn't checked, so a past date can still be booked.
- There is no sign-up: accounts exist only in the sample data.
