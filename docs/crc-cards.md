# CRC Cards — Adventure Booking System

**Team ID:** 3 · Saksham (20251501153) · Naitik (20251501133) · Prerna (20251501135) · Kush (20251501176) · Abhay (20251502033)

One card for each class in `src/`. **Responsibilities** are what the class knows and does.
**Collaborators** are the other classes it works with.

---

## 1. Class: User (abstract) — `User.h`

| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Store the details every account has: ID, name, email, password | — |
| 2. Check a password at login without ever showing it | — |
| 3. Let the name, email and password be changed | — |
| 4. Make every kind of user say its role and show its profile | Customer, Provider, Admin |
| 5. Let only BookingSystem read the password, to save it in the data file (friend class) | BookingSystem |

## 2. Class: Customer — `User.h`

| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Store gender, age and mobile number (plus everything from User) | User |
| 2. Show its own profile | — |
| 3. Say its role: "Customer" | — |
| 4. Be the person a booking belongs to | Booking |

## 3. Class: Provider — `User.h`

| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Store mobile number and company name (plus everything from User) | User |
| 2. Show its own profile | — |
| 3. Say its role: "Provider" | — |
| 4. Own the adventures it lists | Adventure |

## 4. Class: Admin — `User.h`

| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Store the admin's details (everything from User) | User |
| 2. Show its own profile | — |
| 3. Say its role: "Admin" | — |

## 5. Class: Adventure — `Adventure.h`

| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Store its details: name, location, description, difficulty, minimum age, date, price | — |
| 2. Know which provider owns it | Provider |
| 3. Keep the total seats and the seats left | — |
| 4. Say whether a person's age is allowed | — |
| 5. Take seats for a booking, and refuse if not enough are left | Booking |
| 6. Give seats back when a booking is cancelled | Booking |
| 7. Print all its details with `cout <<` | — |

## 6. Struct: Ticket — `Booking.h`

| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Hold one person's name and age | Booking |

## 7. Class: Booking — `Booking.h`

| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Store who booked and which adventure | Customer, Adventure |
| 2. Hold the tickets (one per person) | Ticket |
| 3. Store the total price, fixed at booking time | — |
| 4. Know its status: BOOKED or CANCELLED | — |
| 5. Cancel itself, and refuse if it is already cancelled | — |
| 6. Count its tickets and print itself with `cout <<` | Ticket |
| 7. Know the most tickets one booking may have (`MAX_TICKETS`, the same for every booking) | — |

## 8. Class: BookingSystem — `BookingSystem.h`

| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Hold all users, adventures and bookings | Customer, Provider, Admin, Adventure, Booking |
| 1a. Read them from the data files before every action, and write the files after every change | all classes above |
| 1b. Create the files with the sample data on the very first run | all classes above |
| 2. Log users in by email and password | Customer, Provider, Admin |
| 3. Book an adventure: check every age and the seats, work out the price, save the booking | Adventure, Booking, Ticket |
| 4. Cancel a booking and give its seats back (a customer only their own) | Booking, Adventure |
| 5. Add and edit adventures (never the seats; the date must be DD-MM-YYYY) | Adventure, Provider |
| 6. Edit users: check the email has @, is not used by another account, and the mobile has 10 digits | Customer, Provider |
| 7. Set a new password for any user | Customer, Provider, Admin |
| 8. Search customers and providers by name | Customer, Provider |
| 9. Give the menus copies of the data to show | all classes above |
