# Class diagram

All classes in `src/` and how they connect. Plain getters and setters are left out
to keep the diagram readable.

```mermaid
classDiagram
    class User {
        <<abstract>>
        -string id
        -string name
        -string email
        -string password
        +User(id, name, email, password)
        +setPassword(password)
        +checkPassword(input) bool
        +getRole() string*
        +showProfile()*
    }

    class Customer {
        -string gender
        -int age
        -string mobile
        +getRole() string
        +showProfile()
    }

    class Provider {
        -string mobile
        -string companyName
        +getRole() string
        +showProfile()
    }

    class Admin {
        +getRole() string
        +showProfile()
    }

    class Adventure {
        -string id
        -string providerId
        -string name
        -string location
        -string description
        -string difficulty
        -int minAge
        -string date
        -int price
        -int totalSeats
        -int seatsLeft
        +isAgeAllowed(age) bool
        +bookSeats(n)
        +releaseSeats(n)
        +show()
    }

    class Ticket {
        <<struct>>
        +string name
        +int age
    }

    class Booking {
        -string id
        -string customerId
        -string adventureId
        -vector~Ticket~ tickets
        -int totalPrice
        -string status
        +getTicketCount() int
        +isCancelled() bool
        +cancel()
        +show()
    }

    class BookingSystem {
        -vector~Customer~ customers
        -vector~Provider~ providers
        -vector~Admin~ admins
        -vector~Adventure~ adventures
        -vector~Booking~ bookings
        -loadSampleData()
        +loginCustomer(email, password) Customer
        +loginProvider(email, password) Provider
        +loginAdmin(email, password) Admin
        +getAdventures() vector~Adventure~
        +addAdventure(...)
        +updateAdventure(...)
        +book(customerId, adventureId, tickets) Booking
        +cancelBooking(bookingId)
        +updateCustomer(...)
        +updateProvider(...)
        +changePassword(userId, newPassword)
        +searchUsers(text) vector~User*~
    }

    User <|-- Customer
    User <|-- Provider
    User <|-- Admin

    Booking "1" *-- "1..*" Ticket : contains
    BookingSystem "1" *-- "*" Customer : owns
    BookingSystem "1" *-- "*" Provider : owns
    BookingSystem "1" *-- "*" Admin : owns
    BookingSystem "1" *-- "*" Adventure : owns
    BookingSystem "1" *-- "*" Booking : owns

    Booking "*" --> "1" Customer : customerId
    Booking "*" --> "1" Adventure : adventureId
    Adventure "*" --> "1" Provider : providerId
```

**How to read it**
- `-` is private, `+` is public.
- *Italic* functions are pure virtual (`= 0`): each child class must write its own.
- Empty triangle arrow = inheritance: Customer, Provider and Admin are a `User`.
- Filled diamond = composition: the owner holds the objects (`BookingSystem` holds all
  users, adventures and bookings; a `Booking` holds its `Ticket`s).
- Plain arrow = a link by ID: a `Booking` stores its customer's ID and its adventure's ID,
  and an `Adventure` stores its provider's ID.
- `customer.cpp`, `provider.cpp` and `admin.cpp` are not classes. They show the menus and
  call `BookingSystem` functions.
