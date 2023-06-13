#pragma once
#ifndef QUANLYUSER_H
#define QUANLYUSER_H

#include <iostream>
#include <string>
#include "Vector.cpp"
#include <fstream>
#include "Graphic.h"
#include "User.h"
#include <sstream>

using namespace std;



class QuanLyUser{
    public:
        QuanLyUser();
        QuanLyUser(Vector <User> LU);
        QuanLyUser(const QuanLyUser&);
        ~QuanLyUser();
        
        void ManHinhChaoMung(string&);
        int ManHinhDangNhap(string&);
        int ManHinhNhapMatKhau(const string&, string&);
        int ManHinhDangKy();
        int ManHinhNhapMatKhauDangKy(const string&);
        int ManHinhNhapTenDangKy(const string&, const string&);
        void XacNhanDangKy(const string&, const string&, const string&);
        int findUser(const string&);
        int UsernameCheck(const string&); /*0 : FALSE ; 1 : TRUE*/
        int PasswordCheck(const string&); /*0 : FALSE ; 1 : TRUE*/
        //Các hàm lưu, xuất
        void LoadUser();
        void SaveUser();

    private:
        Vector <User> listUser;
};

#endif