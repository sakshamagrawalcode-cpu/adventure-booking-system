# Class Design and Responsibilities

## 1. Class: User
| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Store basic credentials (userId, name, email, password) | — |
| 2. Authenticate user during login | — |
| 3. Update profile and contact details | — |

## 2. Class: Traveler
| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Maintain emergency contact and medical/fitness details | — |
| 2. Search and browse available trips | Trip |
| 3. Initiate booking and trigger payment process | Booking, Payment |
| 4. View personal booking history and status | Booking |

## 3. Class: AdventureProvider
| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Maintain agency license and certification details | — |
| 2. Create, update, and publish adventure trip packages | Trip |
| 3. View bookings and passenger manifests for hosted trip | Booking, Trip |

## 4. Class: Admin
| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Review and approve adventure providers and trips | AdventureProvider, Trip |
| 2. Monitor overall system users and active bookings | User, Booking |
| 3. Track platform commissions and overall revenue | Payment |

## 5. Class: Trip
| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Store trip details (title, location, price, dates, maxCapacity) | AdventureProvider |
| 2. Calculate and update remaining available slots | Booking |
| 3. Enforce participant requirements (minimum age, gear, fitness level) | Traveler |

## 6. Class: Booking
| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Maintain reservation lifecycle status (PENDING, CONFIRMED, CANCELLED) | — |
| 2. Calculate total cost (Trip.price × number of participants) | Trip |
| 3. Reserve or release trip slots based on payment outcome | Trip |
| 4. Generate booking confirmation and itinerary summary | Traveler, Payment |

## 7. Class: Payment
| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Store transaction details (paymentId, amount, status, timestamp) | Booking |
| 2. Initiate and verify transaction requests with the payment processor | PaymentGateway |
| 3. Process refund requests upon booking cancellation | PaymentGateway, Booking |

## 8. Class: PaymentGateway
| Responsibilities | Collaborators |
| :--- | :--- |
| 1. Connect to external banking and card/UPI processing networks | — |
| 2. Validate payment credentials and authorize fund transfer | Payment |
| 3. Return transaction status (SUCCESS / FAILED) | Payment |

---

## Note on Inheritance & Design Rationale

### 1. Inheritance Hierarchy (Who is the parent?)
*   **Parent Class (Base):** User
*   **Child Classes (Derived):** Traveler, AdventureProvider, and Admin

### 2. Why is User Designed as the Parent Class?
*   **Avoids Code Redundancy (DRY Principle):** All three user roles share core account properties (e.g., name, email, password, authentication logic). Grouping these common properties inside the User class prevents duplicating identical fields across multiple classes.
*   **Unified Authentication:** The security and login service can process credentials polymorphically for any actor simply as an instance of User.
*   **System Extensibility:** If new roles are added later (e.g., TourGuide, SafetyAuditor), they can extend User directly without modifying the existing authentication architecture.
