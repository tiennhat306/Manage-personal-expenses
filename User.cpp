#include "User.h"

User::User(){}

User::~User(){}

User::User(string username, string password, string name){
    this->username = username;
    this->password = password;
    this->name = name;
}

User::User(const User& U){
    this->username = U.username;
    this->password = U.password;
    this->name = U.name;
}

string User::getUsername(){
    return this->username;
}

string User::getPassword(){
    return this->password;
}

string User::getName(){
    return this->name;
}

void User::setUsername(string username){
    this->username = username;
    cout << "Username changed to " << this->username << endl;
}

void User::setPassword(string password){
    this->password = password;
    cout << "Password changed to " << this->password << endl;
}

void User::setName(string name){
    this->name = name;
    cout << "Name changed to " << this->name << endl;
}

void User::setAll(string username, string password, string name){
    this->username = username;
    this->password = password;
    this->name = name;
}


