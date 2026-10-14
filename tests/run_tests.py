#!/usr/bin/env python3
"""
Runs every test case in docs/test-cases.md against the real app.
It starts the app fresh for each test, types the steps into it,
and checks that the expected text appears.

How to run (from the project folder, after building the app):
    Windows:   python tests/run_tests.py app.exe
    Linux/Mac: python3 tests/run_tests.py ./app
"""
import subprocess, sys

APP = sys.argv[1] if len(sys.argv) > 1 else "app.exe"

AARAV = ['1', 'aarav.sharma@gmail.com', 'aarav@123']
ROHIT = ['1', 'ops@himalayantrails.in', 'rohit@123']
KARAN = ['1', 'karan.negi@spitiexpeditions.in', 'karan@123']
SNEHA = ['1', 'sneha.iyer@trekmate.in', 'sneha@123']
VIKRAM = ['1', 'vikram.mehta@trekmate.in', 'vikram@123']
CARD = ['4111111111111111', '12/28']

def book(trip, seats):            # traveler menu -> book with a good card
    return ['4', trip, str(seats)] + CARD

TESTS = [
 # id, title, inputs, expected (in order), must NOT appear
 ("TC-01", "Log in with the right email and password",
  AARAV + ['0', '0'], ["Welcome, Aarav Sharma (Traveler)", "TRAVELER MENU"], []),
 ("TC-02", "Log in with a wrong password",
  ['1', 'aarav.sharma@gmail.com', 'wrongpass', '0'], ["Wrong email or password."], ["TRAVELER MENU"]),
 ("TC-03", "Register a new traveler, then log in",
  ['2', 'Riya Kapoor', 'riya.kapoor@gmail.com', 'riya1234', '+91-90000-11111', '2002-05-10', 'A+', '1',
   'Anil Kapoor', '+91-90000-22222', '1', 'riya.kapoor@gmail.com', 'riya1234', '0', '0'],
  ["Registered! Your user ID is U-5001", "Welcome, Riya Kapoor (Traveler)"], []),
 ("TC-04", "Register with an email that is already used",
  ['2', 'Test User', 'aarav.sharma@gmail.com', 'abcd1234', '123', '2000-01-01', 'O+', '0', 'x', 'y', '0'],
  ["Not registered: This email is already registered."], ["Registered!"]),
 ("TC-05", "Register with a wrong date of birth",
  ['2', 'Test User', 'test.user@gmail.com', 'abcd1234', '123', '10-05-2002', 'O+', '0', 'x', 'y', '0'],
  ["Not registered: Date of birth must look like YYYY-MM-DD."], ["Registered!"]),
 ("TC-06", "Each kind of user gets its own menu",
  ROHIT + ['0'] + SNEHA + ['0'] + VIKRAM + ['0'] + KARAN + ['0', '0'],
  ["PROVIDER MENU (Himalayan Trails Pvt Ltd)", "ADMIN MENU (Sneha Iyer)", "SUPER ADMIN MENU (Vikram Mehta)",
   "Karan Negi: you are a traveler AND a provider"], []),
 ("TC-07", "Browse shows the open trips",
  AARAV + ['1', '0', '0'], ["TRP-1 | Rishikesh River Rafting", "TRP-6 | Spiti Valley Winter Expedition"], []),
 ("TC-08", "Search ignores capital letters",
  AARAV + ['2', 'MANALI', '0', '0'], ["TRP-2 | Hampta Pass Trek | Manali"], ["TRP-1 |", "TRP-3 |"]),
 ("TC-09", "Search with no result",
  AARAV + ['2', 'goa', '0', '0'], ["No trips found for 'goa'."], []),
 ("TC-10", "See trip details; unknown trip ID",
  AARAV + ['3', 'TRP-4', '3', 'TRP-99', '0', '0'],
  ["Title     : Chadar Frozen River Trek", "No trip with that ID."], []),
 ("TC-11", "UC-01 main flow: book 2 seats",
  AARAV + book('TRP-2', 2) + ['1', '0', '0'],
  ["Total to pay: Rs. 9000", "[Email to aarav.sharma@gmail.com] Booking BK-1 confirmed for Hampta Pass Trek",
   "Status     : CONFIRMED", "RECEIPT", "Paid    : Rs. 9000", "TRP-2 | Hampta Pass Trek", "seats left 18"], []),
 ("TC-12", "UC-01 4a: more seats than are left",
  AARAV + ['4', 'TRP-5', '8', '0', '0'], ["Only 6 seat(s) left. Enter a smaller number."], ["Total to pay"]),
 ("TC-13", "Rule by user type: Traveler max 6, TravelerProvider max 15",
  AARAV + ['4', 'TRP-2', '7', '0'] + KARAN + ['1'] + book('TRP-2', 7) + ['0', '0', '0'],
  ["A Traveler can book at most 6 seats at once.", "Booking BK-1 confirmed", "Seats      : 7"], []),
 ("TC-14", "UC-01 6a: payment fails (bad card)",
  AARAV + ['4', 'TRP-2', '2', '1234', '12/28', '1', '0', '0'],
  ["Payment failed. Nothing saved, seats unchanged.", "seats left 20"], ["BK-1"]),
 ("TC-15", "UC-01: zero seats",
  AARAV + ['4', 'TRP-2', '0', '0', '0'], ["Number of seats must be at least 1."], ["Total to pay"]),
 ("TC-16", "Letters typed instead of a number",
  ['abc', '1', 'aarav.sharma@gmail.com', 'aarav@123', 'two', '0', '0'],
  ["Please type a whole number.", "Welcome, Aarav Sharma", "Please type a whole number."], []),
 ("TC-17", "UC-02 main flow: cancel my booking",
  AARAV + book('TRP-2', 2) + ['5', 'BK-1', 'y', '1', '0', '0'],
  ["Cancel BK-1 for Hampta Pass Trek? (y/n)", "Booking BK-1 cancelled. Refund done.", "seats left 20"], []),
 ("TC-18", "UC-02 3a: traveler changes their mind",
  AARAV + book('TRP-2', 2) + ['5', 'BK-1', 'n', '0', '0'],
  ["Nothing changed. BK-1 is still CONFIRMED."], ["cancelled"]),
 ("TC-19", "UC-02: cannot cancel someone else's booking",
  KARAN + ['1'] + book('TRP-2', 1) + ['0', '0'] + AARAV + ['5', 'BK-1', '0', '0'],
  ["Booking BK-1 confirmed", "You have no booking with that ID."], ["cancelled"]),
 ("TC-20", "UC-02 1a: cancel after the trip date",
  AARAV + book('TRP-1', 1) + ['0'] + SNEHA + ['7', '2', '2026-10-26', '0']
  + AARAV + ['5', 'BK-1', 'y', '0', '0'],
  ["Booking BK-1 confirmed for Rishikesh River Rafting", "Today is now 2026-10-26.",
   "Trip date has passed. BK-1 cannot be cancelled."], []),
 ("TC-21", "UC-02 5a: refund fails, admin settles it later",
  AARAV + book('TRP-2', 2) + ['0'] + SNEHA + ['7', '1', '0'] + AARAV + ['5', 'BK-1', 'y', '0']
  + SNEHA + ['7', '1', '6', '0', '0'],
  ["Payment gateway failure is now ON.", "Booking BK-1 cancelled. Refund PENDING, admin will settle it.",
   "Payment gateway failure is now OFF.", "Refund for PAY-1 is now REFUNDED."], []),
 ("TC-22", "My bookings: all, or only confirmed (default argument)",
  AARAV + book('TRP-2', 1) + book('TRP-3', 1) + ['5', 'BK-1', 'y', '6', 'n', '6', 'y', '0', '0'],
  ["Aarav Sharma's bookings:", "BK-1 | Hampta Pass Trek | seats 1 | CANCELLED", "BK-2 | Kedarkantha Winter Trek | seats 1 | CONFIRMED",
   "Aarav Sharma's CONFIRMED bookings:", "BK-2 | Kedarkantha"], []),
 ("TC-23", "UC-03: provider creates a valid trip",
  ROHIT + ['2', 'Valley of Flowers Trek', 'Chamoli, Uttarakhand', '7000', '2027-07-15', '2027-07-20', '12', '12', '1', '1', '0']
  + AARAV + ['2', 'flowers', '0', '0'],
  ["Saved! TRP-7 is now live for travelers.", "TRP-7 | Valley of Flowers Trek | Chamoli"], []),
 ("TC-24", "UC-03 4a: wrong trip details are not saved",
  ROHIT + ['2', 'Free Trek', 'Somewhere', '0', '2027-01-01', '2027-01-02', '5', '10', '0']
  + ['2', 'Old Trek', 'Somewhere', '1000', '2026-01-01', '2026-01-02', '5', '10', '0']
  + ['2', '', 'Somewhere', '1000', '2027-01-01', '2027-01-02', '5', '10', '0', '0', '0'],
  ["Not saved: Price must be above 0.", "Not saved: Start date must be in the future.",
   "Not saved: Trip name and place can not be empty."], ["Saved!"]),
 ("TC-25", "UC-03 3a: edit a booked trip -> warning -> travelers emailed",
  AARAV + book('TRP-2', 2) + ['0'] + ROHIT + ['3', 'TRP-2', '1', '5000', 'n', '3', 'TRP-2', '1', '5000', 'y', '0', '0'],
  ["Warning: this trip has 1 confirmed booking(s).", "Nothing changed.", "Saved.",
   "[Email to aarav.sharma@gmail.com] Hampta Pass Trek: the price is now Rs. 5000 per seat"], []),
 ("TC-26", "UC-03 2a: remove a trip with bookings / without bookings",
  AARAV + book('TRP-2', 2) + ['0'] + ROHIT + ['4', 'TRP-2', 'y', '4', 'TRP-3', 'y', '0'] + AARAV + ['1', '0', '0'],
  ["Cannot remove 'Hampta Pass Trek': it has confirmed bookings.", "'Kedarkantha Winter Trek' removed (status CLOSED).",
   "Open trips:"], ["TRP-3 | Kedarkantha"]),
 ("TC-27", "A provider cannot change another provider's trip",
  ROHIT + ['3', 'TRP-5', '4', 'TRP-6', '0', '0'], ["You have no trip with that ID.", "You have no trip with that ID."], []),
 ("TC-28", "View Trip Bookings: provider sees who booked",
  AARAV + book('TRP-2', 2) + ['0'] + ROHIT + ['5', 'TRP-2', '5', 'TRP-4', '0', '0'],
  ["Bookings for Hampta Pass Trek:", "BK-1 | Aarav Sharma | aarav.sharma@gmail.com | seats 2 | CONFIRMED",
   "No bookings for Chadar Frozen River Trek yet."], []),
 ("TC-29", "Admin: all users and search users",
  SNEHA + ['1', '2', 'negi', '0', '0'],
  ["U-1000 | Vikram Mehta", "U-2031 | Aarav Sharma", "U-3050 | Karan Negi | karan.negi@spitiexpeditions.in | Traveler + AdventureProvider"],
  []),
 ("TC-30", "Admin: trip report and all bookings",
  AARAV + book('TRP-2', 2) + ['0'] + SNEHA + ['4', '3', '0', '0'],
  ["TRP-2 | Hampta Pass Trek | PUBLISHED | seats sold 2 of 20 | money collected Rs. 9000",
   "BK-1 | Aarav Sharma | Hampta Pass Trek | seats 2 | CONFIRMED | payment SUCCESS"], []),
 ("TC-31", "Admin cannot remove a booked trip (friend class shows seat count)",
  AARAV + book('TRP-2', 2) + ['0'] + SNEHA + ['5', 'TRP-2', '5', 'TRP-5', '0', '0'],
  ["Cannot remove 'Hampta Pass Trek': 2 seat(s) are booked.", "'Bir Billing Paragliding' removed (status CLOSED)."], []),
 ("TC-32", "Super admin: stats need the password again",
  VIKRAM + ['2', 'wrong', '2', 'vikram@123', '0', '0'],
  ["Wrong password. Stats not shown.", "TrekMate Pvt Ltd - system stats:", "Users alive    : 5"], []),
 ("TC-33", "Update my profile",
  AARAV + ['7', 'y', '', '+91-11111-22222', '7', 'n', '0', '0'],
  ["Profile saved.", "Name    : Aarav Sharma", "Phone   : +91-11111-22222"], []),
]

def run(inputs):
    p = subprocess.run([APP], input="\n".join(inputs) + "\n", capture_output=True, text=True, timeout=60)
    return p.returncode, p.stdout

failed = 0
for tid, title, inputs, expected, forbidden in TESTS:
    code, out = run(inputs)
    pos, problems = 0, []
    for e in expected:
        i = out.find(e, pos)
        if i < 0: problems.append("missing: " + e)
        else: pos = i + len(e)
    for f in forbidden:
        if f in out: problems.append("should not appear: " + f)
    if code != 0: problems.append("exit code %d" % code)
    if not out.rstrip().endswith("Goodbye!"): problems.append("did not end cleanly")
    status = "PASS" if not problems else "FAIL"
    if problems: failed += 1
    print(f"{tid}  {status}  {title}" + ("" if not problems else "\n      " + "\n      ".join(problems)))
print(f"\n{len(TESTS) - failed} of {len(TESTS)} passed")
sys.exit(1 if failed else 0)
