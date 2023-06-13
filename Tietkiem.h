#pragma once
#ifndef TIETKIEM_H
#define TIETKIEM_H


#include <iostream>
#include <string>
#include "DateTime.h"
#include "GiaoDich.h"

using namespace std;

// #pragma once

class TietKiem
{
    public:
        TietKiem();
        ~TietKiem();
        TietKiem(string, string, float, int, int);
        TietKiem(const TietKiem &);
        void SetID(string);
        void SetTenKhoanTK(string);
        void SetInterest(float);
        void SetTerm(int);
        void SetMode(int);
        void SetAll(string, string, float, int, int);

        string GetIDGD_TK();
        string GetTenKhoanTK();
        float GetInterest();
        int GetTerm();
        int GetMode();

    private:
        string IDGD_TK; //unique
        string TenKhoanTK; //unique
        float InterestRate;
        int Term;
        int Mode; // dạng quay vòng 0 : không quay vòng, 1 : quay vòng goc  2:Quay vong goc va lai
};

#endif