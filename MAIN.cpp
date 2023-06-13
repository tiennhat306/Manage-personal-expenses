#include "Menu.h"

void Login(string&);
void Display0(Menu&, int&); // màn hình chính
void Display1(Menu&); // màn hình thêm giao dịch
void Display2(Menu&); // màn hình sổ giao dịch
void Display3(Menu&, DateTime, int); // 0: mode Tuần 1: mode Tháng   // màn hình báo cáo
void Display4(Menu&, int, int); // màn hình quyết toán tháng
void Display5(Menu&); // màn hình sổ vay nợ
void Display6(Menu&); // màn hình sổ tiết kiệm
void Display7(Menu&); // màn hình ví tiền
void Display8(Menu&); // màn hình lọc thông tin và tìm kiếm
void Display9(Menu&); // màn hình sửa xóa chung


int main(){
    while (true) {
        string currentUser = "";
            try {
                Login(currentUser);
            }
            catch (std::invalid_argument const& ex)
            {
                std::cout << "#2: " << ex.what() << '\n';
            }
        Menu List;
        List.Load(currentUser);
        clr();
        List.updateDipositsList();
        int notLogout = 1;
        while (notLogout) {
            Display0(List, notLogout); 
        }
        List.Save();
    }
    return 0;
}

void Login(string& currentUser){
    clr();
    QuanLyUser List;
    List.LoadUser();
    List.ManHinhChaoMung(currentUser);
}

int Logout(){
    return 0;
}

void Display0(Menu &List, int& notLogout){
    clr();
    hideCursor();
    DateTime today;
    today = today.Today();
    List.tongQuan();
    drawBox(98, 2, 35, 15); gotoXY(101, 2); cout << " DANH SACH TAC VU (^/v/ENTER) ";
    gotoXY(103, 4); cout << "1. Them";
    gotoXY(103, 5); cout << "2. So giao dich";
    gotoXY(103, 6); cout << "3. Bao cao chi tieu";
    gotoXY(103, 7); cout << "4. Quyet toan thang";
    gotoXY(103, 8); cout << "5. So vay no";
    gotoXY(103, 9); cout << "6. So tiet kiem";
    gotoXY(103, 10); cout << "7. Vi tien";
    gotoXY(103, 11); cout << "8. Loc thong tin";
    gotoXY(103, 12); cout << "9. Sua xoa thong tin";
    gotoXY(103, 13); cout << "0. Dang xuat";
    int key = 0; int counter = 1;
    color(14);
    for (;;){
        for (int i = 4; i <= 13; i++){
            gotoXY(101, i); if (i == counter + 3) cout << ">"; else cout << " ";
        }
        key = getkey();
        if (key == 1080) counter = counter + 1 > 10 ? 1 : counter + 1;
        if (key == 1072) counter = counter - 1 <= 0 ? 10 : counter - 1;
        if (key == 13) break;
    }

    resetText();

    int thang, nam;
    clr();
    switch (counter) {
        case 1:
            Display1(List);
            List.Save();
            Display0(List, notLogout);
            break;
        case 2:
            Display2(List);
            Display0(List, notLogout);
            break;
        case 3:
            Display3(List, today, 0);
            Display0(List, notLogout);
            break;
        case 4:
            thang = today.GetMonth();
            nam = today.GetYear();
            Display4(List, thang, nam);
            Display0(List, notLogout);
            break;
        case 5:
            Display5(List);
            Display0(List, notLogout);
            break;
        case 6:
            Display6(List);
            Display0(List, notLogout);
            break;
        case 7:
            Display7(List);
            Display0(List, notLogout);
            break;
        case 8:
            Display8(List);
            Display0(List, notLogout);
            break;
        case 9:
            Display9(List);
            Display0(List, notLogout);
            break;
        case 10:
            notLogout = 0;
    }
}

void Display1(Menu& List){
    clr();
    drawBox(2, 2, 30, 7); gotoXY(4, 2); cout << " THEM GIAO DICH (^/v/ENTER) ";
    gotoXY(6, 4); cout << "1. Them giao dich";
    gotoXY(6, 5); cout << "2. Them vi tien";
    gotoXY(6, 6); cout << "3. Them danh muc";
    gotoXY(6, 7); cout << "4. Quay lai";
    int choice = 1; int key;

    color(14);
    for (;;){
        for (int i = 1; i <= 4; i++){
            gotoXY(4, i + 3); if (i == choice) cout << ">"; else cout << " ";
        }
        key = getkey();

        if (key == 1072) choice = choice - 1 <= 0 ? 4 : choice - 1;
        if (key == 1080) choice = choice + 1 > 4 ? 1 : choice + 1;
        if (key == 13) break;
    }
    resetText();

    switch (choice){
        case 1:
            List.Add();
            Display1(List);
            break;

        case 2:
            List.AddWallet();
            Display1(List);
            break;

        case 3:
            List.AddDanhMuc();
            Display1(List);
            break;
        default:
            clr();
            break;
    }
    List.Save();
    clr();
}

void Display2(Menu& List){
    int pos = List.ShowGD();
    if (pos == -1) return; else List.ShowGD(pos);
}

void Display3(Menu& List, DateTime S, int mode)
{
    int month = S.GetMonth();
    int year = S.GetYear();
    if (mode == 0){
        List.thongKeNgayChiTiet(S);
        int currentY = getY() + 2;
        drawBox(2, currentY, 45, 7); gotoXY(6, currentY); cout << " THONG KE CHI TIET (^/v/ENTER) ";
        gotoXY(6, currentY + 2); cout << "1. Hom qua"<<endl;
        gotoXY(6, currentY + 3); cout << "2. Hom sau"<<endl;
        gotoXY(6, currentY + 4); cout << "3. Tuan nay"<<endl;
        gotoXY(6, currentY + 5); cout << "4. Thang nay"<<endl;
        gotoXY(6, currentY + 6); cout << "5. Quay lai" << endl;
        int choice = 0; int key;
        color(14);
        for (;;){
            for (int i = 0; i < 5; i++){
                gotoXY(4, currentY + 2 + i);
                if (i == choice) cout << ">"; else cout << " ";
            }
            key = getkey();
            if (key == 1072) choice--; if (choice < 0) choice = 4;
            if (key == 1080) choice++; if (choice > 4) choice = 0;
            if (key == 13) break;
        }
        resetText();
        switch(choice){
            case 0:
                clr();
                Display3(List, S-1, 0);
                break;
            case 1:
                clr();
                Display3(List, S+1, 0);
                break;
            case 2:
                clr();
                Display3(List, S, 1);
                break;
            case 3:
                clr();
                Display3(List, S, 2);
                break;
            default:
                clr();
                break;
        }
    } else if(mode == 1){
        List.thongKeTuan(S);
        int currentY = getY() + 2;
        drawBox(2, currentY, 45, 7); gotoXY(6, currentY); cout << " THONG KE CHI TIET (^/v/ENTER) ";
        gotoXY(6, currentY + 2); cout << "1. Tuan truoc"<<endl;
        gotoXY(6, currentY + 3); cout << "2. Tuan sau"<<endl;
        gotoXY(6, currentY + 4); cout << "3. Thang nay"<<endl;
        gotoXY(6, currentY + 5); cout << "4. Thoat" << endl;
        int choice = 0; int key;
        color(14);
        for (;;){
            for (int i = 0; i < 4; i++){
                gotoXY(4, currentY + 2 + i);
                if (i == choice) cout << ">"; else cout << " ";
            }
            key = getkey();
            if (key == 1072) choice--; if (choice < 0) choice = 3;
            if (key == 1080) choice++; if (choice > 3) choice = 0;
            if (key == 13) break;
        }
        resetText();
        switch(choice){
            case 0:
                clr();
                Display3(List, S-7, 1);
                break;
            case 1:
                clr();
                Display3(List, S+7, 1);
                break;
            case 2:
                clr();
                Display3(List, S, 2);
                break;
            default:
                clr();
                break;
        }
    } else if (mode == 2) {
        List.thongKeThang(S.GetMonth(), S.GetYear());
        int currentY = getY() + 11;
        drawBox(2, currentY, 45, 7); gotoXY(6, currentY); cout << " THONG KE CHI TIET (^/v/ENTER) ";
        gotoXY(6, currentY + 2); cout << "1. Thang truoc"<<endl;
        gotoXY(6, currentY + 3);  cout << "2. Thang sau"<<endl;
        gotoXY(6, currentY + 4);  cout << "3. Thoat"<<endl;
        int choice = 0; int key;
        color(14);
        for (;;){
            for (int i = 0; i < 3; i++){
                gotoXY(4, currentY + 2 + i);
                if (i == choice) cout << ">"; else cout << " ";
            }
            key = getkey();
            if (key == 1072) choice--; if (choice < 0) choice = 2;
            if (key == 1080) choice++; if (choice > 2) choice = 0;
            if (key == 13) break;
        }
        resetText();
        DateTime temp_S;
        switch(choice){
            case 0:
                if(month!=1) temp_S.SetDate(1, month-1, year);
                else temp_S.SetDate(1, 12, year-1);
                clr();
                Display3(List, temp_S, 2);
                break;
            case 1:
                if(month!=12) temp_S.SetDate(1, month+1, year);
                else temp_S.SetDate(1, 1, year+1);
                clr();
                Display3(List, temp_S, 2);
                break;
            default:
                clr();
                break;
        }
    }

}

void Display4(Menu& List, int month, int year){
    List.quyetToan(month, year);
    int currentY = getY() + 2;
    drawBox(2, currentY, 30, 5); gotoXY(6, currentY); cout << " CHON CHUC NANG ";
    gotoXY(6, currentY + 2); cout << "1. Quyet toan thang truoc";
    gotoXY(6, currentY + 3); cout << "2. Quyet toan thang sau"<<endl;
    gotoXY(6, currentY + 4); cout << "3. Quay lai"<<endl;
    int choice = 0; int key;
    for (;;){
        for (int i = 0; i < 3; i++){
            gotoXY(4, currentY + 2 + i);
            if (i == choice) cout << ">"; else cout << " ";
        }
        key = getkey();
        if (key == 1072) choice--; if (key == 1080) choice++;
        if (choice < 0) choice = 2; if (choice > 2) choice = 0;
        if (key == 13) break;
        if (key == 27) return;
    }
    resetText();
    switch(choice){
        case 0:
            if(month!=1) month--;
            else {month=12; year--;}
            clr();
            Display4(List, month, year);
            break;
        case 1:
            if(month!=12) month++;
            else {month=1; year++;}
            clr();
            Display4(List, month, year);
            break;
        default:
            clr();
            break;
    }
}

void Display5(Menu& List){
    int pos;
    List.chiTietVN();
    pos = List.ShowVN();
    List.ShowVN(pos); //sua dong ni voi, tai vi trong showGD co sua voi xoa roi.
}

void Display6(Menu& List){
    int pos;
    pos = List.ShowTK(); //pos la thu tu cua giao dich trong activeDiposits
    if (pos == -1) return;//xu li pos : tìm vị trí của tên đầu tiên của pos trong TK để lấy ID, tiếp theo tìm vị trí của GD với ID nớ trong bảng GD
    List.ShowTK(pos);
}

void Display7(Menu& List){
    List.chiTietWallet();
    int currentY = getY() + 2;
    drawBox(2, currentY, 35, 5); gotoXY(6, currentY); cout << " CHON TAC VU (^/v/ENTER) ";
    gotoXY(6, currentY + 2); cout << "1. Chon Vi tien"<<endl;
    gotoXY(6, currentY + 3); cout << "2. Them vi"<<endl;
    gotoXY(6, currentY + 4); cout << "3. Quay lai"<<endl;
    int choice = 0; int key; color(14); int pos;
    for (;;){
        for (int i = 0; i < 3; i++){
            gotoXY(4, currentY + 2 + i);
            if (i == choice) cout << ">"; else cout << " ";
        }
        key = getkey();
        if (key == 1072) choice--; if (choice < 0) choice = 2;
        if (key == 1080) choice++; if (choice > 2) choice = 0;
        if (key == 13) break;
    }
    resetText();
    switch(choice){
        case 0:
            pos = List.ShowWallet();
            clr();
            List.ShowWallet(pos);
            currentY = getY() + 2;
            drawBox(2, currentY, 45, 5); gotoXY(6, currentY); cout << " CHON TAC VU (^/v/ENTER) ";
            gotoXY(6, currentY + 2); cout << "1. Sua ten vi"<<endl;
            gotoXY(6, currentY + 3); cout << "2. Xoa vi"<<endl;
            gotoXY(6, currentY + 4); cout << "3. Quay lai"<<endl;
            int choice1; int key; color(14);
            for (;;){
                for (int i = 0; i < 3; i++){
                    gotoXY(4, currentY + 2 + i);
                    if (i == choice1) cout << ">"; else cout << " ";
                }
                key = getkey();
                if (key == 1072) choice1--; if (choice1 < 0) choice1 = 2;
                if (key == 1080) choice1++; if (choice1 > 2) choice1 = 0;
                if (key == 13) break;
            }
            resetText();
            clr();
            switch(choice1){
                case 0:
                    List.UpdateWallet(pos);
                    break;
                case 1:
                    List.DeleteWallet(pos);
                    break;
                default:
                    break;
            }
            clr();
            Display7(List);
            break;
        case 1:
            List.AddWallet();
            clr();
            Display7(List);
            break;
        default:
            clr();
            break;
    }
}

void Display8(Menu& List){
    clr();
    drawBox(2, 2, 40, 5); gotoXY(6, 2); cout << " TIM KIEM & LOC (^/v/ENTER) ";
    gotoXY(6, 4); cout << "1. Tim kiem thong tin"<<endl;
    gotoXY(6, 5); cout << "2. Loc thong tin"<<endl;
    gotoXY(6, 6); cout << "3. Quay lai"<<endl;
    int choice = 0; int key; color(14);
    for (;;){
        for (int i = 0; i < 3; i++){
            gotoXY(4, 4 + i);
            if (i == choice) cout << ">"; else cout << " ";
        }
        key = getkey();
        if (key == 1072) choice--; if (choice < 0) choice = 2;
        if (key == 1080) choice++; if (choice > 2) choice = 0;
        if (key == 13) break;
    }
    resetText();
    string choice1;
    switch(choice)
    {
        case 0:
            List.Search();
            clr();
            Display8(List);
            break;
        case 1:
            List.locThongTin();
            clr();
            Display8(List);
            break;
        default:
            clr();
            break;
    }
}

void Display9(Menu& List)
{
    drawBox(2, 2, 40, 5); gotoXY(6, 2); cout << " SUA & XOA (^/v/ENTER) ";
    gotoXY(6, 4); cout << "1. Sua thong tin"<<endl;
    gotoXY(6, 5); cout << "2. Xoa thong tin"<<endl;
    gotoXY(6, 6); cout << "3. Quay lai"<<endl;
    int choice = 0; int key; color(14);
    for (;;){
        for (int i = 0; i < 3; i++){
            gotoXY(4, 4 + i);
            if (i == choice) cout << ">"; else cout << " ";
        }
        key = getkey();
        if (key == 1072) choice--; if (choice < 0) choice = 2;
        if (key == 1080) choice++; if (choice > 2) choice = 0;
        if (key == 13) break;
    }
    resetText();
    string choice1; 
    switch(choice)
    {
        case 0:
            List.CallUpdate();
            clr();
            Display9(List);
            break;
        case 1:
            List.CallDelete();
            List.updateDipositsList();
            clr();
            Display9(List);
            break;
        default:
            clr();
            break;
    }
}
