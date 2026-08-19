# CRC Cards — Adventure Booking System

**Team ID:** 37
Saksham (20251501153) · Prerna (20251501135) · Naitik (20251501133) · Kush (20251501176) · Abhay (2025102033)

---

## 1. Class: User

| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Store basic credentials (userId, name, email, password) | — |
| 2. Authenticate user during login | — |
| 3. Update profile details | — |

## 2. Class: Traveler

| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Browse the list of available trips | Trip |
| 2. Initiate a booking and trigger the payment process | Booking, Payment |
| 3. Cancel an existing booking | Booking |
| 4. View own booking history and status | Booking |

## 3. Class: AdventureProvider

| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Create, update, and publish adventure trips | Trip |
| 2. Remove a trip that is no longer offered | Trip |
| 3. View the bookings made on hosted trips | Booking, Trip |

## 4. Class: Admin

| Responsibilities | Collaborators |
| :--- | :--- |
| 1. View and manage all user accounts | User |
| 2. View and manage all trips in the system | Trip |
| 3. View and manage all bookings, including pending refunds | Booking, Payment |

## 5. Class: Trip

| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Store trip details (title, location, price, date, totalSeats) | AdventureProvider |
| 2. Track and update the number of seats remaining | Booking |
| 3. Validate its own details (future date, price above zero, seats above zero) | — |
| 4. Block its own removal while confirmed bookings exist | Booking |

## 6. Class: Booking

| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Maintain reservation status (CONFIRMED, CANCELLED) | — |
| 2. Calculate total cost (Trip.price × number of seats) | Trip |
| 3. Reserve or release trip seats based on payment outcome | Trip |
| 4. Trigger the confirmation email after booking or cancellation | Traveler, Payment |

## 7. Class: Payment

| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Store transaction details (paymentId, amount, status, timestamp) | Booking |
| 2. Initiate and verify a transaction through the gateway | PaymentGateway |
| 3. Process a refund when a booking is cancelled | PaymentGateway, Booking |

## 8. Class: PaymentGateway

| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Validate the payment details it is given | Payment |
| 2. Simulate the processing of a payment or a refund | Payment |
| 3. Return the transaction status (SUCCESS / FAILED) | Payment |

---

## Why User is the parent class

Traveler, AdventureProvider and Admin all need the same four things — a name, an email, a password, and a way to log in. Writing those three times would be pointless repetition, so we put them once in a `User` class and let the other three inherit from it.

This also means the login code does not care who is logging in. It just gets a User and checks the password.

And if we ever add a new kind of user later, say a guide, it can inherit from User too and login will already work for it.

## Why PaymentGateway does not talk to a real bank

Our PaymentGateway is a fake one. It takes the payment details, checks them, and sends back either SUCCESS or FAILED.

We did this on purpose. The whole app works from start to finish without depending on any outside service, so nothing can break during the demo. It also lets us make a payment fail whenever we want, which is useful when we test what happens on a failed booking.
