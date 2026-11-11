// User.h
// All account types: User (base class), Customer, Provider, Admin.

#pragma once
#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------------------------
// User: the base class. Holds what every account has.
// It is abstract (has "= 0" functions), so a plain User
// object can never be created.
// ---------------------------------------------------------------
class User {
private:
    string id;
    string name;
    string email;
    string password;

public:
    // Constructor: sets the 4 common fields
    User(string id, string name, string email, string password) {
        this->id = id;
        this->name = name;
        this->email = email;
        this->password = password;
    }

    // Virtual destructor: needed because we use children through User*
    virtual ~User() {}

    // Getters (no getPassword: nobody can read a password)
    string getId()    { return id; }
    string getName()  { return name; }
    string getEmail() { return email; }

    // Setters
    void setName(string name)         { this->name = name; }
    void setEmail(string email)       { this->email = email; }
    void setPassword(string password) { this->password = password; }

    // Returns true if the given password is correct
    bool checkPassword(string input) {
        return input == password;
    }

    // Each child class must write these two functions
    virtual string getRole() = 0;
    virtual void showProfile() = 0;
};

// ---------------------------------------------------------------
// Customer: a person who books adventures
// ---------------------------------------------------------------
class Customer : public User {
private:
    string gender;
    int age;
    string mobile;

public:
    // Sends the first 4 values to User's constructor, then sets its own 3
    Customer(string id, string name, string email, string password,
             string gender, int age, string mobile)
        : User(id, name, email, password) {
        this->gender = gender;
        this->age = age;
        this->mobile = mobile;
    }

    string getGender() { return gender; }
    int    getAge()    { return age; }
    string getMobile() { return mobile; }

    void setGender(string gender) { this->gender = gender; }
    void setAge(int age)          { this->age = age; }
    void setMobile(string mobile) { this->mobile = mobile; }

    string getRole() override { return "Customer"; }

    void showProfile() override {
        cout << "Name   : " << getName() << "\n";
        cout << "Email  : " << getEmail() << "\n";
        cout << "Gender : " << gender << "\n";
        cout << "Age    : " << age << "\n";
        cout << "Mobile : " << mobile << "\n";
    }
};

// ---------------------------------------------------------------
// Provider: a company that lists adventures
// ---------------------------------------------------------------
class Provider : public User {
private:
    string mobile;
    string companyName;

public:
    Provider(string id, string name, string email, string password,
             string mobile, string companyName)
        : User(id, name, email, password) {
        this->mobile = mobile;
        this->companyName = companyName;
    }

    string getMobile()      { return mobile; }
    string getCompanyName() { return companyName; }

    void setMobile(string mobile)           { this->mobile = mobile; }
    void setCompanyName(string companyName) { this->companyName = companyName; }

    string getRole() override { return "Provider"; }

    void showProfile() override {
        cout << "Name    : " << getName() << "\n";
        cout << "Email   : " << getEmail() << "\n";
        cout << "Mobile  : " << mobile << "\n";
        cout << "Company : " << companyName << "\n";
    }
};

// ---------------------------------------------------------------
// Admin: manages everything. Has no extra data.
// ---------------------------------------------------------------
class Admin : public User {
public:
    Admin(string id, string name, string email, string password)
        : User(id, name, email, password) {}

    string getRole() override { return "Admin"; }

    void showProfile() override {
        cout << "Name  : " << getName() << "\n";
        cout << "Email : " << getEmail() << "\n";
    }
};
