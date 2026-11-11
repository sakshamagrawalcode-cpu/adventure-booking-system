# Noun–Verb Analysis — Adventure Booking System

**Team ID:** 3 · Saksham (20251501153) · Naitik (20251501133) · Prerna (20251501135) · Kush (20251501176) · Abhay (20251502033)

Taken from our four use cases: Book Adventure, Cancel Booking, Manage Adventures and
Manage Users ([use-cases.md](use-cases.md)).

- **Nouns** become candidate classes. Each one either stays a class, becomes an attribute
  (a piece of data inside a class), or is dropped.
- **Verbs** become responsibilities, which turn into functions.

---

# PART A — NOUNS

## Candidate nouns (35)

customer, provider, admin, user, account, system, adventure, trip, booking, ticket,
person, name, age, gender, mobile, email, password, company, location, date, difficulty,
minimum age, price, seat, seats left, description, details, total, refund, status,
profile, menu, list, number, message

## What happened to each noun

### Kept as classes (8)

| Noun | Class | Why |
|---|---|---|
| user | `User` | What every account has in common: name, email, password, login |
| customer | `Customer` | A user who books; has its own data (gender, age, mobile) |
| provider | `Provider` | A user who lists adventures; has its own data (mobile, company) |
| admin | `Admin` | A user who manages everything |
| adventure | `Adventure` | The thing that is booked; has details and seats |
| booking | `Booking` | Links a customer to an adventure, with a status and a total |
| ticket | `Ticket` | One person on a booking (name, age) |
| system | `BookingSystem` | Holds all data and all rules |

### Became attributes (data inside a class)

| Noun | Inside class |
|---|---|
| name, email, password | `User` |
| gender, age, mobile | `Customer` |
| mobile, company | `Provider` |
| location, date, difficulty, minimum age, price, description, seat (total seats), seats left | `Adventure` |
| total, status | `Booking` |
| name, age | `Ticket` |

### Dropped

| Noun | Why |
|---|---|
| account | Same as user |
| trip | Same as adventure |
| person | Same as ticket (one person = one ticket) |
| details | Just the attributes of an adventure |
| refund | Always equal to the booking's total, so nothing extra is stored |
| profile | Not stored; it is printed from the user's attributes by `showProfile()` |
| menu, list, number, message | Part of the screen (the programs), not the data |

---

# PART B — VERBS

| Verb from the use cases | Responsibility | Function |
|---|---|---|
| log in | Check email and password | `loginCustomer()`, `loginProvider()`, `loginAdmin()`, `User::checkPassword()` |
| show / see | Show adventures, bookings, profiles | `getAdventures()`, `cout << adventure`, `cout << booking` (overloaded `<<`), `showProfile()` |
| book | Save a booking for some tickets | `BookingSystem::book()` |
| check age | Is this person old enough? | `Adventure::isAgeAllowed()` |
| take seats | Reduce seats left, refuse if too few | `Adventure::bookSeats()` |
| work out the total | Price per person × tickets | inside `BookingSystem::book()` |
| cancel | Mark a booking CANCELLED | `BookingSystem::cancelBooking()`, `Booking::cancel()` |
| give seats back | Increase seats left | `Adventure::releaseSeats()` |
| add an adventure | Save a new adventure | `BookingSystem::addAdventure()` |
| edit an adventure | Change any field except seats | `BookingSystem::updateAdventure()` |
| edit a user | Change a customer's or provider's details | `updateCustomer()`, `updateProvider()` |
| set a new password | Replace a user's password | `BookingSystem::changePassword()` |
| search | Find users whose name contains some text | `BookingSystem::searchUsers()` |

---

# Result

The 8 classes found here are exactly the classes in `src/`. See the [CRC cards](crc-cards.md)
for what each one does, and the [class diagram](class-diagram.md) for how they connect.
