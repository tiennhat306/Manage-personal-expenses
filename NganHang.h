#pragma once
#ifndef NGANHANG_H
#define NGANHANG_H


#include <iostream>
// #include "GiaoDich.h"

using namespace std;
typedef long long currency;
#pragma once

class NganHang{
    public:
        NganHang();
        ~NganHang();
        NganHang(string, currency);
        NganHang(const NganHang&);

        //các hàm set:
        void SetIDGD_NHG(string);
        void SetCost(currency);
        void SetAll(string, currency);

        //các hàm get:
        string GetIDGD_NHG();
        currency GetCost();


    private:
        string IDGD_NHG;
        currency cost; /*phí giao dịch*/
};

#endif