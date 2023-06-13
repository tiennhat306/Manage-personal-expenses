#pragma once
#ifndef USER_H
#define USER_H


#include <iostream>
#include <string>
#include "Vector.cpp"
#include <fstream>

using namespace std;



class User{
    public:
        User();
        User(string, string, string);
        User(const User&);
        ~User();

        string getUsername();
        string getPassword();
        string getName();

        void setUsername(string);
        void setPassword(string);
        void setName(string);
        void setAll(string, string, string);

        

    private:
        string username;
        string password;
        string name;

};

#endif