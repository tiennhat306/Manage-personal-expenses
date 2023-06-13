#pragma once
#ifndef QL_H
#define QL_H

#include "GiaoDich.h"
#include "NganHang.h"
#include "TietKiem.h"
#include "VayNo.h"
#include "Vector.cpp"
#include "User.h"
#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <windows.h>
#include "Graphic.h"
#include <cstdint>
#include <limits>

class QL
{
public:
    virtual void Load(const string&) = 0;
    virtual void Save() = 0;
    template<class T>
    int searchID(Vector<T>, string);
    string currencyShow(currency C);

};

#endif