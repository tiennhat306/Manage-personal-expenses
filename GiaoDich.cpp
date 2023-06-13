#include "GiaoDich.h"

string listGroup1[5] = {"Thu", "Chi", "Vay no", "Tiet kiem", "Vi tien"};
string listCategory1[5][10] = {
    {"Thu nhap", "Tro cap", "Duoc chuyen tien"},
    {"An uong", "Nha o", "Di lai", "Mua sam", "Hoc tap", "Di choi", "Chuyen tien"},
    {"Cho vay", "Thu no", "Di vay", "Tra no"},
    {"Tao tai khoan tiet kiem", "Rut tien tiet kiem"},
    {"Tao them vi", "Chuyen tien cac vi"}};

GiaoDich::GiaoDich()
{
    IDGD = "";
    amount = 0;
    group = 0;
    category = 0;
    wTagF = "";
    //wTagE = "";
    note = "";
}
int GiaoDich::Getgroup()
{
    return group;
}
int GiaoDich::Getcategory()
{
    return category;
}
GiaoDich::~GiaoDich()
{
}

GiaoDich::GiaoDich(string t_IDGD, currency t_amount, int t_group, int t_category, string t_wTagF, string t_wTagE, DateTime &t_date, string t_note)
{
    IDGD = t_IDGD;
    amount = t_amount;
    group = t_group;
    category = t_category;
    wTagF = t_wTagF;
    //wTagE = t_wTagE;
    date.SetDate(t_date);
    note = t_note;
}

void GiaoDich::SetID(string ID)
{
    IDGD = ID;
}

void GiaoDich::Setamount(const currency temp_amount)
{
    amount = temp_amount;
}

void GiaoDich::Setdate(DateTime D)
{
    date.SetDate(D);
}
void GiaoDich::Setgroup(int temp_group)
{
    group = temp_group;
}
void GiaoDich::Setcategory(int temp_category)
{
    category = temp_category;
}

void GiaoDich::Setwallet(string F)
{
    wTagF = F;
    //wTagE = E;
}

void GiaoDich::Setnote(string temp_note)
{
    note = temp_note;
}

void GiaoDich::SetAll(string temp_ID, int temp_group, int temp_category,  currency temp_amount, string temp_F, string temp_note, DateTime D)
{
    SetID(temp_ID);
    Setgroup(temp_group);
    Setcategory(temp_category);
    Setamount(temp_amount);
    Setwallet(temp_F);
    Setnote(temp_note);
    Setdate(D);
}

// void GiaoDich::Show()
// {
//     cout << "Ma giao dich:  " << IDGD << endl
//          << "Nhom:  " << listGroup1[group - 1] << endl
//          << "Danh muc:  " << listCategory1[group - 1][category - 1] << endl
//          << "So tien:  " << amount
//          //<< "Chuyen tu " << wTagE << " den " << wTagF
//          << "Vi : " << wTagF
//          << "Ngay: " << date << endl
//          << ((group==1||group==2||group==4)?"Ghi chu: ":((category==1||category==2)? "Nguoi vay: ":"Nguoi cho vay: ")) << note << endl;
// }

string GiaoDich::GetID()
{
    return this->IDGD;
}

// string GiaoDich::GetwalletE()
// {
//     //return this->wTagE;
// }

string GiaoDich::GetwalletF()
{
    return this->wTagF;
}

string GiaoDich::Getnote()
{
    return this->note;
}

currency GiaoDich::Getamount()
{
    return this->amount;
}

DateTime GiaoDich::GetDate()
{
    return this->date;
}

ostream &operator<<(ostream &o, GiaoDich gd)
{
    o 
      << setw(15) << left << listGroup1[gd.group - 1] << " | " 
      << setw(25) << left << listCategory1[gd.group - 1][gd.category - 1] << " | ";
      if (gd.amount < 0 || gd.group == 2) color(12); else color(10);
      cout << setw(20)<< right << gd.amount; resetText();
      cout << " | " << setw(20) << left << gd.wTagF << " | " 
      << setw(20) << left << gd.note << " | " 
      << setw(15) << right << gd.date.GetDateinString() << endl;
    return o;
}

