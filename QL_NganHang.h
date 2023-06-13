#pragma once
#ifndef QL_NGANHANG_H
#define QL_NGANHANG_H

#include "QL.h"
#include "QL_GiaoDich.h"
#include "QL_VayNo.h"
#include "QL_TietKiem.h"

class QL_GiaoDich;
class QL_VayNo;
class QL_TietKiem;

class QL_NganHang : public QL
{
    private:
        Vector<NganHang*> tableNH; // Bảng dữ liệu chứa phí giao dịch

        friend class QL_GiaoDich;
        friend class QL_VayNo;
        friend class QL_TietKiem;
    public:
        QL_NganHang();
        ~QL_NganHang();
        void AddNH(QL_GiaoDich&);
        void AddNH(string, currency); /*thêm một GD ngân hàng*/

        void DeleteNH(int, QL_GiaoDich&, QL_VayNo&, QL_TietKiem&);
        void Load(const string&); /*Load file Ngân hàng vào tableNH*/
        void Save(); /*Lưu file*/


        string NH_FILE = "DATA_NGANHANG.txt";

};

#endif