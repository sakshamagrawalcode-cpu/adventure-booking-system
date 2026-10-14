#ifndef PAYMENT_H
#define PAYMENT_H

#include "PaymentGateway.h"

class Payment {
private:
    string paymentId;
    double amount;
    PaymentStatus status;
    string timestamp;

    // [Static variable] counts payment attempts, also used to generate paymentId
    static int paymentCount;

public:
    Payment(double amount, string timestamp) {
        // [this pointer] same names for parameter and data member
        this->amount = amount;
        this->timestamp = timestamp;
        this->status = FAILED;   // counts as unpaid until the gateway says SUCCESS

        paymentCount++;
        paymentId = "PAY-" + to_string(paymentCount);
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
    // Admin calls this again later to settle a PENDING refund.
    PaymentStatus processRefund(const PaymentGateway& gateway) {
        if (status != SUCCESS && status != PENDING) return status;   // nothing to refund

        if (gateway.processRefund(amount) == SUCCESS) status = REFUNDED;
        else status = PENDING;
        return status;
    }

    PaymentStatus getStatus() const { return status; }
    string getPaymentId() const { return paymentId; }
    double getAmount() const { return amount; }

    // [Static function]
    static int getPaymentCount() {
        return paymentCount;
    }

    // [Stream operator overloading using friend function]
    friend ostream& operator<<(ostream& out, const Payment& p);
};

int Payment::paymentCount = 0;

inline ostream& operator<<(ostream& out, const Payment& p) {
    out << p.paymentId << " | Rs. " << p.amount << " | " << toString(p.status)
        << " | " << p.timestamp;
    return out;
}

#endif
