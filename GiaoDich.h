#pragma once
#ifndef GIAODICH_H
#define GIAODICH_H


#include <iostream>
#include "DateTime.h"
#include "Graphic.h"
#include <string>
#include <iomanip>

using namespace std;

typedef long long currency;

class GiaoDich
{

    public:
        const static int max_ID_digit = 5;

    private:
        string IDGD;     /*Mã giao dịch của từng giao dịch, được ghi bằng kiểu string - hexa;
                                    sinh nextID bằng thuật toán sinh chỉnh hợp lặp tiếp theo*/
        currency amount; /*Lượng tiền thông hành trong 1 giao dịch, dấu '-' nghĩa là đang chi, '+' nghĩa là đang thu*/
        string wTagF;    /*Trường lưu đích xuất phát dòng tiền*/
        //string wTagE;    /*Trường lưu đích đến phát dòng tiền*/
        DateTime date;   /*Thời gian giao dịch*/
        string note;     /*Ghi chú*/
        int group;
        int category;
        friend class TietKiem;

    public:
        GiaoDich();
        ~GiaoDich();
        void SetID(string);
        void Setamount(const currency);
        void Setwallet(string);
        void Setdate(const DateTime);
        void Setgroup(int);
        void Setcategory(int);
        void Setnote(string);

        string GetID();
        currency Getamount();
        string GetwalletF();
        DateTime GetDate();
        int Getgroup();
        int Getcategory();
        string Getnote();
        void SetAll(string, int, int, currency, string, string, DateTime);
        GiaoDich(string, currency, int, int, string, string, DateTime &, string);
        //void Show();
        friend class DateTime;
        // const string currencyShow(currency); /*hàm xuất số tiền dạng tiền*/

        friend ostream &operator<<(ostream &, GiaoDich);

};

#endif