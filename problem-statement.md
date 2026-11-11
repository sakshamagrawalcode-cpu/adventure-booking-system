# Problem Statement — Adventure Booking System

---

Booking an adventure trip today still runs on phone calls.

Say I want to join a river rafting trip this Sunday. I have to find the organiser's number, call him, and ask if seats are left. He checks a notebook or an Excel sheet and says yes. I send the money on UPI and hope my name actually gets written down somewhere. There is no ticket and no confirmation. A week later I am not even sure my seat exists. If my plan changes, I call again, ask him to remove my name, and again just hope it happened.

The organisers are not doing any better. A small trekking or rafting company takes bookings over WhatsApp and phone calls all day. The same questions come again and again — is Sunday free, how many seats are left, can my 12-year-old come. The seat list lives in a notebook, so when two people book at the same time, both get told "confirmed" and one of them ends up standing at the pickup point with no seat. Nobody checks ages until the group reaches the spot, and someone who is too young has to be sent back.

And when many organisers sell trips on one platform, somebody has to watch over all of it. A wrong phone number, a booking that has to be cancelled, a forgotten password — right now there is no single place from where such things can be fixed.

## What we are going to build

A booking system with three kinds of users. Each one has its own program and logs in with an email and a password.

A **customer** sees the list of adventures and opens one to see the place, date, difficulty, minimum age, price and seats left. They book tickets for themselves and their friends by giving each person's name and age. The system checks that enough seats are left and that every person meets the minimum age, then shows the total price. Their bookings stay visible in the app, and cancelling one frees the seats at once with a full refund. They can also see and edit their profile.

An **adventure provider** puts up their own adventures — name, place, description, difficulty, minimum age, date, price and seats. They can edit an adventure later (everything except the seats) and see who has booked it, with each customer's name, gender, mobile number and email.

An **admin** sees every customer, provider, booking and seat count in one place. The admin can search users by name, cancel any booking, edit anyone's details and set a new password for anyone.

## What this version does not have

This is a console program in C++. It keeps its data in simple text files instead of a database; the three programs share these files, so a booking made by a customer shows up at once for the provider and the admin. There is no real payment, no email and no sign-up. These can come in a later version.

## The outcome

Nobody calls anybody. A customer books in two minutes and sees the booking in their list. A provider sees the true seat count of every adventure they run and knows who is coming. Seats are never sold twice, and nobody below the minimum age gets booked. The admin steps in only when needed.
