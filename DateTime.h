#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
#include <afxres.h>
#include <string>
#include <ctime>
#include "Graphic.h"

using namespace std;

class DateTime
{
private:
    int day;
    int month;
    int year;

public:
    DateTime();
    ~DateTime();
    DateTime GetDate();
    const string GetDateinString();
    DateTime(const string);
    DateTime(int, int, int);
    DateTime(const DateTime &);
    void SetDate(int = 1, int = 1, int = 1990);
    void SetDate(const DateTime &);
    void SetDate(string);
    int GetDay();
    int GetMonth();
    int GetYear();
    friend ostream &operator<<(ostream &, const DateTime);
    friend istream &operator>>(istream &, DateTime &);
    bool leapcheck(int);
    bool operator>=(const DateTime &);
    bool operator<=(const DateTime &);
    bool operator>(const DateTime &);
    bool operator<(const DateTime &);
    bool operator==(const DateTime &);
    void operator=(const DateTime &);


    string chuanHoa(string);
    DateTime operator-(const int);
    DateTime operator+(const int);
    int DisMonth(DateTime, DateTime); //So thang tu ngay gui tiet kiem den hien tai

    DateTime Today();
    bool legalDate();
};

#endif