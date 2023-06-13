#pragma once
#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <iomanip>
#include "Vector.cpp"



using namespace std;


//thư viện đồ họa
//Khai báo nguyên mẫu hàm


void color(int); /*hàm nhận màu sắc : 15/240(mặc định), 10/114(xanh lá), 11/241(xanh dương), 12/116(đỏ), 14/246(vàng) */
void color2(int); /*hàm nhận màu sắc có định dạng 
                    0(mặc định),
                    1(in đậm),
                    32(xanh lá),
                    34(xanh dương),
                    31(đỏ),
                    33(vàng) */
void gotoXY(int, int); /*hàm điều hướng con trỏ*/
void drawBox(int, int, int, int); /*hàm vẽ khung*/
void clr(); /*hàm xóa màn hình*/
void drawLine(int, int, int); /*vẽ đường thẳng nằm ngang*/
void resetText(); /*reset lại màu chữ*/
void showCursor(); /*hiện con trỏ*/
void hideCursor(); /*ẩn con trỏ*/
void getCursorXY(int&, int&); /*lấy vị trí hiện tại của con trỏ*/
void centerText(int, int, const string&); /*vẽ chữ ở giữa màn hình*/
void button(int, int, string, int, int, int, string); /*vẽ nút ; số thứ tự của nút, biến chỉ, tên nút, x, y, màu*/
void centerButton(int, int, string, int, int, int, string); /*vẽ nút với chữ ở giữa ; số thứ tự của nút, biến chỉ, tên nút, x, y*/
void hide_password_input(char*); /*ẩn mật khẩu*/
void input_username(char*); /*nhập tên đăng nhập*/
int getkey();
int showList(Vector<string>&, int, int, int, string, int); //0 : left, 1 : centerized
void titleBar(int, int, int, string, string);
int getX(); int getY();
long long currencyInput();
#endif