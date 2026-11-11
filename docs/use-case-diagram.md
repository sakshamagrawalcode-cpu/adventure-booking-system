# Use case diagram

Who can do what. Each actor uses its own program (`customer.cpp`, `provider.cpp`, `admin.cpp`).
The box is the system; each rounded box is one use case. The diagram is drawn in three
parts, one per actor, so that no lines cross.

![Use case diagram](use-case-diagram.png)

The picture above is made from the Mermaid code below. If you change the code, the picture must be made again.

## Customer

```mermaid
flowchart LR
    actor["👤 Customer"]

    subgraph system["Adventure Booking System — Customer"]
        login(["Login / Logout"])
        viewAdv(["View adventures"])
        book(["Book an adventure"])
        myBookings(["View my bookings"])
        cancelOwn(["Cancel own booking"])
        profile(["View / edit own profile"])
        checks(["Check seats and ages"])
    end

    actor --- login
    actor --- viewAdv
    actor --- book
    actor --- myBookings
    actor --- cancelOwn
    actor --- profile
    book -.->|"«include»"| checks

    classDef actorStyle fill:none,stroke:none,font-size:18px
    class actor actorStyle
```

## Provider

```mermaid
flowchart LR
    actor["👤 Provider"]

    subgraph system["Adventure Booking System — Provider"]
        login(["Login / Logout"])
        myAdv(["View my adventures"])
        addAdv(["Add adventure"])
        editAdv(["Edit adventure"])
        bookers(["See who booked"])
        profile(["View own profile"])
    end

    actor --- login
    actor --- myAdv
    actor --- addAdv
    actor --- editAdv
    actor --- bookers
    actor --- profile

    classDef actorStyle fill:none,stroke:none,font-size:18px
    class actor actorStyle
```

## Admin

```mermaid
flowchart LR
    actor["👤 Admin"]

    subgraph system["Adventure Booking System — Admin"]
        login(["Login / Logout"])
        allUsers(["View all customers and providers"])
        search(["Search users by name"])
        allBookings(["View all bookings"])
        seats(["View seats left"])
        cancelAny(["Cancel any booking"])
        editUser(["Edit any user"])
        password(["Change any password"])
    end

    actor --- login
    actor --- allUsers
    actor --- search
    actor --- allBookings
    actor --- seats
    actor --- cancelAny
    actor --- editUser
    actor --- password

    classDef actorStyle fill:none,stroke:none,font-size:18px
    class actor actorStyle
```

**How to read it**
- A plain line means the actor can use that use case.
- `«include»` means "Book an adventure" always runs "Check seats and ages" as part of it.
- All three parts are the same system: the three programs share the same data files.
