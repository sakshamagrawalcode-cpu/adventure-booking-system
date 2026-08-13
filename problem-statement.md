# Problem Statement — Adventure Booking System

---

Booking an adventure trip today still runs on phone calls.

Say I want to join a river rafting trip this Sunday. I have to find the organiser's number, call him, and ask if seats are left. He checks a notebook or an Excel sheet and says yes. I send the money on UPI and hope my name actually gets written down somewhere. There is no ticket and no confirmation. A week later I am not even sure my seat exists. If my plan changes, I call again, ask him to remove my name, and again just hope it happened.

The organisers are not doing any better. A small trekking or rafting company takes bookings over WhatsApp and phone calls all day. The same questions come again and again — is Sunday free, how many seats are left. The seat list lives in a notebook, so when two people pay at the same time, both get told "confirmed" and one of them ends up standing at the pickup point with no seat. There is no clean record of who paid and who did not, and people who book but never show up keep blocking seats that someone else wanted.

And when many organisers sell trips on one platform, somebody has to watch over all of it. A wrong price, a fake listing, a customer complaint — right now there is no single place from where such things can be fixed.

## What we are going to build

A booking app with three kinds of users.

A **traveler** makes an account, browses the list of adventures, opens one to see the place, date, price and seats left, books the seats they want, and pays through a payment gateway. A confirmation email goes out automatically. Their bookings stay visible inside the app, and cancelling one frees the seat immediately.

An **adventure provider** logs in and puts up their own trips — name, place, date, price and total seats. They can edit or remove a trip, and can see exactly who has booked it. The seat count goes down and up on its own as people book and cancel.

An **admin** can see every user, listing and booking in one place, and can correct or remove anything when something goes wrong.

## The outcome

Nobody calls anybody. A traveler books and pays in two minutes and has an email to prove it. A provider opens the app and sees the true seat count of every trip they run. The admin steps in only when needed. One list, in one database, updated the moment anything changes.
