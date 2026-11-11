# Use Case Specifications — Adventure Booking System

**Team ID:** 3 · Saksham (20251501153) · Naitik (20251501133) · Prerna (20251501135) · Kush (20251501176) · Abhay (20251502033)

These use cases match the programs in `src/`. Text in quotes is exactly what the program prints.

> **Note:** the three programs (customer, provider, admin) share the same data files in
> `data/`. A change made in one program is seen at once by the other two.

---

## UC-01 · Book Adventure

A customer picks an adventure and books tickets for one or more people.

**Primary actor:** Customer
**Program:** `customer.cpp`

### Stakeholders and interests

| Stakeholder | Interest |
|---|---|
| Customer | Wants the seats booked in a couple of minutes and the booking visible in the app. |
| Adventure Provider | Wants the seat count to stay correct and only people of the allowed age on the trip. |
| Admin | Wants the system to never sell more seats than an adventure has. |

### Preconditions
1. The customer is logged in.

### Trigger
The customer chooses **1. Show adventures** in the customer menu.

### Main flow
1. The system shows every adventure with its location, date, price and seats left.
2. The customer types the number of an adventure.
3. The system shows its full details: name, location, date, difficulty, minimum age, price per person, seats left and description.
4. The customer types **1** at "Book this? (1 = Yes, 0 = No)".
5. The customer enters how many tickets they want (1 to 20).
6. For each ticket, the customer enters the person's name and age.
7. The system checks that every person is at least the minimum age.
8. The system checks that enough seats are left, and takes them.
9. The system works out the total (price per person × number of tickets) and saves the booking with status BOOKED.
10. The system shows "Booked! 2 ticket(s) for River Rafting (16 km). Total: Rs. 3000".

### Alternate flows

**2a — The customer goes back.** The customer types 0. The menu is shown again and nothing is booked.

**4a — The customer does not book.** The customer types 0. Nothing is booked.

**5a, 6a — Wrong input.** Letters, negative numbers and numbers out of range are not accepted.
The system asks again ("Please enter a whole number." or "Please enter a number from 1 to 20.").
An empty name is not accepted ("This cannot be empty.").

**7a — Someone is too young.** The system shows "Booking failed: Arjun Rao is below the minimum age 18".
No seats are taken and nothing is saved.

**8a — Not enough seats.** The system shows "Booking failed: Only 6 seats left". Nothing is saved.

### Postconditions
- The booking is saved with status BOOKED and appears in **My bookings**,
  in the provider's **Who booked** and in the admin's **All bookings**.
- The adventure's seats left go down by the number of tickets.

---

## UC-02 · Cancel Booking

A customer cancels one of their bookings and gets a full refund.
The admin can cancel any customer's booking in the same way.

**Primary actor:** Customer
**Other actor:** Admin (option **6. Cancel a booking** in `admin.cpp`)
**Programs:** `customer.cpp`, `admin.cpp`

### Stakeholders and interests

| Stakeholder | Interest |
|---|---|
| Customer | Wants the money back and the booking clearly marked as cancelled. |
| Adventure Provider | Wants the freed seats to become available again at once. |
| Admin | Wants to cancel a booking for a customer when needed. |

### Preconditions
1. The customer (or admin) is logged in.
2. There is at least one booking with status BOOKED.

### Trigger
The customer chooses **3. Cancel a booking** in the customer menu.

### Main flow
1. The system lists only the bookings that are still BOOKED, with the adventure's name and date, the number of tickets and the total price.
2. The customer types the number of a booking.
3. The system marks the booking CANCELLED.
4. The system gives the booking's seats back to the adventure.
5. The system shows "Cancelled. Refunded Rs. 19000" (always the full amount).

### Alternate flows

**1a — Nothing to cancel.** The system shows "No bookings to cancel."

**2a — The customer goes back.** The customer types 0. Nothing is cancelled.

**3a — Already cancelled.** The system refuses with "Booking is already cancelled".
This can happen if the admin cancelled it in the admin program a moment earlier.

**3b — Not the customer's booking.** The customer version of `cancelBooking()` refuses
with "This booking is not yours". (The menu lists only the customer's own bookings, so this
is a safety check.)

**Admin path.** The admin chooses **6. Cancel a booking**. The list shows the BOOKED bookings
of every customer, with the customer's name. Steps 2 to 5 are the same.

### Postconditions
- The booking stays in **My bookings**, marked CANCELLED.
- The adventure's seats left go up by the number of tickets.
- The provider's **Who booked** list no longer shows this booking.
- Only a whole booking can be cancelled, not single tickets.

---

## UC-03 · Manage Adventures

A provider lists a new adventure, edits it later, and sees who booked it.

**Primary actor:** Adventure Provider
**Program:** `provider.cpp`

### Stakeholders and interests

| Stakeholder | Interest |
|---|---|
| Adventure Provider | Wants to put up adventures quickly, fix mistakes, and know who is coming. |
| Customer | Wants the details of an adventure to be correct. |
| Admin | Wants seat counts that can't be broken by editing. |

### Preconditions
1. The provider is logged in.

### Trigger
The provider chooses **2. Add adventure**, **3. Edit adventure** or **4. Who booked**.

### Main flow — add an adventure
1. The provider chooses **2. Add adventure**.
2. The provider enters the name, location and description.
3. The provider picks the difficulty: 1. Easy, 2. Moderate or 3. Hard.
4. The provider enters the minimum age (1 to 120), the date (DD-MM-YYYY), the price per person (Rs. 1 to 10,00,000) and the number of seats (1 to 1000).
5. The system saves the adventure with all seats free and shows "Adventure added."

### Main flow — edit an adventure
6. The provider chooses **3. Edit adventure**. The system lists only this provider's adventures.
7. The provider picks one. The system shows each field with its current value: name, location, description, difficulty, minimum age, date and price.
8. The provider picks a field and enters the new value. The system shows "Saved." and the list again, until the provider types 0.

### Main flow — see who booked
9. The provider chooses **4. Who booked** and picks one of their adventures.
10. For every active booking, the system shows the customer's name, gender, mobile and email.

### Alternate flows

**6a — No adventures yet.** The system shows "You have no adventures yet."

**4a — Wrong input.** Numbers out of range or letters are not accepted, and the system asks again.

**4b — Wrong date format.** The system shows "Could not add: Date must be like 20-12-2026 (DD-MM-YYYY)".
When editing, it shows "Could not save: ..." with the same message.

**8a — Seats can't be edited.** Seats are not in the edit list, so the seat count set when the adventure was added can't be changed.

**10a — No bookings.** The system shows "No bookings yet." Cancelled bookings are not shown.

### Postconditions
- A new adventure appears in **My adventures**.
- An edited price applies to new bookings only. Old bookings keep the total they were booked at.

---

## UC-04 · Manage Users

The admin finds a user, changes their details, or sets a new password.

**Primary actor:** Admin
**Program:** `admin.cpp`

### Stakeholders and interests

| Stakeholder | Interest |
|---|---|
| Admin | Wants to fix wrong details and help users who forgot their password, from one place. |
| Customer / Adventure Provider | Wants their details correct and their account usable again. |

### Preconditions
1. The admin is logged in.

### Trigger
The admin chooses **3. Search users by name**, **7. Edit a user** or **8. Change a password**.

### Main flow — edit a user
1. The admin chooses **7. Edit a user**, then **1. Customer** or **2. Provider**.
2. The system lists those users with their name and email. The admin picks one.
3. The system shows each field with its current value.
   Customer: name, email, gender, age, mobile. Provider: name, email, mobile, company.
4. The admin picks a field and enters the new value.
5. The system checks the value, saves it and shows "Saved."

### Main flow — set a new password
6. The admin chooses **8. Change a password**, then the kind of user (customer, provider or admin), then the user.
7. The admin types the new password. The old password is never shown.
8. The system saves it and shows "Password changed."

### Main flow — search users
9. The admin chooses **3. Search users by name** and types a name or part of one.
10. The system shows every customer and provider whose name contains that text, capitals ignored, each with its role and profile.

### Alternate flows

**5a — Email without @.** "Could not save: Email must contain @"

**5b — Email used by another account.** "Could not save: Email already in use"

**5c — Mobile is not exactly 10 digits.** "Could not save: Mobile must be exactly 10 digits"

**10a — No match.** "No user found."

### Postconditions
- Edited details show at once in **All customers** or **All providers**.
- A new password works from the next login.
