
# Use Case Specifications — Adventure Booking System

## UC-01 · Book Adventure

A traveler picks a trip, books seats on it, pays, and gets a confirmation email.

**Primary Actor:** Traveler
**Supporting Actors:** Payment Gateway, Email Service

### Stakeholders and Interests

| Stakeholder | Interest |
|---|---|
| Traveler | Wants the seat reserved in a couple of minutes and proof that the booking is real. |
| Adventure Provider | Wants every confirmed booking to be a paid one, and the seat count of the trip to stay correct. |
| Admin | Wants the system to never sell more seats than a trip has. |
| Payment Gateway | Wants to take the payment and clearly report success or failure. |

### Preconditions
1. The traveler has an account and is logged in.
2. The trip is live and has at least one seat left.

### Trigger
The traveler presses **Book** on a trip.

### Main Flow
1. Traveler opens a trip from the browse list.
2. App shows the place, date, price and seats left.
3. Traveler enters how many seats they want and continues.
4. App checks that many seats are still free.
5. App shows the total amount and takes the payment details.
6. App sends the payment to the Payment Gateway, which reports success.
7. App saves the booking as CONFIRMED, reduces the seats left, and creates a booking ID.
8. App automatically sends a confirmation email to the traveler.
9. App shows the booking ID on screen.

### Alternate Flows

**4a — Not enough seats.**
Someone else booked first, or the traveler asked for more seats than remain. The app says how many are actually left and lets them enter a smaller number.

**6a — Payment fails.**
The gateway reports failure. Nothing is saved, the seat count does not change, and the traveler can try the payment again.

**8a — Email does not go out.**
The booking is still valid. The app shows the booking ID on screen anyway and tries the email again later.

### Postconditions
- **Success:** a CONFIRMED booking exists, seats left have gone down by that number, the payment is recorded, and an email has been sent.
- **Failure:** no booking exists, seat counts are unchanged, and nothing has been charged.

---

## UC-02 · Cancel Booking

A traveler cancels one of their bookings and the seats go back to the trip.

**Primary Actor:** Traveler
**Supporting Actors:** Payment Gateway, Email Service

### Stakeholders and Interests

| Stakeholder | Interest |
|---|---|
| Traveler | Wants to cancel in one place and get the money back without calling anyone. |
| Adventure Provider | Wants the freed seat back on sale immediately. |
| Admin | Wants every cancellation recorded, not just erased. |
| Payment Gateway | Wants the refund matched correctly to the original payment. |

### Preconditions
1. The traveler is logged in and has a booking with status CONFIRMED.
2. The trip date has not passed.

### Trigger
The traveler presses **Cancel** on one of their bookings.

### Main Flow
1. Traveler opens **My Bookings** and picks a booking.
2. App asks them to confirm the cancellation.
3. Traveler confirms.
4. App changes the booking to CANCELLED and adds the seats back to the trip.
5. App sends a refund request to the Payment Gateway, which confirms it.
6. App sends a cancellation email to the traveler.
7. App shows on screen that the booking is cancelled.

### Alternate Flows

**1a — The trip is already over.**
The app does not allow cancelling a past trip and simply says so.

**3a — Traveler changes their mind.**
They close the confirmation box. Nothing changes and the booking stays CONFIRMED.

**5a — Refund fails.**
The booking is still CANCELLED and the seats are still freed, but the refund is marked PENDING and the admin is alerted to settle it.

### Postconditions
- **Success:** the booking is CANCELLED, seats left have gone up by that number, the refund is done or marked PENDING, and the traveler has an email about it.
- **Failure:** the booking stays CONFIRMED and nothing else changes.

---

## UC-03 · Manage Trips

An adventure provider puts up a new trip, edits one, or removes one. The admin can do the same on any trip.

**Primary Actor:** Adventure Provider
**Secondary Actor:** Admin
**Supporting Actor:** Email Service

### Stakeholders and Interests

| Stakeholder | Interest |
|---|---|
| Adventure Provider | Wants to publish and update their own trips without going through anyone. |
| Traveler | Wants what the listing says — date, price, seats — to be true. |
| Admin | Wants the ability to fix or take down a bad listing. |

### Preconditions
1. The provider is logged in.
2. For editing or removing, the trip exists and belongs to that provider (the admin can touch any trip).

### Trigger
The provider presses **Add Trip**, or opens one of their trips to edit.

### Main Flow
1. Provider opens their **My Trips** page.
2. Provider chooses to add a new trip or picks an existing one.
3. Provider fills in the name, place, date, price and total seats.
4. App checks the entries — no blank fields, price above zero, seats above zero, date in the future.
5. Provider saves the trip.
6. App publishes it, and it appears in the traveler's browse list.
7. App confirms on screen that the trip is live.

### Alternate Flows

**4a — Something is invalid.**
A past date, a zero price, an empty field. The app points at the exact field and does not save until it is fixed.

**3a — Editing a trip that already has bookings.**
The provider changes the date or price of a trip people have paid for. The app warns them first, and if they go ahead, emails every booked traveler about the change.

**2a — Removing a trip that has confirmed bookings.**
The app blocks the removal and tells the provider to deal with those bookings first, so no one loses a trip silently.

### Postconditions
- **Success:** the trip is saved and visible to travelers with the new details.
- **Failure:** nothing is saved, and existing bookings and seat counts stay exactly as they were.
