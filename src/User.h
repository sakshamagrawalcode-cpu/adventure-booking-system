#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

class User {
private:
    string userId;
    string name;
    string email;
    string password;
    string phone;

    // [Static variable] one copy shared by ALL User objects (and child objects)
    static int totalUsers;

protected:
    bool validatePassword(const string& raw) const {
        return raw == password;
    }

public:
    User(string id, string n, string e, string pass, string ph)
        : userId(id), name(n), email(e), password(pass), phone(ph) {
        totalUsers++;
    }

    // Copy constructor also counts, because the destructor always decrements.
    // (Slicing copies go through this constructor.)
    User(const User& other)
        : userId(other.userId), name(other.name), email(other.email),
          password(other.password), phone(other.phone) {
        totalUsers++;
    }

    // [Virtual destructor] if a child object is deleted through a User*,
    // the child's destructor also runs (not only User's)
    virtual ~User() {
        totalUsers--;
    }

    // [Virtual function] each child class gives its own version (override).
    // Called through a User* or User&, the CHILD's version runs.
    virtual string getRole() const {
        return "User";
    }

    bool login(const string& e, const string& pass) const {
        return e == email && validatePassword(pass);
    }

    string getUserId() const { return userId; }
    string getName() const { return name; }
    string getEmail() const { return email; }

    // [Static function] called on the class, no object needed: User::getTotalUsers()
    static int getTotalUsers() {
        return totalUsers;
    }

    // [Stream operator overloading using friend function]
    friend ostream& operator<<(ostream& out, const User& u);
};

// Static variable definition (memory is allocated here, outside the class).
// 'inline' lets this header be included from more than one .cpp file
// without a "multiple definition" linker error.
inline int User::totalUsers = 0;

inline ostream& operator<<(ostream& out, const User& u) {
    out << "User ID : " << u.userId << "\n"
        << "Name    : " << u.name << "\n"
        << "Email   : " << u.email << "\n"
        << "Phone   : " << u.phone << "\n";
    return out;
}

#endif
