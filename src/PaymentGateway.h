// =====================================================================
//  PaymentGateway.h  -  a FAKE (simulated) payment gateway
// =====================================================================
//  No real bank is contacted. It checks the card details and answers
//  SUCCESS or FAILED. 'failMode' makes it fail on purpose, so we can test
//  what happens when a payment or refund fails (UC-01 6a, UC-02 5a).
//
//  OOP topics in this file:
//    [this pointer]  [Inline function]  [Function overloading]  toString()
// =====================================================================
#ifndef PAYMENTGATEWAY_H
#define PAYMENTGATEWAY_H

#include <iostream>
#include <string>
using namespace std;

// Kept here (not in Payment.h) because the gateway returns it,
// and Payment.h already includes this file.
// PENDING = a refund failed and is waiting for the admin to settle it (UC-02 5a)
enum PaymentStatus { SUCCESS, FAILED, PENDING, REFUNDED };

// [Inline function] + [Function overloading] another toString() version
inline string toString(PaymentStatus s) {
    if (s == SUCCESS) return "SUCCESS";
    if (s == FAILED) return "FAILED";
    if (s == PENDING) return "PENDING";
    return "REFUNDED";
}

class PaymentGateway {
private:
    string gatewayName;
    bool failMode;

public:
    PaymentGateway(string gatewayName) {
        // [this pointer] the parameter has the SAME name as the data member,
        // so  this->gatewayName  means "the member of THIS object"
        this->gatewayName = gatewayName;
        this->failMode = false;
    }

    void setFailMode(bool failMode) {
        this->failMode = failMode;
    }

    bool isFailing() const { return failMode; }

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
