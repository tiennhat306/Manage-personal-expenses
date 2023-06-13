#pragma once
#ifndef QL_VAYNO_H
#define QL_VAYNO_H

#include "QL.h"
#include "QL_NganHang.h"
#include "QL_GiaoDich.h"

class QL_NganHang;
class QL_GiaoDich;
class QL_TietKiem;

class QL_VayNo : public QL
{
    private:
        Vector<VayNo*> tableVN; // Bảng dữ liệu các sổ đối tượng vay nợ
        Vector<string> activeLoans; //khoản vay đang hoạt động

        friend class QL_GiaoDich;
    public:
        QL_VayNo();
        // QL_GiaoDich(const QL_GiaoDich &);
        ~QL_VayNo();

        void AddVN(QL_GiaoDich&);
        void AddVN(string, string);

        int ShowVN(QL_NganHang&, QL_GiaoDich&, QL_TietKiem&); 
        void ShowVN(int pos, QL_NganHang&, QL_GiaoDich&, QL_TietKiem&);
        void DeleteVN(int, QL_NganHang&, QL_GiaoDich&, QL_TietKiem&);
        void UpdateVN(int, QL_NganHang&, QL_GiaoDich&, QL_TietKiem&);
        void Load(const string&); /*Load file Vay nợ vào tableVN*/
        void Save(); /*Lưu file*/

        void tongQuanVN(QL_GiaoDich&);
        void chiTietVN(QL_GiaoDich&);

        void updateLoansList(QL_GiaoDich&);
        int getSizeVN();
        string VN_FILE = "DATA_VAYNO.txt";
};

#endif