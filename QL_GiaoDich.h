#pragma once
#ifndef QL_GIAODICH_H
#define QL_GIAODICH_H


#include "QL.h"
#include "QL_VayNo.h"
#include "QL_TietKiem.h"
#include "QL_NganHang.h"

using namespace std;

class QL_NganHang;
class QL_VayNo;
class QL_TietKiem;
class QL_GiaoDich : public QL
{
    private:
        Vector<GiaoDich*> tableGD; /*Bảng chưa dữ liệu của các giao dịch*/

        Vector<string> tableTMA; // Tên các ví tiền mặt
        Vector<string> tableNHG; // Tên các ví ngân hàng
        Vector<currency> duChi; // Các mức dự chi
        Vector<string> listCategory[5]; // Tên các danh mục

        friend class QL_NganHang;
        friend class QL_VayNo;
        friend class QL_TietKiem;
    public:
        QL_GiaoDich();
        // QL_GiaoDich(const QL_GiaoDich &);
        ~QL_GiaoDich();
        void AddGD(QL_NganHang &, QL_VayNo&, QL_TietKiem&);
        void AddWallet(); /*Tạo thêm ví mới bằng cách thêm mã ví*/
        void ChuyenTien(QL_NganHang&);
        void AddDanhMuc();

        void AddGD(string, int, int, currency, string, string, DateTime); 

        void Search(QL_NganHang&);
        int searchWallet(string);

        int ShowGD(QL_NganHang&, QL_VayNo&, QL_TietKiem&);
        int ShowWallet();
   

        void ShowGD(int, QL_NganHang&, QL_VayNo&, QL_TietKiem&);
        void ShowWallet(int, QL_NganHang&);

        void DeleteGD(int, QL_NganHang&, QL_VayNo&, QL_TietKiem&);
        void DeleteWallet(int, QL_NganHang&, QL_VayNo&, QL_TietKiem&); /*Xóa bớt ví wallet thứ index*/

        void UpdateGD(int, QL_NganHang&, QL_VayNo&, QL_TietKiem&);
        void UpdateDuChi();
        void UpdateWallet(int);

        void LoadGD(); /*Load file Giao dịch vào tableGD*/
        void LoadWallet();
        void LoadDuChi();
        void LoadDanhMuc();
        void Load(const string&);
        void Save(); /*Lưu file*/

        currency SumWallet(string, QL_NganHang&);
        void GetBalance(DateTime, QL_NganHang&); /*tính ra +/- trong khoản thời gian*/

        void GDGanDay(QL_NganHang&);
        void tongQuanGD(QL_NganHang&);

        void chiTietWallet(QL_NganHang&);

        void quyetToan(int, int, QL_NganHang&);

        int dayInWeek(DateTime);

        void thongKeNgay(DateTime, QL_NganHang&);
        void thongKeNgay(DateTime, currency&, currency&, QL_NganHang&);
        void thongKeNgayChiTiet(DateTime, QL_NganHang&);
        void thongKeTuan(DateTime, QL_NganHang&);
        void thongKeTuan(DateTime, currency&, currency&, QL_NganHang&);
        void thongKeTuanDauThang(DateTime, currency&, currency&, QL_NganHang&);
        void thongKeTuanCuoiThang(DateTime, currency&, currency&, QL_NganHang&);
        void thongKeThang(int, int, QL_NganHang&);


        void sortDate(Vector<GiaoDich*>&);
        void locThongTin(QL_NganHang&);
        string next_ID(string&, int);
        string upcase(const string&);

        int getSizeGD();

        int getSizeTMA();
        int getSizeNHG();
        const string& getWalletName(int);




        string GD_FILE = "DATA_GIAODICH.txt";
        string WL_FILE = "DATA_WALLETLIST.txt";
        string DC_FILE = "DATA_DUCHI.txt";
        string DM_FILE = "DATA_DANHMUC.txt";


        string listGroup[5] = {"Thu", "Chi", "Vay no", "Tiet kiem", "Vi tien"};



        // thống kê chi tiêu nhiều nhất
        // chi tiêu trung bình hằng ngày trong thống kê tuần / tháng / khoảng...
};

#endif