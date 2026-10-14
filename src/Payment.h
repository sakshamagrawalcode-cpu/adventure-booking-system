// =====================================================================
//  Payment.h  -  one payment (or refund) for a booking
// =====================================================================
//  Lives inside a Booking. Talks to the PaymentGateway.
//
//  OOP topics in this file:
//    [this pointer]  [Static data member]  [Static member function]
//    [Default arguments in constructor]  Payment(double amount, string timestamp = "N/A")
//    [Data conversion: basic -> class]   Payment p = 2000.0;
//    [Data conversion: class -> basic]   double d = p;
//    [Friend function]  [Stream operator overloading]
// =====================================================================
#ifndef PAYMENT_H
#define PAYMENT_H

#include "PaymentGateway.h"

class Payment {
private:
    string paymentId;
    double amount;
    PaymentStatus status;
    string timestamp;

    // [Static data member] counts payment attempts; also used to make the payment ID
    static int paymentCount;

public:
    // [Default arguments in constructor] timestamp can be left out.
    // [Data conversion: basic -> class] because this constructor can be called
    // with ONE double, a double can be turned into a Payment:
    //     Payment p = 2000.0;
    Payment(double amount, string timestamp = "N/A") {
        // [this pointer] same names for parameter and data member
        this->amount = amount;
        this->timestamp = timestamp;
        this->status = FAILED;   // counts as unpaid until the gateway says SUCCESS

        paymentCount++;
        paymentId = "PAY-" + to_string(paymentCount);
    }

    // [Data conversion: class -> basic] a Payment can be used as a double
    // (its amount):     double d = p;
    operator double() const {
        return amount;
    }

    // UC-01 steps 5-6. Card details are only passed to the gateway, never stored.
    PaymentStatus processPayment(const PaymentGateway& gateway,
                                 const string& cardNo, const string& expiry) {
        if (!gateway.validateDetails(cardNo, expiry)) {
            status = FAILED;
        } else {
            status = gateway.processTransaction(amount);
        }
        return status;
    }

    // UC-02 step 5 (refund) and 5a (refund fails -> PENDING).
    // The admin calls this again later to settle a PENDING refund.
    PaymentStatus processRefund(const PaymentGateway& gateway) {
        if (status != SUCCESS && status != PENDING) return status;   // nothing to refund

        if (gateway.processRefund(amount) == SUCCESS) status = REFUNDED;
        else status = PENDING;
        return status;
    }

    PaymentStatus getStatus() const { return status; }
    string getPaymentId() const { return paymentId; }
    double getAmount() const { return amount; }

    // [Static member function]
    static int getPaymentCount() { return paymentCount; }

    // [Friend function] + [Stream operator overloading]
    friend ostream& operator<<(ostream& out, const Payment& p);
};

inline int Payment::paymentCount = 0;

inline ostream& operator<<(ostream& out, const Payment& p) {
    out << p.paymentId << " | Rs. " << p.amount << " | " << toString(p.status)
        << " | " << p.timestamp;
    return out;
}

#endif
