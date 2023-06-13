#include "Menu.h"

Menu::Menu(){

}

Menu::~Menu(){

}

void Menu::Add(){
    QL_GD.AddGD(QL_NH, QL_VN, QL_TK);
    Save();
}

void Menu::AddWallet(){
    QL_GD.AddWallet();
    Save();
}
void Menu::RutTienTK(){
    QL_TK.RutTienTK(QL_NH, QL_GD, QL_VN);
    Save();
}
void Menu::ChuyenTien(){
    QL_GD.ChuyenTien(QL_NH);
    Save();
}
void Menu::AddDanhMuc(){
    QL_GD.AddDanhMuc();
    Save();
}

void Menu::Search(){
    QL_GD.Search(QL_NH);
}

int Menu::searchWallet(string wallet){ //hàm này kiểm tra dạng của ví (1 : ví tiềm mặt, 2 : ví tiền ngân hàng)
    QL_GD.searchWallet(wallet);
}

int Menu::ShowGD(){
    return QL_GD.ShowGD(QL_NH, QL_VN, QL_TK);
    Save();
}

int Menu::ShowVN(){
    return QL_VN.ShowVN(QL_NH, QL_GD, QL_TK);
    Save();
}
int Menu::ShowTK(){
    return QL_TK.ShowTK(QL_NH, QL_GD, QL_VN);
    Save();
}

int Menu::ShowWallet(){
    return QL_GD.ShowWallet();
    Save();
}


void Menu::ShowGD(int pos){
    QL_GD.ShowGD(pos, QL_NH, QL_VN, QL_TK);
    Save();
}

void Menu::ShowVN(int pos){
    QL_VN.ShowVN(pos, QL_NH, QL_GD, QL_TK);
    Save();
}
void Menu::ShowTK(int pos){
    QL_TK.updateDipositsList();
    int tk_pos = QL_TK.searchDipositsName_inTK(QL_TK.activeDiposits[pos]);
    QL_TK.ShowTK(tk_pos, QL_NH, QL_GD, QL_VN);
    Save();
}
void Menu::ShowWallet(int pos){
    QL_GD.ShowWallet(pos, QL_NH);
    Save();
}


void Menu::DeleteGD(int pos){
    cout << "pos = " << pos << endl;
    QL_GD.DeleteGD(pos, QL_NH, QL_VN, QL_TK);
    Save();
}
void Menu::DeleteVN(int pos){
    QL_VN.DeleteVN(pos, QL_NH, QL_GD, QL_TK);
    Save();
}
void Menu::DeleteTK(int pos){
    QL_TK.DeleteTK(pos, QL_NH, QL_GD, QL_VN);
    Save();
}
void Menu::DeleteNH(int pos){
    QL_NH.DeleteNH(pos, QL_GD, QL_VN, QL_TK);
    Save();
}
void Menu::DeleteWallet(int pos){
    QL_GD.DeleteWallet(pos, QL_NH, QL_VN, QL_TK);
    Save();
}

void Menu::CallDelete(){
    clr();
    drawBox(2, 2, 40, 10); gotoXY(4, 2); cout << " CHON DOI TUONG XOA (</>/ENTER) ";
    gotoXY(6, 4); cout << "1. Xoa giao dich thu chi";
    gotoXY(6, 5); cout << "2. Xoa giao dich vay no";
    gotoXY(6, 6); cout << "3. Xoa tai khoan tiet kiem";
    gotoXY(6, 7); cout << "4. Xoa vi tien";
    int choice = 0; color(14); int key;
    for (;;){
        for (int i = 0; i < 4; i++){
            gotoXY(4, i + 4); 
            if (choice == i) {
                 cout << ">";
            } else cout << " ";
        }
        key = getkey();
        if (key == 1072) choice--;
        if (key == 1080) choice++;
        if (choice < 0) choice = 3; if (choice > 3) choice = 0;
        if (key == 13) break;
    }
    resetText();
    
    int pos;
    switch(choice){
        case 0:
            pos = ShowGD();
            if (pos != -1) DeleteGD(pos);
            break;
        case 1:
            clr();
            pos = ShowVN();
            if (pos != -1) DeleteVN(pos);
            break;
        case 2:
            pos = ShowTK();
            if (pos != -1) DeleteTK(QL_TK.searchDipositsName_inTK(QL_TK.activeDiposits[pos]));
            break;
        case 3:
            if (pos != -1) DeleteWallet(-1);
            break;
    }
    Save();
}

void Menu::UpdateGD(int pos){
    QL_GD.UpdateGD(pos, QL_NH, QL_VN, QL_TK);
    Save();
    return;
}
void Menu::UpdateVN(int t_pos){
    QL_VN.UpdateVN(t_pos, QL_NH, QL_GD, QL_TK);
    Save();
}
void Menu::UpdateTK(int t_pos){
    QL_TK.UpdateTK(t_pos, QL_NH, QL_GD, QL_VN);
    Save();
}
void Menu::UpdateDuChi(){
    QL_GD.UpdateDuChi();
    Save();
}
void Menu::UpdateWallet(int t_pos){
    QL_GD.UpdateWallet(t_pos);
    Save();
}
void Menu::CallUpdate(){
    clr();
    drawBox(2, 2, 50, 7); gotoXY(6, 2); cout << " CHON LOAI GD CAN CAP NHAT ";
    gotoXY(6, 4); cout << "1. Giao dich chi tieu"<<endl;
    gotoXY(6, 5); cout << "2. Giao dich vay no"<<endl;
    gotoXY(6, 6); cout << "3. Giao dich tiet kiem"<<endl;
    gotoXY(6, 7); cout << "4. Cap nhat muc du chi"<<endl;
    gotoXY(6, 8); cout << "5. Cap nhat ten Vi"<<endl;
    int key; int choice = 0; color(14);
    for (;;){
        for (int i = 0; i < 5; i++){
            gotoXY(4, 4 + i); if (i == choice) cout << ">"; else cout << " ";
        }
        key = getkey();
        if (key == 1072) choice--; if (key == 1080) choice++;
        if (choice == -1) choice = 4; if (choice == 5) choice = 0;
        if (key == 13) break;
        if (key == 27) return;
    }
    resetText();
    clr();
    switch(choice){
        case 0:
        {
            UpdateGD(-1);
            break;
        }
        case 1:
        {
            UpdateVN(-1);
            break;
        }
        case 2:
        {
            UpdateTK(-1);
            break;
        }
        case 3:
        {
            UpdateDuChi();
            break;
        }
        case 4:
        {
            UpdateWallet(-1);
            break;
        }
        default:
        {
            cout << "\nKhong co thao tac can tim"<<endl;
        }
    }
    Save();
}


void Menu::Load(const string& currentUser){
    QL_GD.Load(currentUser);
    QL_NH.Load(currentUser);
    QL_TK.Load(currentUser);
    QL_VN.Load(currentUser);
}

void Menu::Save(){
    QL_GD.Save();
    QL_NH.Save();
    QL_VN.Save();
    QL_TK.Save();
}


currency Menu::SumWallet(const string& wallet){ //tính số dư tiền theo tên Ví
    return QL_GD.SumWallet(wallet, QL_NH);
}

void Menu::GetBalance(DateTime E){ //tính số dư tiền từ 1 thời gian E
    QL_GD.GetBalance(E, QL_NH);
}


void Menu::tongQuanVN(){
    QL_VN.tongQuanVN(QL_GD);
}
void Menu::tongQuanTK(){
    QL_TK.tongQuanTK(QL_GD);
}
void Menu::tongQuan(){
    QL_GD.tongQuanGD(QL_NH);
    QL_VN.tongQuanVN(QL_GD);
    QL_TK.tongQuanTK(QL_GD);
    Save();
}

void Menu::chiTietVN(){
    QL_VN.chiTietVN(QL_GD);
}

void Menu::chiTietWallet(){
    QL_GD.chiTietWallet(QL_NH);
}

void Menu::quyetToan(int thang, int nam){
    QL_GD.quyetToan(thang, nam, QL_NH);
}


void Menu::thongKeNgay(DateTime S){
    QL_GD.thongKeNgay(S, QL_NH);
}

void Menu::thongKeNgayChiTiet(DateTime S){
    QL_GD.thongKeNgayChiTiet(S, QL_NH);
}

void Menu::thongKeTuan(DateTime S){
    QL_GD.thongKeTuan(S, QL_NH);
}


void Menu::thongKeThang(int month, int year){
    QL_GD.thongKeThang(month, year, QL_NH);
}


void Menu::locThongTin(){
    QL_GD.locThongTin(QL_NH);
}

int Menu::getSizeGD(){
    return QL_GD.getSizeGD();
}
int Menu::getSizeVN() {
    return QL_VN.getSizeVN();
}
int Menu::getSizeTK(){
    return QL_TK.getSizeTK();
}
int Menu::getSizeTMA(){
    return QL_GD.getSizeTMA();
}
int Menu::getSizeNHG(){
    return QL_GD.getSizeNHG();
}


void Menu::updateDipositsList(){
    QL_TK.updateDipositsList();
}
