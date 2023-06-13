#pragma once
#ifndef QL_TIETKIEM_H
#define QL_TIETKIEM_H

#include "QL.h"
#include "QL_NganHang.h"
#include "QL_GiaoDich.h"

class QL_NganHang;
class QL_GiaoDich;
class QL_VayNo;

class QL_TietKiem : public QL
{
    private:
        Vector<TietKiem*> tableTK; // Bảng dữ liệu các khoản tiết kiệm
        Vector<string> activeDiposits; //tài khoản tiết kiệm đang hoạt động

        friend class QL_GiaoDich;
        friend class Menu;
    public:
        QL_TietKiem();
        // QL_TietKiem(const QL_TietKiem &);
        ~QL_TietKiem();
        void RutTienTK(QL_NganHang&, QL_GiaoDich&, QL_VayNo&);

        void AddTK(QL_GiaoDich&, QL_NganHang&);
        void AddTK(string, string, float, int, int); /*thêm một GD tiết kiệm*/


        //int ShowGD();
        int ShowTK(QL_NganHang&, QL_GiaoDich&, QL_VayNo&); 
        void ShowTK(int, QL_NganHang&, QL_GiaoDich&, QL_VayNo&);


        void DeleteTK(int, QL_NganHang&, QL_GiaoDich&, QL_VayNo&);
        void UpdateTK(int, QL_NganHang&, QL_GiaoDich&, QL_VayNo&);
        void Load(const string&); /*Load file Tiết kiệm vào tableTK*/
        void Save(); /*Lưu file*/

        currency UpdateLaiSuatTK(TietKiem*, QL_GiaoDich&);
        void tongQuanTK(QL_GiaoDich&);



        int getSizeTK();
        string TK_FILE = "DATA_TIETKIEM.txt";

        void updateDipositsList();
        int searchDiposits(const string&);
        void showDiposits();
        int searchDipositsName_inTK(const string&);
};

#endif