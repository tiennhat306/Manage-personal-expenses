#include "QuanLyUser.h"

QuanLyUser::QuanLyUser(){}

QuanLyUser::~QuanLyUser(){
}

QuanLyUser::QuanLyUser(Vector <User> LU){
    listUser = LU;
}

QuanLyUser::QuanLyUser(const QuanLyUser& QL){
    this->listUser = QL.listUser;
}

void QuanLyUser::LoadUser(){
    ifstream file;
    file.open("QL_User.txt");

    string temp_usrname, temp_pass, temp_name;
    string temp_string, line;
    User temp_user;
    //listUser.reserve(150);

    while (!file.eof()){
        getline(file, line);
        stringstream ss(line);
        getline(ss, temp_usrname, '|');
        if (temp_usrname == "F_END") break;
        getline(ss, temp_pass, '|');
        getline(ss, temp_name, '|');
        temp_user.setAll(temp_usrname, temp_pass, temp_name);

        listUser.push_back(temp_user);
    }
    file.close();

    cout << "FUNCTION ENDED SUCCESSFULLY!\n";
    return;
}

void QuanLyUser::SaveUser(){
    ofstream file;
    file.open("USER.txt");

    for (int i = 0; i < listUser.size(); i++){
        file << listUser[i].getUsername() << "|";
        file << listUser[i].getPassword() << "|";
        file << listUser[i].getName() << "|\n";
    }
    file << "F_END";
}

void QuanLyUser::ManHinhChaoMung(string& currentUser){

    int next = 0;
    do {
        clr();
        hideCursor();
        int work = 0; /*0 : đăng nhập, 1 : đăng ký*/
        drawBox(5, 5, 81, 8);
        centerText(45, 7, "CHAO MUNG BAN DEN VOI CHUONG TRINH QUAN LY CHI TIEU CA NHAN");

        int key;
        for (;;){
            centerButton(1, work, "DANG KY", 65, 10, 15, "BLUE");
            centerButton(0, work, "DANG NHAP", 49, 10, 15, "BLUE");
            key = getkey();
            if (key == 1075 || key == 1077){
                work = !work;
            }
            else if (key == 13){
                break;
            }
        }

        switch (work){
            case 0 : 
                next = ManHinhDangNhap(currentUser);
                break;
            case 1 :
                next = ManHinhDangKy();
        }
    } while (next == 0);
}

int QuanLyUser::findUser(const string& username){
    for (int i = 0; i < listUser.size(); i++){
        if (listUser[i].getUsername() == username){
            return i;
        }
    }
    return -1;
}

int QuanLyUser::ManHinhDangNhap(string& currentUser){
    int c = 0;
    int ch; char username[255];
    int next_job = 1; /*0 : trở về, 1 : kiểm tra*/
    do {
       
        clr();
        hideCursor();
        drawBox(5, 5, 81, 12);
        centerText(45, 7, "DANG NHAP");
        if (c) {
            color(12);
            gotoXY(9, 13); cout << " Tai khoan khong ton tai. Vui long nhap lai.";
        } else color(11); drawBox(9, 9, 73, 1);
        color(15); gotoXY(12, 9); cout << " TAI KHOAN DANG NHAP : "; 
        gotoXY(9, 15); cout << " ->, <- : Tro ve/ Dang nhap";
        gotoXY(9, 16); cout << " ENTER : Chon";
        int key; int i = 0;
        for (;;){
            centerButton(0, next_job, "TRO VE", 49, 15, 15, "WHITE");
            centerButton(1, next_job, "DANG NHAP", 65, 15, 15, "BLUE");       
            
            gotoXY(11 + i, 10); 
            showCursor();
            ch = getkey();
            if(ch == 13){
                if (next_job == 0){
                    return 0;
                }
                else if (next_job == 1){
                    username[i] = '\0';

                    break;
                }
            }
            else if(ch == 8){
                if(i > 0){
                    i--;
                    cout << "\b \b";
                }
            }

            if (ch == 1075 || ch == 1077 || ch == 1080 || ch == 1072) next_job = !next_job;
            else if (ch > char(32) && ch <= char(126)){
                username[i] = ch;
                i++;
                cout << char(ch);
            }
        }
        c++;
    } while (!UsernameCheck(username));
    ManHinhNhapMatKhau(username, currentUser);

    clr();
    drawBox(5, 5, 81, 12);
    color(11);
    centerText(45, 12, "DANG NHAP THANH CONG");
    return 1;
}

int QuanLyUser::UsernameCheck(const string& input){
    for (int i = 0; i < listUser.size(); i++){
        if (listUser[i].getUsername() == input){
            return 1;
        }
    }
    return 0;
}

int QuanLyUser::PasswordCheck(const string& input){
    for (int i = 0; i < listUser.size(); i++){
        if (listUser[i].getPassword() == input){
            return 1;
        }
    }
    return 0;
}

int QuanLyUser::ManHinhNhapMatKhau(const string& account, string& currentUser){
    int c = 0;
    int ch; char password[255];
    string name = listUser[findUser(account)].getName();
    name = "Chao mung " + name;
    do {
       
        clr();
        hideCursor();
        drawBox(5, 5, 81, 12);
        centerText(45, 7, name);
        if (c) {
            color(12);
            gotoXY(9, 13); cout << " Sai mat khau. Vui long nhap lai.";
        } else color(11); drawBox(9, 9, 73, 1);
        color(15); gotoXY(12, 9); cout << " NHAP MAT KHAU : "; 
        gotoXY(9, 15); cout << " ->, <- : Tro ve/ Dang nhap";
        gotoXY(9, 16); cout << " ENTER : Chon";
        int key; int i = 0;
        for (;;){
            centerButton(1, 1, "DANG NHAP", 65, 15, 15, "BLUE");
            
            
            showCursor();
            gotoXY(11 + i, 10); 
            ch = getkey();
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

            if (ch > char(32) && ch <= char(126)){
                password[i] = ch;
                i++;
                cout << "*";
            }
        }
        c++;
    } while (!PasswordCheck(password));
    currentUser = account;
    return 1;
}

int QuanLyUser::ManHinhDangKy(){
    hideCursor();
    int next_job = 0; /*0 : trở về, 1 : tiếp theo*/
    int c = 0;
    int ch; char username[255];
    
    hideCursor();
    do {
        clr();
        drawBox(4, 4, 82, 12);
        centerText(45, 6, "DANG KY"); gotoXY(9, 8); cout << "Buoc 1 / 4 : ";
        if (c) {
            color(12);
            gotoXY(9, 12); cout << " Tai khoan da ton tai. Vui long chon ten khac.";
        } else color(11); drawBox(9, 9, 73, 1);
        gotoXY(13, 9); color(15); cout << " NHAP TEN TAI KHOAN MOI : ";

        gotoXY(9, 14); cout << " ->, <- : Tro ve/ Tiep tuc";
        gotoXY(9, 15); cout << " ENTER : Chon";

        int key; int i = 0;
    
        for (;;){
            centerButton(0, next_job, "TRO VE", 51, 15, 15, "WHITE");
            centerButton(1, next_job, "TIEP THEO", 67, 15, 15, "BLUE");
            
            showCursor();
            gotoXY(11 + i, 10); 
            ch = getkey();
            if(ch == 13){
                if (next_job == 0){
                    return 0;
                }
                else if (next_job == 1){
                    username[i] = '\0';
                    break;
                }
            }
            else if(ch == 8){
                if(i > 0){
                    i--;
                    cout << "\b \b";
                }
            }

            if (ch == 1075 || ch == 1077 || ch == 1080 || ch == 1072) next_job = !next_job;
            else if (ch > char(32) && ch <= char(126)){
                username[i] = ch;
                i++;
                cout << char(ch);
            }
            hideCursor();
        }
        c++;
    } while (UsernameCheck(username));
    ManHinhNhapMatKhauDangKy(username);
    return 1;
}

int QuanLyUser::ManHinhNhapMatKhauDangKy(const string& username){

    hideCursor();
    
    int ch; char password[255];
    
    hideCursor();
    
    clr();
    drawBox(4, 4, 82, 12);
    centerText(45, 6, "DANG KY"); gotoXY(9, 8); cout << "Buoc 2 / 4 : ";
    color(11); drawBox(9, 9, 73, 1);
    gotoXY(13, 9); color(15); cout << " NHAP MAT KHAU CHO TAI KHOAN : ";

    gotoXY(9, 14); cout << " ->, <- : Tro ve/ Tiep tuc";
    gotoXY(9, 15); cout << " ENTER : Chon";

    int key; int i = 0;

    for (;;){
        centerButton(1, 1, "TIEP THEO", 67, 15, 15, "BLUE");
                    
        showCursor();
        gotoXY(11 + i, 10); 
        ch = getkey();
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

        if (ch > char(32) && ch <= char(126)){
            password[i] = ch;
            i++;
            cout << "*";
        }
        hideCursor();
    }
    ManHinhNhapTenDangKy(username, password);
    return 1;
}

int QuanLyUser::ManHinhNhapTenDangKy(const string& username, const string& password){
    int ch; char name[255]; 
    hideCursor();  
    clr();
    drawBox(4, 4, 82, 12);
    centerText(45, 6, "DANG KY"); gotoXY(9, 8); cout << "Buoc 3 / 4 : ";
    color(11); drawBox(9, 9, 73, 1);
    gotoXY(13, 9); color(15); cout << " BAN MUON DUOC GOI LA GI ? ";

    gotoXY(9, 14); cout << " ->, <- : Tro ve/ Tiep tuc";
    gotoXY(9, 15); cout << " ENTER : Chon";

    int key; int i = 0;

    for (;;){
        centerButton(1, 1, "TIEP THEO", 67, 15, 15, "BLUE");
                    
        showCursor();
        gotoXY(11 + i, 10); 
        ch = getkey();
        if(ch == 13){
            name[i] = '\0';
            break;
        }
        else if(ch == 8){
            if(i > 0){
                i--;
                cout << "\b \b";
            }
        }

        if (ch >= char(32) && ch <= char(126)){
            name[i] = ch;
            i++;
            cout << char(ch);
        }
        hideCursor();
    }
    XacNhanDangKy(username, password, name);

    return 1;
}

void QuanLyUser::XacNhanDangKy(const string& username, const string& password, const string& name){
    hideCursor();
    int next_job = 0; /*0 : hien an mat khau, 1 : huy, 2 : xac nhan*/
    int hide = 1;
    int ch;
    
    hideCursor();
    
    clr();
    drawBox(4, 4, 100, 12);
    centerText(52, 6, "XAC NHAN DANG KY"); gotoXY(9, 8); cout << "Buoc 4 / 4 : ";
    
    gotoXY(9, 7); cout << " Tai khoan dang nhap : " << username;
    gotoXY(9, 8); cout << " Mat khau            : "; 
    gotoXY(9, 9); cout << " Ten                 : " << name;

    gotoXY(9, 14); cout << " ->, <- : Hien, an/ Tro ve/ Tiep tuc";
    gotoXY(9, 15); cout << " ENTER : Chon";

    int key; int i = 0;

    for (;;){
        gotoXY(32, 8);
        if (hide){
            for (int i = 0; i < password.length(); i++) cout << "*";
        } else {
            //gray text
            color2(30);
            cout << password;
            color(15);
        }
        
        if (hide) centerButton(0, next_job, "HIEN MAT KHAU", 69, 15, 15, "WHITE");
        else centerButton(0, next_job, "AN MAT KHAU", 69, 15, 15, "BLUE");
        centerButton(1, next_job, "XAC NHAN", 85, 15, 15, "BLUE");
                    
        ch = getkey();
        if(ch == 13){
            if (next_job == 0){
                hide = !hide;
            }
            // if (next_job == 1){
            //     clr();
            //     drawBox(4, 4, 100, 12);
            //     centerText(52, 8, "DA HUY TAI KHOAN DANG KY");
            //     getch(); next_job = -1;
            //     break;
            // }
            if (next_job == 1){
                clr();
                drawBox(4, 4, 100, 12);
                centerText(52, 8, "DA DANG KY THANH CONG"); getch();
                listUser.push_back(User(username, password, name));
                SaveUser();
                ofstream file;
                file.open("DATA/" + username + "_DATA_DANHMUC.txt");
                file << "Tien Luong" << endl <<
                        "Thu nhap phu" << endl <<
                        "Tien thuong" << endl <<
                        "Duoc thuong" << endl <<
                        "Tro cap" << endl <<
                        "Duoc chuyen tien" << endl <<
                        "Khac" << endl <<
                        "W_END" << endl <<
                        "An uong" << endl <<
                        "Mua sam" << endl <<
                        "Quan ao" << endl <<
                        "Di lai" << endl <<
                        "Di choi" << endl <<
                        "Tien dien nuoc" << endl <<
                        "Chuyen tien" << endl <<
                        "Khac" << endl <<
                        "W_END";
                file.close();
                file.open("DATA/" + username + "_DUCHI.txt");
                file.close();
                file.open("DATA/" + username + "_DATA_GIAODICH.txt");
                file.close();
                file.open("DATA/" + username + "_DATA_NGANHANG.txt");
                file.close();
                file.open("DATA/" + username + "_DATA_TIETKIEM.txt");
                file.close();
                file.open("DATA/" + username + "_DATA_VAYNO.txt");
                file.close();
                file.open("DATA/" + username + "_DATA_WALLETLIST.txt");
                file.close();
                getkey();
                return;
            }
        }
        if (next_job != -1){
            if (ch == 1075) next_job = (next_job - 1 + 2) % 2;
            if (ch == 1077) next_job = (next_job + 1 + 2) % 2;
        }        
    }
}