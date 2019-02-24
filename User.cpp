#include <iostream>
#include <string>

using namespace std;

#include "User.h"

User::User() {
    //username;
    //password;
}

User::User(const string& uname, const string& pass) {
    username=uname;
    password=pass;
}

string User::getUsername() const {
    return username;
}

bool User::check(const string &uname, const string &pass) const {
    if ((uname == username && pass == password) && (username.size() != 0 || password.size() != 0)){
        return true;
    }
    else {
        return false;
    }
}

bool User::setPassword(const string &oldpass, const string &newpass) {
    if (username == "") {
        cout << "error cannot change pass b/c user is default" <<endl;
        return false;
    }
    if (password == oldpass) {
        password = newpass;
        return true;
    }
    return false;
}

void User::moduser (const string tempnam ,const string temppas) {
    username = tempnam;
    password = temppas;
    
}

string User::getpassword() const {
    return password;
}