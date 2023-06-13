#include "QL.h"

template<class T>
int QL::searchID(Vector<T> table, string x)
{    
    // int left = 0, right = (table.size() - 1);
    // while (left <= right){
    //     int mid = left + (right - left) / 2;
    //     if (table[mid].GetID() == x)
    //         return mid;
    //     if (table[mid].GetID() > x)
    //         right = mid - 1;
    //     if (table[mid].GetID() < x)
    //         left = mid + 1;
    // }
    // return -1;
    return -1;
}

template<>
int QL::searchID<GiaoDich*>(Vector<GiaoDich*> table, string x)
{    
    int left = 0, right = (table.size() - 1);
    while (left <= right){
        int mid = left + (right - left) / 2;
        if (table[mid]->GetID() == x)
            return mid;
        if (table[mid]->GetID() > x)
            right = mid - 1;
        if (table[mid]->GetID() < x)
            left = mid + 1;
    }
    return -1;
}
template<>
int QL::searchID<NganHang*>(Vector<NganHang*> table, string x)
{    
    int left = 0, right = (table.size() - 1);
    while (left <= right){
        int mid = left + (right - left) / 2;
        if (table[mid]->GetIDGD_NHG() == x)
            return mid;
        if (table[mid]->GetIDGD_NHG() > x)
            right = mid - 1;
        if (table[mid]->GetIDGD_NHG() < x)
            left = mid + 1;
    }
    return -1;
}
template<>
int QL::searchID<TietKiem*>(Vector<TietKiem*> table, string x)
{    
    int left = 0, right = (table.size() - 1);
    while (left <= right){
        int mid = left + (right - left) / 2;
        if (table[mid]->GetIDGD_TK() == x)
            return mid;
        if (table[mid]->GetIDGD_TK() > x)
            right = mid - 1;
        if (table[mid]->GetIDGD_TK() < x)
            left = mid + 1;
    }
    return -1;
}
template<>
int QL::searchID<VayNo*>(Vector<VayNo*> table, string x)
{    
    int left = 0, right = (table.size() - 1);
    while (left <= right){
        int mid = left + (right - left) / 2;
        if (table[mid]->GetIDGD_VN() == x)
            return mid;
        if (table[mid]->GetIDGD_VN() > x)
            right = mid - 1;
        if (table[mid]->GetIDGD_VN() < x)
            left = mid + 1;
    }
    return -1;
}


string QL::currencyShow(currency C){
    int pos;
    if (C >= 0)
        pos = 1;
    else {
        pos = 0;
        C = -C;
    }
    string temp_ss;
    temp_ss = to_string(C);
    int n = (temp_ss.size() - 1) / 3;
    for (int i = 1; i <= n; i++)
        temp_ss.insert(temp_ss.size() - 3 * i - (i - 1), ".");
    temp_ss += " VND";
    if (pos == 0){
        temp_ss = "-" + temp_ss;
    }
    return temp_ss;
}