# Class diagram

All classes in `src/` and how they connect. Plain getters and setters are left out
to keep the diagram readable.

![Class diagram](class-diagram.png)

The picture above is made from the Mermaid code below. If you change the code, the picture must be made again.

```mermaid
classDiagram
    class User {
        <<abstract>>
        -string id
        -string name
        -string email
        -string password
        -getPassword() string
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
        +Adventure(id, ..., totalSeats)
        +Adventure(id, ..., totalSeats, seatsLeft)
        +isAgeAllowed(age) bool
        +bookSeats(n)
        +releaseSeats(n)
        +operator<<(out, adventure) ostream
    }

    class Ticket {
        <<struct>>
        +string name
        +int age
    }

    class Booking {
        +int MAX_TICKETS$
        -string id
        -string customerId
        -string adventureId
        -vector~Ticket~ tickets
        -int totalPrice
        -string status
        +Booking(id, customerId, adventureId, tickets, totalPrice)
        +Booking(other)
        +operator=(other) Booking
        +getTicketCount() int
        +isCancelled() bool
        +cancel()
        +operator<<(out, booking) ostream
    }

    class BookingSystem {
        -vector~Customer~ customers
        -vector~Provider~ providers
        -vector~Admin~ admins
        -vector~Adventure~ adventures
        -vector~Booking~ bookings
        -string dataFolder
        -load()
        -save()
        -loadSampleData()
        -isValidEmail(email) bool$
        -isValidMobile(mobile) bool$
        -isValidDate(date) bool$
        +loginCustomer(email, password) Customer
        +loginProvider(email, password) Provider
        +loginAdmin(email, password) Admin
        +getAdventures() vector~Adventure~
        +addAdventure(...)
        +updateAdventure(...)
        +book(customerId, adventureId, tickets) Booking
        +getBookingsOfCustomer(customerId, onlyActive = false) vector~Booking~
        +cancelBooking(bookingId)
        +cancelBooking(bookingId, customerId)
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
    BookingSystem ..> User : friend

    Booking "*" --> "1" Customer : customerId
    Booking "*" --> "1" Adventure : adventureId
    Adventure "*" --> "1" Provider : providerId
```

**How to read it**
- `-` is private, `+` is public.
- *Italic* functions are pure virtual (`= 0`): each child class must write its own.
- Underlined members are `static`: one for the whole class, not one per object.
- Empty triangle arrow = inheritance: Customer, Provider and Admin are a `User`.
- Filled diamond = composition: the owner holds the objects (`BookingSystem` holds all
  users, adventures and bookings; a `Booking` holds its `Ticket`s).
- Plain arrow = a link by ID: a `Booking` stores its customer's ID and its adventure's ID,
  and an `Adventure` stores its provider's ID.
- Dashed arrow «friend» = `BookingSystem` is a friend class of `User`, so it can call the
  private `getPassword()` to save the password in the data file.
- `operator<<` is a friend function, not a member; it is listed in the class it prints.
- Two lines with the same name (the `Adventure` constructors, `cancelBooking`) are
  overloaded functions.
- `customer.cpp`, `provider.cpp` and `admin.cpp` are not classes. They show the menus and
  call `BookingSystem` functions.
