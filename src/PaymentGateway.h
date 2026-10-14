#ifndef PAYMENTGATEWAY_H
#define PAYMENTGATEWAY_H

#include <iostream>
#include <string>
using namespace std;

// Kept here (not in Payment.h) because the gateway returns it,
// and Payment already includes this file.
// PENDING = refund failed, waiting for admin to settle it (UC-02 5a)
enum PaymentStatus { SUCCESS, FAILED, PENDING, REFUNDED };

inline string toString(PaymentStatus s) {
    if (s == SUCCESS) return "SUCCESS";
    if (s == FAILED) return "FAILED";
    if (s == PENDING) return "PENDING";
    return "REFUNDED";
}

// Simulated gateway: no real bank is contacted.
// failMode lets us make payments/refunds fail on purpose (to test UC-01 6a, UC-02 5a).
class PaymentGateway {
private:
    string gatewayName;
    bool failMode;

public:
    PaymentGateway(string gatewayName) {
        // [this pointer] parameter has the same name as the data member,
        // so this->gatewayName means "the member of this object"
        this->gatewayName = gatewayName;
        this->failMode = false;
    }

    void setFailMode(bool failMode) {
        this->failMode = failMode;
    }

    // Card number must be 16 digits, expiry must look like MM/YY
    bool validateDetails(const string& cardNo, const string& expiry) const {
        if (cardNo.length() != 16) return false;
        for (char ch : cardNo) {
            if (ch < '0' || ch > '9') return false;
        }
        return expiry.length() == 5 && expiry[2] == '/';
    }

    PaymentStatus processTransaction(double amount) const {
        if (failMode || amount <= 0) return FAILED;
        return SUCCESS;
    }

    PaymentStatus processRefund(double amount) const {
        if (failMode || amount <= 0) return FAILED;
        return SUCCESS;
    }

    string getGatewayName() const { return gatewayName; }
};

#endif
