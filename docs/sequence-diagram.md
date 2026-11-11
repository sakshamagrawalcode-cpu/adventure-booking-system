# Sequence diagram: booking an adventure

What happens, step by step, when a customer books an adventure in `customer.cpp`.
Time goes from top to bottom.

![Sequence diagram](sequence-diagram.png)

The picture above is made from the Mermaid code below. If you change the code, the picture must be made again.

```mermaid
sequenceDiagram
    actor C as Customer
    participant P as customer.cpp
    participant S as BookingSystem
    participant A as Adventure
    participant B as Booking

    C->>P: Choose "Show adventures"
    P->>S: getAdventures()
    S-->>P: list of adventures
    P-->>C: numbered list
    C->>P: Pick an adventure, then "Book this? 1"
    P-->>C: Ask how many tickets, then name and age of each person
    C->>P: tickets
    P->>S: book(customerId, adventureId, tickets)
    S->>S: load() - read the latest data files

    loop for each ticket
        S->>A: isAgeAllowed(age)
        A-->>S: true or false
    end

    alt someone is too young
        S-->>P: throw runtime_error (below the minimum age)
        P-->>C: Booking failed - Arjun Rao is below the minimum age 18
    else everyone is old enough
        S->>A: bookSeats(number of tickets)
        alt not enough seats
            A-->>S: throw runtime_error (Only 2 seats left)
            S-->>P: the error passes up to the menu
            P-->>C: Booking failed - Only 2 seats left
        else seats taken
            S->>B: create Booking (status BOOKED)
            S->>S: save() - write the data files
            S-->>P: the new booking
            P-->>C: Booked! Total - Rs. 3000
        end
    end
```

**How to read it**
- Solid arrow = a function call. Dashed arrow = the answer coming back.
- `loop` = repeated for each ticket.
- `alt` / `else` = only one of the boxes happens, depending on the condition.
- `load()` and `save()` are how the three programs share data: the booking is in the
  files right away, so the provider and admin programs see it.
- The two errors are `runtime_error`s thrown by `BookingSystem` and `Adventure`,
  and caught by the `try` / `catch` in `bookScreen()` in `customer.cpp`.
