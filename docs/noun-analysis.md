# Noun–Verb Analysis — Adventure Booking System

**Team ID:** _[37]_
Saksam (20251501153) . Prerna (20251501135) · Naitik (20251501133) · Kush (20251501176) · Abhay (2025102033)

Taken from our three use cases: Book Adventure, Cancel Booking, Manage Trips.

---

# PART A — NOUNS

## Candidate nouns (58)

- traveler
- trip
- seat
- seats
- seats left
- total seats
- seat count
- booking
- bookings
- booking ID
- payment
- payment details
- Payment Gateway
- gateway
- Email Service
- email
- confirmation
- confirmation email
- confirmation box
- Adventure Provider
- provider
- Admin
- admin
- account
- system
- app
- screen
- page
- My Bookings
- My Trips
- Add Trip
- browse list
- listing
- place
- name
- date
- trip date
- price
- amount
- money
- number
- entries
- fields
- field
- details
- change
- removal
- cancellation
- refund
- refund request
- status
- proof
- failure
- success
- mind
- someone
- future
- past trip

---

## Filter 1 — Redundancy (two or more words that mean the same thing in our system, so only one is kept)

**Eliminated (18):**

- seat, seats, seats left, total seats — same as seat count
- bookings — same as booking
- provider — same as Adventure Provider
- admin — same as Admin
- gateway — same as Payment Gateway
- confirmation, confirmation email — same as email
- listing — same as trip
- trip date — same as date
- money, amount — same as price
- refund request — same as refund
- past trip — same as trip
- app — same as system

**Surviving (40):**

- traveler
- trip
- seat count
- booking
- booking ID
- payment
- payment details
- Payment Gateway
- Email Service
- email
- confirmation box
- Adventure Provider
- Admin
- account
- system
- screen
- page
- My Bookings
- My Trips
- Add Trip
- browse list
- place
- name
- date
- price
- number
- entries
- fields
- field
- details
- change
- removal
- cancellation
- refund
- status
- proof
- failure
- success
- mind
- someone
- future

---

## Filter 2 — Vagueness (words with no clear meaning of their own, so they cannot be a class)

**Eliminated (12):**

- details
- entries
- fields
- field
- change
- removal
- number
- proof
- mind
- someone
- future
- confirmation box

**Surviving (29):**

- traveler
- trip
- seat count
- booking
- booking ID
- payment
- payment details
- Payment Gateway
- Email Service
- email
- Adventure Provider
- Admin
- account
- system
- screen
- page
- My Bookings
- My Trips
- Add Trip
- browse list
- place
- name
- date
- price
- cancellation
- refund
- status
- failure
- success

---

## Filter 3 — Attribute (a value that lives inside another class instead of being a class itself)

**Eliminated (14):**

- seat count — inside Trip
- booking ID — inside Booking
- place — inside Trip
- name — inside Trip and User
- date — inside Trip
- price — inside Trip
- status — inside Booking
- cancellation — a status value of Booking
- refund — a function of Payment
- failure — a result value of Payment
- success — a result value of Payment
- payment details — inside Payment
- account — its email and password go inside the user classes

**Surviving (15):**

- traveler
- trip
- booking
- payment
- Payment Gateway
- Email Service
- Adventure Provider
- Admin
- system
- screen
- page
- My Bookings
- My Trips
- Add Trip
- browse list

---

## Filter 4 — Out of scope (things our program does not build or control)

**Eliminated (8):**

- system — the whole application, not a class inside it
- screen — user interface
- page — user interface
- My Bookings — a screen name
- My Trips — a screen name
- Add Trip — a button
- browse list — a screen
- Email Service — an outside service, we only send to it
- email — the message is produced by that outside service

**Surviving (7) — our classes:**

- Traveler
- AdventureProvider
- Admin
- Trip
- Booking
- Payment
- PaymentGateway

We are also adding a `User` class in the class diagram as the parent of Traveler, AdventureProvider and Admin, since all three need name, email, password and login. It did not come from the nouns, we added it while designing.

---

## Final classes

| Class | Meaning |
|---|---|
| User | User — parent class holding what all three share (name, email, password, login) |
| Traveler | user who books trips |
| AdventureProvider | user who lists trips |
| Admin | user who manages everything |
| Trip | one adventure with place, date, price, seats |
| Booking | seats reserved by a traveler on a trip |
| Payment | money paid for a booking, and its refund |
| PaymentGateway | the class that processes the payment (simulated) |

---

# PART B — VERBS

## Candidate verbs (29)

- pick
- book
- pay
- cancel
- confirm
- log in
- press
- open
- browse
- show
- enter
- check
- send
- report
- save
- reduce
- increase
- create
- add
- remove
- edit
- publish
- update
- validate
- block
- warn
- notify
- alert
- settle

---

## Dropped verbs (17)

- pick — same as book
- confirm — the last step of book
- press — user interface action
- open — user interface action
- browse — user interface action
- show — user interface action
- enter — user interface action
- report — part of pay, done by the gateway
- send — handled by the outside Email Service
- notify — same as send
- warn — same as send
- alert — same as send
- block — the result of validate failing
- settle — vague, part of refund
- add — same as create
- update — same as edit
- check — same as validate

---

## Final verbs (12) — these become our operations

- log in
- book
- cancel
- pay
- refund
- create
- edit
- remove
- publish
- validate
- reduce
- increase
