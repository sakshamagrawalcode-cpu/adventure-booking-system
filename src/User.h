// =====================================================================
//  User.h  -  the PARENT class of every kind of user
// =====================================================================
//  Stores what every user has: id, name, email, password, phone.
//  Children: Traveler, AdventureProvider, Admin (and their children).
//
//  OOP topics in this file:
//    [Class and object]  [Access specifiers]  [Encapsulation]
//    [Abstract class]  [Pure virtual function]  [Virtual destructor]
//    [Parameterized constructor]  [Copy constructor]
//    [Static data member]  [Static member function]  [Protected member]
//    [Friend function]  [Stream operator overloading]
// =====================================================================
#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

// [Abstract class] User has a pure virtual function (getRole() = 0),
// so a plain User object can NOT be created. Only its children can be.
class User {
// [Access specifiers]
//   private   -> only User's own functions can use it
//   protected -> User AND its child classes can use it
//   public    -> anyone can use it
private:
    // [Encapsulation] the data is private; others use it only through functions
    string userId;
    string name;
    string email;
    string password;
    string phone;

    // [Static data member] ONE copy shared by ALL user objects.
    // It counts how many user objects exist right now.
    static int totalUsers;

protected:
    // [Static data member] when true, each class's constructor prints its name.
    // main() turns it on to show the [Constructor execution order].
    static bool showConstructorCalls;

    // [Protected member] child classes can call these two, main() cannot.
    static void traceConstructor(const string& className) {
        if (showConstructorCalls) {
            cout << "   " << className << " constructor runs\n";
        }
    }

    bool validatePassword(const string& raw) const {
        return raw == password;
    }

public:
    // [Parameterized constructor]
    User(string id, string n, string e, string pass, string ph)
        : userId(id), name(n), email(e), password(pass), phone(ph) {
        totalUsers++;
        traceConstructor("User");
    }

    // [Copy constructor] runs when a user object is copied,
    // e.g.  Traveler copy = aarav;   The copy is one more user, so count it.
    User(const User& other)
        : userId(other.userId), name(other.name), email(other.email),
          password(other.password), phone(other.phone) {
        totalUsers++;
    }

    // [Virtual destructor] if a child object is deleted through a User*,
    // the child's destructor also runs (not only User's).
    virtual ~User() {
        totalUsers--;
    }

    // [Pure virtual function] "= 0" means User gives NO body here.
    // Every child class MUST write its own getRole().
    virtual string getRole() const = 0;

    // [Encapsulation] password is private, so this is the only way to check it
    bool login(const string& e, const string& pass) const {
        return e == email && validatePassword(pass);
    }

    string getUserId() const { return userId; }
    string getName() const { return name; }
    string getEmail() const { return email; }

    // [Static member function] called on the class itself: User::getTotalUsers()
    static int getTotalUsers() { return totalUsers; }
    static void setShowConstructorCalls(bool on) { showConstructorCalls = on; }

    // [Friend function] + [Stream operator overloading]  ->  cout << someUser;
    friend ostream& operator<<(ostream& out, const User& u);
};

// [Static data member] definitions: the real memory is created here, outside the class.
// 'inline' lets this header be included from more than one .cpp file
// without a "multiple definition" linker error.
inline int User::totalUsers = 0;
inline bool User::showConstructorCalls = false;

inline ostream& operator<<(ostream& out, const User& u) {
    // A friend function can read private members (u.userId, u.name, ...)
    out << "User ID : " << u.userId << "\n"
        << "Name    : " << u.name << "\n"
        << "Email   : " << u.email << "\n"
        << "Phone   : " << u.phone << "\n";
    return out;
}

#endif
