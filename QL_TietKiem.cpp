#include "QL_TietKiem.h"

QL_TietKiem::QL_TietKiem(){}

QL_TietKiem::~QL_TietKiem(){
    for(int i=0; i<tableTK.size();i++){
        delete tableTK[i];
    }
    tableTK.clear();
}


void QL_TietKiem::AddTK(QL_GiaoDich& QL_GD, QL_NganHang& QL_NH){
    //init interface
    clr();
    cout << "- Chon vi tien muon rut ra de gui tiet kiem..." << endl; getkey(); 
    int wallet_index = QL_GD.ShowWallet(); clr();
    string wallet_name = QL_GD.getWalletName(wallet_index);
    drawBox(2, 2, 60, 25); gotoXY(6, 2); cout << " TAO MOI SO TIET KIEM ";
    gotoXY(6, 4); cout << "Vi tien       : " << wallet_name;
    gotoXY(6, 6); cout << "Ten tai khoan : ";
    gotoXY(6, 8); cout << "So tien       : ";
    gotoXY(6, 10); cout << "Ngay mo       : ";
    gotoXY(6, 12); cout << "Ky han        :       thang";
    gotoXY(6, 14); cout << "Lai suat      :       %/nam";
    gotoXY(6, 16); cout << "Che do        : ";
    gotoXY(6, 18); cout << "Ghi chu       : ";

    //processing part
    TietKiem *tk = new TietKiem;
    string tempID = QL_GD.tableGD[QL_GD.tableGD.size() - 1]->GetID();
    tempID = QL_GD.next_ID(tempID, GiaoDich::max_ID_digit - 1);
    tk->SetID(tempID);

    string newName; //input name of new Diposit
    int error_count = 0; //var for checking if the name has already existed.
    do { //check if the name is valid
        do {
            if (error_count == 1){
                gotoXY(22, 6); cout << "Ten da ton tai, hay thu ten khac...";
                getchar();
                gotoXY(22, 6); cout << "                                   ";
            }
            error_count++;
            gotoXY(22, 6); getline(cin, newName);
        } while (searchDipositsName_inTK(newName) != -1);
        error_count = 0; //reset error count
        tk->SetTenKhoanTK(newName);
    } while (newName == "");
    
    
    int newAmount; //input amount of new Diposit
    gotoXY(22, 8); cin >> newAmount;
    gotoXY(22, 8); cout << currencyShow(newAmount);

    DateTime newDate; //input date of new Diposit
    gotoXY(22, 10); cin >> newDate;
    gotoXY(22, 10); cout << newDate.GetDateinString();

    int newTerm; //input term of new Diposit
    gotoXY(22, 12); cin >> newTerm;
    gotoXY(22, 12); cout << setw(5) << right <<  newTerm;
    tk->SetTerm(newTerm);

    double newInterest; //input interest of new Diposit
    gotoXY(22, 14); cin >> newInterest;
    gotoXY(22, 14); cout << setw(5) << setprecision(2) << fixed << right << newInterest;
    tk->SetInterest(newInterest);

    int newMode = 0; //input mode of new Diposit
    hideCursor(); drawBox(63, 2, 40, 7); gotoXY(67, 2); cout << " CHON DANG GUI (^/v/ENTER) "; //select mode box
    gotoXY(67, 4); cout << "1. Khong quay vong";
    gotoXY(67, 5); cout << "2. Quay vong goc";
    gotoXY(67, 6); cout << "3. Quay vong ca goc lan lai";
    int key; //key value for holding event
    for (;;){
        color(14);
        for (int i = 0; i < 3; i++){
            gotoXY(65, 4 + i);
            if (i == newMode) cout << ">";
            else cout << " ";
        }
        resetText();
        key = getkey(); //catch event
        if (key == 1072) newMode--; //up
        else if (key == 1080) newMode++; //down
        else if (key == 13) break; //enter
        if (newMode < 0) newMode = 2;
        else if (newMode > 2) newMode = 0;
    }
    showCursor();
    for (int i = 0; i <= 9; i++){ //erase select mode box
        gotoXY(63, 2 + i);
        cout << "                                          ";
    }
    tk->SetMode(newMode);
    gotoXY(22, 16);
    switch (newMode){ //print mode
        case 0: cout << "Khong quay vong"; break;
        case 1: cout << "Quay vong goc"; break;
        case 2: cout << "Quay vong ca goc lan lai"; break;
    }

    string newNote; //input note of new Diposit
    gotoXY(22, 18); cin.ignore(); getline(cin, newNote);

    if (QL_GD.searchWallet(wallet_name) == 2) {
        gotoXY(6, 20); cout << "Phi giao dich : "; currency fee = currencyInput();
        gotoXY(6, 20); cout << "Phi giao dich : " << currencyShow(fee);
        NganHang* temp_NH = new NganHang;
        temp_NH->SetAll(tempID, fee);
        QL_NH.tableNH.push_back(temp_NH);
    }

    //store new Diposit
    tableTK.push_back(tk);
    GiaoDich *newGD = new GiaoDich; newGD->SetAll(tempID, 4, 1, newAmount, wallet_name, newNote, newDate);
    QL_GD.tableGD.push_back(newGD); getchar();
    updateDipositsList();

    clr(); //success message
    drawBox(2, 2, 30, 5); gotoXY(6, 2); cout << " THONG BAO ";
    centerText(17, 4, "Tao so tiet kiem thanh cong!");
    centerButton(1, 1, "OK", 12, 6, 10, "BLUE"); getchar();
}

void QL_TietKiem::AddTK(string ID, string TaiKhoanTK, float Interest, int Term, int Mode){
    TietKiem *temp_TK = new TietKiem; 
    temp_TK->SetAll(ID, TaiKhoanTK, Interest, Term, Mode);
    tableTK.push_back(temp_TK);
    updateDipositsList();
}


void QL_TietKiem::RutTienTK(QL_NganHang& QL_NH, QL_GiaoDich& QL_GD, QL_VayNo& QL_VN){
    clr();
    int posW, pos; currency cost; //pos chỉ định vị trí của tài khoản cần rút trong activeDiposits; posW chỉ định vị trí của ví cần rút tiền về
    if (activeDiposits.size() <= 0){
        drawBox(2, 2, 30, 5); gotoXY(6, 2); cout << " THONG BAO ";
        centerText(17, 5, "Ban hien khong co tai khoan tiet kiem nao");
        getch();
        return;
    }
    
    //chọn tài khoản tiết kiệm cần rút rồi chỉ định index của tài khoản đó trong bảng lưu tất cả giao dịch với tiết kiệm
    pos = ShowTK(QL_NH, QL_GD, QL_VN); int index_in_TK = searchDipositsName_inTK(activeDiposits[pos]); clr();

    posW = QL_GD.ShowWallet(); string t_wallet; //t_wallet là tên của ví cần rút tiền về

    int isBanking = 1; //check if is using bank service for cost applied
    if (posW >= 0 && posW < QL_GD.tableTMA.size()) {
        t_wallet = QL_GD.tableTMA[posW];
        isBanking = 0;
    }
    else if (posW < QL_GD.tableTMA.size() + QL_GD.tableNHG.size()) t_wallet = QL_GD.tableNHG[posW - QL_GD.tableTMA.size()];
    int money = UpdateLaiSuatTK(tableTK[index_in_TK], QL_GD);
    int index_in_GD = searchID(QL_GD.tableGD, tableTK[index_in_TK]->GetIDGD_TK());
    clr();
    drawBox(2, 2, 50, 15); gotoXY(5, 2); cout << " XAC NHAN TAT TOAN : " << activeDiposits[pos] << " ";
    gotoXY(5, 4); cout << setw(10) << left << "SO TIEN" << " : " << setw(18) << left << currencyShow(money);
    gotoXY(5, 6); cout << setw(10) << left << "TIEN GOC" << " : " << setw(18) << left << currencyShow(QL_GD.tableGD[index_in_GD]->Getamount());
    gotoXY(5, 8); cout << setw(10) << left << "VI TIEN" << " : " << setw(18) << left << t_wallet;
    gotoXY(5, 10); cout << setw(10) << left << "GHI CHU" << " : "; 
    gotoXY(5, 12); cout << setw(10) << left << "NGAY" << " : ";
    if (isBanking){
        gotoXY(5, 14); cout << setw(10) << left << "PHI" << " : ";
    }
    gotoXY(18, 10); string note; cin.ignore(); getline(cin, note);
    gotoXY(18, 12); DateTime t_date; cin >> t_date;
    if (isBanking) {
        gotoXY(18, 14); cin >> cost;
    }

    //Control cursor code
    int confirm = 1; int key; hideCursor();
    for (;;){
        centerButton(0, confirm, "HUY", 15, 16, 10, "RED");
        centerButton(1, confirm, "XAC NHAN", 25, 16, 10, "BLUE"); 

        key = getkey();
        if (key == 1077 || key == 1075) confirm = !confirm;
        if (key == 13){
            if (confirm) break;
            else return;
        }        
    }
    
    // Tao giao dich rut tien
    string id = QL_GD.tableGD[QL_GD.tableGD.size() - 1]->GetID();
    id = QL_GD.next_ID(id, GiaoDich::max_ID_digit - 1);
    QL_GD.AddGD(id, 4, 2, money, t_wallet, note, t_date);
    if (isBanking) QL_NH.AddNH(id, cost);
    AddTK(id, activeDiposits[pos], 0, 0, 0);
    updateDipositsList();
}

int QL_TietKiem::ShowTK(QL_NganHang& QL_NH, QL_GiaoDich& QL_GD, QL_VayNo& QL_VN){ // vector<VayNo*>& tableVN){
    clr();
    //left_align = 7; //right margin = 107
    int key; 
    int sizeDip = activeDiposits.size();
    if (sizeDip <=0){
        drawBox(10, 15, 70, 6); gotoXY(15, 15); color2(34); cout << " THONG BAO "; resetText();
        centerText(45, 17, "Ban hien khong co tai khoan tiet kiem nao.");
        centerButton(13, 13, "DONG", 45, 19, 8, "RED");
        key = getch();
        return -1;
    }
    int index = 0; int index_in_TK = -1;
    //clr();
    titleBar(7, 146, 4, "DANH SACH TAI KHOAN TIET KIEM", "BLUE"); centerButton(1, 1, "ESC : THOAT", 132, 4, 15, "RED");
    gotoXY(7, 6); color2(43);
    cout << setw(5) << right << "STT" << " | ";
    cout << setw(17) << left << "TAI KHOAN TIET KIEM" << " | ";
    cout << setw(17) << right << "SO TIEN GUI" << " | ";
    cout << setw(18) << right << "TONG TIET KIEM" << " | "; // khuc nay in ra tong va lai cho toi Today
    cout << setw(10) << right << "LAI SUAT" << " | ";
    cout << setw(10) << right << "KY HAN" << " | ";
    cout << setw(22) << right << "DANG" << " | ";
    cout << setw(15) << right << "NGAY GUI" << " | " << endl;
    resetText();
    for (;;){
        for (int i = 0; i < sizeDip; i++){
            index_in_TK = searchDipositsName_inTK(activeDiposits[i]);
            gotoXY(5, 7 + i); (i == index) ? color2(33) : resetText();        
            gotoXY(7, 7 + i);
            int GD_index = searchID(QL_GD.tableGD, tableTK[index_in_TK]->GetIDGD_TK()); /*tìm vị trí của giao dịch này trong table_GD*/
            cout << setw(5) << right << i + 1 << " | ";
            cout << setw(19) << left << tableTK[index_in_TK]->GetTenKhoanTK() << " | ";
            cout << setw(17) << right << currencyShow(QL_GD.tableGD[GD_index]->Getamount()) << " | ";
            cout << setw(18) << right << currencyShow(UpdateLaiSuatTK(tableTK[index_in_TK], QL_GD)) << " | "; // in ra tong tien gui cho toi hom nay~~
            cout << setw(9) << right << setprecision(2) << fixed << tableTK[index_in_TK]->GetInterest() << "%" << " | ";
            cout << setw(4) << right << tableTK[index_in_TK]->GetTerm() << " thang" << " | ";
            if (tableTK[index_in_TK]->GetMode() == 0)
                cout << setw(22) << right << "KHONG QUAY VONG";
            else if (tableTK[index_in_TK]->GetMode() == 1)
                cout << setw(22) << right << "QUAY VONG GOC";
            else cout << setw(22) << right << "QUAY VONG GOC VA LAI";
            cout << " | " << setw(15) << right << QL_GD.tableGD[GD_index]->GetDate().GetDateinString() << " | " <<endl;
        }
        key = getkey();
        if (key == 1072){
            index--;
            if (index < 0) index = sizeDip - 1;
        }
        else if (key == 1080){
            index++;
            if (index >= sizeDip) index = 0;
        }
        else if (key == 13){
            resetText();
            return index;
        } else if (key == 27){
            resetText();
            return -1;
        }
    }
    resetText();
    return index;
}

void QL_TietKiem::ShowTK(int pos, QL_NganHang& QL_NH, QL_GiaoDich& QL_GD, QL_VayNo& QL_VN){
    int GD_index = searchID(QL_GD.tableGD, tableTK[pos]->GetIDGD_TK());
    QL_GD.ShowGD(GD_index, QL_NH, QL_VN, *this);
}

void QL_TietKiem::DeleteTK(int pos, QL_NganHang& QL_NH, QL_GiaoDich& QL_GD, QL_VayNo& QL_VN){
    int GD_index = searchID(QL_GD.tableGD, tableTK[pos]->GetIDGD_TK());
    QL_GD.DeleteGD(GD_index, QL_NH, QL_VN, *this);
    updateDipositsList();
}

void QL_TietKiem::UpdateTK(int t_pos, QL_NganHang& QL_NH, QL_GiaoDich& QL_GD, QL_VayNo& QL_VN){
    int pos;
    if (t_pos == -1){
        pos = ShowTK(QL_NH, QL_GD, QL_VN); //pos la vi tri cua so tiet kiem trong activeDiposit
        if (pos == -1) return;
        pos = searchDipositsName_inTK(activeDiposits[pos]); //pos la vi tri cua so tiet kiem trong tableTK
        pos = searchID(QL_GD.tableGD, tableTK[pos]->GetIDGD_TK()); //pos la vi tri cua giao dich trong tableGD
    } else pos = searchID(QL_GD.tableGD, tableTK[t_pos]->GetIDGD_TK());
    QL_GD.UpdateGD(pos, QL_NH, QL_VN, *this);
}
void QL_TietKiem::Load(const string& userPath){
    string temp_IDGD_TK, taiKhoanTK, temp_string, line;
    float temp_Interest;
    int temp_Term,temp_Mode;
    TK_FILE = "DATA/" + userPath + "_" + TK_FILE;
    ifstream file;
    file.open(TK_FILE);
    while (!file.eof()){
        TietKiem *temp_T = new TietKiem;
        getline(file, line);
        stringstream ss(line);
        getline(ss, temp_IDGD_TK, '|');
        if (temp_IDGD_TK == "F_END")
        {
            break;
        }
        getline(ss, taiKhoanTK, '|');
        getline(ss, temp_string, '|');
        temp_Interest = stof(temp_string);
        getline(ss, temp_string, '|');
        temp_Term = stoi(temp_string);
        getline(ss, temp_string, '|');
        temp_Mode = stoi(temp_string);
        temp_T->SetAll(temp_IDGD_TK, taiKhoanTK, temp_Interest, temp_Term, temp_Mode);
        tableTK.push_back(temp_T);
    }
    file.close();
}


void QL_TietKiem::Save(){
    ofstream file;
    file.open(TK_FILE);
    int sizeTK = tableTK.size();
    for (int i = 0; i < sizeTK; i++){
        file << tableTK[i]->GetIDGD_TK()<<'|'<< tableTK[i]->GetTenKhoanTK()<<'|'<<tableTK[i]->GetInterest()<<'|'<< tableTK[i]->GetTerm()<<'|'<<tableTK[i]->GetMode()<<endl;
    }
    file << "F_END";
    file.close();
}

currency QL_TietKiem::UpdateLaiSuatTK(TietKiem *tk, QL_GiaoDich& QL_GD){

    DateTime DateToday = DateToday.Today();
    int GD_index = searchID(QL_GD.tableGD, tk->GetIDGD_TK());
    DateTime temp_Date = QL_GD.tableGD[GD_index]->GetDate();
    currency ref_amount = QL_GD.tableGD[GD_index]->Getamount();

    int refTerm = tk->GetTerm();
    DateTime refDate = QL_GD.tableGD[GD_index]->GetDate();

    //0 : khong quay vong, 1 : quay vong goc, 2 : quay vong goc lai
    if (tk->GetMode() == 0){
        if (refDate + 30 * refTerm <= DateToday) return ref_amount * (1 + tk->GetInterest() * refTerm / 1200);
        else return ref_amount;
    }

    int cycle = -1; DateTime tmp_Date = refDate;
    while (refDate < DateToday) {
        cycle++;
        refDate = refDate + 30 * refTerm;
    }

    if (tk->GetMode() == 1){
        return ref_amount * (1 + tk->GetInterest() / 1200 * cycle);
    }
    if (tk->GetMode() == 2){
        cycle = 0;
        while ((temp_Date + cycle * 30) < DateToday) cycle++;
        cycle--;
        while (cycle > 0){
            ref_amount = ref_amount * (1 + tk->GetInterest() / 1200);
            cycle--;
        }
        return ref_amount;
    }
}

void QL_TietKiem::tongQuanTK(QL_GiaoDich& QL_GD){

    int currentY = getY();

    int sizeTK = activeDiposits.size();
    if(sizeTK <=0) {
        gotoXY(4, ++currentY);
        cout << "Ban hien khong co so tiet kiem nao." << endl;
        return;
    } 

    currency gui = 0;
    
    int GD_index, TK_index;
    for (int i = 0; i < sizeTK; i++){
        TK_index = searchDipositsName_inTK(activeDiposits[i]);
        GD_index = searchID(QL_GD.tableGD, tableTK[TK_index]->GetIDGD_TK());

        gui += QL_GD.tableGD[GD_index]->Getamount();
    }
    gotoXY(60, currentY - 2); color(240); cout << setw(30) << left << " SO TIET KIEM"; resetText();
    gotoXY(60, currentY - 1); cout << "Tong gui:  " << currencyShow(gui) << endl;
}

int QL_TietKiem::getSizeTK(){
    return this->tableTK.size();
}

void QL_TietKiem::updateDipositsList(){
    activeDiposits.clear();
    int count = 1;
    int size = tableTK.size();
    //activeDiposits.reserve(500); 
    int i = 0;
    while (i < size){
        count = 1;
        for (int j = 0; j < size; j++){
            if (tableTK[i]->GetTenKhoanTK() == tableTK[j]->GetTenKhoanTK() && i != j){
                count++;
            }
        }
        if (count <= 1) activeDiposits.push_back(tableTK[i]->GetTenKhoanTK());
        i++;
    }
}

int QL_TietKiem::searchDiposits(const string& dipName){
    for (int i = 0; i < activeDiposits.size(); i++)
        if (activeDiposits[i] == dipName) return i;
    return -1;
}

void QL_TietKiem::showDiposits(){
    for (int i = 0; i < activeDiposits.size(); i++){
        cout << i + 1 << ". " << activeDiposits[i] << endl;
    }
}

int QL_TietKiem::searchDipositsName_inTK(const string& dipName){
    for (int i = 0; i < tableTK.size(); i++)
        if (tableTK[i]->GetTenKhoanTK() == dipName) return i;    
    return -1;
}

