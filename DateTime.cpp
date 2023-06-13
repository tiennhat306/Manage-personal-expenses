#include "DateTime.h"

using namespace std;

DateTime::DateTime()
{
    this->day = 1;
    this->month = 1;
    this->year = 1990;
}

DateTime::~DateTime()
{
}

DateTime::DateTime(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
    if (d < 1 && d > 31)
        day = 31;
    if (m < 1 && m > 12)
        month = 12;

    int yearstatus = leapcheck(y);
    if (yearstatus == 1 && m == 2 && d >= 30)
    {
        day = 29;
    }
    if (yearstatus == 0 && m == 2 && d >= 29)
    {
        day = 28;
    }

    if (m == 4 || m == 6 || m == 9 || m == 11)
    {
        if (d == 31)
            day = 30;
    }
}

DateTime::DateTime(const string s)
{
    string str = chuanHoa(s);
    this->day = (str[0] - 48) * 10 + str[1] - 48;
    this->month = (str[3] - 48) * 10 + str[4] - 48;
    this->year = (str[6] - 48) * 1000 + (str[7] - 48) * 100 + (str[8] - 48) * 10 + str[9] - 48;
}

DateTime::DateTime(const DateTime &D)
{
    this->day = D.day;
    this->month = D.month;
    this->year = D.year;
}

DateTime DateTime::GetDate()
{
    return *this;
}

ostream &operator<<(ostream &o, const DateTime D)
{
    if (D.day < 10)
    {
        o << "0";
    }
    o << D.day << "/";
    if (D.month < 10)
    {
        o << "0";
    }
    else
    o << D.month<< "/" << D.year;
    return o;
}

istream &operator>>(istream &in, DateTime &D){
    int count = 0;
    int initX = getX(), initY = getY();
    int currentX, currentY;
    int dd, mm, yy;
    do {
        D.SetDate(1, 1, 1970);
        gotoXY(initX, initY);
        if (count) {
            color(12); cout << setw(2) << D.day << "/" << setw(2) << D.month << "/" << setw(4) << D.year;
            gotoXY(initX, initY);
            resetText();
        }
        
        D.day = currencyInput();
        gotoXY(initX, initY); cout << setfill('0') << setw(2) << right << D.day << "/";
        D.month = currencyInput();
        gotoXY(initX, initY); cout << setfill('0') << setw(2) << right << D.day << "/" << setfill('0') << setw(2) << right << D.month << "/";
        D.year = currencyInput();
        count++;
    } while (!D.legalDate());
    cout << setfill(' ');
    return in;
}

void DateTime::SetDate(int d, int m, int y){
    this->day = d;
    this->month = m;
    this->year = y;
}

void DateTime::SetDate(string s)
{
    string str = chuanHoa(s);
    this->day = (str[0] - 48) * 10 + str[1] - 48;
    this->month = (str[3] - 48) * 10 + str[4] - 48;
    this->year = (str[6] - 48) * 1000 + (str[7] - 48) * 100 + (str[8] - 48) * 10 + str[9] - 48;
}

void DateTime::SetDate(const DateTime &D){
    
    this->day = D.day;
    this->month = D.month;
    this->year = D.year;
}

int DateTime::GetDay()
{
    return this->day;
}

int DateTime::GetMonth()
{
    return this->month;
}

int DateTime::GetYear()
{
    return this->year;
}

bool DateTime::leapcheck(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        return true;
    }
    return false;
}

bool DateTime::operator>=(const DateTime &D)
{
    if (this->year != D.year)
        return this->year > D.year;
    if (this->month != D.month)
        return this->month > D.month;
    if (this->day != D.day)
        return this->day > D.day;
    return true;
}

bool DateTime::operator<=(const DateTime &D)
{
    if (this->year != D.year)
        return this->year < D.year;
    if (this->month != D.month)
        return this->month < D.month;
    if (this->day != D.day)
        return this->day < D.day;
    return true;
}

bool DateTime::operator>(const DateTime &D)
{

    if (this->year != D.year)
        return this->year > D.year;
    if (this->month != D.month)
        return this->month > D.month;
    if (this->day != D.day)
        return this->day > D.day;
    return false;
}

bool DateTime::operator<(const DateTime &D)
{
    if (this->year != D.year)
        return this->year < D.year;
    if (this->month != D.month)
        return this->month < D.month;
    if (this->day != D.day)
        return this->day < D.day;
    return false;
}

const string DateTime::GetDateinString()
{
    int tday = day;
    int tmonth = month;
    int tyear = year;
    string ss_date;
    string s_day, s_month, s_year;
    (tday > 9) ? s_day = to_string(tday) : s_day = "0" + to_string(tday);
    (tmonth > 9) ? s_month = to_string(tmonth) : s_month = "0" + to_string(tmonth);
    s_year = to_string(tyear);
    ss_date = s_day + "/" + s_month + "/" + s_year;
    return ss_date;
}

string DateTime::chuanHoa(string str)
{
    if (str[2] != '/')
        str = "0" + str;
    if (str[5] != '/')
        str.insert(3, "0");
    return str;
}

DateTime DateTime::operator-(int x){
    DateTime tmp;
    tmp.day = this->day;
    tmp.month = this->month;
    tmp.year = this->year;
    if(tmp.day > x){
        tmp.day -= x;
        return tmp;
    } 
    else while(x>0){
        if(tmp.month==1||tmp.month==2||tmp.month==4||tmp.month==6||tmp.month==8||tmp.month==9||tmp.month==11){
            if((tmp.day - x + 31) > 0){
                tmp.day = tmp.day - x + 31;
                x = 0;
            } else x-=31;
            if(tmp.month != 1) tmp.month--;
            else {
                tmp.month=12;
                tmp.year--;
            }
            if(x==0) return tmp;
            if(tmp.day > x){
                tmp.day -= x;
                return tmp;
            }
        }
        if(tmp.month==5||tmp.month==7||tmp.month==10||tmp.month==12){
            if((tmp.day - x + 30) > 0){
                tmp.day = tmp.day - x + 30;
                x = 0;
            } else x-=30;
            tmp.month--;
            if(x==0) return tmp;
            if(tmp.day > x){
                tmp.day -= x;
                return tmp;
            }
        }
        if(tmp.month==3){
            int cntDay = (leapcheck(tmp.year))? 29 : 28;
            if((tmp.day - x + cntDay) > 0){
                tmp.day = tmp.day - x + cntDay;
                x = 0;
            } else x-=cntDay;
            tmp.month--;
            if(x==0) return tmp;
            if(tmp.day > x){
                tmp.day -= x;
                return tmp;
            }
        }
    }
}

DateTime DateTime::operator+(int x){
    DateTime tmp;
    tmp.day = this->day;
    tmp.month = this->month;
    tmp.year = this->year;

    while (x > 0){
        if (tmp.month == 1 || tmp.month == 3 || tmp.month == 5 || tmp.month == 7 || tmp.month == 8 || tmp.month == 10 || tmp.month == 12){
            if (tmp.day + x <= 31){
                tmp.day += x;
                return tmp;
            }
            else{
                x -= (31 - tmp.day + 1);
                tmp.day = 1;
                if (tmp.month != 12) tmp.month++;
                else{
                    tmp.month = 1;
                    tmp.year++;
                }
            }
        }
        if (tmp.month == 4 || tmp.month == 6 || tmp.month == 9 || tmp.month == 11){
            if (tmp.day + x <= 30){
                tmp.day += x;
                return tmp;
            }
            else{
                x -= (30 - tmp.day + 1);
                tmp.day = 1;
                tmp.month++;
            }
        }
        if (tmp.month == 2){
            int cntDay = (leapcheck(tmp.year)) ? 29 : 28;
            if (tmp.day + x <= cntDay){
                tmp.day += x;
                return tmp;
            }
            else{
                x -= (cntDay - tmp.day + 1);
                tmp.day = 1;
                tmp.month++;
            }
        }
    }
    return tmp;
}

bool DateTime::operator==(const DateTime &S){
    if(this->day != S.day) return false;
    if(this->month != S.month) return false;
    if(this->year != S.year) return false;
    return true;
}

void DateTime::operator=(const DateTime &S){
    this->day = S.day;
    this->month = S.month;
    this->year = S.year;
}

DateTime DateTime::Today(){
    time_t t_now = time(0);
    string now = ctime(&t_now);
    DateTime dt;
    dt.day = stoi(now.substr(8, 9));
    dt.year = stoi(now.substr(20, 23));
    string t_month = now.substr(4,3);
    if(t_month=="Jan") dt.month = 1;
    else if(t_month=="Feb") dt.month=2;
    else if(t_month=="Mar") dt.month=3;
    else if(t_month=="Apr") dt.month=4;
    else if(t_month=="May") dt.month=5;
    else if(t_month=="Jun") dt.month=6;
    else if(t_month=="Jul") dt.month=7;
    else if(t_month=="Aug") dt.month=8;
    else if(t_month=="Sep") dt.month=9;
    else if(t_month=="Oct") dt.month=10;
    else if(t_month=="Nov") dt.month=11;
    else if(t_month=="Dec") dt.month=12;
    return dt;
}

bool DateTime::legalDate(){
    if (year > 9999 || year < 1) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
 
    if (month == 2){
        int tmp = this->year;
        if (leapcheck(tmp)) return (day <= 29);
        else return (day <= 28);
    }

    if (month == 4 || month == 6 || month == 9 || month == 11) return (day <= 30);
 
    return true;
}