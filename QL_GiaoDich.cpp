#include "QL_GiaoDich.h"

QL_GiaoDich::QL_GiaoDich(){}

QL_GiaoDich::~QL_GiaoDich(){
    for(int i=0; i<tableGD.size();i++){
        delete tableGD[i];
    }
    tableGD.clear();
}

void QL_GiaoDich::AddGD(QL_NganHang& QL_NH, QL_VayNo& QL_VN, QL_TietKiem& QL_TK){
    int left_align = 7; currency t_amount;
    int work = 0; int temp_cursor = 0; int key; string t_wallet, t_note; DateTime t_date; int check_done = 0;
    int t_group = 0, t_category = -1;
    while (work < 6){
        clr(); hideCursor(); resetText();
        drawBox(3, 3, 100, 20); gotoXY(8, 3); cout << " TAO GIAO DICH MOI ";
        gotoXY(left_align, 5); color2(31); cout << "Thuc hien lien tiep tu tren xuong duoi";
        gotoXY(left_align, 7); color(15); cout << "- NHOM            : ";
        if (work == 0){
            for (;;){
                centerButton(0, temp_cursor, "Thu nhap", 7, 9, 16, "GREEN");
                centerButton(1, temp_cursor, "Chi tieu", 24, 9, 16, "RED");
                centerButton(2, temp_cursor, "Vay no", 41, 9, 16, "BLUE");
                centerButton(3, temp_cursor, "Tiet kiem", 58, 9, 16, "BLUE");
                centerButton(4, temp_cursor, "Chinh sua vi", 75, 9, 16, "WHITE");
                key = getkey();
                if (key == 1075){
                    temp_cursor -= 1;
                    if (temp_cursor < 0) temp_cursor = 4;
                }
                if (key == 1077){
                    temp_cursor += 1;
                    if (temp_cursor > 4) temp_cursor = 0;
                }
                if (key == 13){
                    t_group = temp_cursor;
                    //t_category = -1;
                    break;
                }
            }
        } 
        
        if (work > 0){
            gotoXY(left_align, 7); color(15); cout << "- NHOM            : ";
            switch (t_group){
                case 0 : color(10); cout << "Thu nhap"; break;
                case 1 : color(12); cout << "Chi tieu"; break;
                case 2 : color(11); cout << "Vay no"; break;
                case 3 : color(11); cout << "Tiet kiem"; break;
                case 4 : color(15); cout << "Chinh sua vi"; break;
            }
            resetText();
        }
        
        temp_cursor = 0;
        if (work == 1){
            gotoXY(left_align, 9); color(15); cout << "- DANH MUC        : ";
            t_category = showList(listCategory[t_group], 7, 11, 30, "WHITE", 0);
        } else {
            if (work > 1){
                gotoXY(left_align, 9); cout << "- DANH MUC        : " << listCategory[t_group][t_category] << "     ";
                resetText();
            }
        }
        
        //nếu là giao dịch rút tiền
        if(t_group == 3){
            if (t_category == 1){
                clr();
                QL_TK.RutTienTK(QL_NH, *this, QL_VN); 
                return;
            }
            if (t_category == 0){
                clr();
                QL_TK.AddTK(*this, QL_NH);
                return;
            }
        }
        
        //nếu là thao tác với Ví
        if(t_group == 4){
            if(t_category == 0){
                AddWallet();
                return;
            } 
            if(t_category == 1){
                getkey();
                ChuyenTien(QL_NH);
                return;
            }
        }
        
        if (work == 2){
            int temp_wallet_index = 0;
            temp_wallet_index = ShowWallet();
            if (temp_wallet_index < tableTMA.size()) t_wallet = tableTMA[temp_wallet_index];
            else t_wallet = tableNHG[temp_wallet_index - tableTMA.size()];
        } else if (work > 2){
            gotoXY(left_align, 11); cout << "- VI TIEN         : " << t_wallet;
        }

        if (work == 3){
            gotoXY(left_align, 13); color(15); cout << "- SO TIEN         : ";
            if (t_group == 0) color(10); else if (t_group == 1) color(12); t_amount = currencyInput();
        } else {
            if (work > 3){
                gotoXY(left_align, 13); color(15); cout << "- SO TIEN         : ";
                if (t_group == 0) color(10); else if (t_group == 1) color(12); cout << currencyShow(t_amount) << "     "; resetText();
            }
        }
        
        if (work == 4){
            if (searchWallet(t_wallet) == 2) QL_NH.AddNH(*this);
            if (t_group == 3 && t_category == 0) {
                QL_TK.AddTK(*this, QL_NH); //tao tk moi
                // them updatediposit ở đây ha sao
                return;
            }
            gotoXY(left_align, 15); cin.sync();
            cout << "- GHI CHU         : "; getline(cin, t_note);
        } else if (work > 4){ 
            if (searchWallet(t_wallet) == 2) cout << "- Phi giao dich : " << currencyShow(QL_NH.tableNH[QL_NH.tableNH.size() - 1]->GetCost());
            gotoXY(left_align, 15); cout << "- GHI CHU         : " << t_note;
        }

        if (work == 5){
            gotoXY(left_align, 17); cout << "- NGAY            : "; cin >> t_date; check_done++;
            if (t_group == 2) QL_VN.AddVN(*this);

        } else if (work == 6){
            gotoXY(left_align, 17); cout << "- NGAY            : " << t_date.GetDateinString();
        }

        if (check_done){
            GiaoDich *temp_Q = new GiaoDich;
            string temp_ID;
            temp_ID = tableGD[tableGD.size() - 1]->GetID();
            temp_ID = next_ID(temp_ID, GiaoDich::max_ID_digit - 1);
            temp_Q->SetAll(temp_ID, t_group + 1, t_category + 1, t_amount, t_wallet, t_note, t_date);
            tableGD.push_back(temp_Q);
            //delete temp_Q;
        }
        work++;
    }
    cin.sync();
    
}


void QL_GiaoDich::AddWallet(){
    hideCursor(); clr(); int key; 
    drawBox(1, 1, 80, 12); gotoXY(5, 1); cout << " THEM VI TIEN ";

    gotoXY(5, 3); cout << "Chon loai vi tien ban muon them: ";
    gotoXY(5, 5); cout << "1. Vi tien mat";
    gotoXY(5, 6); cout << "2. Vi ngan hang";

    int choose = 0;
    for (;;){
        gotoXY(3, 5 + choose); cout << ">"; gotoXY(3, !choose + 5); cout << " ";

        key = getkey();
        if (key == 1072 || key == 1080){
            choose = !choose;
        }
        if (key == 13){
            break;
        }      
    }

    string wallet; showCursor();
    if (choose == 0){
        gotoXY(5, 8); cout << "Nhap ten vi tien mat moi  : ";
        
    } else {
        gotoXY(5, 8); cout << "Nhap ten vi ngan hang moi : ";
    }
    for (;;) {
        gotoXY(33, 8); cout << setw(30) << " ";
        gotoXY(33, 8); 
        do {
            getline(cin, wallet);
        } while (wallet == "");

        if (searchWallet(wallet) == -1){
            if (choose == 0){
                tableTMA.push_back(wallet);
            } else {
                tableNHG.push_back(wallet);
            }
            break;
        } else {
            gotoXY(5, 10); cout << "Vi da nhap trung ten voi mot vi khac. Hay nhap lai";
        }
    }
    gotoXY(5, 10); cout << "Tao vi thanh cong";
}

void QL_GiaoDich::ChuyenTien(QL_NganHang& QL_NH){

    int walletInit, walletFinal; /*vị trí ví đầu và ví đích*/
    for (int i = 0; i < 2; i++){
        clr();
        centerButton(0, 1, "TIEP TUC", 20, 24, 10, "BLUE");
        drawBox(2, 2, 50, 27); gotoXY(6, 2); cout << " CHUYEN TIEN ";
        gotoXY(5, 4); cout << setw(10) << left << "TU VI        : ";
        gotoXY(5, 6); cout << setw(10) << left << "DEN VI       : ";
        if (i == 0){
            gotoXY(20, 4); cout << "dang chon vi nay..."; getkey(); walletInit = ShowWallet(); getkey();
        } if (i > 0){
            gotoXY(20, 4); cout << setw(20) << left << getWalletName(walletInit);
            gotoXY(20, 6); cout << "dang chon vi nay...";
            
            int collision_check = 0;
            do {
                if (collision_check){
                    clr(); drawBox(2, 2, 30, 5); gotoXY(6, 2); cout << " THONG BAO ";
                    centerText(17, 5, "Vi dich bi trung, hay chon lai"); getkey();
                }
                getkey();
                walletFinal = ShowWallet();
            } while (walletInit == walletFinal);
        }

        gotoXY(20, 6); cout << setw(20) << left << getWalletName(walletFinal);
        centerButton(1, 1, "TIEP TUC", 25, 8, 10, "BLUE");
    }
    
    string walletInit_name = getWalletName(walletInit);
    string walletFinal_name = getWalletName(walletFinal);
    clr();
    drawBox(2, 2, 50, 27); gotoXY(6, 2); cout << " CHUYEN TIEN : " << walletInit_name << " > " << walletFinal_name  << " ";
    centerButton(0, 1, "TIEP TUC", 20, 24, 10, "BLUE");
    currency available = SumWallet(walletInit_name, QL_NH);
    gotoXY(5, 4); cout << "Vi " << walletInit_name << " hien co:  " << currencyShow(available);
    currency amount = 0;
    gotoXY(5, 6); cout << "So tien        : "; 
    gotoXY(5, 8); cout << "Ghi chu        : ";
    gotoXY(5, 10); cout << "Ngay           : ";
    do {
        if (amount > available){
            gotoXY(22, 6); cout << "                 ";
            gotoXY(5, 7); color(12); cout << "So tien khong hop le, moi nhap lai"; resetText();
        }
        gotoXY(22, 6); amount = currencyInput();
    } while (amount > available);
    gotoXY(22, 6); cout << currencyShow(amount);
    gotoXY(22, 8); string note; cin.ignore(); getline(cin,note);

    DateTime t_date; gotoXY(22, 10); cin >> t_date;
    string id = tableGD[tableGD.size() - 1]->GetID();
    id = next_ID(id, GiaoDich::max_ID_digit - 1);
    
    AddGD(id, 2, 7, amount, walletInit_name, note, t_date);

    //if there is either a wallet is a banking account, require a fee
    currency cost;
    if (searchWallet(walletInit_name) == 2 || searchWallet(walletFinal_name) == 2){
        gotoXY(5, 12); cout << "Phi giao dich  : "; cost = currencyInput();
        gotoXY(22, 12); cout << currencyShow(cost);
    }

    //if walletInit is a banking account, add that fee to the list
    if (searchWallet(walletInit_name) == 2){
        QL_NH.AddNH(id, cost);
    }

    //if walletFinal is a banking account, add that fee to the list
    string id2 = tableGD[tableGD.size() - 1]->GetID();
    id2 = next_ID(id2, GiaoDich::max_ID_digit - 1);
    AddGD(id2, 1, 6, amount, walletFinal_name, note, t_date);
    if (searchWallet(walletFinal_name) == 2){
        QL_NH.AddNH(id2, cost);
    }

    //if both are banking accounts, change the fee of the second banking account transaction to 0
    if (searchWallet(walletInit_name) == 2 && searchWallet(walletFinal_name) == 2){
        QL_NH.tableNH[QL_NH.tableNH.size() - 1]->SetCost(0);
    }

    centerButton(1, 1, "TIEP TUC", 20, 24, 10, "BLUE");

    clr();
    drawBox(2, 2, 40, 10); gotoXY(6, 2); cout << " THONG BAO : CHUYEN TIEN ";
    centerText(22, 5, "Chuyen tien thanh cong"); 
    centerButton(1, 1, "TIEP TUC", 20, 7, 10, "BLUE"); getkey();
}
void QL_GiaoDich::AddDanhMuc(){
    clr(); int choice = 0; int key; hideCursor();
    drawBox(2, 2, 50, 10); gotoXY(6, 2); cout << " THEM DANH MUC (^/v/ENTER) ";
    gotoXY(6, 4); cout << "1. Them danh muc cac khoan Thu" << endl;
    gotoXY(6, 6); cout << "2. Them danh muc cac khoan Chi";

    color(14);
    for (;;){
        for (int i = 0; i < 2; i++){
            gotoXY(4, 4 + i * 2);
            if (i == choice) cout << ">";
            else cout << "  ";
        }
        key = getkey();
        if (key == 1072 || key == 1080) choice = !choice;
        if (key == 13) break;
    }
    resetText();

    clr(); drawBox(2, 2, 50, 10); string cate; centerButton(0, 1, "TIEP TUC", 40, 8, 10, "BLUE");
    int checkUnique = 1;
    switch (choice){
        case 0 :
            gotoXY(6, 2); cout << " THEM DANH MUC THU ";
            gotoXY(6, 4); cout << "Nhap danh muc Thu moi : ";
            do {
                if (!checkUnique) {
                    color(12); gotoXY(6, 6); cout << "Danh muc nay da ton tai, moi nhap lai"; resetText();
                }
                checkUnique = 1; showCursor(); gotoXY(30, 4); cout << "              "; //presetting
                gotoXY(30, 4); getline(cin, cate); hideCursor();

                for (int i = 0; i < listCategory[0].size(); i++){ //check if is unique
                    if (cate == listCategory[0][i]) {
                        checkUnique = 0;
                        break;
                    }
                }
                
            } while (cate == "" || !checkUnique);
            listCategory[0].push_back(cate);
            break;

        case 1 :
            gotoXY(6, 2); cout << " THEM DANH MUC CHI ";
            gotoXY(6, 4); cout << "Nhap danh muc Chi moi : ";
            do {
                if (!checkUnique) {
                    color(12); gotoXY(6, 6); cout << "Danh muc nay da ton tai, moi nhap lai"; resetText();
                }
                checkUnique = 1; showCursor(); gotoXY(30, 4); cout << "              "; //presetting
                gotoXY(30, 4); getline(cin, cate); hideCursor();

                for (int i = 0; i < listCategory[1].size(); i++){ //check if is unique
                    if (cate == listCategory[1][i]) {
                        checkUnique = 0;
                        break;
                    }
                }

            } while (cate == "" || !checkUnique);
            listCategory[1].push_back(cate);
            break;
    }
    centerButton(1, 1, "TIEP TUC", 40, 8, 10, "BLUE"); getkey();
    clr(); drawBox(2, 2, 50, 10); gotoXY(6, 2); cout << " THONG BAO : ";
    centerText(27, 5, "Them danh muc thanh cong. Nhan phim bat ki..."); getch();
}

void QL_GiaoDich::AddGD(string ID, int group, int category, currency amount, string wTagF, string note, DateTime date){
    GiaoDich *temp_Q = new GiaoDich;
    temp_Q->SetAll(ID, group, category, amount, wTagF, note, date);
    tableGD.push_back(temp_Q);
    //delete temp_Q;
}

void QL_GiaoDich::Search(QL_NganHang& QL_NH){
    
    clr(); hideCursor(); drawBox(2, 2, 70, 6); gotoXY(6, 2); cout << " TIM KIEM ";
    centerButton(0, 1, "TIEP TUC", 61, 7, 10, "BLUE");
    gotoXY(6, 4); cout << " Nhap thong tin de tim kiem : ";
    string text;

    showCursor();
    do { //text input before search and check if it is empty
        gotoXY(36, 4); getline(cin, text);
    } while (text == "");
    text = upcase(text);
    hideCursor(); centerButton(1, 1, "TIEP TUC", 61, 7, 10, "BLUE"); getkey();

    currency income = 0; currency payment = 0; //variable init
    int sizeGD = tableGD.size();
    int check = 0;

    int count = 0; //counting the number of satisfied transactions
    for (int i = sizeGD - 1; i >= 0; i--){ //satisfied transaction search
        string group = listGroup[tableGD[i]->Getgroup() - 1]; group = upcase(group);
        string category = listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory() - 1]; category = upcase(category);
        string money = to_string(tableGD[i]->Getamount());
        string wallet = tableGD[i]->GetwalletF(); wallet = upcase(wallet);
        string note = tableGD[i]->Getnote(); note = upcase(note);

        if (group == text || category == text || money == text || wallet == text || note == text){
            if (check == 0) {
                clr(); titleBar(2, 141, 2, " KET QUA TIM KIEM CHO \"" + text + "\" " ,"YELLOW"); //title bar
                color(240); gotoXY(1, 8);
                cout << setw(7) << right << "STT" << " | " 
                     << setw(15) << left << "NHOM" << " | " 
                     << setw(25) << left << "DANH MUC" << " | " 
                     << setw(20)<< right << "SO TIEN" << " | " 
                     << setw(20) << left << "VI TIEN" << " | " 
                     << setw(20) << left << "GHI CHU" << " | " 
                     << setw(15) << right << "NGAY" << " \n";
                     resetText();
            }
            check = 1; count++;
            cout << " " << setw(7) << right << count << " | ";// << *tableGD[i];
            cout
                << setw(15) << left << listGroup[tableGD[i]->Getgroup() - 1] << " | " 
                << setw(25) << left << listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory() - 1] << " | ";
                if (tableGD[i]->Getgroup()-1 == 0) color2(32); else if (tableGD[i]->Getgroup()-1 == 1) color2(31); else color2(34);
                cout << setw(20)<< right << tableGD[i]->Getamount(); resetText();
                cout << " | " << setw(20) << left << tableGD[i]->GetwalletF() << " | " 
                << setw(20) << left << tableGD[i]->Getnote() << " | " 
                << setw(15) << right << tableGD[i]->GetDate().GetDateinString()<<endl;
            if(tableGD[i]->Getgroup() == 1 || tableGD[i]->Getgroup() == 3 && (tableGD[i]->Getcategory() == 2 || tableGD[i]->Getcategory() == 3) || tableGD[i]->Getgroup() == 4 && tableGD[i]->Getcategory() == 2){
                income += tableGD[i]->Getamount();
                if(searchWallet(tableGD[i]->GetwalletF())==2){
                    int NH_index = searchID(QL_NH.tableNH, tableGD[i]->GetID());
                    payment += QL_NH.tableNH[NH_index]->GetCost();
                }
            } else {
                payment += tableGD[i]->Getamount();
                if(searchWallet(tableGD[i]->GetwalletF())==2){
                    int NH_index = searchID(QL_NH.tableNH, tableGD[i]->GetID());
                    payment += QL_NH.tableNH[NH_index]->GetCost();
                }
            }
        }
    }

    if(check == 0){ //if no transaction is satisfied
        clr(); drawBox(2, 2, 70, 6); gotoXY(6, 2); cout << " TIM KIEM > THONG BAO ";
        centerText(36, 4, "Khong co giao dich lien quan den tu khoa nay");
        centerButton(1, 1, "THOAT", 35, 7, 10, "RED"); getkey();
        return;
    } else {
        centerButton(1, 1, "THOAT", 132, getY() + 2, 10, "RED");
        gotoXY(2, 4); cout << "Tong thu : "; color(10); cout << currencyShow(income); resetText();
        gotoXY(2, 5); cout << "Tong chi : "; color(12); cout << currencyShow(payment); resetText();
        gotoXY(2, 6); cout << "So du    : ";
        if (income - payment < 0) color(12);
        if (income - payment > 0) color(10);
        if (income == payment) color(11);
        cout << currencyShow(income - payment); resetText(); getkey();
    }
}

int QL_GiaoDich::searchWallet(string wallet){ //hàm này kiểm tra dạng của ví (1 : ví tiềm mặt, 2 : ví tiền ngân hàng)
    for(int i=0; i< tableTMA.size();i++){ 
        if(tableTMA[i] == wallet) return 1;
    }
    for(int i=0; i< tableNHG.size();i++){ 
        if(tableNHG[i] == wallet) return 2;
    }
    return -1;
}

int QL_GiaoDich::ShowGD(QL_NganHang& QL_NH, QL_VayNo& QL_VN, QL_TietKiem& QL_TK){
    clr(); hideCursor();
    
    int sizeGD = tableGD.size();
    if(sizeGD <=0) {
        drawBox(10, 15, 70, 6); gotoXY(15, 15); color2(34); cout << " THONG BAO ";
        centerText(45, 17, "Ban hien khong co giao dich nao.");
        centerButton(13, 13, "DONG", 45, 19, 8, "RED");
        getch();
        return -1;
    }

    int key;
    int index = sizeGD - 1;
    titleBar(5, 145, 3, " DANH SACH CAC GIAO DICH ", "BLUE");
    gotoXY(5, 5); color2(47);
    cout << setw(6) << right << "STT" << " | ";
    cout << setw(15) << left << "NHOM" << " | ";
    cout << setw(25) << left << "DANH MUC" << " | ";
    cout << setw(20) << right << "SO TIEN" << " | ";
    cout << setw(20) << left << " VI" << " | ";
    cout << setw(20) << left << "GHI CHU" << " | ";
    cout << setw(15) << right << "THOI GIAN" << setw(2) << " ";
    resetText();
    
    for (int i = sizeGD - 1; i >= 0; i--){
        gotoXY(5, sizeGD - 1 - i + 7);
        cout << setw(6) << right << sizeGD - i << " | ";
        cout << setw(15) << left << listGroup[tableGD[i]->Getgroup() - 1] << " | ";
        cout << setw(25) << left << listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory() - 1] << " | ";
        switch (tableGD[i]->Getgroup() - 1){
            case 0 : color(10); break;
            case 1 : color(12); break;
            default : color(11); break;
        }
        if (searchWallet(tableGD[i]->GetwalletF()) == 2){
            int NH_index = searchID(QL_NH.tableNH, tableGD[i]->GetID());
            currency cost = QL_NH.tableNH[NH_index]->GetCost();
            if (tableGD[i]->Getgroup() == 1 || (tableGD[i]->Getgroup() == 3 && (tableGD[i]->Getcategory() == 2 || tableGD[i]->Getcategory() == 3)) || (tableGD[i]->Getgroup() == 4 && tableGD[i]->Getcategory() == 2))
            {
                cout << setw(20) << right <<currencyShow(tableGD[i]->Getamount() - cost);
            }
            else{
                cout << setw(20) << right << currencyShow(tableGD[i]->Getamount() + cost);
            } 
        } else cout << setw(20) << right << currencyShow(tableGD[i]->Getamount());
        resetText();
        cout << " |  " << setw(19) << left << tableGD[i]->GetwalletF() << " | ";
        cout << setw(20) << left << tableGD[i]->Getnote() << " | ";
        cout << setw(15) << right << tableGD[i]->GetDate().GetDateinString() << " | ";
        cout << endl;
    }

    for(;;){
        for (int i = sizeGD - 1; i >= 0; i--){
            gotoXY(4, sizeGD - 1 - i + 7);
            if (index == i){
                color2(33);
                cout << ">";
            } else cout << " ";
        }
        key = getkey();
        if (key == 1080){
            index--;
            if (index < 0) index = sizeGD - 1;
        }
        if (key == 1072){
            index++;
            if (index > sizeGD - 1) index = 0;
        }
        if (key == 13){
            break;
        }
        if (key == 27){
            resetText();
            return -1;
        }
    }
    showCursor();
    resetText();
    return index;  
}

int QL_GiaoDich::ShowWallet(){
    clr();
    hideCursor();

    if(tableTMA.size()<=0 && tableNHG.size()<=0){
        drawBox(10, 15, 70, 6); gotoXY(10, 20); color2(34); cout << " THONG BAO ";
        centerText(45, 17, "Ban hien khong co giao dich nao.");
        centerButton(13, 13, "DONG", 45, 19, 8, "RED");
        getch();
        return -1;
    }
    titleBar(3, 47, 2, " CHON VI TIEN ", "BLUE");
    int key; int wallet_index = 0; int choose_value = 0; int index = 0;
    gotoXY(3, 4); color2(47);
    cout << setw(10) << right << "STT  " << setw(35) << left << "Ten vi tien";
    resetText();

    for (int i = 0; i < tableTMA.size(); i++){
        gotoXY(3, index + 5);
        cout << setw(8) << right << ++index << "  "
             << setw(35) << left << tableTMA[i];
    }
    for (int i = 0; i < tableNHG.size(); i++){
        gotoXY(3, index + 5);
        cout << setw(8) << right << ++index << "  "
             << setw(35) << left << tableNHG[i];
    }
    for(;;){
        for (int i = 0; i < index; i++){
            gotoXY(2, i + 5);
            if (choose_value == i){
                color2(33);
                cout << ">";
            } else cout << " ";
        }
        key = getkey();
        if (key == 1072){
            choose_value--;
            if (choose_value < 0) choose_value = tableTMA.size() + tableNHG.size() - 1;
        }
        if (key == 1080){
            choose_value++;
            if (choose_value > tableTMA.size() + tableNHG.size() - 1) choose_value = 0;
        }
        if (key == 13){
            break;
        }
    }
    showCursor();
    resetText();
    return choose_value;
}


void QL_GiaoDich::ShowGD(int pos, QL_NganHang& QL_NH, QL_VayNo& QL_VN, QL_TietKiem& QL_TK){
    hideCursor();
    int key; int index = 0; int choose_value = 0; int type = 0; int work = 2;

    clr(); drawBox(2, 1, 78, 23);
    gotoXY(7, 1); color2(34); cout << " CHI TIET GIAO DICH "; resetText();

    gotoXY(6, 3); cout << "Nhom                : " << listGroup[tableGD[pos]->Getgroup()-1];
    gotoXY(6, 5); cout << "Danh muc            : " << listCategory[tableGD[pos]->Getgroup()-1][tableGD[pos]->Getcategory()-1];
    gotoXY(6, 7); cout << "So tien             : "; if (tableGD[pos]->Getgroup()-1 == 0) color2(32); else if (tableGD[pos]->Getgroup()-1 == 1) color2(31); else color2(34);
    cout << currencyShow(tableGD[pos]->Getamount()); resetText();
    gotoXY(6, 9); cout << "Vi                  : " << tableGD[pos]->GetwalletF();
    gotoXY(6, 11); cout << "Ghi chu             : " << tableGD[pos]->Getnote();
    gotoXY(6, 13); cout << "Thoi gian           : " << tableGD[pos]->GetDate().GetDateinString();
    if(tableGD[pos]->Getgroup() == 3){
        type = 1;
        color2(30); drawLine(4, 14, 70);
        gotoXY(6, 15); color(14); cout << "THONG TIN VAY/MUON"; resetText();
        int VN_index = searchID(QL_VN.tableVN, tableGD[pos]->GetID());
        gotoXY(6, 17); cout << ((tableGD[pos]->Getcategory() <= 2) ? "Nguoi vay           : " : "Nguoi cho vay       : ") << QL_VN.tableVN[VN_index]->GetWho();
    } else if(tableGD[pos]->Getgroup( ) == 4){
        type = 2;
        int TK_index = searchID(QL_TK.tableTK, tableGD[pos]->GetID());
        color2(30); drawLine(4, 14, 70); color(14); 
        gotoXY(6, 15); cout << "THONG TIN TIET KIEM"; resetText();
        gotoXY(6, 17); cout << "Ten khoan tiet kiem : " << QL_TK.tableTK[TK_index]->GetTenKhoanTK() <<endl;
        gotoXY(6, 19); cout << "Lai suat            : "<< setprecision(2) << fixed <<QL_TK.tableTK[TK_index]->GetInterest() <<"%"<<endl;
        gotoXY(45, 19); cout << "Ky han : " << QL_TK.tableTK[TK_index]->GetTerm() << " thang" <<endl;
        gotoXY(6, 21); cout << "Che do              : "<< ((QL_TK.tableTK[TK_index]->GetMode()==0)?"Khong quay vong":((QL_TK.tableTK[TK_index]->GetMode()==1)?"Quay vong goc":"Quay vong goc va lai"));
    }
    if(searchWallet(tableGD[pos]->GetwalletF()) == 2){
        type = 3;
        int NH_index = searchID(QL_NH.tableNH, tableGD[pos]->GetID());
        gotoXY(50, 7);color(12);
        cout << "(" << currencyShow(QL_NH.tableNH[NH_index]->GetCost()) << " phi GD)";
    }
    resetText();

    for (;;){
        centerButton(0, work, "SUA", 60, 1, 5, "YELLOW");
        centerButton(1, work, "XOA", 65, 1, 5, "RED");
        centerButton(2, work, "X", 70, 1, 5, "RED");
        key = getkey();
        if (key == 1075){
            work--;
            if (work < 0) work = 2;
        }
        if (key == 1077){
            work++;
            if (work > 2) work = 0;
        }
        if (key == 13){

            if (work == 2) return;
            if (work == 1) {
                //thong bao
                int confirm = 0;
                clr(); drawBox(2, 1, 50, 6); gotoXY(5, 1); cout << " THONG BAO ";
                centerText(27, 3, "BAN CO CHAC CHAN MUON XOA KHONG?");
                for (;;){
                    centerButton(1, confirm, "CO", 20, 5, 5, "BLUE");
                    centerButton(0, confirm, "KHONG", 30, 5, 5, "RED");
                    key = getkey();
                    if (key == 1075 || key == 1077) confirm = !confirm;
                    if (key == 13){
                        if (confirm) {
                            DeleteGD(pos, QL_NH, QL_VN, QL_TK);
                            return;
                        } else {
                            ShowGD(pos, QL_NH, QL_VN, QL_TK);
                            return;
                        }
                    }
                }           
                return;
            }
            if (work == 0){
                UpdateGD(pos, QL_NH, QL_VN, QL_TK);
                ShowGD(pos, QL_NH, QL_VN, QL_TK);
                return;
            }
        }
    }
}


void QL_GiaoDich::ShowWallet(int pos, QL_NganHang& QL_NH){
    if(tableTMA.size()<=0 && tableNHG.size()<=0){
        cout << "Ban hien chua co Vi nao"<<endl;
        return;
    }

    clr(); //interface
    drawBox(2, 2, 50, 9); gotoXY(5, 2); cout << " THONG TIN VI TIEN ";
    gotoXY(5, 4); cout << "TEN VI TIEN        : ";
    gotoXY(5, 6); cout << "DANG VI TIEN       : ";
    gotoXY(5, 8); cout << "SO TIEN HIEN CO    : ";

    
    gotoXY(26, 4); cout << getWalletName(pos);
    gotoXY(26, 6); currency walletBalance;
    if (pos >= 0 && pos < tableTMA.size()){
        cout << "Vi tien mat";
        walletBalance = SumWallet(tableTMA[pos], QL_NH);
    } else {
        cout << "Tai khoan ngan hang";
        walletBalance = SumWallet(tableNHG[pos - tableTMA.size()], QL_NH);
    }
    gotoXY(26, 8); walletBalance < 0 ? color(12) : color(10);
    cout << currencyShow(walletBalance);
    resetText();
    
    centerButton(1, 1, "TRO VE", 22, 10, 10, "YELLOW"); getch();
}


void QL_GiaoDich::DeleteGD(int pos, QL_NganHang& QL_NH, QL_VayNo& QL_VN, QL_TietKiem& QL_TK){
    //if the transaction is a transfer, delete the other transaction
    if ((tableGD[pos]->Getgroup() == 1 && tableGD[pos]->Getcategory() == 6) || (tableGD[pos]->Getgroup() == 2 && tableGD[pos]->Getcategory() == 7)){
        int posSend = 0, posReceive = 0;
        if (tableGD[pos]->Getgroup() == 1){ //if the transaction is RECEIVE, find the SEND
            posReceive = pos;
            for (posSend = posReceive - 1; posSend >= 0; posSend--){
                string oID = tableGD[posSend]->GetID();
                int oGroup = tableGD[posSend]->Getgroup();
                int oCategory = tableGD[posSend]->Getcategory();
                currency oAmount = tableGD[posSend]->Getamount();
                string note = tableGD[posSend]->Getnote();
                DateTime oDate = tableGD[posSend]->GetDate();

                if (next_ID(oID, GiaoDich::max_ID_digit - 1) == tableGD[posReceive]->GetID() 
                    && oGroup == 2 && oCategory == 7
                    && oAmount == tableGD[posReceive]->Getamount()
                    && note == tableGD[posReceive]->Getnote()
                    && oDate == tableGD[posReceive]->GetDate()){
                    break;
                }
            }
            tableGD[posSend]->Setcategory(-1);
            DeleteGD(posSend, QL_NH, QL_VN, QL_TK);
        } else {
            posSend = pos;
            for (posReceive = posSend + 1; posReceive < tableGD.size(); posReceive++){
                string oID = tableGD[posReceive]->GetID();
                int oGroup = tableGD[posReceive]->Getgroup();
                int oCategory = tableGD[posReceive]->Getcategory();
                currency oAmount = tableGD[posReceive]->Getamount();
                string note = tableGD[posReceive]->Getnote();
                DateTime oDate = tableGD[posReceive]->GetDate();
                string temp_ID = tableGD[posSend]->GetID();

                if (oID == next_ID(temp_ID, GiaoDich::max_ID_digit - 1) 
                    && oGroup == 1 && oCategory == 6
                    && oAmount == tableGD[posSend]->Getamount()
                    && note == tableGD[posSend]->Getnote()
                    && oDate == tableGD[posSend]->GetDate()){
                    break;
                }
            }
            tableGD[posReceive]->Setcategory(-1);
            DeleteGD(posReceive, QL_NH, QL_VN, QL_TK);
        }
    }
    if(searchWallet(tableGD[pos]->GetwalletF()) == 2){
        int NH_index = searchID(QL_NH.tableNH, tableGD[pos]->GetID());
        QL_NH.tableNH.erase(NH_index);
    }
    if(tableGD[pos]->Getgroup() == 3){
        int VN_index = searchID(QL_VN.tableVN, tableGD[pos]->GetID());
        QL_VN.tableVN.erase(VN_index);
        QL_VN.updateLoansList(*this);
    } 
    else if(tableGD[pos]->Getgroup() == 4){
        int TK_index = searchID(QL_TK.tableTK, tableGD[pos]->GetID());
        QL_TK.tableTK.erase(TK_index);
        QL_TK.updateDipositsList();
    }
    tableGD.erase(pos);
}

void QL_GiaoDich::DeleteWallet(int pos, QL_NganHang& QL_NH, QL_VayNo& QL_VN, QL_TietKiem& QL_TK){
    if(pos == -1){ //nếu như ví tiền cần xóa chưa được xác định
        int index = 0;
        pos = ShowWallet();
    }

    try {
        if (pos < 0 || pos > tableTMA.size() + tableNHG.size() - 1) throw "Vi tien duoc chi dinh nam ngoai pham vi";

        string walletName = getWalletName(pos); hideCursor();
        clr();
        drawBox(2, 2, 60, 5); gotoXY(4, 2); cout << " XAC NHAN XOA (</>/ENTER) ";
        centerText(31, 4, "Ban co chac chan muon xoa vi tien " + walletName + " khong?");
        int key = 0; int choice = 0;
        for (;;){
            centerButton(0, choice, "KHONG", 41, 6, 10, "BLUE");
            centerButton(1, choice, "CO", 51, 6, 10, "RED");
            key = getkey();
            if (key == 1075 || key == 1077) choice = !choice;
            if (key == 13) break;
        }

        if (choice == 0) return; //nếu người dùng không muốn xóa ví tiền
        for (int i = 0; i < tableGD.size();){
            if (tableGD[i]->GetwalletF() == walletName) {
                DeleteGD(i, QL_NH, QL_VN, QL_TK);
            } else i++;
        }

        if (pos < tableTMA.size()){
            tableTMA.erase(pos);
        }
        else
        if (pos >= tableTMA.size()){
            tableNHG.erase(pos - tableTMA.size());
        }
    }
    catch (const char * err){
        clr();
        drawBox(1, 1, 40, 5); gotoXY(4, 1); cout << " DA CO LOI XAY RA ";
        centerText(21, 3, err); getch(); return;
    }
    catch (...){
        clr();
        drawBox(1, 1, 40, 5); gotoXY(4, 1); cout << " DA CO LOI XAY RA ";
        centerText(21, 3, "Da co loi xay ra"); getch(); return;
    }
}



void QL_GiaoDich::UpdateGD(int pos, QL_NganHang& QL_NH, QL_VayNo& QL_VN, QL_TietKiem& QL_TK){
    if (pos <= -1) pos = ShowGD(QL_NH, QL_VN, QL_TK);
    if (pos == -1) return;
    if(tableGD[pos]->Getgroup() == 4 && tableGD[pos]->Getcategory() == 2){
        clr();
        drawBox(2, 2, 50, 5); gotoXY(4, 2); cout << " THONG BAO ";
        centerText(26, 4, "Giao dich rut tiet kiem khong the thay doi");
        centerText(26, 6, "Nhan phim bat ki de tro ve"); getch();
        return;
    }

    //GiaoDich
    int temp_group = 0, temp_category = 0;
    currency temp_amount = 0;
    string temp_walletSend = "", temp_note = "";
    DateTime temp_Date;

    //TietKiem
    string temp_name = "";
    float temp_interestRate = 0;
    int temp_term = 0;
    int temp_mode = 0;

    //VayNo
    string temp_Who = "";

    //Transfer
    string temp_walletReceive = "";
    
    //NganHang
    currency temp_Cost = 0;

    int oldNganHang = 0;
    int oldTietKiem = 0;
    int oldVayNo = 0;
    int oldTransfer = 0;
    int key = 0;
    int isContinue = 0;

    if (searchWallet(tableGD[pos]->GetwalletF()) == 1) oldNganHang = 0; else oldNganHang = 1;
    if (tableGD[pos]->Getgroup() == 4) oldTietKiem = 1; else oldTietKiem = 0;
    if (tableGD[pos]->Getgroup() == 3) oldVayNo = 1; else oldVayNo = 0;
    if ((tableGD[pos]->Getgroup() == 2 && tableGD[pos]->Getcategory() == 7) || (tableGD[pos]->Getgroup() == 1 && tableGD[pos]->Getcategory() == 6)) oldTransfer = 1; else oldTransfer = 0;

    clr();
    int isNganHang = 0;
    int isTietKiem = 0;
    int isVayNo = 0;
    int isTransfer = 0;

    if (searchWallet(tableGD[pos]->GetwalletF()) == 1) isNganHang = 0; else isNganHang = 1;
    if (tableGD[pos]->Getgroup() == 4) isTietKiem = 1; else isTietKiem = 0;
    if (tableGD[pos]->Getgroup() == 3) isVayNo = 1; else isVayNo = 0;
    if ((tableGD[pos]->Getgroup() == 2 && tableGD[pos]->Getcategory() == 7) || (tableGD[pos]->Getgroup() == 1 && tableGD[pos]->Getcategory() == 6)) isTransfer = 1; else isTransfer = 0;

    // cout << isNganHang << isTietKiem << isVayNo << isTransfer << endl; getch();
    //nếu isNganHang thì khi chỉnh sửa cho phép chỉnh sửa thêm phí giao dịch
    //nếu isTietKiem thì khi chỉnh sửa không cho phép đổi group, category
    //nếu is VayNo thì không cho phép chuyển group, cho phép thay đổi category, thay đổi người cho vay

    for (;;){
    Vector<string> updateChoices; //this vector stroes options for user to choose
    if (isTietKiem != 1 && isVayNo != 1 && isTransfer != 1) updateChoices.push_back("Thay doi Nhom");
    if (isTietKiem != 1 && isTransfer != 1) updateChoices.push_back("Thay doi Danh muc");
    updateChoices.push_back("Thay doi So tien");
    if (isTietKiem != 1) updateChoices.push_back("Thay doi Vi tien");
    updateChoices.push_back("Thay doi Ghi chu");
    updateChoices.push_back("Thay doi Ngay thang");

    if (isNganHang == 1) updateChoices.push_back("Thay doi Phi giao dich");
    if (isTransfer == 1) updateChoices.push_back("Thay doi Vi tien nhan");
    if (isVayNo == 1) updateChoices.push_back("Thay doi Nguoi cho vay / nguoi vay");
    if (isTietKiem == 1) updateChoices.push_back("Thay doi Lai suat");
    if (isTietKiem == 1) updateChoices.push_back("Thay doi Ky han");
    if (isTietKiem == 1) updateChoices.push_back("Thay doi Dang gui tien");
    if (isTietKiem == 1) updateChoices.push_back("Thay doi Ten so tiet kiem");

    int choice = 0; int innerChoice = 0;
    
    clr();
    drawBox(2, 2, 50, updateChoices.size()); gotoXY(4, 2); cout << " CHON THONG TIN CAN THAY DOI ";
    choice = showList(updateChoices, 3, 3, 48, "WHITE", 0);
    
    if (updateChoices[choice] == "Thay doi Nhom"){
        clr();
        int oldGroup = tableGD[pos]->Getgroup() - 1;//nếu nhóm bị thay đổi, yêu cầu thay đổi luôn category
        int currentY = getY();
        drawBox(2, currentY, 50, 7); gotoXY(4, currentY); cout << " THAY DOI NHOM " << endl;
        gotoXY(3, getY()); cout << " - Nhom cu      : " << listGroup[oldGroup];
        gotoXY(3, getY() + 2); cout << " - Nhom moi     : "; if (temp_group != 0) cout << listGroup[temp_group]; else cout << "...";

        Vector<string> groupChoices;
        groupChoices.push_back("Thu nhap");
        groupChoices.push_back("Chi tieu");
        drawBox(53, currentY, 35, groupChoices.size()); gotoXY(55, currentY); cout << " CHON NHOM MOI ";
        temp_group = showList(groupChoices, 54, currentY + 1, 33, "WHITE", 0);
        gotoXY(3, currentY + 3); cout << " - Nhom moi     : " << listGroup[temp_group];

        //0 : thu nhap, 1 : chi tieu, 2 : vay no
        if (temp_group != oldGroup){
            tableGD[pos]->Setgroup(temp_group + 1);
            //nếu nhóm bị thay đổi, yêu cầu thay đổi luôn category
            gotoXY(3, currentY + 5); cout << " - Danh muc cu  : " << listCategory[oldGroup][tableGD[pos]->Getcategory()];
            gotoXY(3, currentY + 7); cout << " - Danh muc moi : "; if (temp_category != 0) cout << listCategory[temp_group][temp_category]; else cout << "...";
            drawBox(53, currentY, 35, listCategory[temp_group].size()); gotoXY(55, currentY); cout << " CHON DANH MUC MOI ";
            do {
                temp_category = showList(listCategory[temp_group], 54, currentY + 1, 33, "WHITE", 0);
                if (listCategory[tableGD[pos]->Getgroup() - 1][temp_category] == "Duoc chuyen tien" || listCategory[tableGD[pos]->Getgroup() - 1][temp_category] == "Chuyen tien"){
                    gotoXY(3, 8); cout << " THONG BAO : Khong the chon " << upcase(listCategory[tableGD[pos]->Getgroup() - 1][temp_category]) << " !"; getch();
                }
            } while (listCategory[tableGD[pos]->Getgroup() - 1][temp_category] == "Duoc chuyen tien" || listCategory[tableGD[pos]->Getgroup() - 1][temp_category] == "Chuyen tien");
            temp_category = showList(listCategory[temp_group], 54, currentY + 1, 33, "WHITE", 0);
            tableGD[pos]->Setcategory(temp_category + 1);
        }

        
            // if (oldVayNo == 0 && temp_group == 2){ //nếu là giao dịch với vay nợ, cần thêm thông tin
            //     clr();
            //     drawBox(2, 2, 50, 7); gotoXY(4, 2); cout << " THAY DOI NHOM : THEM THONG TIN ";
            //     gotoXY(4, 4); cout << " - Nhom          : Vay no";
            //     gotoXY(4, 6); cout << " - Danh muc      : " << listCategory[temp_group - 1][temp_category - 1];
            //     gotoXY(4, 8);
            //     if (temp_category == 0 || temp_category == 1) {
            //         cout << " - Nguoi vay     : ";
            //     } else cout << " - Nguoi cho vay     : ";

            //     do {
            //         gotoXY(23, 8);
            //         try {
            //             getline(cin, temp_Who);
            //             if (temp_Who == "") throw 1;
            //         }
            //         catch (int i){
            //             continue;
            //         }
            //     } while (0);
            // }

        tableGD[pos]->Setgroup(temp_group + 1); tableGD[pos]->Setcategory(temp_category + 1);
    }

        if (updateChoices[choice] == "Thay doi Danh muc"){
            clr();
            drawBox(2, 2, 50, 7); gotoXY(4, 2); cout << " THAY DOI DANH MUC ";
            gotoXY(3, 4); cout << " - Danh muc cu  : " << listCategory[tableGD[pos]->Getgroup() - 1][tableGD[pos]->Getcategory() - 1];
            gotoXY(3, 6); cout << " - Danh muc moi : ...";
            drawBox(53, 2, 50, listCategory[tableGD[pos]->Getgroup() - 1].size()); gotoXY(54, 2); cout << " CHON DANH MUC MOI ";
            do {
                temp_category = showList(listCategory[tableGD[pos]->Getgroup() - 1], 54, 3, 48, "WHITE", 0);
                if (listCategory[tableGD[pos]->Getgroup() - 1][temp_category] == "Duoc chuyen tien" || listCategory[tableGD[pos]->Getgroup() - 1][temp_category] == "Chuyen tien"){
                    gotoXY(3, 8); cout << " THONG BAO : Khong the chon " << upcase(listCategory[tableGD[pos]->Getgroup() - 1][temp_category]) << " !"; getch();
                }
            } while (listCategory[tableGD[pos]->Getgroup() - 1][temp_category] == "Duoc chuyen tien" || listCategory[tableGD[pos]->Getgroup() - 1][temp_category] == "Chuyen tien");
            
            gotoXY(3, 6); cout << " - Danh muc moi : " << listCategory[tableGD[pos]->Getgroup() - 1][temp_category];
            tableGD[pos]->Setcategory(temp_category + 1);
        }

        if (updateChoices[choice] == "Thay doi Vi tien"){ //thay đổi ví tiền
            clr();
            drawBox(2, 2, 50, 12); gotoXY(4, 2); cout << " THAY DOI VI TIEN ";
            gotoXY(3, 4); cout << " - Vi tien cu   : " << tableGD[pos]->GetwalletF();
            gotoXY(3, 6); cout << " - Vi tien moi  : ...";
            innerChoice = ShowWallet();
            clr();
            drawBox(2, 2, 50, 7); gotoXY(4, 2); cout << " THAY DOI VI TIEN ";
            gotoXY(3, 4); cout << " - Vi tien cu   : " << tableGD[pos]->GetwalletF();
            gotoXY(3, 6); cout << " - Vi tien moi  : " << getWalletName(innerChoice);
            temp_walletSend = getWalletName(innerChoice);
            tableGD[pos]->Setwallet(temp_walletSend);

            if (oldNganHang == 0 && searchWallet(temp_walletSend) == 2){
                drawBox(53, 2, 50, 7); gotoXY(55, 2); cout << " THAY DOI NHOM : THEM THONG TIN ";
                gotoXY(55, 4); cout << " - Phi giao dich          : "; temp_Cost = currencyInput();
                gotoXY(55, 4); cout << " - Phi giao dich          : " << currencyShow(temp_Cost);
            }
        }

        if (updateChoices[choice] == "Thay doi Ngay thang"){
            clr();
            drawBox(2, 2, 50, 7); gotoXY(4, 2); cout << " THAY DOI NGAY THANG ";
            gotoXY(4, 4); cout << " - Ngay thang cu  : " << tableGD[pos]->GetDate().GetDateinString();
            gotoXY(4, 6); cout << " - Ngay thang moi : ";
            do {
                try {
                    gotoXY(24, 6); cin >> temp_Date;
                }
                catch (...) {
                    gotoXY(4, 8); color(12); cout << "Nhap khong hop le, hay nhap lai"; resetText();
                    continue;
                }
            } while (0);
            
            if (isTransfer == 1){
                int isSender = 0;
                string otherID, thisID; int otherPos = pos;
                try {
                    if (tableGD[pos]->Getgroup() == 1) isSender = 0; else isSender = 1;
                    //find the other transaction
                    thisID = tableGD[pos]->GetID();
                    if (isSender == 1){ //tim vi tien nhan
                        if (isSender == 1){
                        while (1){
                            otherID = tableGD[otherPos]->GetID();
                            if (next_ID(thisID, GiaoDich::max_ID_digit - 1) == otherID) break;
                            otherPos++;
                            if (otherPos == tableGD.size()) throw "OUT OF RANGE";
                        }
                    }
                    } else { //tim vi tien gui
                        while (1){
                            otherID = tableGD[otherPos]->GetID();
                            if (next_ID(otherID, GiaoDich::max_ID_digit - 1) == thisID) break;
                            otherPos--;
                            if (otherPos == -1) throw "OUT OF RANGE";
                        }
                    }
                }
                catch (const char * message) {
                    clr();
                    gotoXY(4, 8); color(12); cout << "Khong tim thay giao dich con lai : " << message; resetText();
                    getch();
                    return;
                }

                int posSend, posReceive;
                if (isSender == 1){
                    posSend = pos;
                    posReceive = otherPos;
                } else {
                    posSend = otherPos;
                    posReceive = pos;
                }
                tableGD[posSend]->Setdate(temp_Date);
                tableGD[posReceive]->Setdate(temp_Date);
            } else tableGD[pos]->Setdate(temp_Date);
        }

        if (updateChoices[choice] == "Thay doi So tien"){
            clr();
            drawBox(2, 2, 50, 7); gotoXY(4, 2); cout << " THAY DOI SO TIEN ";
            gotoXY(4, 4); cout << " - So tien cu     : " << currencyShow(tableGD[pos]->Getamount());
            gotoXY(4, 6); cout << " - So tien moi    : ";
            temp_amount = currencyInput();
            gotoXY(4, 6); cout << " - So tien moi    : " << currencyShow(temp_amount);
            if (isTransfer == 1){
                int isSender = 0;
                string otherID, thisID; int otherPos = pos;
                try {
                    if (tableGD[pos]->Getgroup() == 1) isSender = 0; else isSender = 1;
                    //find the other transaction
                    thisID = tableGD[pos]->GetID();
                    if (isSender == 1){ //tim vi tien nhan
                        if (isSender == 1){
                        while (1){
                            otherID = tableGD[otherPos]->GetID();
                            if (next_ID(thisID, GiaoDich::max_ID_digit - 1) == otherID) break;
                            otherPos++;
                            if (otherPos == tableGD.size()) throw "OUT OF RANGE";
                        }
                    }
                    } else { //tim vi tien gui
                        while (1){
                            otherID = tableGD[otherPos]->GetID();
                            if (next_ID(otherID, GiaoDich::max_ID_digit - 1) == thisID) break;
                            otherPos--;
                            if (otherPos == -1) throw "OUT OF RANGE";
                        }
                    }
                }
                catch (const char * message) {
                    clr();
                    gotoXY(4, 8); color(12); cout << "Khong tim thay giao dich con lai : " << message; resetText();
                    getch();
                    return;
                }

                int posSend, posReceive;
                if (isSender == 1){
                    posSend = pos;
                    posReceive = otherPos;
                } else {
                    posSend = otherPos;
                    posReceive = pos;
                }
                tableGD[posSend]->Setamount(temp_amount);
                tableGD[posReceive]->Setamount(temp_amount);
            } else tableGD[pos]->Setamount(temp_amount);
            hideCursor();
        }

        if (updateChoices[choice] == "Thay doi Phi giao dich"){
            clr();
            int NHpos = searchID(QL_NH.tableNH, tableGD[pos]->GetID());
            drawBox(2, 2, 50, 7); gotoXY(4, 2); cout << " THAY DOI PHI GIAO DICH ";
            gotoXY(4, 4); cout << " - Phi giao dich cu  : " << currencyShow(QL_NH.tableNH[NHpos]->GetCost());
            gotoXY(4, 6); cout << " - Phi giao dich moi : ";
            temp_Cost = currencyInput();
            gotoXY(4, 6); cout << " - Phi giao dich moi : " << currencyShow(temp_Cost);
            QL_NH.tableNH[NHpos]->SetCost(temp_Cost);
            hideCursor();
        }

        if (updateChoices[choice] == "Thay doi Ghi chu"){
            clr();
            drawBox(2, 2, 50, 7); gotoXY(4, 2); cout << " THAY DOI GHI CHU ";
            gotoXY(4, 4); cout << " - Ghi chu cu  : " << tableGD[pos]->Getnote();
            gotoXY(4, 6); cout << " - Ghi chu moi : ";
            do {
                try {
                    gotoXY(24, 6); getline(cin, temp_note);
                }
                catch (...) {
                    gotoXY(4, 8); color(12); cout << "Nhap khong hop le, hay nhap lai"; resetText();
                    continue;
                }
            } while (0);
            if (isTransfer == 1){
                int isSender = 0;
                string otherID, thisID; int otherPos = pos;
                try {
                    if (tableGD[pos]->Getgroup() == 1) isSender = 0; else isSender = 1;
                    //find the other transaction
                    thisID = tableGD[pos]->GetID();
                    if (isSender == 1){ //tim vi tien nhan
                        if (isSender == 1){
                        while (1){
                            otherID = tableGD[otherPos]->GetID();
                            if (next_ID(thisID, GiaoDich::max_ID_digit - 1) == otherID) break;
                            otherPos++;
                            if (otherPos == tableGD.size()) throw "OUT OF RANGE";
                        }
                    }
                    } else { //tim vi tien gui
                        while (1){
                            otherID = tableGD[otherPos]->GetID();
                            if (next_ID(otherID, GiaoDich::max_ID_digit - 1) == thisID) break;
                            otherPos--;
                            if (otherPos == -1) throw "OUT OF RANGE";
                        }
                    }
                }
                catch (const char * message) {
                    clr();
                    gotoXY(4, 8); color(12); cout << "Khong tim thay giao dich con lai : " << message; resetText();
                    getch();
                    return;
                }

                int posSend, posReceive;
                if (isSender == 1){
                    posSend = pos;
                    posReceive = otherPos;
                } else {
                    posSend = otherPos;
                    posReceive = pos;
                }
                tableGD[posSend]->Setnote(temp_note);
                tableGD[posReceive]->Setnote(temp_note);
            } else tableGD[pos]->Setnote(temp_note);
        }

        //Neu la giao dich Tiet kiem
        if (updateChoices[choice] == "Thay doi Lai suat"){
            int TKPos = searchID(QL_TK.tableTK, tableGD[pos]->GetID());
            clr();
            drawBox(2, 2, 50, 7); gotoXY(4, 2); cout << " THAY DOI LAI SUAT ";
            gotoXY(4, 4); cout << " - Lai suat cu  : " << setprecision(2) << QL_TK.tableTK[TKPos]->GetInterest() << "%";
            gotoXY(4, 6); cout << " - Lai suat moi : ";
            do {
                try {
                    showCursor();
                    string inputString; inputString.clear();
                    gotoXY(22, 6); cin >> inputString;
                    temp_interestRate = stod(inputString);
                }
                catch (...) {
                    gotoXY(4, 8); color(12); cout << "Nhap khong hop le, hay nhap lai"; resetText();
                    continue;
                }
            } while (temp_interestRate <= 0.0);
            hideCursor();
            gotoXY(4, 6); cout << " - Lai suat moi : " << setprecision(2) << temp_interestRate << "%";
            QL_TK.tableTK[TKPos]->SetInterest(temp_interestRate);
        }

        if (updateChoices[choice] == "Thay doi Ky han"){
            int TKPos = searchID(QL_TK.tableTK, tableGD[pos]->GetID());
            clr();
            drawBox(2, 2, 50, 7); gotoXY(4, 2); cout << " THAY DOI KY HAN ";
            gotoXY(4, 4); cout << " - Ky han cu    : " << QL_TK.tableTK[TKPos]->GetTerm() << " thang";
            gotoXY(4, 6); cout << " - Ky han moi   : ";
            do {
                try {
                    showCursor();
                    string inputString; inputString.clear();
                    gotoXY(22, 6); cin >> inputString;
                    temp_term = stoi(inputString);
                }
                catch (...) {
                    gotoXY(4, 8); color(12); cout << "Nhap khong hop le, hay nhap lai"; resetText();
                    continue;
                }
            } while (temp_term <= 0);
            hideCursor();
            gotoXY(4, 6); cout << " - Ky han moi   : " << temp_term << " thang";
            QL_TK.tableTK[TKPos]->SetTerm(temp_term);
        }

        if (updateChoices[choice] == "Thay doi Ten so tiet kiem"){
            int TKPos = searchID(QL_TK.tableTK, tableGD[pos]->GetID());
            clr();
            drawBox(2, 2, 50, 7); gotoXY(4, 2); cout << " THAY DOI TEN SO TIET KIEM ";
            gotoXY(4, 4); cout << " - Ten cu    : " << QL_TK.tableTK[TKPos]->GetTenKhoanTK() << endl;
            gotoXY(4, 6); cout << " - Ten moi   : "; showCursor();
            do {
                gotoXY(19, 6); getline(cin, temp_name);
            } while (temp_name == "");
            hideCursor();
            gotoXY(4, 6); cout << " - Ten moi   : " << temp_name;

            for (int i = 0; i < QL_TK.tableTK.size(); i++){
                if (QL_TK.tableTK[i]->GetTenKhoanTK() == QL_TK.tableTK[TKPos]->GetTenKhoanTK()){
                    QL_TK.tableTK[i]->SetTenKhoanTK(temp_name);
                }
            }
        }

        if (updateChoices[choice] == "Thay doi Dang gui tien"){
            hideCursor();
            int TKPos = searchID(QL_TK.tableTK, tableGD[pos]->GetID());
            int oldMode = QL_TK.tableTK[TKPos]->GetMode();
            Vector<string> modeChoices;
            modeChoices.push_back("Khong quay vong");
            modeChoices.push_back("Quay vong goc");
            modeChoices.push_back("Quay vong ca goc lan lai");
            clr();
            drawBox(2, 2, 50, 7); gotoXY(4, 2); cout << " THAY DOI DANG GUI ";
            gotoXY(4, 4); cout << " - Dang gui cu  : " << modeChoices[oldMode];
            gotoXY(4, 6); cout << " - Dang gui moi : ";
            
            drawBox(53, 2, 30, 3); gotoXY(55, 2); cout << " CHON DANG GUI TIEN MOI ";
            temp_mode = showList(modeChoices, 54, 3, 28, "WHITE", 0);

            for (int i = 2; i <= 7; i++){
                gotoXY(53, i); cout << "                                 ";
            }
            gotoXY(4, 6); cout << " - Dang gui moi : " << modeChoices[temp_mode];
            QL_TK.tableTK[TKPos]->SetMode(temp_mode);
        }

        if (updateChoices[choice] == "Thay doi Nguoi cho vay / nguoi vay"){
            int VNPos = searchID(QL_VN.tableVN, tableGD[pos]->GetID());
            clr();
            int type = tableGD[pos]->Getcategory();
            drawBox(2, 2, 50, 7); gotoXY(4, 2); 
            if (type == 1 || type == 2){
                cout << " THAY DOI NGUOI VAY ";
                gotoXY(4, 4); cout << " - Nguoi vay cu      : " << QL_VN.tableVN[VNPos]->GetWho();
                gotoXY(4, 6); cout << " - Nguoi vay moi     : ";
            } else {
                cout << " THAY DOI NGUOI CHO VAY ";
                gotoXY(4, 4); cout << " - Nguoi cho vay cu  : " << QL_VN.tableVN[VNPos]->GetWho();
                gotoXY(4, 6); cout << " - Nguoi cho vay moi : ";
            }
            
            showCursor();
            do {
                gotoXY(27, 6); getline(cin, temp_Who);
            } while (temp_Who == "");
            hideCursor();
            if (type == 1 || type == 2){
                gotoXY(4, 6); cout << " - Nguoi vay moi     : " << temp_Who;
            } else {
                gotoXY(4, 6); cout << " - Nguoi cho vay moi : " << temp_Who;
            }
            QL_VN.tableVN[VNPos]->SetWho(temp_Who);
        }

        if (updateChoices[choice] == "Thay doi Vi tien nhan"){
            int isSender = 0;
            string otherID, thisID; int otherPos = pos;
            try {
                if (tableGD[pos]->Getgroup() == 1) isSender = 0; else isSender = 1;
                //find the other transaction
                thisID = tableGD[pos]->GetID();
                if (isSender == 1){ //tim vi tien nhan
                    if (isSender == 1){
                    while (1){
                        otherID = tableGD[otherPos]->GetID();
                        if (next_ID(thisID, GiaoDich::max_ID_digit - 1) == otherID) break;
                        otherPos++;
                        if (otherPos == tableGD.size()) throw "OUT OF RANGE";
                    }
                }
                } else { //tim vi tien gui
                    while (1){
                        otherID = tableGD[otherPos]->GetID();
                        if (next_ID(otherID, GiaoDich::max_ID_digit - 1) == thisID) break;
                        otherPos--;
                        if (otherPos == -1) throw "OUT OF RANGE";
                    }
                }
            } catch (const char * message) {
                clr();
                gotoXY(4, 8); color(12); cout << "Khong tim thay giao dich con lai : " << message; resetText();
                getch();
                return;
            }

            int posSend, posReceive;
            if (isSender == 1){
                posSend = pos;
                posReceive = otherPos;
            } else {
                posSend = otherPos;
                posReceive = pos;
            }
            clr();
            drawBox(2, 2, 65, 7); gotoXY(4, 2); cout << " THAY DOI VI TIEN NHAN "; gotoXY(4, 4);
            
            gotoXY(4, 4); cout << " GD Chuyen tien cu  : " << tableGD[posSend]->GetwalletF() << " > "; color(14); cout << tableGD[posReceive]->GetwalletF(); resetText();
            gotoXY(4, 6); cout << " GD Chuyen tien moi : " << tableGD[posSend]->GetwalletF() << " > ...";
            getch();
            int err_check = 0;
            do {
                if (err_check == 1){
                    gotoXY(4, 8); cout << " - Vi nhan khong duoc trung voi vi gui. Vui long nhap lai..."; getch();
                }
                err_check = 1;
                temp_walletReceive = getWalletName(ShowWallet());
            } while (temp_walletReceive == tableGD[posSend]->GetwalletF());

            clr();
            drawBox(2, 2, 65, 7); gotoXY(4, 2); cout << " THAY DOI VI TIEN NHAN "; gotoXY(4, 4);
            gotoXY(4, 4); cout << " GD Chuyen tien cu  : " << tableGD[posSend]->GetwalletF() << " > "; color(14); cout << tableGD[posReceive]->GetwalletF(); resetText();
            gotoXY(4, 6); cout << " GD Chuyen tien moi : " << tableGD[posSend]->GetwalletF() << " > "; color(14); cout << temp_walletReceive; resetText();
            gotoXY(4, 8); cout << "                                                             ";
            tableGD[posReceive]->Setwallet(temp_walletReceive);
        }

        //Phan xu li truoc khi thay doi
        if (searchWallet(tableGD[pos]->GetwalletF()) == 1) isNganHang = 0; else isNganHang = 1;
        if (tableGD[pos]->Getgroup() == 4) isTietKiem = 1; else isTietKiem = 0;
        if (tableGD[pos]->Getgroup() == 3) isVayNo = 1; else isVayNo = 0;
        if ((tableGD[pos]->Getgroup() == 2 && tableGD[pos]->Getcategory() == 7) || (tableGD[pos]->Getgroup() == 1 && tableGD[pos]->Getcategory() == 6)) isTransfer = 1; else isTransfer = 0;
        
        //Phan xu li sau khi thay doi
        if (isNganHang != oldNganHang){
            if (isNganHang == 0 && oldNganHang == 1){
                int index_in_NH = searchID(QL_NH.tableNH, tableGD[pos]->GetID());
                QL_NH.DeleteNH(index_in_NH, *this, QL_VN, QL_TK);
            } else {
                int insertPos = 0;
                while (QL_NH.tableNH[insertPos]->GetIDGD_NHG() < tableGD[pos]->GetID()) insertPos++;
                if (insertPos < QL_NH.tableNH.size() - 1 && QL_NH.tableNH[insertPos]->GetIDGD_NHG() == QL_NH.tableNH[insertPos + 1]->GetIDGD_NHG()){
                    QL_NH.tableNH[insertPos]->SetCost(temp_Cost);
                    return;
                } else {
                    NganHang *newNganHang = new NganHang;
                    newNganHang->SetAll(tableGD[pos]->GetID(), temp_Cost);
                    QL_NH.tableNH.insert(insertPos, newNganHang);
                }
            }
        }
        if (isTietKiem != oldTietKiem){
            if (isTietKiem == 0 && oldTietKiem == 1){
                int index_in_TK = searchID(QL_TK.tableTK, tableGD[pos]->GetID());
                // QL_TK.DeleteTK(index_in_TK, QL_NH, *this, QL_VN);
            } else {
                int insertPos = 0;
                while (QL_TK.tableTK[insertPos]->GetIDGD_TK() < tableGD[pos]->GetID()) insertPos++;
                TietKiem *newTietKiem = new TietKiem;
                newTietKiem->SetAll(tableGD[pos]->GetID(), temp_name, temp_interestRate, temp_term, temp_mode);
                QL_TK.tableTK.insert(insertPos, newTietKiem);
            }
            QL_TK.updateDipositsList();
        }

        if (isVayNo != oldVayNo){
            if (isVayNo == 0 && oldVayNo == 1){
                int index_in_VN = searchID(QL_VN.tableVN, tableGD[pos]->GetID());
                QL_VN.DeleteVN(index_in_VN, QL_NH, *this, QL_TK);
            } else {
                int insertPos = 0;
                while (QL_VN.tableVN[insertPos]->GetIDGD_VN() < tableGD[pos]->GetID()) insertPos++;
                VayNo *newVayNo = new VayNo;
                newVayNo->SetAll(tableGD[pos]->GetID(), temp_Who);
                QL_VN.tableVN.insert(insertPos, newVayNo);
            }
        }

        if (searchWallet(tableGD[pos]->GetwalletF()) == 1) oldNganHang = 0; else oldNganHang = 1;
        if (tableGD[pos]->Getgroup() == 4) oldTietKiem = 1; else oldTietKiem = 0;
        if (tableGD[pos]->Getgroup() == 3) oldVayNo = 1; else oldVayNo = 0;
        if ((tableGD[pos]->Getgroup() == 2 && tableGD[pos]->Getcategory() == 7) || (tableGD[pos]->Getgroup() == 1 && tableGD[pos]->Getcategory() == 6)) oldTransfer = 1; else oldTransfer = 0;

        clr();
        drawBox(2, 2, 40, 6); gotoXY(4, 2); cout << " THONG BAO ";
        centerText(22, 4, "Ban muon tiep tuc sua khong?");
        for (;;) {
            centerButton(0, isContinue, "LUU", 11, 6, 10, "BLUE");
            centerButton(1, isContinue, "TIEP TUC", 22, 6, 10, "YELLOW");

            key = getkey();
            if (key == 13) break;
            if (key == 1077 || key == 1075) isContinue = !isContinue;
        }
        if (isContinue == 0) break;
    }

    QL_TK.updateDipositsList();
    Save();
    QL_NH.Save();
    QL_VN.Save();
    QL_TK.Save();
    return;
}

void QL_GiaoDich::UpdateDuChi()
{
    clr();
    titleBar(2, 100, 2, "CAP NHAT DU CHI", "YELLOW");
    gotoXY(2, 4); cout << "MUC DU CHI CU ----------------" << endl;
    color(240); gotoXY(1, 5); cout << setw(4) << right << " STT" << " | " << setw(20) << left << " TEN DU CHI " << " | " << setw(20) << left << " MUC DU CHI " << endl; resetText();
    for (int i = 0; i < listCategory[1].size(); i++)
        cout << "  " << setw(3) << right << i + 1 << " | " << setw(20) << left << listCategory[1][i] << " | " << setw(20) << left << currencyShow(duChi[i]) << endl;
    cout << endl;
    int currentY = getY();
    drawBox(2, currentY, 50, 6); gotoXY(6, currentY); cout << " CHON HINH THUC CAP NHAT ";
    gotoXY(6, currentY + 2); cout << "1. Cap nhat tat ca" << endl; currentY = getY() - 1;
    gotoXY(6, getY()); cout << "2. Cap nhat mot so khoan du chi"<<endl;
    gotoXY(6, getY()); cout << "0. Thoat"<<endl;
    int key; int choice = 0;
    color(14);
    for (;;){
        for (int i = 0; i < 3; i++){
            gotoXY(4, currentY + i);
            if (i == choice) cout << ">"; else cout << " ";
        }
        key = getkey();
        if (key == 1072) choice--;
        if (key == 1080) choice++;
        if (key == 13) break;
        if (choice == -1) choice = 2; if (choice == 3) choice = 0;
    }
    if (choice == 0){
        clr();
        titleBar(2, 100, 2, "NHAP MUC DU CHI MOI", "YELLOW");
        for (int i = 0; i < listCategory[1].size(); i++){
            duChi.clear();
            gotoXY(2, 4 + i); cout << i+1 << " . " <<listCategory[1][i] << " : ";
            currency money = currencyInput();
            duChi.push_back(money);
        }
    }
    else if(choice==1) {
        int pos;
        clr();
        drawBox(2, 2, 27, listCategory[1].size() + 2); gotoXY(4, 2); cout << " DANH SACH DU CHI ";
        pos = showList(listCategory[1], 3, 4, 25, "WHITE", 0);

        clr();
        drawBox(2, 2, 50, 7); gotoXY(4, 2); cout << " CAP NHAT DU CHI ";
        gotoXY(4, 4); cout << " Danh muc du chi : " << listCategory[1][pos] << endl;
        gotoXY(4, 6); cout << " Muc du chi cu   : " << currencyShow(duChi[pos]) << endl;
        gotoXY(4, 8); cout << " Muc du chi moi  : ";
        currency newDuChi = currencyInput();
        gotoXY(4, 8); cout << " Muc du chi moi  : " << currencyShow(newDuChi) << endl;
        duChi[pos] = newDuChi;
    } else return;
}
void QL_GiaoDich::UpdateWallet(int t_pos){
    int pos;
    if(t_pos==-1){
        clr();
        drawBox(2, 2, 50, 6); gotoXY(4, 2); cout << " THONG BAO  ";
        centerText(27, 4, "Tiep theo, chon vi can sua..."); centerButton(1, 1, "TIEP TUC", 17, 6, 10, "BLUE");
        pos = ShowWallet();
        clr();
    } else pos = t_pos;

    if(pos < 0 || pos >= (tableTMA.size()+tableNHG.size())){
        gotoXY(20, 6); cout << "Vi tri khong hop le" << endl;
        return;
    }
    string wallet;
    string t_wallet;
    wallet = getWalletName(pos);
    drawBox(2, 2, 50, 6); gotoXY(4, 2); cout << " THAY DOI TEN VI ";
    gotoXY(4, 4); cout << "Ten vi cu  : " << getWalletName(pos);
    gotoXY(4, 6); cout << "Ten vi moi : ";

    do {
        showCursor();
        gotoXY(17, 6); getline(cin, t_wallet);
    } while (t_wallet == "");
    hideCursor();
    
    if(pos >=0 && pos<tableTMA.size()){
        tableTMA[pos] = t_wallet;
    }
    else if(pos>=tableTMA.size() && pos<tableTMA.size()+tableNHG.size()){
        tableNHG[pos - tableTMA.size()] = t_wallet;
    }
    int size = tableGD.size();
    for (int i = 0; i < size; i++){
        if(tableGD[i]->GetwalletF() == wallet) tableGD[i]->Setwallet(t_wallet);
    }
}

void QL_GiaoDich::LoadGD(){
    string temp_ID, temp_note, temp_walletF, temp_Datec, temp_string, line;
    int temp_group, temp_category;
    currency temp_amount;
    DateTime temp_DateD;

    ifstream file;
    file.open(GD_FILE);
    while (!file.eof()){
        GiaoDich *temp_Q = new GiaoDich;
        getline(file, line);
        stringstream ss(line);
        getline(ss, temp_ID, '|');
        if (temp_ID == "F_END")
        {
            break;
        }
        getline(ss, temp_string, '|');
        temp_group = stoi(temp_string);
        getline(ss, temp_string, '|');
        temp_category = stoi(temp_string);
        getline(ss, temp_string, '|');
        temp_amount = stoll(temp_string);
        getline(ss, temp_walletF, '|');
        getline(ss, temp_note, '|');
        getline(ss, temp_Datec, '|');
        temp_DateD.SetDate(temp_Datec);
        temp_Q->SetAll(temp_ID, temp_group, temp_category, temp_amount, temp_walletF, temp_note, temp_DateD);
        tableGD.push_back(temp_Q);
    }
    file.close();
}

void QL_GiaoDich::LoadWallet(){
    string line;
    int count = 0;
    ifstream file;
    file.open(WL_FILE);
    while (!file.eof()){
        getline(file, line);
        if (line == "W_END") count++;
        else {
            switch (count){
                case 0 :
                    tableTMA.push_back(line);
                    break;
                case 1 :
                    tableNHG.push_back(line);
                    break;
            }
        }  
    }
    file.close();
}

void QL_GiaoDich::LoadDuChi(){
    currency t_duChi;
    string line;
    ifstream file;
    file.open(DC_FILE);
    while (!file.eof()){ 
        getline(file, line);
        if (line == "F_END")
        {
            break;
        }
        t_duChi = stoll(line);
        duChi.push_back(t_duChi);
    }
    file.close();
}
void QL_GiaoDich::LoadDanhMuc(){
    string line;
    int count = 0;
    ifstream file;
    file.open(DM_FILE);
    while (!file.eof()){
        getline(file, line);
        if (line == "W_END") count++;
        else {
            switch (count){
                case 0 :
                    listCategory[0].push_back(line);
                    break;
                case 1 :
                    listCategory[1].push_back(line);
                    break;
            }
        }  
    }
    //listCategory[2]->reserve(4);
    listCategory[2].push_back("Cho vay");
    listCategory[2].push_back("Thu no");
    listCategory[2].push_back("Di vay");
    listCategory[2].push_back("Tra no");
    //listCategory[3].reserve(2);
    listCategory[3].push_back("Tao khoan tiet kiem");
    listCategory[3].push_back("Rut tien tiet kiem");
    //listCategory[4]->reserve(2);
    listCategory[4].push_back("Tao them vi");
    listCategory[4].push_back("Chuyen tien cac vi");
    file.close();
}
void QL_GiaoDich::Load(const string& userPath){
    GD_FILE = "DATA/" + userPath + "_" + GD_FILE;
    WL_FILE = "DATA/" + userPath + "_" + WL_FILE;
    DC_FILE = "DATA/" + userPath + "_" + DC_FILE;
    DM_FILE = "DATA/" + userPath + "_" + DM_FILE;
    LoadGD();
    LoadWallet();
    LoadDuChi();
    LoadDanhMuc();
}

void QL_GiaoDich::Save(){
    ofstream file;
    file.open(GD_FILE); //lưu GiaoDich
    int t_day, t_month, t_year;
    int sizeGD = tableGD.size();
    for (int i = 0; i < sizeGD; i++){
        DateTime temp_Date(tableGD[i]->GetDate());
        t_day = temp_Date.GetDay();
        t_month = temp_Date.GetMonth();
        t_year = temp_Date.GetYear();
        file << tableGD[i]->GetID()<<'|'<<tableGD[i]->Getgroup()<<'|'<<tableGD[i]->Getcategory()<<'|'<<tableGD[i]->Getamount()<<'|'<< tableGD[i]->GetwalletF()<<'|'<<tableGD[i]->Getnote()<<'|';
        file << t_day << "/" << t_month << "/" << t_year<< endl;
    }
    file << "F_END";
    file.close();

    file.open(WL_FILE); //lưu Ví
    int sizeTMA = tableTMA.size(), sizeNHG = tableNHG.size();
    for (int i = 0; i < sizeTMA; i++){
        file << tableTMA[i] << endl;
    }
    file << "W_END" << endl; 
    for (int i = 0; i < sizeNHG; i++){
        file << tableNHG[i] << endl;
    }
    file << "W_END";
    file.close();

    file.open(DC_FILE); //lưu dự chi
    int sizeDC = listCategory[1].size();
    for(int i=0; i<sizeDC;i++){
        file << duChi[i] << endl;
    }
    file << "F_END";
    file.close();

    file.open(DM_FILE); //lưu danh mục
    int size1 = listCategory[0].size(), size2=listCategory[1].size();
    for(int i=0;i<size1;i++){
        file << listCategory[0][i]<<endl;
    }
    file << "W_END"<<endl;
    for(int i=0;i<size2;i++){
        file << listCategory[1][i]<<endl;
    }
    file << "W_END"<<endl;
    file.close();
}


currency QL_GiaoDich::SumWallet(string wallet, QL_NganHang& QL_NH){
    currency sum = 0;
    int check = searchWallet(wallet);
    int sizeGD = tableGD.size();
    for (int i=0;i<sizeGD;i++){
        if(tableGD[i]->GetwalletF() == wallet){
            if(tableGD[i]->Getgroup() == 1 || tableGD[i]->Getgroup()==3 && (tableGD[i]->Getcategory()==2||tableGD[i]->Getcategory()==3)||tableGD[i]->Getgroup()==4 && tableGD[i]->Getcategory()==2) 
                sum += tableGD[i]->Getamount();
            else sum -= tableGD[i]->Getamount(); 
            if (check == 2){
                int NH_index = searchID(QL_NH.tableNH, tableGD[i]->GetID());
                currency cost = QL_NH.tableNH[NH_index]->GetCost();
                sum -= cost;
            }
        }
    }
    return sum;
}

void QL_GiaoDich::GetBalance(DateTime E, QL_NganHang& QL_NH){
    currency in = 0;
    currency out = 0;
    int sizeGD = tableGD.size();
    for (int i = 0; i < sizeGD; i++){
        if (tableGD[i]->GetDate() <= E){
            if (tableGD[i]->Getgroup() == 1|| (tableGD[i]->Getgroup() == 3 && (tableGD[i]->Getcategory() == 2 || tableGD[i]->Getcategory() == 3)) || (tableGD[i]->Getgroup() == 4 && tableGD[i]->Getcategory() == 2)){
                in += tableGD[i]->Getamount();
                if(searchWallet(tableGD[i]->GetwalletF())==2){
                    int NH_index = searchID(QL_NH.tableNH, tableGD[i]->GetID());
                    currency cost = QL_NH.tableNH[NH_index]->GetCost();
                    out += cost;
                }
            }
            else{
                out += tableGD[i]->Getamount();
                if(searchWallet(tableGD[i]->GetwalletF())==2){
                    int NH_index = searchID(QL_NH.tableNH, tableGD[i]->GetID());
                    currency cost = QL_NH.tableNH[NH_index]->GetCost();
                    out += cost;
                }
            }
        }
    }
    gotoXY(4, 4); cout << " - TONG THU NHAP  : "; color(10); cout << setw(25) << right << currencyShow(in) << endl; resetText();
    gotoXY(4, 5); cout << " - TONG CHI TIEU  : "; color(12); cout << setw(25) << right << currencyShow(out) << endl; resetText();
    gotoXY(4, 6); cout << " - SO DU          : "; cout << setw(25) << right << currencyShow(in - out) << endl;
}


string QL_GiaoDich::next_ID(string& inputID, int k){
    string ID = inputID;
    if (ID[k] == '9'){
        ID[k] = 'A';
        return ID;
    }
    if (ID[k] == 'Z'){
        ID[k] = 'a';
        return ID;
    }
    if (ID[k] == 'z'){
        ID[k] = '0';
        return next_ID(ID, k - 1);
    }
    ID[k] += 1;
    return ID;
}


void QL_GiaoDich::GDGanDay(QL_NganHang& QL_NH){
    int currentY = getY();
    color(11); centerText(49, ++currentY, "GIAO DICH GAN DAY"); resetText();
    int sizeGD=tableGD.size();
    if (sizeGD <= 0) {
        gotoXY(4, ++currentY);
        cout << "Ban hien khong co giao dich nao";
        return;
    } else {
        gotoXY(4, ++currentY);
        color(240);
        cout << setw(5) << right << "STT";
        cout << setw(15) << left << "  NHOM";
        cout << setw(20) << left << "DANH MUC";
        cout << setw(18) << right << "SO TIEN";
        cout << setw(16) << left << "   VI";
        //cout << setw(20) << left << "GHI CHU";
        cout << setw(15) << right << "THOI GIAN" << " ";
        resetText();
        for (int i = sizeGD - 1; i >= sizeGD - 5 && i >= 0; i--){
            gotoXY(4, ++currentY);
            cout << setw(5) << right << sizeGD - i;
            cout << setw(15) << left << "  " + listGroup[tableGD[i]->Getgroup() - 1];
            cout << setw(20) << left << listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory() - 1];
            if (tableGD[i]->Getgroup() == 1) color(10); else if (tableGD[i]->Getgroup() == 2) color(12);
            if (searchWallet(tableGD[i]->GetwalletF()) == 2){
                int NH_index = searchID(QL_NH.tableNH, tableGD[i]->GetID());
                currency cost = QL_NH.tableNH[NH_index]->GetCost();
                if (tableGD[i]->Getgroup() == 1 || (tableGD[i]->Getgroup() == 3 && (tableGD[i]->Getcategory() == 2 || tableGD[i]->Getcategory() == 3)) || (tableGD[i]->Getgroup() == 4 && tableGD[i]->Getcategory() == 2))
                {
                    cout << setw(18) << right << currencyShow(tableGD[i]->Getamount() - cost);
                }
                else{
                    cout << setw(18) << right << currencyShow(tableGD[i]->Getamount() + cost);
                } 
            } else cout << setw(18) << right << currencyShow(tableGD[i]->Getamount());
            resetText();
            cout << setw(16) << left << "   " + tableGD[i]->GetwalletF();
            cout <<setw(15) << right << tableGD[i]->GetDate().GetDateinString();
            cout << endl;
        }
    }
}
void QL_GiaoDich::tongQuanGD(QL_NganHang& QL_NH){
    drawBox(2, 2, 95, 32);
    gotoXY(7, 2); cout << " TONG QUAN ";
    DateTime timeE;
    timeE = timeE.Today(); gotoXY(80, 2); cout << " " << timeE << " ";
    GetBalance(timeE, QL_NH);
    chiTietWallet(QL_NH);
    GDGanDay(QL_NH);
    Save();
}


void QL_GiaoDich::chiTietWallet(QL_NganHang& QL_NH){
    int currentX = 4; int currentY = getY();

    int sizeTMA = tableTMA.size();
    int sizeNHG = tableNHG.size();
    if (sizeTMA <= 0 && sizeNHG <= 0){
        currentY += 2;
        gotoXY(currentX, currentY + 2); cout << "Ban hien chua mo vi tien nao"<<endl;
        return;
    }
    currency soDu = 0;
    map<string, currency> Wallet;
    int sizeGD = tableGD.size();
    for (int i = 0; i < sizeGD; i++){
        string name = tableGD[i]->GetwalletF();
        currency money = tableGD[i]->Getamount();
        if(tableGD[i]->Getgroup()==1 || tableGD[i]->Getgroup()==3 && (tableGD[i]->Getcategory()==2||tableGD[i]->Getcategory()==3) || tableGD[i]->Getgroup()==4 && tableGD[i]->Getcategory()==2)
        {
            Wallet[name] += money;
        }
        else
        {
            Wallet[name] -= money;
        }
        if(searchWallet(name)==2){
            int NH_index = searchID(QL_NH.tableNH, tableGD[i]->GetID());
            currency cost = QL_NH.tableNH[NH_index]->GetCost();
            Wallet[name] -= cost;
        }
    }
    int index = 0; currentY += 2;
    color(14); gotoXY(currentX, currentY); cout << "CHI TIET VI TIEN MAT : " << endl; resetText();
    for (int i=0; i<tableTMA.size();i++){
        currentY += 1;
        gotoXY(6, currentY); cout << ++index << ". "<<tableTMA[i] << ":  " << currencyShow(Wallet[tableTMA[i]])<< endl;
        soDu += Wallet[tableTMA[i]];
    }
    currentY += 2;
    color(14); gotoXY(currentX, currentY); cout << "CHI TIET VI NGAN HANG : " << endl; resetText();
    for (int i=0; i<tableNHG.size();i++){
        currentY += 1;
        gotoXY(6, currentY); cout << ++index <<". " <<tableNHG[i] << ":  " << currencyShow(Wallet[tableNHG[i]])<< endl;
        soDu += Wallet[tableNHG[i]];
    }
    // gotoXY(currentX, currentY + 2); cout << "Tong so du :  " << setw(30) << right << currencyShow(soDu) << endl;
}

void QL_GiaoDich::quyetToan(int thang, int nam, QL_NganHang& QL_NH){
    DateTime S(1, thang, nam);
    DateTime F(31, thang, nam);
    int sizeGD = tableGD.size();
    currency in = 0, out = 0;
    for (int i = 0; i < sizeGD; i++){
        if (tableGD[i]->GetDate() < S){
            if (tableGD[i]->Getgroup() == 1 || (tableGD[i]->Getgroup() == 3 && (tableGD[i]->Getcategory() == 2 || tableGD[i]->Getcategory() == 3)) || (tableGD[i]->Getgroup() == 4 && tableGD[i]->Getcategory() == 2)){
                in += tableGD[i]->Getamount();
                if(searchWallet(tableGD[i]->GetwalletF())==2){
                    int NH_index = searchID(QL_NH.tableNH, tableGD[i]->GetID());
                    out += QL_NH.tableNH[NH_index]->GetCost();
                }
            } else {
                out += tableGD[i]->Getamount();
                if(searchWallet(tableGD[i]->GetwalletF())==2){
                    int NH_index = searchID(QL_NH.tableNH, tableGD[i]->GetID());
                    out += QL_NH.tableNH[NH_index]->GetCost();
                }
            }
        }
    }
    titleBar(2, 113, 2, " BANG QUYET TOAN ", "BLUE");
    gotoXY(2, 4); if (thang != 1){
        cout << "So du thang " << thang - 1 << "/" << nam << " : ";
        (in - out >= 0) ? color(10) : color(12);
        cout << currencyShow(in - out) << endl;
    } else {
        cout << "So du thang " << 12 << "/" << nam - 1 << " : ";
        (in - out >= 0) ? color(10) : color(12);
        cout << currencyShow(in - out) << endl;
    }
    resetText();
    map<int, currency> chiTieu;
    for (int i = 0; i < sizeGD; i++){
        if (tableGD[i]->GetDate() >= S && tableGD[i]->GetDate() <= F){
            if (tableGD[i]->Getgroup() == 2){
                chiTieu[tableGD[i]->Getcategory()-1] += tableGD[i]->Getamount();
                if(searchWallet(tableGD[i]->GetwalletF())==2){
                    int NH_index = searchID(QL_NH.tableNH, tableGD[i]->GetID());
                    chiTieu[listCategory[1].size()-1] += QL_NH.tableNH[NH_index]->GetCost();
                }
            }
        }
    }
    gotoXY(2, 6);cout << "BANG QUYET TOAN THANG " << thang << "/" << nam << endl;
    color(240);
    gotoXY(2, 7); cout << " " << setw(3) << right << "STT" << " | " << setw(25) << left << "DANH MUC CHI TIEU" << " | " << setw(20) << left << "CHI TIEU" << " | " << setw(20) << left << "DU CHI" << " | "
         << setw(8) << right << "TIEN DO" << " | " << setw(15) << left << "TINH TRANG" << " | " << endl;
    resetText();
    for (int i = 0; i < listCategory[1].size(); i++){
        gotoXY(2, getY());
        cout << " " << setw(3) << right << i + 1 << " | " << setw(25) << left << listCategory[1][i] << " | " << setw(20) << right << currencyShow(chiTieu[i]) << " | " << setw(20) << right << currencyShow(duChi[i]) << " |"
             << setw(7) << right << setprecision(1) << fixed << (float)chiTieu[i] / duChi[i] * 100 <<" % | " << setw(15) << left << ((chiTieu[i] > duChi[i]) ? "Vuot qua" : "Dung tien do") << " | " << endl;
    }

}

int QL_GiaoDich::dayInWeek(DateTime S){
    int d = S.GetDay();
    int m = S.GetMonth();
    int y = S.GetYear();
    int n = (d + 2 * m + (3 * (m + 1)) / 5 + y + y / 4) % 7;
    if (n != 0) return n; else return 7;
}

void QL_GiaoDich::thongKeNgay(DateTime S, QL_NganHang& QL_NH){
    currency income = 0, payment = 0;
    int sizeGD = tableGD.size();
    for (int i=0; i<sizeGD;i++){
        if (tableGD[i]->GetDate() == S){
            if (tableGD[i]->Getgroup() == 1 || tableGD[i]->Getgroup() == 3 && (tableGD[i]->Getcategory() == 2||tableGD[i]->Getcategory() == 3) || tableGD[i]->Getgroup() == 4 && tableGD[i]->Getcategory() == 2){
                income += tableGD[i]->Getamount();
                if (searchWallet(tableGD[i]->GetwalletF())==2){
                    int NH_index = searchID(QL_NH.tableNH, tableGD[i]->GetID());
                    payment += QL_NH.tableNH[NH_index]->GetCost();
                }
            } else {
                payment += tableGD[i]->Getamount();
                if (searchWallet(tableGD[i]->GetwalletF())==2){
                    int NH_index = searchID(QL_NH.tableNH, tableGD[i]->GetID());
                    payment += QL_NH.tableNH[NH_index]->GetCost();
                }
            }
        }
    }
    int coordX = getX();
    gotoXY(coordX, getY()); color(240); cout << setw(24) << left << " Ngay " + S.GetDateinString() << endl; resetText();
    gotoXY(coordX, getY()); cout << "| Thu   : "; color(10); cout << currencyShow(income) << endl; resetText();
    gotoXY(coordX, getY()); cout << "| Chi   : "; color(12); cout << currencyShow(payment) << endl; resetText();
    gotoXY(coordX, getY()); cout << "| So du : "; (income - payment >= 0) ? color(10) : color(12); cout << currencyShow(income - payment) << endl << endl; resetText();
}
void QL_GiaoDich::thongKeNgay(DateTime S, currency& thu, currency& chi, QL_NganHang& QL_NH){
    currency income = 0, payment = 0;
    int sizeGD = tableGD.size();
    for (int i=0; i<sizeGD;i++){
        if (tableGD[i]->GetDate() == S){
            if (tableGD[i]->Getgroup() == 1 || tableGD[i]->Getgroup() == 3 && (tableGD[i]->Getcategory() == 2||tableGD[i]->Getcategory() == 3) || tableGD[i]->Getgroup() == 4 && tableGD[i]->Getcategory() == 2){
                income += tableGD[i]->Getamount();
                if (searchWallet(tableGD[i]->GetwalletF()) == 2){
                    int NH_index = searchID(QL_NH.tableNH, tableGD[i]->GetID());
                    payment += QL_NH.tableNH[NH_index]->GetCost();
                }
            } else {
                payment += tableGD[i]->Getamount();
                if (searchWallet(tableGD[i]->GetwalletF()) == 2){
                    int NH_index = searchID(QL_NH.tableNH, tableGD[i]->GetID());
                    payment += QL_NH.tableNH[NH_index]->GetCost();
                }
            }
        }
    }
    thu += income;
    chi += payment;
}

void QL_GiaoDich::thongKeNgayChiTiet(DateTime S, QL_NganHang& QL_NH){
    currency income = 0, payment = 0;
    map<string, currency> Thu;
    map<string, currency> Chi;
    int sizeThu, sizeChi;
    sizeThu = listCategory[0].size();
    sizeChi = listCategory[1].size();
    int sizeGD = tableGD.size();
    for (int i=0; i<sizeGD;i++){
        if (tableGD[i]->GetDate() == S){
            if (tableGD[i]->Getgroup() == 1 || tableGD[i]->Getgroup() == 3 && (tableGD[i]->Getcategory() == 2||tableGD[i]->Getcategory() == 3) || tableGD[i]->Getgroup() == 4 && tableGD[i]->Getcategory() == 2)
            {
                income += tableGD[i]->Getamount();
                Thu[listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory() - 1]] += tableGD[i]->Getamount();
                if (searchWallet(tableGD[i]->GetwalletF()) == 2){
                    int NH_index = searchID(QL_NH.tableNH, tableGD[i]->GetID());
                    Chi[listCategory[1][sizeChi - 1]] += QL_NH.tableNH[NH_index]->GetCost();
                    payment += QL_NH.tableNH[NH_index]->GetCost();
                }
            } else {
                payment += tableGD[i]->Getamount();
                Chi[listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory()-1]] += tableGD[i]->Getamount();
                if(searchWallet(tableGD[i]->GetwalletF())==2){
                    int NH_index = searchID(QL_NH.tableNH, tableGD[i]->GetID());
                    Chi[listCategory[1][sizeChi-1]] += QL_NH.tableNH[NH_index]->GetCost();
                    payment += QL_NH.tableNH[NH_index]->GetCost();
                }
            } 
        }
    }
    color(240); cout << " - Ngay " << S.GetDateinString() << " : "<< endl; resetText();
    cout << "   | Thu   : "; color(10); cout << currencyShow(income) << endl; resetText();
    cout << "   | Chi   : "; color(12); cout << currencyShow(payment) << endl; resetText();
    cout << "   | So Du : "; (income - payment >= 0) ? color(10) : color(12); cout << currencyShow(income - payment) << endl << endl; resetText();
    int coordY = getY();
    color(240); cout << setw(53) << left << "   CHI TIET THU NHAP" << endl; resetText();
    color(14); cout << "   Cac khoan thu ca nhan ----------------------------" << endl; resetText();
    for (int i = 0; i < sizeThu; i++){
        cout << setw(6) << right << " + " << setw(20) << left << listCategory[0][i] << " : "<< currencyShow(Thu[listCategory[0][i]]) << endl;
    }
    color(14); cout << endl << "   Khoan thu vay no ---------------------------------" << endl; resetText();
    cout << setw(6) << right << " + " << setw(20) << left << listCategory[2][1] << " : " << currencyShow(Thu[listCategory[2][1]]) << endl;
    cout << setw(6) << right << " + " << setw(20) << left << listCategory[2][2] << " : " << currencyShow(Thu[listCategory[2][2]]) << endl;

    color(14); cout << endl << "   Rut tiet kiem ------------------------------------" << endl; resetText();
    cout << setw(6) << right << " + " << setw(20) << left << listCategory[3][1] << " : " << currencyShow(Thu[listCategory[3][1]]) << endl;

    gotoXY(60, coordY); color(240); cout << setw(53) << left << "   CHI TIET CHI TIEU " << endl; resetText();
    gotoXY(60, getY()); color(14); cout << "   Chi tieu hang ngay -------------------------------" << endl; resetText();
    for (int i = 0; i < sizeChi; i++){
        gotoXY(60, getY()); cout << setw(6) << right << " + " << setw(20) << left << listCategory[1][i] << " : " << currencyShow(Chi[listCategory[1][i]]) << endl;
    }
    gotoXY(60, getY() + 1); color(14); cout << "   Khoan chi vay no ---------------------------------" << endl; resetText();
    gotoXY(60, getY()); cout << setw(6) << right << " + " << setw(20) << left << listCategory[2][0] << " : " << currencyShow(Chi[listCategory[2][0]]) << endl;
    gotoXY(60, getY()); cout << setw(6) << right << " + " << setw(20) << left << listCategory[2][3] << " : " << currencyShow(Chi[listCategory[2][3]]) << endl;
    gotoXY(60, getY() + 1); color(14); cout << "   Gui tiet kiem ------------------------------------" << endl; resetText();
    gotoXY(60, getY()); cout << setw(6) << right << " + " << setw(20) << left << listCategory[3][0] << " : " << currencyShow(Chi[listCategory[3][0]]) << endl;
}

void QL_GiaoDich::thongKeTuan(DateTime S, QL_NganHang& QL_NH){
    int currentY = getY();
    currency thu = 0, chi = 0;
    int n = dayInWeek(S);
    for (int i = n - 1; i >= 0 ; i--) thongKeNgay(S - i, thu, chi, QL_NH);
    for (int i = 1 ; i <= 7 - n ; i++) thongKeNgay(S + i, thu, chi, QL_NH);

    gotoXY(4, currentY); color(240); cout << setw(45) << " Tuan (" + (S - (n - 1)).GetDateinString() + " -> " + (S + (7 - n)).GetDateinString() + ") : " << endl; resetText();
    gotoXY(4, ++currentY); cout << " - Tong thu   : "; color(10); cout << currencyShow(thu); resetText();
    gotoXY(4, ++currentY); cout << " - Tong chi   : "; color(12); cout << currencyShow(chi); resetText();
    gotoXY(4, ++currentY); cout << " - Tong so Du : "; (thu - chi >= 0) ? color(10) : color(12); cout << currencyShow(thu - chi) << endl; resetText();
    gotoXY(4, ++currentY); cout << "Chi tieu trung binh moi ngay : " << currencyShow(chi / 7) << endl << endl;
    int coordX = 1, coordY = getY();
    for (int i = n - 1; i >= 0; i--) {
        gotoXY(coordX, coordY);
        thongKeNgay(S - i, QL_NH);
        coordX += 25;
    }
    for (int i = 1; i <= 7 - n; i++) {
        gotoXY(coordX, coordY);
        thongKeNgay(S+i, QL_NH);
        coordX += 25;
    }
}
void QL_GiaoDich::thongKeTuan(DateTime S, currency& in, currency& out, QL_NganHang& QL_NH){
    int currentY = getY(), currentX = getX();
    currency thu = 0, chi = 0;
    int n = dayInWeek(S);
    for (int i = n - 1; i >= 0; i--) thongKeNgay(S - i, thu, chi, QL_NH);
    for (int i = 1; i <= 7 - n; i++) thongKeNgay(S + i, thu, chi, QL_NH);
    in += thu;
    out += chi;
    gotoXY(currentX, currentY); color(240); cout << setw(45) << " Tuan (" + (S - (n - 1)).GetDateinString() + " -> " + (S + (7 - n)).GetDateinString() + ") : " << endl; resetText();
    gotoXY(currentX, ++currentY); cout << " - Tong thu   : "; color(10); cout << currencyShow(thu); resetText();
    gotoXY(currentX, ++currentY); cout << " - Tong chi   : "; color(12); cout << currencyShow(chi); resetText();
    gotoXY(currentX, ++currentY); cout << " - Tong so Du : "; (thu - chi >= 0) ? color(10) : color(12); cout << currencyShow(thu - chi) << endl; resetText();
}
void QL_GiaoDich::thongKeTuanDauThang(DateTime S, currency& in, currency& out, QL_NganHang& QL_NH){
    int currentY = getY(), currentX = getX();
    currency thu = 0, chi = 0;
    int n = dayInWeek(S);
    for (int i = 0; i <= 7 - n; i++) thongKeNgay(S + i, thu, chi, QL_NH);
    in += thu;
    out += chi;
    gotoXY(currentX, currentY); color(240); cout << setw(45) << " Tuan (" + S.GetDateinString() + " -> " + (S + (7 - n)).GetDateinString() + ") : " << endl; resetText();
    gotoXY(currentX, ++currentY); cout << " - Tong thu   : "; color(10); cout << currencyShow(thu); resetText();
    gotoXY(currentX, ++currentY); cout << " - Tong chi   : "; color(12); cout << currencyShow(chi); resetText();
    gotoXY(currentX, ++currentY); cout << " - Tong so du : "; (thu - chi >= 0) ? color(10) : color(12); cout << currencyShow(thu - chi) << endl; resetText();
}
void QL_GiaoDich::thongKeTuanCuoiThang(DateTime S, currency& in, currency &out, QL_NganHang& QL_NH){
    int currentY = getY(), currentX = getX();
    currency thu = 0, chi = 0;
    int n = dayInWeek(S);
    for (int i = n - 1; i >= 0; i--) thongKeNgay(S - i, thu, chi, QL_NH);
    in += thu;
    out += chi;
    gotoXY(currentX, currentY); color(240); cout << setw(45) << " Tuan (" + (S - (n - 1)).GetDateinString() + " -> " + S.GetDateinString() + ") : " << endl; resetText();
    gotoXY(currentX, ++currentY); cout << " - Tong thu   : "; color(10); cout << currencyShow(thu); resetText();
    gotoXY(currentX, ++currentY); cout << " - Tong chi   : "; color(12); cout << currencyShow(chi); resetText();
    gotoXY(currentX, ++currentY); cout << " - Tong so du : "; (thu - chi >= 0) ? color(10) : color(12); cout << currencyShow(thu - chi) << endl; resetText();
}


void QL_GiaoDich::thongKeThang(int month, int year, QL_NganHang& QL_NH){
    currency income = 0, payment = 0;
    int m = month, y = year;
    int endDay;
    if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) endDay = 31;
    else if(m == 4 || m == 6 || m == 9 || m == 11) endDay = 30;
    else if(m == 2){
        if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) endDay = 29;
        else endDay = 28;
    }

    DateTime begin(1, m, y);
    DateTime end(endDay, m, y);
    int n = dayInWeek(begin);
    gotoXY(49, 3); thongKeTuanDauThang(begin, income, payment, QL_NH); cout << endl;
    begin.SetDate(1 + 7 - n + 1, m, y);
    int tempDay = begin.GetDay();
    while (tempDay + 7 < endDay){
        gotoXY(49, getY()); thongKeTuan(begin, income, payment, QL_NH); cout << endl;
        begin.SetDate(begin.GetDay() + 7, m, y);
        tempDay += 7;
    }
    gotoXY(49, getY()); thongKeTuanCuoiThang(end, income, payment, QL_NH);

    int tempY = getY();
    drawBox(48, 2, 45, tempY - 2); gotoXY(50, 2); color(14); cout << " THONG KE THEO TUNG TUAN "; resetText();
    drawBox(2, 2, 45, tempY - 2); gotoXY(4, 2); color(14); cout << " TONG QUAN THONG KE THANG " << m << '/' << y << " "; resetText();
    
    gotoXY(5, 4); cout << "TONG THU   : "; color(10); cout << currencyShow(income); resetText();
    gotoXY(5, 6); cout << "TONG CHI   : "; color(12); cout << currencyShow(payment); resetText();
    gotoXY(5, 8); cout << "TONG SO DU : "; (income - payment >= 0) ? color(10) : color(12); cout << currencyShow(income - payment) << endl; resetText();
}

void QL_GiaoDich::sortDate(Vector<GiaoDich*>& table){
    int size = table.size();
    for (int i = 0; i < size; i++){
	    for (int j = 0; j < size-1; j++){
            if (table[j]->GetDate() > table[j+1]->GetDate()){
                GiaoDich *temp = new GiaoDich;
                *temp = *table[j];
                *table[j] = *table[j+1];
                *table[j + 1] = *temp;
                delete temp;
            }
        }
	}
}


void QL_GiaoDich::locThongTin(QL_NganHang& QL_NH){

    //interface
    clr();
    drawBox(2, 2, 50, 7); gotoXY(6, 2); cout << " LOC THONG TIN  ";
    gotoXY(6, 4); cout << "1. Loc theo So tien";
    gotoXY(6, 5); cout << "2. Loc theo Thoi gian";
    gotoXY(6, 6); cout << "3. Loc theo Nhom";
    gotoXY(6, 7); cout << "4. Loc theo Ghi chu";
    gotoXY(6, 8); cout << "5. Loc theo Vi";
    //rooling menu
    int choice = 0; int key; color(14);
    for (;;){
        for (int i = 0; i < 5; i++){
            gotoXY(4, 4 + i); if (choice == i) cout << ">"; else cout << " ";
        }
        key = getkey();
        if (key == 1080) choice += 1;
        if (key == 1072) choice -= 1;
        if (choice < 0) choice = 4; if (choice > 4) choice = 0;
        if (key == 13) break;
        if (key == 27) return;
    }
    resetText();

    int task = 0; int isAvail = 0; int num = 0; currency thu = 0, chi = 0;
    Vector<GiaoDich*> t_tableGD(tableGD);
    switch (choice){
        case 0:{
            clr();
            drawBox(2, 2, 50, 6); gotoXY(6, 2); cout << " LOC THEO SO TIEN  ";
            gotoXY(6, 4); cout << "1. Lon hon";
            gotoXY(6, 5); cout << "2. Nho hon";
            gotoXY(6, 6); cout << "3. Trong khoang";
            gotoXY(6, 7); cout << "4. Chinh xac";
            color(14);
            for (;;){
                for (int i = 0; i < 4; i++){
                    gotoXY(4, 4 + i); if (task == i) cout << ">"; else cout << " ";
                }
                key = getkey();
                if (key == 1080) task += 1;
                if (key == 1072) task -= 1;
                if (key < 0) task = 3; if (task > 3) task = 0;
                if (key == 13) break;
                if (key == 27) return;
            }
            resetText();

            if (task == 0){
                drawBox(53, 2, 50, 3); gotoXY(55, 2); cout << " SO TIEN > LON HON ";
                gotoXY(55, 4); cout << "Nhap so tien : "; currency money = currencyInput(); gotoXY(70, 4); cout << currencyShow(money);

                for (int i = t_tableGD.size() - 1; i >= 0; i--){
                    if(t_tableGD[i]->Getamount() > money){
                        if (isAvail == 0){ 
                            gotoXY(2, 10); color(14); cout << " CAC GIAO DICH CO SO TIEN LON HON " << currencyShow(money) << " : "; resetText();
                            gotoXY(2, 11); color2(47);
                            cout << setw(6) << right << "STT" << " | ";
                            cout << setw(15) << left << "NHOM" << " | ";
                            cout << setw(25) << left << "DANH MUC" << " | ";
                            cout << setw(20) << right << "SO TIEN" << " | ";
                            cout << setw(20) << left << " VI" << " | ";
                            cout << setw(20) << left << "GHI CHU" << " | ";
                            cout << setw(15) << right << "THOI GIAN" << setw(2) << " " << endl; resetText();
                            isAvail = 1;
                        }
                        num++; cout << "  " << setw(6) << right << num << " | ";// << *t_tableGD[i];
                        cout
                            << setw(15) << left << listGroup[tableGD[i]->Getgroup() - 1] << " | " 
                            << setw(25) << left << listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory() - 1] << " | ";
                            if (tableGD[i]->Getgroup()-1 == 0) color2(32); else if (tableGD[i]->Getgroup()-1 == 1) color2(31); else color2(34);
                            cout << setw(20)<< right << tableGD[i]->Getamount(); resetText();
                            cout << " | " << setw(20) << left << tableGD[i]->GetwalletF() << " | " 
                            << setw(20) << left << tableGD[i]->Getnote() << " | " 
                            << setw(15) << right << tableGD[i]->GetDate().GetDateinString() << endl;
                        if (t_tableGD[i]->Getgroup() == 1 || t_tableGD[i]->Getgroup() == 3 && (t_tableGD[i]->Getcategory() == 2 || t_tableGD[i]->Getcategory() == 3) || t_tableGD[i]->Getgroup() == 4 && t_tableGD[i]->Getcategory() == 2){
                            thu += t_tableGD[i]->Getamount();
                            if (searchWallet(t_tableGD[i]->GetwalletF()) == 2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        } else {
                            chi += t_tableGD[i]->Getamount();
                            if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        }
                    }
                }
            } else if (task == 1){
                drawBox(53, 2, 50, 3); gotoXY(55, 2); cout << " SO TIEN > BE HON ";
                gotoXY(55, 4); cout << "Nhap so tien : "; currency money = currencyInput(); gotoXY(70, 4); cout << currencyShow(money);
                for (int i = t_tableGD.size() - 1; i >= 0; i--) {
                    if(t_tableGD[i]->Getamount() < money ){
                        if (isAvail == 0){ 
                            gotoXY(2, 10); color(14); cout << " CAC GIAO DICH CO SO TIEN BE HON " << currencyShow(money) << " : "; resetText();
                            gotoXY(2, 11); color2(47);
                            cout << setw(6) << right << "STT" << " | ";
                            cout << setw(15) << left << "NHOM" << " | ";
                            cout << setw(25) << left << "DANH MUC" << " | ";
                            cout << setw(20) << right << "SO TIEN" << " | ";
                            cout << setw(20) << left << " VI" << " | ";
                            cout << setw(20) << left << "GHI CHU" << " | ";
                            cout << setw(15) << right << "THOI GIAN" << setw(2) << " " << endl; resetText();
                            isAvail = 1;
                        }
                        num++; cout << "  " << setw(6) << right << num << " | ";
                        cout
                            << setw(15) << left << listGroup[tableGD[i]->Getgroup() - 1] << " | " 
                            << setw(25) << left << listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory() - 1] << " | ";
                            if (tableGD[i]->Getgroup()-1 == 0) color2(32); else if (tableGD[i]->Getgroup()-1 == 1) color2(31); else color2(34);
                            cout << setw(20)<< right << tableGD[i]->Getamount(); resetText();
                            cout << " | " << setw(20) << left << tableGD[i]->GetwalletF() << " | " 
                            << setw(20) << left << tableGD[i]->Getnote() << " | " 
                            << setw(15) << right << tableGD[i]->GetDate().GetDateinString() << endl;
                        if(t_tableGD[i]->Getgroup() == 1 || t_tableGD[i]->Getgroup() == 3 && (t_tableGD[i]->Getcategory() == 2 || t_tableGD[i]->Getcategory() == 3) || t_tableGD[i]->Getgroup() == 4 && t_tableGD[i]->Getcategory() == 2){
                            thu += t_tableGD[i]->Getamount();
                            if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        } else {
                            chi += t_tableGD[i]->Getamount();
                            if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        }
                    }
                }
            } else if (task == 2){
                currency money1, money2;
                drawBox(53, 2, 50, 5); gotoXY(55, 2); cout << " SO TIEN > TRONG KHOANG ";
                gotoXY(55, 4); cout << "Khoang tien tu tren : "; money1 = currencyInput(); gotoXY(77, 4); cout << currencyShow(money1);
                do {
                    try {
                        gotoXY(55, 5); cout << "Den duoi            : "; money2 = currencyInput(); gotoXY(77, 5); cout << currencyShow(money2);
                        if (money1 >= money2) throw 1;
                    }
                    catch (...){
                        gotoXY(55, 6); color(12); cout << "Khoang tien khong hop le. Vui long nhap lai."; resetText();
                        gotoXY(77, 5); cout << "                      ";
                        continue;
                    }
                } while (money1 >= money2);
                gotoXY(55, 6); cout << "                                            ";
                for (int i = t_tableGD.size() - 1; i >= 0; i--){
                    if (t_tableGD[i]->Getamount() > money1 && t_tableGD[i]->Getamount() < money2){
                        if (isAvail == 0){ 
                            gotoXY(2, 10); color(14); cout << " CAC GIAO DICH CO SO TIEN TREN " << currencyShow(money1) << " VA DUOI " << currencyShow(money2) << " : "; resetText();
                            gotoXY(2, 11); color2(47);
                            cout << setw(6) << right << "STT" << " | ";
                            cout << setw(15) << left << "NHOM" << " | ";
                            cout << setw(25) << left << "DANH MUC" << " | ";
                            cout << setw(20) << right << "SO TIEN" << " | ";
                            cout << setw(20) << left << " VI" << " | ";
                            cout << setw(20) << left << "GHI CHU" << " | ";
                            cout << setw(15) << right << "THOI GIAN" << setw(2) << " " << endl; resetText();
                            isAvail = 1;
                        }
                        num++; cout << "  " << setw(6) << right << num << " | ";// << *t_tableGD[i];
                        cout
                            << setw(15) << left << listGroup[tableGD[i]->Getgroup() - 1] << " | " 
                            << setw(25) << left << listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory() - 1] << " | ";
                            if (tableGD[i]->Getgroup()-1 == 0) color2(32); else if (tableGD[i]->Getgroup()-1 == 1) color2(31); else color2(34);
                            cout << setw(20)<< right << tableGD[i]->Getamount(); resetText();
                            cout << " | " << setw(20) << left << tableGD[i]->GetwalletF() << " | " 
                            << setw(20) << left << tableGD[i]->Getnote() << " | " 
                            << setw(15) << right << tableGD[i]->GetDate().GetDateinString() << endl;
                        if(t_tableGD[i]->Getgroup() == 1 || t_tableGD[i]->Getgroup() == 3 && (t_tableGD[i]->Getcategory() == 2 || t_tableGD[i]->Getcategory() == 3) || t_tableGD[i]->Getgroup() == 4 && t_tableGD[i]->Getcategory() == 2){
                            thu += t_tableGD[i]->Getamount();
                            if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        } else {
                            chi += t_tableGD[i]->Getamount();
                            if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        }
                    }
                }
            } else if(task == 3){
                drawBox(53, 2, 50, 3); gotoXY(55, 2); cout << " SO TIEN > CHINH XAC BANG ";
                gotoXY(55, 4); cout << "Nhap so tien : "; currency money = currencyInput(); gotoXY(70, 4); cout << currencyShow(money);
                for(int i =t_tableGD.size() - 1; i>=0;i--){
                    if(t_tableGD[i]->Getamount() == money ){
                        if (isAvail == 0){ 
                            gotoXY(2, 10); color(14); cout << " CAC GIAO DICH CO SO TIEN CHINH XAC BANG " << currencyShow(money) << " : "; resetText();
                            gotoXY(2, 11); color2(47);
                            cout << setw(6) << right << "STT" << " | ";
                            cout << setw(15) << left << "NHOM" << " | ";
                            cout << setw(25) << left << "DANH MUC" << " | ";
                            cout << setw(20) << right << "SO TIEN" << " | ";
                            cout << setw(20) << left << " VI" << " | ";
                            cout << setw(20) << left << "GHI CHU" << " | ";
                            cout << setw(15) << right << "THOI GIAN" << setw(2) << " " << endl; resetText();
                            isAvail = 1;
                        }
                        num++; cout << "  " << setw(6) << right << num << " | ";// << *t_tableGD[i];
                        cout
                            << setw(15) << left << listGroup[tableGD[i]->Getgroup() - 1] << " | " 
                            << setw(25) << left << listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory() - 1] << " | ";
                            if (tableGD[i]->Getgroup()-1 == 0) color2(32); else if (tableGD[i]->Getgroup()-1 == 1) color2(31); else color2(34);
                            cout << setw(20)<< right << tableGD[i]->Getamount(); resetText();
                            cout << " | " << setw(20) << left << tableGD[i]->GetwalletF() << " | " 
                            << setw(20) << left << tableGD[i]->Getnote() << " | " 
                            << setw(15) << right << tableGD[i]->GetDate().GetDateinString() << endl;
                        if(t_tableGD[i]->Getgroup()==1 || t_tableGD[i]->Getgroup()==3 && (t_tableGD[i]->Getcategory()==2||t_tableGD[i]->Getcategory()==3) || t_tableGD[i]->Getgroup()==4 && t_tableGD[i]->Getcategory()==2){
                            thu += t_tableGD[i]->Getamount();
                            if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        } else {
                            chi += t_tableGD[i]->Getamount();
                            if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        }
                    }
                }
            }
            break;
        }
        case 1:{
            clr();
            drawBox(2, 2, 50, 6); gotoXY(6, 2); cout << " LOC THEO THOI GIAN  ";
            gotoXY(6, 4); cout << "1. Sau";
            gotoXY(6, 5); cout << "2. Truoc";
            gotoXY(6, 6); cout << "3. Trong khoang";
            gotoXY(6, 7); cout << "4. Chinh xac";
            color(14);
            for (;;){
                for (int i = 0; i < 4; i++){
                    gotoXY(4, 4 + i); if (task == i) cout << ">"; else cout << " ";
                }
                key = getkey();
                if (key == 1080) task += 1;
                if (key == 1072) task -= 1;
                if (key < 0) task = 3; if (task > 3) task = 0;
                if (key == 13) break;
                if (key == 27) return;
            }
            resetText();
            DateTime S;

            if (task == 0){ //sau
                drawBox(53, 2, 50, 3); gotoXY(55, 2); cout << " THOI GIAN > SAU ";
                gotoXY(55, 4); cout <<"Nhap thoi gian : "; cin >> S;
                for (int i = t_tableGD.size() - 1; i >= 0; i--){
                    if(t_tableGD[i]->GetDate() > S){
                        if (isAvail == 0){ 
                            gotoXY(2, 10); color(14); cout << " CAC GIAO DICH SAU NGAY " << S.GetDateinString() << " : "; resetText();
                            gotoXY(2, 11); color2(47);
                            cout << setw(6) << right << "STT" << " | ";
                            cout << setw(15) << left << "NHOM" << " | ";
                            cout << setw(25) << left << "DANH MUC" << " | ";
                            cout << setw(20) << right << "SO TIEN" << " | ";
                            cout << setw(20) << left << " VI" << " | ";
                            cout << setw(20) << left << "GHI CHU" << " | ";
                            cout << setw(15) << right << "THOI GIAN" << setw(2) << " " << endl; resetText();
                            isAvail = 1;
                        }
                        num++; cout << "  " << setw(6) << right << num << " | ";// << *t_tableGD[i];
                        cout
                            << setw(15) << left << listGroup[tableGD[i]->Getgroup() - 1] << " | " 
                            << setw(25) << left << listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory() - 1] << " | ";
                            if (tableGD[i]->Getgroup()-1 == 0) color2(32); else if (tableGD[i]->Getgroup()-1 == 1) color2(31); else color2(34);
                            cout << setw(20)<< right << tableGD[i]->Getamount(); resetText();
                            cout << " | " << setw(20) << left << tableGD[i]->GetwalletF() << " | " 
                            << setw(20) << left << tableGD[i]->Getnote() << " | " 
                            << setw(15) << right << tableGD[i]->GetDate().GetDateinString() << endl;
                        if(t_tableGD[i]->Getgroup()==1 || t_tableGD[i]->Getgroup()==3 && (t_tableGD[i]->Getcategory()==2||t_tableGD[i]->Getcategory()==3) || t_tableGD[i]->Getgroup()==4 && t_tableGD[i]->Getcategory()==2)
                        {
                            thu += t_tableGD[i]->Getamount();
                            if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        } else
                        {
                            chi += t_tableGD[i]->Getamount();
                            if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        }
                    }
                }
            } 
            else if(task == 1){
                drawBox(53, 2, 50, 3); gotoXY(55, 2); cout << " THOI GIAN > TRUOC ";
                gotoXY(55, 4); cout << "Nhap thoi gian :  "; string t_S; cin>>t_S;
                DateTime S;
                S.SetDate(t_S);
                for(int i =t_tableGD.size() - 1; i>=0;i--){
                    if(t_tableGD[i]->GetDate() < S ){
                        if (isAvail == 0){ 
                            gotoXY(2, 10); color(14); cout << " CAC GIAO DICH TRUOC NGAY " << S.GetDateinString() << " : "; resetText();
                            gotoXY(2, 11); color2(47);
                            cout << setw(6) << right << "STT" << " | ";
                            cout << setw(15) << left << "NHOM" << " | ";
                            cout << setw(25) << left << "DANH MUC" << " | ";
                            cout << setw(20) << right << "SO TIEN" << " | ";
                            cout << setw(20) << left << " VI" << " | ";
                            cout << setw(20) << left << "GHI CHU" << " | ";
                            cout << setw(15) << right << "THOI GIAN" << setw(2) << " " << endl; resetText();
                            isAvail = 1;
                        }
                        num++; cout << "  " << setw(6) << right << num << " | ";// << *t_tableGD[i];
                        cout
                            << setw(15) << left << listGroup[tableGD[i]->Getgroup() - 1] << " | " 
                            << setw(25) << left << listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory() - 1] << " | ";
                            if (tableGD[i]->Getgroup()-1 == 0) color2(32); else if (tableGD[i]->Getgroup()-1 == 1) color2(31); else color2(34);
                            cout << setw(20)<< right << tableGD[i]->Getamount(); resetText();
                            cout << " | " << setw(20) << left << tableGD[i]->GetwalletF() << " | " 
                            << setw(20) << left << tableGD[i]->Getnote() << " | " 
                            << setw(15) << right << tableGD[i]->GetDate().GetDateinString() << endl;
                        if(t_tableGD[i]->Getgroup()==1 || t_tableGD[i]->Getgroup()==3 && (t_tableGD[i]->Getcategory()==2||t_tableGD[i]->Getcategory()==3) || t_tableGD[i]->Getgroup()==4 && t_tableGD[i]->Getcategory()==2)
                        {
                            thu += t_tableGD[i]->Getamount();
                            if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        } else
                        {
                            chi += t_tableGD[i]->Getamount();
                            if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        }
                    }
                }
            }
            else if(task == 2){
                DateTime S1, S2;
                drawBox(53, 2, 50, 5); gotoXY(55, 2); cout << " THOI GIAN > TRONG KHOANG ";
                gotoXY(55, 4); cout << "Khoang thoi gian tu : "; showCursor(); cin >> S1; hideCursor();
                do {
                    try {
                        gotoXY(55, 5); cout << "Den                 : "; showCursor(); cin >> S2; hideCursor();
                        if (S1 > S2) throw 1;
                    }
                    catch (int e) {
                        gotoXY(55, 6); color(12); cout << "Ngay bat dau phai truoc ngay ket thuc"; resetText();
                        gotoXY(77, 5); cout << "                ";
                        continue;
                    }
                    catch (...) {
                        gotoXY(55, 6); color(12); cout << "Da co loi xay ra"; resetText();
                        return;
                    }
                } while (S1 > S2);
                gotoXY(55, 6); cout << "                                           ";
                for (int i = t_tableGD.size() - 1; i >= 0; i--){
                    if(t_tableGD[i]->GetDate() > S1 && tableGD[i]->GetDate() < S2 ){
                        if (isAvail == 0){ 
                            gotoXY(2, 10); color(14); cout << " CAC GIAO DICH TU " << S1.GetDateinString() << " DEN " << S2.GetDateinString() << " : "; resetText();
                            gotoXY(2, 11); color2(47);
                            cout << setw(6) << right << "STT" << " | ";
                            cout << setw(15) << left << "NHOM" << " | ";
                            cout << setw(25) << left << "DANH MUC" << " | ";
                            cout << setw(20) << right << "SO TIEN" << " | ";
                            cout << setw(20) << left << " VI" << " | ";
                            cout << setw(20) << left << "GHI CHU" << " | ";
                            cout << setw(15) << right << "THOI GIAN" << setw(2) << " " << endl; resetText();
                            isAvail = 1;
                        }
                        num++; cout << "  " << setw(6) << right << num << " | ";// << *t_tableGD[i];
                        cout
                            << setw(15) << left << listGroup[tableGD[i]->Getgroup() - 1] << " | " 
                            << setw(25) << left << listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory() - 1] << " | ";
                            if (tableGD[i]->Getgroup()-1 == 0) color2(32); else if (tableGD[i]->Getgroup()-1 == 1) color2(31); else color2(34);
                            cout << setw(20)<< right << tableGD[i]->Getamount(); resetText();
                            cout << " | " << setw(20) << left << tableGD[i]->GetwalletF() << " | " 
                            << setw(20) << left << tableGD[i]->Getnote() << " | " 
                            << setw(15) << right << tableGD[i]->GetDate().GetDateinString() << endl;
                        if(t_tableGD[i]->Getgroup()==1 || t_tableGD[i]->Getgroup()==3 && (t_tableGD[i]->Getcategory()==2||t_tableGD[i]->Getcategory()==3) || t_tableGD[i]->Getgroup()==4 && t_tableGD[i]->Getcategory()==2) {
                            thu += t_tableGD[i]->Getamount();
                            if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        } else {
                            chi += t_tableGD[i]->Getamount();
                            if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        }
                    }
                }
            }
            else if (task == 3){
                drawBox(53, 2, 50, 3); gotoXY(55, 2); cout << " THOI GIAN > CHINH XAC ";
                gotoXY(55, 4); cout << "Nhap thoi gian:  "; cin >> S;
                for(int i = t_tableGD.size() - 1; i >= 0; i--){
                    if(t_tableGD[i]->GetDate() == S){
                        if (isAvail == 0){ 
                            gotoXY(2, 10); color(14); cout << " CAC GIAO DICH XAY RA TRONG NGAY " << S.GetDateinString() << " : "; resetText();
                            gotoXY(2, 11); color2(47);
                            cout << setw(6) << right << "STT" << " | ";
                            cout << setw(15) << left << "NHOM" << " | ";
                            cout << setw(25) << left << "DANH MUC" << " | ";
                            cout << setw(20) << right << "SO TIEN" << " | ";
                            cout << setw(20) << left << " VI" << " | ";
                            cout << setw(20) << left << "GHI CHU" << " | ";
                            cout << setw(15) << right << "THOI GIAN" << setw(2) << " " << endl; resetText();
                            isAvail = 1;
                        }
                        num++; cout << "  " << setw(6) << right << num << " | ";// << *t_tableGD[i];
                        cout
                            << setw(15) << left << listGroup[tableGD[i]->Getgroup() - 1] << " | " 
                            << setw(25) << left << listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory() - 1] << " | ";
                            if (tableGD[i]->Getgroup()-1 == 0) color2(32); else if (tableGD[i]->Getgroup()-1 == 1) color2(31); else color2(34);
                            cout << setw(20)<< right << tableGD[i]->Getamount(); resetText();
                            cout << " | " << setw(20) << left << tableGD[i]->GetwalletF() << " | " 
                            << setw(20) << left << tableGD[i]->Getnote() << " | " 
                            << setw(15) << right << tableGD[i]->GetDate().GetDateinString() << endl;
                        if(t_tableGD[i]->Getgroup()==1 || t_tableGD[i]->Getgroup()==3 && (t_tableGD[i]->Getcategory()==2||t_tableGD[i]->Getcategory()==3) || t_tableGD[i]->Getgroup()==4 && t_tableGD[i]->Getcategory()==2) {
                            thu +=t_tableGD[i]->Getamount();
                            if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        } else {
                            chi += t_tableGD[i]->Getamount();
                            if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        }
                    }
                }
            }
            break;
        }
        case 2: {
            clr();
            drawBox(2, 2, 50, 6); gotoXY(6, 2); cout << " LOC THEO NHOM ";
            gotoXY(6, 4); cout << "1. Thu nhap";
            gotoXY(6, 5); cout << "2. Chi tieu";
            gotoXY(6, 6); cout << "3. Vay no";
            gotoXY(6, 7); cout << "4. Tiet kiem";
            color(14);
            for (;;){
                for (int i = 0; i < 4; i++){
                    gotoXY(4, 4 + i); if (task == i) cout << ">"; else cout << " ";
                }
                key = getkey();
                if (key == 1080) task += 1;
                if (key == 1072) task -= 1;
                if (key < 0) task = 3; if (task > 3) task = 0;
                if (key == 13) break;
                if (key == 27) return;
            }
            resetText();

            if (task == 0){
                for(int i =t_tableGD.size() - 1; i>=0;i--){
                    if(t_tableGD[i]->Getgroup()==1 || t_tableGD[i]->Getgroup()==3 && (t_tableGD[i]->Getcategory()==2||t_tableGD[i]->Getcategory()==3) || t_tableGD[i]->Getgroup()==4 && t_tableGD[i]->Getcategory()==2){
                        if (isAvail == 0){ 
                            gotoXY(2, 10); color(14); cout << " CAC GIAO DICH THUOC NHOM THU NHAP : "; resetText();
                            gotoXY(2, 11); color2(47);
                            cout << setw(6) << right << "STT" << " | ";
                            cout << setw(15) << left << "NHOM" << " | ";
                            cout << setw(25) << left << "DANH MUC" << " | ";
                            cout << setw(20) << right << "SO TIEN" << " | ";
                            cout << setw(20) << left << " VI" << " | ";
                            cout << setw(20) << left << "GHI CHU" << " | ";
                            cout << setw(15) << right << "THOI GIAN" << setw(2) << " " << endl; resetText();
                            isAvail = 1;
                        }
                        num++; cout << "  " << setw(6) << right << num << " | ";// << *t_tableGD[i];
                        cout
                            << setw(15) << left << listGroup[tableGD[i]->Getgroup() - 1] << " | " 
                            << setw(25) << left << listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory() - 1] << " | ";
                            if (tableGD[i]->Getgroup()-1 == 0) color2(32); else if (tableGD[i]->Getgroup()-1 == 1) color2(31); else color2(34);
                            cout << setw(20)<< right << tableGD[i]->Getamount(); resetText();
                            cout << " | " << setw(20) << left << tableGD[i]->GetwalletF() << " | " 
                            << setw(20) << left << tableGD[i]->Getnote() << " | " 
                            << setw(15) << right << tableGD[i]->GetDate().GetDateinString() << endl;
                        thu += t_tableGD[i]->Getamount();
                        if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                            int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                            chi += QL_NH.tableNH[NH_index]->GetCost();
                        }
                    } 
                }
            } else if (task == 1){
                for(int i = t_tableGD.size() - 1; i>=0;i--){
                    if(t_tableGD[i]->Getgroup()==1 || t_tableGD[i]->Getgroup()==3 && (t_tableGD[i]->Getcategory()==2||t_tableGD[i]->Getcategory()==3) || t_tableGD[i]->Getgroup()==4 && t_tableGD[i]->Getcategory()==2){
                        if (isAvail == 0){ 
                            gotoXY(2, 10); color(14); cout << " CAC GIAO DICH THUOC NHOM CHI TIEU :"; resetText();
                            gotoXY(2, 11); color2(47);
                            cout << setw(6) << right << "STT" << " | ";
                            cout << setw(15) << left << "NHOM" << " | ";
                            cout << setw(25) << left << "DANH MUC" << " | ";
                            cout << setw(20) << right << "SO TIEN" << " | ";
                            cout << setw(20) << left << " VI" << " | ";
                            cout << setw(20) << left << "GHI CHU" << " | ";
                            cout << setw(15) << right << "THOI GIAN" << setw(2) << " " << endl; resetText();
                            isAvail = 1;
                        }
                        num++; cout << "  " << setw(6) << right << num << " | ";// << *t_tableGD[i];
                        cout
                            << setw(15) << left << listGroup[tableGD[i]->Getgroup() - 1] << " | " 
                            << setw(25) << left << listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory() - 1] << " | ";
                            if (tableGD[i]->Getgroup()-1 == 0) color2(32); else if (tableGD[i]->Getgroup()-1 == 1) color2(31); else color2(34);
                            cout << setw(20)<< right << tableGD[i]->Getamount(); resetText();
                            cout << " | " << setw(20) << left << tableGD[i]->GetwalletF() << " | " 
                            << setw(20) << left << tableGD[i]->Getnote() << " | " 
                            << setw(15) << right << tableGD[i]->GetDate().GetDateinString() << endl;
                        continue;
                    }
                    chi += t_tableGD[i]->Getamount();
                    if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                        int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                        chi += QL_NH.tableNH[NH_index]->GetCost();
                    }
                }
            } else if (task == 2){
                for(int i = t_tableGD.size() - 1; i>=0;i--){
                    if(t_tableGD[i]->Getgroup() == 3 ){
                        if (isAvail == 0){ 
                            gotoXY(2, 10); color(14); cout << " CAC GIAO DICH THUOC NHOM VAY NO : "; resetText();
                            gotoXY(2, 11); color2(47);
                            cout << setw(6) << right << "STT" << " | ";
                            cout << setw(15) << left << "NHOM" << " | ";
                            cout << setw(25) << left << "DANH MUC" << " | ";
                            cout << setw(20) << right << "SO TIEN" << " | ";
                            cout << setw(20) << left << " VI" << " | ";
                            cout << setw(20) << left << "GHI CHU" << " | ";
                            cout << setw(15) << right << "THOI GIAN" << setw(2) << " " << endl; resetText();
                            isAvail = 1;
                        }
                        num++; cout << "  " << setw(6) << right << num << " | ";// << *t_tableGD[i];
                        cout
                            << setw(15) << left << listGroup[tableGD[i]->Getgroup() - 1] << " | " 
                            << setw(25) << left << listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory() - 1] << " | ";
                            if (tableGD[i]->Getgroup()-1 == 0) color2(32); else if (tableGD[i]->Getgroup()-1 == 1) color2(31); else color2(34);
                            cout << setw(20)<< right << tableGD[i]->Getamount(); resetText();
                            cout << " | " << setw(20) << left << tableGD[i]->GetwalletF() << " | " 
                            << setw(20) << left << tableGD[i]->Getnote() << " | " 
                            << setw(15) << right << tableGD[i]->GetDate().GetDateinString() << endl;
                        if(t_tableGD[i]->Getcategory()==2||t_tableGD[i]->Getcategory()==3) {
                            thu += t_tableGD[i]->Getamount();
                            if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        } else {
                            chi += t_tableGD[i]->Getamount();
                            if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        }
                    }
                }
            } else if (task == 5){
                for(int i =t_tableGD.size() - 1; i >= 0; i--){
                    if (t_tableGD[i]->Getgroup() == 4){
                        if (isAvail == 0){ 
                            gotoXY(2, 10); color(14); cout << " CAC GIAO DICH NHOM TIET KIEM : "; resetText();
                            gotoXY(2, 11); color2(47);
                            cout << setw(6) << right << "STT" << " | ";
                            cout << setw(15) << left << "NHOM" << " | ";
                            cout << setw(25) << left << "DANH MUC" << " | ";
                            cout << setw(20) << right << "SO TIEN" << " | ";
                            cout << setw(20) << left << " VI" << " | ";
                            cout << setw(20) << left << "GHI CHU" << " | ";
                            cout << setw(15) << right << "THOI GIAN" << setw(2) << " " << endl; resetText();
                            isAvail = 1;
                        }
                        num++; cout << "  " << setw(6) << right << num << " | ";// << *t_tableGD[i];
                        cout
                            << setw(15) << left << listGroup[tableGD[i]->Getgroup() - 1] << " | " 
                            << setw(25) << left << listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory() - 1] << " | ";
                            if (tableGD[i]->Getgroup()-1 == 0) color2(32); else if (tableGD[i]->Getgroup()-1 == 1) color2(31); else color2(34);
                            cout << setw(20)<< right << tableGD[i]->Getamount(); resetText();
                            cout << " | " << setw(20) << left << tableGD[i]->GetwalletF() << " | " 
                            << setw(20) << left << tableGD[i]->Getnote() << " | " 
                            << setw(15) << right << tableGD[i]->GetDate().GetDateinString() << endl;
                        if(t_tableGD[i]->Getcategory()==2){ 
                            thu += t_tableGD[i]->Getamount();
                            if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        }
                        else if(t_tableGD[i]->Getcategory()==1){ 
                            chi+= t_tableGD[i]->Getamount();
                            if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                                int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                                chi += QL_NH.tableNH[NH_index]->GetCost();
                            }
                        }
                    }
                }
            }
            break;
        }
        case 3 : {
            drawBox(2, 2, 50, 3); gotoXY(4, 2); cout << " LOC THEO GHI CHU ";
            gotoXY(4, 4); cout << "Nhap ghi chu : "; string ghiChu;
            do {
                gotoXY(19, 4); getline(cin, ghiChu);
            } while (ghiChu != "");
            for (int i = t_tableGD.size() - 1; i >= 0; i--){
                if (t_tableGD[i]->Getnote() == ghiChu){
                    if (isAvail == 0){ 
                        gotoXY(2, 10); color(14); cout << " CAC GIAO DICH NHOM TIET KIEM : "; resetText();
                        gotoXY(2, 11); color2(47);
                        cout << setw(6) << right << "STT" << " | ";
                        cout << setw(15) << left << "NHOM" << " | ";
                        cout << setw(25) << left << "DANH MUC" << " | ";
                        cout << setw(20) << right << "SO TIEN" << " | ";
                        cout << setw(20) << left << " VI" << " | ";
                        cout << setw(20) << left << "GHI CHU" << " | ";
                        cout << setw(15) << right << "THOI GIAN" << setw(2) << " " << endl; resetText();
                        isAvail = 1;
                    }
                    num++; cout << "  " << setw(6) << right << num << " | ";// << *t_tableGD[i];
                    cout
                        << setw(15) << left << listGroup[tableGD[i]->Getgroup() - 1] << " | " 
                        << setw(25) << left << listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory() - 1] << " | ";
                        if (tableGD[i]->Getgroup()-1 == 0) color2(32); else if (tableGD[i]->Getgroup()-1 == 1) color2(31); else color2(34);
                        cout << setw(20)<< right << tableGD[i]->Getamount(); resetText();
                        cout << " | " << setw(20) << left << tableGD[i]->GetwalletF() << " | " 
                        << setw(20) << left << tableGD[i]->Getnote() << " | " 
                        << setw(15) << right << tableGD[i]->GetDate().GetDateinString() << endl;
                    if(t_tableGD[i]->Getgroup()==1 || t_tableGD[i]->Getgroup()==3 && (t_tableGD[i]->Getcategory()==2||t_tableGD[i]->Getcategory()==3) || t_tableGD[i]->Getgroup()==4 && t_tableGD[i]->Getcategory()==2){
                        thu += t_tableGD[i]->Getamount();
                        if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                            int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                            chi += QL_NH.tableNH[NH_index]->GetCost();
                        }
                    } else {
                        chi += t_tableGD[i]->Getamount();
                        if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                            int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                            chi += QL_NH.tableNH[NH_index]->GetCost();
                        }
                    } 
                }
            }
            break;
        }
        case 4:{
            drawBox(2, 2, 50, 3); gotoXY(4, 2); cout << " LOC THEO VI TIEN ";
            gotoXY(4, 4); cout << "Dang chon vi...";
            string wallet = getWalletName(ShowWallet());
            clr();
            drawBox(2, 2, 50, 3); gotoXY(4, 2); cout << " LOC THEO VI TIEN ";
            gotoXY(4, 4); cout << "Vi tien : " << wallet;
            for(int i=t_tableGD.size()-1;i>=0;i--){
                if(t_tableGD[i]->GetwalletF() == wallet){
                    if (isAvail == 0){ 
                        gotoXY(2, 10); color(14); cout << " CAC GIAO DICH NHOM TIET KIEM : "; resetText();
                        gotoXY(2, 11); color2(47);
                        cout << setw(6) << right << "STT" << " | ";
                        cout << setw(15) << left << "NHOM" << " | ";
                        cout << setw(25) << left << "DANH MUC" << " | ";
                        cout << setw(20) << right << "SO TIEN" << " | ";
                        cout << setw(20) << left << " VI" << " | ";
                        cout << setw(20) << left << "GHI CHU" << " | ";
                        cout << setw(15) << right << "THOI GIAN" << setw(2) << " " << endl; resetText();
                        isAvail = 1;
                    }
                    num++; cout << "  " << setw(6) << right << num << " | ";// << *t_tableGD[i];
                    cout
                        << setw(15) << left << listGroup[tableGD[i]->Getgroup() - 1] << " | " 
                        << setw(25) << left << listCategory[tableGD[i]->Getgroup() - 1][tableGD[i]->Getcategory() - 1] << " | ";
                        if (tableGD[i]->Getgroup()-1 == 0) color2(32); else if (tableGD[i]->Getgroup()-1 == 1) color2(31); else color2(34);
                        cout << setw(20)<< right << tableGD[i]->Getamount(); resetText();
                        cout << " | " << setw(20) << left << tableGD[i]->GetwalletF() << " | " 
                        << setw(20) << left << tableGD[i]->Getnote() << " | " 
                        << setw(15) << right << tableGD[i]->GetDate().GetDateinString() << endl;
                    if(t_tableGD[i]->Getgroup()==1 || t_tableGD[i]->Getgroup()==3 && (t_tableGD[i]->Getcategory()==2||t_tableGD[i]->Getcategory()==3) || t_tableGD[i]->Getgroup()==4 && t_tableGD[i]->Getcategory()==2)
                    {
                        thu += t_tableGD[i]->Getamount();
                        if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                            int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                            chi += QL_NH.tableNH[NH_index]->GetCost();
                        }
                    } else
                    {
                        chi += t_tableGD[i]->Getamount();
                        if(searchWallet(t_tableGD[i]->GetwalletF())==2){
                            int NH_index = searchID(QL_NH.tableNH, t_tableGD[i]->GetID());
                            chi += QL_NH.tableNH[NH_index]->GetCost();
                        }
                    }
                }
            }
            break;
        }
    }
    if (isAvail == 0){
        gotoXY(2, getY() + 7);cout << "Khong co giao dich thoa man yeu cau da cho." << endl;
    } else {
        gotoXY(2, getY() + 1);
        cout << "Khoan thu : "; color(10); cout << currencyShow(thu) << endl; resetText();
        cout << "Khoan chi : "; color(12); cout << currencyShow(chi) << endl; resetText();
        cout << "So du     : "; if (thu - chi < 0) color(12); else color(10); cout << currencyShow(thu - chi) << endl; resetText();
    }
    gotoXY(2, getY() + 1); cout << "Nhan Enter de quay lai...";
    while (getch() != 13);
}

int QL_GiaoDich::getSizeGD(){
    return this->tableGD.size();
}
int QL_GiaoDich::getSizeTMA(){
    return this->tableTMA.size();
}
int QL_GiaoDich::getSizeNHG(){
    return this->tableNHG.size();
}


const string& QL_GiaoDich::getWalletName(int w_index){
    if (w_index < tableTMA.size()) return tableTMA[w_index];
    else return tableNHG[w_index - tableTMA.size()];
}


string QL_GiaoDich::upcase(const string& s){
    string temp = "";
    for (int i = 0; i < s.size(); i++){
        if (s.at(i) >= 'a' && s.at(i) <= 'z') temp += s.at(i) - 32;
        else temp += s.at(i);
    }
    return temp;
}