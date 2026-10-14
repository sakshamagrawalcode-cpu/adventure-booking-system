# Test Cases — Adventure Booking System

Every feature of the app (`src/main.cpp`) was tested with the cases below.
**All 33 passed** (run on 15 Oct 2026).

**How to run a test by hand:** start the app fresh (`.\app.exe`), type exactly what the
"Steps" column says, and check that you see the "Expected" text.

**How to run all of them at once (optional, needs Python):**
`python tests/run_tests.py app.exe` — it types the steps into the app and prints PASS / FAIL.

**Short forms used in the steps**

| Short form | Means |
|---|---|
| *Aarav* | Main menu `1` → `aarav.sharma@gmail.com` → `aarav@123` (traveler) |
| *Rohit* | Main menu `1` → `ops@himalayantrails.in` → `rohit@123` (provider) |
| *Karan* | Main menu `1` → `karan.negi@spitiexpeditions.in` → `karan@123` (traveler + provider) |
| *Sneha* | Main menu `1` → `sneha.iyer@trekmate.in` → `sneha@123` (admin) |
| *Vikram* | Main menu `1` → `vikram.mehta@trekmate.in` → `vikram@123` (super admin) |
| *book TRP-2, 2 seats* | Traveler menu `4` → `TRP-2` → `2` → `4111111111111111` → `12/28` |
| `0` | Log out / go back |

The app always starts with the same sample data and the date **2026-10-15**,
so the same steps always give the same result.

---

## Log in and register

| ID | What we test | Steps | Expected | Result |
|---|---|---|---|---|
| TC-01 | Log in with the right email and password | *Aarav* | `Welcome, Aarav Sharma (Traveler)` and the TRAVELER MENU opens | ✅ Pass |
| TC-02 | Log in with a wrong password | Main menu `1` → `aarav.sharma@gmail.com` → `wrongpass` | `Wrong email or password.` | ✅ Pass |
| TC-03 | Register a new traveler, then log in | Main menu `2` → `Riya Kapoor`, `riya.kapoor@gmail.com`, `riya1234`, `+91-90000-11111`, `2002-05-10`, `A+`, `1`, `Anil Kapoor`, `+91-90000-22222` → log in as riya.kapoor@gmail.com / riya1234 | `Registered! Your user ID is U-5001` then `Welcome, Riya Kapoor (Traveler)` | ✅ Pass |
| TC-04 | Register with an email that is already used | Register as in TC-03 but with email `aarav.sharma@gmail.com` | `Not registered: This email is already registered.` | ✅ Pass |
| TC-05 | Register with a wrong date of birth | Register as in TC-03 but with date of birth `10-05-2002` | `Not registered: Date of birth must look like YYYY-MM-DD.` | ✅ Pass |
| TC-06 | Each kind of user gets its own menu (run-time polymorphism) | *Rohit* `0`, *Sneha* `0`, *Vikram* `0`, *Karan* `0` | PROVIDER MENU, ADMIN MENU, SUPER ADMIN MENU, `Karan Negi: you are a traveler AND a provider` | ✅ Pass |

## Browse and search (Browse Adventures)

| ID | What we test | Steps | Expected | Result |
|---|---|---|---|---|
| TC-07 | Browse shows the open trips | *Aarav* → `1` | TRP-1 to TRP-6 are listed | ✅ Pass |
| TC-08 | Search ignores capital letters | *Aarav* → `2` → `MANALI` | Only `TRP-2 \| Hampta Pass Trek \| Manali...` | ✅ Pass |
| TC-09 | Search with no result | *Aarav* → `2` → `goa` | `No trips found for 'goa'.` | ✅ Pass |
| TC-10 | See a trip's details; unknown trip ID | *Aarav* → `3` → `TRP-4`, then `3` → `TRP-99` | Full details of Chadar Frozen River Trek, then `No trip with that ID.` | ✅ Pass |

## UC-01 Book Adventure

| ID | What we test | Steps | Expected | Result |
|---|---|---|---|---|
| TC-11 | Main flow: book 2 seats | *Aarav* → *book TRP-2, 2 seats* → `1` | `Total to pay: Rs. 9000`, `[Email to aarav.sharma@gmail.com] Booking BK-1 confirmed`, the booking shows status CONFIRMED, a RECEIPT, and browse shows `seats left 18` | ✅ Pass |
| TC-12 | 4a: more seats than are left | *Aarav* → `4` → `TRP-5` → `8` | `Only 6 seat(s) left. Enter a smaller number.` (card details are not asked) | ✅ Pass |
| TC-13 | Rule that changes by user type | *Aarav* → `4` → `TRP-2` → `7` ; then *Karan* → `1` → *book TRP-2, 7 seats* | Aarav: `A Traveler can book at most 6 seats at once.` Karan: the booking is confirmed with 7 seats (his limit is 15) | ✅ Pass |
| TC-14 | 6a: payment fails | *Aarav* → `4` → `TRP-2` → `2` → `1234` → `12/28` → `1` | `Payment failed. Nothing saved, seats unchanged.` and browse still shows `seats left 20` | ✅ Pass |
| TC-15 | Zero seats | *Aarav* → `4` → `TRP-2` → `0` | `Number of seats must be at least 1.` | ✅ Pass |
| TC-16 | Letters typed where a number is needed | Type `abc` in the main menu; after logging in as Aarav type `two` | `Please type a whole number.` and the program keeps going | ✅ Pass |

## UC-02 Cancel Booking

| ID | What we test | Steps | Expected | Result |
|---|---|---|---|---|
| TC-17 | Main flow: cancel my booking | *Aarav* → *book TRP-2, 2 seats* → `5` → `BK-1` → `y` → `1` | `Booking BK-1 cancelled. Refund done.` and browse shows `seats left 20` again | ✅ Pass |
| TC-18 | 3a: the traveler changes their mind | *Aarav* → *book TRP-2, 2 seats* → `5` → `BK-1` → `n` | `Nothing changed. BK-1 is still CONFIRMED.` | ✅ Pass |
| TC-19 | Cannot cancel someone else's booking | *Karan* → `1` → *book TRP-2, 1 seat* → `0` `0`; *Aarav* → `5` → `BK-1` | `You have no booking with that ID.` | ✅ Pass |
| TC-20 | 1a: cancel after the trip date | *Aarav* → *book TRP-1, 1 seat* (trip is on 2026-10-25); *Sneha* → `7` → `2` → `2026-10-26`; *Aarav* → `5` → `BK-1` → `y` | `Trip date has passed. BK-1 cannot be cancelled.` | ✅ Pass |
| TC-21 | 5a: refund fails, admin settles it later | *Aarav* → *book TRP-2, 2 seats*; *Sneha* → `7` → `1` (failure ON); *Aarav* → `5` → `BK-1` → `y`; *Sneha* → `7` → `1` (failure OFF) → `6` | `Refund PENDING, admin will settle it.` then `Refund for PAY-1 is now REFUNDED.` | ✅ Pass |
| TC-22 | My bookings: all, or only confirmed (default argument) | *Aarav* → *book TRP-2, 1 seat* → *book TRP-3, 1 seat* → `5` → `BK-1` → `y` → `6` → `n` → `6` → `y` | First list: BK-1 CANCELLED and BK-2 CONFIRMED. Second list: only BK-2 | ✅ Pass |

## UC-03 Manage Trips and View Trip Bookings

| ID | What we test | Steps | Expected | Result |
|---|---|---|---|---|
| TC-23 | Main flow: create a valid trip | *Rohit* → `2` → `Valley of Flowers Trek`, `Chamoli, Uttarakhand`, `7000`, `2027-07-15`, `2027-07-20`, `12`, `12`, `1`; then *Aarav* → `2` → `flowers` | `Saved! TRP-7 is now live for travelers.` and the search finds TRP-7 | ✅ Pass |
| TC-24 | 4a: wrong details are not saved | *Rohit* → `2` with price `0`; again with start date `2026-01-01`; again with an empty trip name | `Not saved: Price must be above 0.` / `Start date must be in the future.` / `Trip name and place can not be empty.` | ✅ Pass |
| TC-25 | 3a: edit a trip that has bookings | *Aarav* → *book TRP-2, 2 seats*; *Rohit* → `3` → `TRP-2` → `1` → `5000` → `n`; again with `y` | Warning `this trip has 1 confirmed booking(s)`; with `n`: `Nothing changed.`; with `y`: `Saved.` and `[Email to aarav.sharma@gmail.com] Hampta Pass Trek: the price is now Rs. 5000 per seat` | ✅ Pass |
| TC-26 | 2a: remove a trip with / without bookings | *Aarav* → *book TRP-2, 2 seats*; *Rohit* → `4` → `TRP-2` → `y`; `4` → `TRP-3` → `y`; *Aarav* → `1` | `Cannot remove 'Hampta Pass Trek': it has confirmed bookings.`; `'Kedarkantha Winter Trek' removed (status CLOSED).`; TRP-3 is no longer in the browse list | ✅ Pass |
| TC-27 | A provider cannot touch another provider's trip | *Rohit* → `3` → `TRP-5`; `4` → `TRP-6` (both are Karan's) | `You have no trip with that ID.` (twice) | ✅ Pass |
| TC-28 | See who booked a trip | *Aarav* → *book TRP-2, 2 seats*; *Rohit* → `5` → `TRP-2`; `5` → `TRP-4` | `BK-1 \| Aarav Sharma \| aarav.sharma@gmail.com \| seats 2 \| CONFIRMED`; `No bookings for Chadar Frozen River Trek yet.` | ✅ Pass |

## Admin, super admin and profile

| ID | What we test | Steps | Expected | Result |
|---|---|---|---|---|
| TC-29 | All users and search users | *Sneha* → `1`; `2` → `negi` | All 5 users with their roles; the search shows only Karan Negi | ✅ Pass |
| TC-30 | Trip report and all bookings | *Aarav* → *book TRP-2, 2 seats*; *Sneha* → `4`; `3` | `TRP-2 \| Hampta Pass Trek \| PUBLISHED \| seats sold 2 of 20 \| money collected Rs. 9000`; booking list with `payment SUCCESS` | ✅ Pass |
| TC-31 | Admin cannot remove a booked trip | *Aarav* → *book TRP-2, 2 seats*; *Sneha* → `5` → `TRP-2`; `5` → `TRP-5` | `Cannot remove 'Hampta Pass Trek': 2 seat(s) are booked.`; `'Bir Billing Paragliding' removed (status CLOSED).` | ✅ Pass |
| TC-32 | Super admin stats need the password again | *Vikram* → `2` → `wrong`; `2` → `vikram@123` | `Wrong password. Stats not shown.` then the stats | ✅ Pass |
| TC-33 | Update my profile | *Aarav* → `7` → `y` → (press Enter) → `+91-11111-22222`; `7` | `Profile saved.`; the profile shows the new phone and the same name | ✅ Pass |

---

## Which use case flows are covered

| Use case | Main flow | Alternate flows |
|---|---|---|
| UC-01 Book Adventure | TC-11 | 4a not enough seats: TC-12 · 6a payment fails: TC-14 · 8a email fails: not tested (the email is only printed) |
| UC-02 Cancel Booking | TC-17 | 1a trip already over: TC-20 · 3a changes mind: TC-18 · 5a refund fails: TC-21 |
| UC-03 Manage Trips | TC-23 | 2a remove with bookings: TC-26, TC-31 · 3a edit with bookings: TC-25 · 4a wrong details: TC-24 |
| Register / Login | TC-01, TC-03 | TC-02, TC-04, TC-05 |
| Browse Adventures | TC-07, TC-08 | TC-09, TC-10 |
| View Trip Bookings | TC-28 | — |
| Manage Users and Listings | TC-29, TC-30 | TC-31 |

## Other checks that were done

- The app was run with memory checking on (AddressSanitizer + UndefinedBehaviorSanitizer):
  no memory errors and no memory leaks.
- The input was cut off after every single line of every test, and 300 runs were made
  with random junk input: the app never crashed or got stuck, and always ended with `Goodbye!`.
- Both programs (`main.cpp` and `demo.cpp`) compile with no warnings on g++ and clang++
  (`-Wall -Wextra -Wpedantic`).
