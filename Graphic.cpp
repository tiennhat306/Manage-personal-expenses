#include "Graphic.h"

using namespace std;

//thư viện đồ họa
//Khai báo nguyên mẫu hàm


//Khai báo hàm
void color(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void color2(int x){
    cout << "\033[1;" << x << "m";
}


void gotoXY(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void drawBox(int x, int y, int width, int height){
    height++;
    for(int i = 0; i < width; i++){
        gotoXY(x + i, y);
        cout << (char)205;
        gotoXY(x + i, y + height);
        cout << (char)205;
    }
    for(int i = 0; i < height; i++){
        gotoXY(x, y + i);
        cout << (char)186;
        gotoXY(x + width, y + i);
        cout << (char)186;
    }
    gotoXY(x, y);
    cout << (char)201;
    gotoXY(x + width, y);
    cout << (char)187;
    gotoXY(x, y + height);
    cout << (char)200;
    gotoXY(x + width, y + height);
    cout << (char)188;
}

void clr(){
    system("cls");
    resetText();
    hideCursor();
}

void drawLine(int x, int y, int width){
    for(int i = 0; i < width; i++){
        gotoXY(x + i, y);
        cout << (char)196;
    }
}

void resetText(){
    color(15);
}

int getX(){
    int x;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.X;
}

int getY(){
    int y;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.Y;
}

void hideCursor(){
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void getCursorXY(int &x, int &y){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    x = csbi.dwCursorPosition.X;
    y = csbi.dwCursorPosition.Y;
}

void showCursor(){
    CONSOLE_CURSOR_INFO info;
    info.bVisible = true;
    info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void centerText(int x, int y, const string &text){
    int length = text.length();
    gotoXY(x - length / 2, y);
    cout << text;
}

void button(int number, int counter, string text, int x, int y, int width, string colour){
    gotoXY(x, y);
    if(counter == number){
        if (colour == "BLUE") color2(44);
        if (colour == "WHITE") color(240);
        if (colour == "GREEN") color(114);
        if (colour == "RED") color2(41);
        if (colour == "YELLOW") color2(43);
    }
    else{
        color(15);
    }
    cout << setw(width) << left << text;
    // color(15);
}

void centerButton(int number, int counter, string text, int x, int y, int width, string colour){
    gotoXY(x, y);
    if(counter == number){
        if (colour == "BLUE") color2(44);
        if (colour == "WHITE") color(240);
        if (colour == "GREEN") color(114);
        if (colour == "RED") color2(41);
        if (colour == "YELLOW") color2(43);
        cout << setw(width) << " ";
    }
    else{
        color(15);
        cout << setw(width) << " ";
    }
    int length = text.length();
    gotoXY(x + width / 2 - length / 2, y);
    cout << setw(width / 2 + length / 2) << left << text;
    color(15);
}

void hide_password_input(char *password){
    char ch;
    int status = 0; /*0 : đang nhập, 1 : đang không nhập*/
    int next_job = 0; /*0 : trở về, 1 : kiểm tra*/
    int i = 0;
    while(1){
        ch = getch();
        if(ch == 13){
            password[i] = '\0';
            break;
        }
        else if(ch == 8){
            if(i > 0){
                i--;
                cout << "\b \b";
            }
        }
        if (ch >= 32 && ch <= 126){
            password[i] = ch;
            i++;
            cout << "*";
        }

        if (ch == 72 || ch == 80) status = !status;
        if (status == 0 && (ch == 75 || ch == 77)) next_job = !next_job;
    }
}

int getkey(){
    int high = 0; int low = 0;
    high = getch();
    if (high == 224){
        low = getch();
        return 1000 + low;
    } else return high;
}

int showList(Vector<string>& chooseList, int x, int y, int width, string colour, int align){
    int size = chooseList.size();
    int counter = 0; int key;
    for (;;){
        for (int i = 0; i < size; i++){
            if (align) centerButton(i, counter, chooseList[i], x, y + i, width, colour);
            else button(i, counter, chooseList[i], x, y + i, width, colour);
            //getchar();
        }
        key = getkey();
        if (key == 1080){
            counter++;
            if (counter == size) counter = 0;
        }
        if (key == 1072){
            counter--;
            if (counter == -1) counter = size - 1;
        }
        if (key == 13) break;
    }
    resetText();
    return counter;
}

void titleBar(int left_margin, int right_margin, int line, string Text, string colour){ /*left, right, line, text, color*/
    int COLOR;
    if (colour == "RED") COLOR = 41;
    if (colour == "GREEN") COLOR = 42;
    if (colour == "YELLOW") COLOR = 43;
    if (colour == "BLUE") COLOR = 44;
    if (colour == "WHITE") COLOR = 47;

    gotoXY(left_margin, line); color2(COLOR); cout << setw(right_margin - left_margin + 1) << " ";
    gotoXY(left_margin + 5, line); color2(49); cout << " " + Text + " ";
    resetText();
}

long long currencyInput(){
    showCursor();
    int count = 0;
    int key = 0; long long res = 0;
    for (;;){
        key = getkey();
        if (key >= '0' && key <= '9'){
            count++;
            cout << (char)key;
            res = res * 10 + key - '0';
        }
        if (key == 8 && count > 0){
            count--;
            cout << "\b \b";
            res /= 10;
        }
        if (key == 13) break;
    }
    hideCursor();
    return res;
}