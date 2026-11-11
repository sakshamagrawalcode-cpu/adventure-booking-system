# Test Cases — Adventure Booking System

**Team ID:** 3 · Saksham (20251501153) · Naitik (20251501133) · Prerna (20251501135) · Kush (20251501176) · Abhay (20251502033)

Every feature of the three programs was tested with the cases below. **All 49 passed** (run on 11 Nov 2026).

**How to run a test by hand:** build the program (see the README), start it fresh, type exactly what the "Steps" column says (pressing Enter after each value), and check that you see the "Expected" text. **Before each test, delete the `.txt` files in the `data` folder**, so the program starts again from the sample data and the same steps always give the same result.

**Short forms used in the steps**

| Short form | Means |
|---|---|
| *Rahul* | log in with `rahul@example.com` → `rahul123` (customer, age 20) |
| *Arjun* | log in with `arjun@example.com` → `arjun123` (customer, age 16) |
| *Amit* | log in with `amit@example.com` → `amit123` (provider, Himalayan Treks) |
| *Neha* | log in with `neha@example.com` → `neha123` (provider, Rishikesh Rapids) |
| *Admin* | log in with `admin@example.com` → `admin123` |
| `→` | press Enter, then type the next value |

## Customer program (`customer.cpp`)

| ID | What is tested | Steps | Expected | Result |
|---|---|---|---|---|
| C-01 | Wrong password is refused | `rahul@example.com` → `wrongpass` | "Wrong email or password. Try again." and the login asks again | Pass |
| C-02 | Correct login | *Rahul* | "Welcome, Rahul Mehta!" and the customer menu | Pass |
| C-03 | Show adventures | *Rahul* → `1` → `0` | 4 adventures with place, date, price and seats left; Kedarkantha shows Seats left: 8 | Pass |
| C-04 | Open one adventure | *Rahul* → `1` → `3` → `0` | Full details of River Rafting: Min age 14, Rs. 1500 per person, Seats left 12 of 12 | Pass |
| C-05 | Book 2 tickets | *Rahul* → `1` → `3` → `1` → `2` → `Rahul Mehta`, `20` → `Priya Patel`, `22` → `1` → `0` | "Booked! 2 ticket(s) for River Rafting (16 km). Total: Rs. 3000"; the list then shows River Rafting with Seats left: 10 | Pass |
| C-06 | Person below the minimum age | *Arjun* → `1` → `4` → `1` → `1` → `Arjun Rao`, `16` | "Booking failed: Arjun Rao is below the minimum age 18" | Pass |
| C-07 | More tickets than seats | *Rahul* → `1` → `4` → `1` → `7` → 7 people, each age `20` | "Booking failed: Only 6 seats left" | Pass |
| C-08 | My bookings | *Rahul* → `2` | Kedarkantha Winter Trek (20-12-2026), Status BOOKED, 2 tickets, Total Rs. 19000 | Pass |
| C-09 | Cancel a booking | *Rahul* → `3` → `1` → `2` → `1` → `0` | "Cancelled. Refunded Rs. 19000"; My bookings shows Status CANCELLED; Kedarkantha is back to Seats left: 10 | Pass |
| C-10 | Nothing to cancel | *Arjun* → `3` | "No bookings to cancel." | Pass |
| C-11 | View profile | *Rahul* → `4` | Name, email, gender, age and mobile of Rahul | Pass |
| C-12 | Edit age | *Rahul* → `5` → `3` → `21` → `0` → `4` | "Saved."; the profile shows Age 21 | Pass |
| C-13 | Edit gender (picked from a list) | *Rahul* → `5` → `2` → `2` → `0` → `4` | "Saved."; the profile shows Gender Female | Pass |
| C-14 | Mobile with fewer than 10 digits | *Rahul* → `5` → `4` → `12345` | "Could not save: Mobile must be exactly 10 digits" | Pass |
| C-15 | Wrong input in a menu | *Rahul* → `abc` → `9` → (empty line) → `0` | "Please enter a whole number.", then "Please enter a number from 0 to 5.", then "This cannot be empty." | Pass |
| C-16 | Logout | *Rahul* → `0` | "Logged out." and the login screen again | Pass |
| C-17 | Exit from the login screen | `0` | "Goodbye!" and the program closes | Pass |
| C-18 | Email capitals are ignored at login | `RAHUL@Example.com` → `rahul123` | "Welcome, Rahul Mehta!" | Pass |
| C-19 | The character \| is refused | *Rahul* → `5` → `1` → `Rahul\|Mehta` → `Rahul M` → `0` → `4` | "The character \| can't be used." then "Saved."; the profile shows Rahul M | Pass |

## Provider program (`provider.cpp`)

| ID | What is tested | Steps | Expected | Result |
|---|---|---|---|---|
| P-01 | Correct login | *Amit* | "Welcome, Amit Sharma (Himalayan Treks)!" | Pass |
| P-02 | My adventures | *Amit* → `1` | Only Amit's 2 adventures, e.g. Kedarkantha with Seats left: 8 of 10 | Pass |
| P-03 | Add an adventure | *Amit* → `2` → `Chopta Tungnath Trek` → `Uttarakhand` → `A short trek to Tungnath temple.` → `1` → `10` → `25-03-2027` → `6500` → `15` → `1` | "Adventure added."; My adventures shows it with Seats left: 15 of 15 | Pass |
| P-04 | Wrong numbers while adding | *Amit* → `2` → `X` → `Y` → `Z` → `1` → `-5` → `10` → `01-01-2027` → `0` → `100` → `5` | "Please enter a whole number." for -5, "Please enter a number from 1 to 1000000." for 0, then "Adventure added." | Pass |
| P-05 | Edit the price (seats can't be edited) | *Amit* → `3` → `1` → `7` → `9900` → `0` → `1` | "Saved."; the edit list has no seats option; My adventures shows Rs. 9900 | Pass |
| P-06 | Who booked | *Amit* → `4` → `1` | Rahul Mehta with gender, mobile and email | Pass |
| P-07 | Who booked, no bookings | *Amit* → `4` → `2` | "No bookings yet." | Pass |
| P-08 | View profile | *Amit* → `5` | Name, email, mobile and company of Amit | Pass |
| P-09 | Each provider sees only their own adventures | *Neha* → `1` | River Rafting and Bungee Jumping only (no Kedarkantha) | Pass |
| P-10 | Wrong date format | *Amit* → `2` → `X` → `Y` → `Z` → `1` → `10` → `2026-12-20` → `500` → `5` | "Could not add: Date must be like 20-12-2026 (DD-MM-YYYY)" | Pass |

## Admin program (`admin.cpp`)

| ID | What is tested | Steps | Expected | Result |
|---|---|---|---|---|
| A-01 | Wrong, then correct login | `admin@example.com` → `x` → *Admin* | "Wrong email or password. Try again.", then "Welcome, Saksham!" | Pass |
| A-02 | All customers (no passwords shown) | *Admin* → `1` | 3 customer profiles; no password appears | Pass |
| A-03 | All providers | *Admin* → `2` | 2 provider profiles with company names; no password appears | Pass |
| A-04 | Search by part of a name, capitals ignored | *Admin* → `3` → `RA` | Rahul Mehta and Arjun Rao, each shown as Customer | Pass |
| A-05 | Search finds both kinds of users | *Admin* → `3` → `a` | 3 customers and 2 providers; each prints its own kind of profile (polymorphism) | Pass |
| A-06 | Search with no match | *Admin* → `3` → `xyz` | "No user found." | Pass |
| A-07 | All bookings with who booked | *Admin* → `4` | Kedarkantha booking, Rahul's full profile, both tickets | Pass |
| A-08 | Seats left for every adventure | *Admin* → `5` | 4 adventures with company and seats, e.g. Kedarkantha Seats left: 8 of 10 | Pass |
| A-09 | Cancel any booking | *Admin* → `6` → `1` → `5` | "Cancelled. Refunded Rs. 19000"; Kedarkantha is back to Seats left: 10 of 10 | Pass |
| A-10 | Email already used by another account | *Admin* → `7` → `1` → `2` → `2` → `rahul@example.com` | "Could not save: Email already in use" | Pass |
| A-11 | Email without @ | *Admin* → `7` → `1` → `2` → `2` → `priya.example.com` | "Could not save: Email must contain @" | Pass |
| A-12 | Edit a provider | *Admin* → `7` → `2` → `1` → `4` → `Himalayan Treks Pvt Ltd` → `0` → `2` | "Saved."; All providers shows the new company name | Pass |
| A-13 | Set a new password | *Admin* → `8` → `3` → `1` → `newpass123` → `0` → old password → new password | "Password changed."; after logout the old password is refused and `newpass123` works | Pass |

## Shared data and files (more than one program)

| ID | What is tested | Steps | Expected | Result |
|---|---|---|---|---|
| S-01 | A booking made in the customer program shows in admin and provider | customer: *Rahul* → `1` → `3` → `1` → `1` → `Rahul Mehta`, `20`; then admin: *Admin* → `4`; then provider: *Neha* → `4` → `1` | Admin's All bookings lists the River Rafting booking; Neha's Who booked lists Rahul Mehta | Pass |
| S-02 | Data stays after the program closes | customer: *Rahul* → `3` → `1`; close; start again: *Rahul* → `2` | After the restart, My bookings shows the Kedarkantha booking as CANCELLED | Pass |
| S-03 | A password set by the admin works in the customer program | admin: *Admin* → `8` → `1` → `1` → `rahulNEW` ; then customer: `rahul@example.com` → `rahul123` → `rahul@example.com` → `rahulNEW` | The old password is refused, the new one gives "Welcome, Rahul Mehta!" | Pass |
| S-04 | A new adventure from the provider shows for customers | provider: *Amit* → `2` → `Chopta Trek` → `Uttarakhand` → `Short trek.` → `1` → `10` → `25-03-2027` → `6500` → `15`; then customer: *Rahul* → `1` → `0` | The customer's list shows Chopta Trek with Seats left: 15 | Pass |
| S-05 | First run creates the data files | Delete the files in `data/`, then start any program | The files customers.txt, providers.txt, admins.txt, adventures.txt, bookings.txt and tickets.txt appear in data/ with the sample data | Pass |
| S-06 | Program started from the wrong folder | Start a program when `../data/` does not exist | "Error: Can't write ../data/customers.txt. Run the program from the src folder." | Pass |
| S-07 | Damaged data file | Add a broken line to `data/customers.txt`, then start a program | "Error: The data file customers.txt is damaged" | Pass |
