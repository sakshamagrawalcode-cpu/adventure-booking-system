# Use case diagram

Who can do what. Each actor uses its own program (`customer.cpp`, `provider.cpp`, `admin.cpp`).
The big box is the system; each rounded box is one use case.

```mermaid
flowchart LR
    customer["👤 Customer"]
    provider["👤 Provider"]
    admin["👤 Admin"]

    subgraph system["Adventure Booking System"]
        login(["Login / Logout"])

        viewAdv(["View adventures"])
        book(["Book an adventure"])
        checks(["Check seats and ages"])
        myBookings(["View my bookings"])
        cancelOwn(["Cancel own booking"])
        custProfile(["View / edit own profile"])

        myAdv(["View my adventures"])
        addAdv(["Add adventure"])
        editAdv(["Edit adventure"])
        bookers(["See who booked"])
        provProfile(["View own profile"])

        allUsers(["View all customers and providers"])
        search(["Search users by name"])
        allBookings(["View all bookings"])
        seats(["View seats left"])
        cancelAny(["Cancel any booking"])
        editUser(["Edit any user"])
        password(["Change any password"])
    end

    customer --- login
    customer --- viewAdv
    customer --- book
    customer --- myBookings
    customer --- cancelOwn
    customer --- custProfile
    book -.->|"«include»"| checks

    provider --- login
    provider --- myAdv
    provider --- addAdv
    provider --- editAdv
    provider --- bookers
    provider --- provProfile

    admin --- login
    admin --- allUsers
    admin --- search
    admin --- allBookings
    admin --- seats
    admin --- cancelAny
    admin --- editUser
    admin --- password

    classDef actor fill:none,stroke:none,font-size:18px
    class customer,provider,admin actor
```

**How to read it**
- A plain line means the actor can use that use case.
- `«include»` means "Book an adventure" always runs "Check seats and ages" as part of it.
