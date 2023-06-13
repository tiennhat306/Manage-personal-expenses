#pragma once
#ifndef MENU_H
#define MENU_H


#include "QuanLyUser.h"
#include "QL_GiaoDich.h"
#include "QL_VayNo.h"
#include "QL_TietKiem.h"
#include "QL_NganHang.h"


using namespace std;

class Menu
{
    private:
        string idUser;

        QL_GiaoDich QL_GD;
        QL_NganHang QL_NH;
        QL_VayNo QL_VN;
        QL_TietKiem QL_TK;


    public:
        Menu();
        // QuanLy(const QuanLy &);
        ~Menu();
        void Add();
        void AddWallet(); /*Tạo thêm ví mới bằng cách thêm mã ví*/
        void RutTienTK();
        void ChuyenTien();
        void AddDanhMuc();

        void Search();
        int searchWallet(string);

        int ShowGD();
        int ShowTK();
        int ShowVN();
        int ShowWallet();
   

        void ShowGD(int);
        void ShowVN(int);
        void ShowTK(int);
        void ShowWallet(int);

        void DeleteGD(int);
        void DeleteTK(int);
        void DeleteNH(int);
        void DeleteVN(int);
        void DeleteWallet(int); /*Xóa bớt ví wallet thứ index*/
        void CallDelete();

        void UpdateGD(int);
        void UpdateVN(int);
        void UpdateTK(int);
        void UpdateDuChi();
        void UpdateWallet(int);
        void CallUpdate();

        void Load(const string&);
        void Save(); /*Lưu file*/

        currency SumWallet(const string&);
        void GetBalance(DateTime); /*tính ra +/- trong khoản thời gian*/
        void tongQuan();
        void tongQuanVN();
        void tongQuanTK();
        void chiTietVN();
        void chiTietWallet();

        void quyetToan(int, int);


        void thongKeNgay(DateTime);
        void thongKeNgayChiTiet(DateTime);
        void thongKeTuan(DateTime );
        void thongKeThang(int, int);


        void locThongTin();

        int getSizeGD();
        int getSizeVN();
        int getSizeTK();
        int getSizeTMA();
        int getSizeNHG();

        void updateDipositsList();
        // const string GD_FILE = "DATA_GIAODICH.txt";
        // const string TK_FILE = "DATA_TIETKIEM.txt";
        // const string NH_FILE = "DATA_NGANHANG.txt";
        // const string VN_FILE = "DATA_VAYNO.txt";
        // const string WL_FILE = "DATA_WALLETLIST.txt";
        // const string DC_FILE = "DATA_DUCHI.txt";
        // const string DM_FILE = "DATA_DANHMUC.txt";

        // thống kê chi tiêu nhiều nhất
        // chi tiêu trung bình hằng ngày trong thống kê tuần / tháng / khoảng...
};

#endif