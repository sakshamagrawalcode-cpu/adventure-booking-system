# Object diagram

The objects in memory right after a program reads the sample data: the booking made by
Rahul for the Kedarkantha trek, and the objects linked to it.
Each box is one object, written as `objectName : ClassName`, with the values of its data.
(Only the objects in this one booking are shown; the rest of the sample data is left out.)

![Object diagram](object-diagram.png)

The picture above is made from the Mermaid code below. If you change the code, the picture must be made again.

```mermaid
classDiagram
    class app["app : BookingSystem"]
    app : dataFolder = ../data/
    app : customers = 3 Customer objects
    app : providers = 2 Provider objects
    app : admins = 1 Admin object
    app : adventures = 4 Adventure objects
    app : bookings = 1 Booking object

    class rahul["rahul : Customer"]
    rahul : id = C1
    rahul : name = Rahul Mehta
    rahul : email = rahul@example.com
    rahul : gender = Male
    rahul : age = 20
    rahul : mobile = 9123400001

    class amit["amit : Provider"]
    amit : id = P1
    amit : name = Amit Sharma
    amit : email = amit@example.com
    amit : mobile = 9876500001
    amit : companyName = Himalayan Treks

    class kedarkantha["kedarkantha : Adventure"]
    kedarkantha : id = A1
    kedarkantha : providerId = P1
    kedarkantha : name = Kedarkantha Winter Trek
    kedarkantha : date = 20-12-2026
    kedarkantha : minAge = 12
    kedarkantha : price = 9500
    kedarkantha : totalSeats = 10
    kedarkantha : seatsLeft = 8

    class booking["booking : Booking"]
    booking : id = B5
    booking : customerId = C1
    booking : adventureId = A1
    booking : totalPrice = 19000
    booking : status = BOOKED

    class ticket1["ticket1 : Ticket"]
    ticket1 : name = Rahul Mehta
    ticket1 : age = 20

    class ticket2["ticket2 : Ticket"]
    ticket2 : name = Aman Mehta
    ticket2 : age = 24

    app *-- rahul
    app *-- amit
    app *-- kedarkantha
    app *-- booking
    booking *-- ticket1
    booking *-- ticket2
    booking --> rahul : customerId
    booking --> kedarkantha : adventureId
    kedarkantha --> amit : providerId
```

**How to read it**
- `seatsLeft = 8`: the trek has 10 seats and this booking took 2 (one per ticket).
- `totalPrice = 19000`: 2 tickets × Rs. 9500.
- The booking does not store the customer or adventure object itself, only their IDs
  (`C1`, `A1`). The arrows show which object each ID points to.
- Filled diamond = the object on the diamond side holds the other one inside it.
