#include "QL_VayNo.h"

QL_VayNo::QL_VayNo(){}

QL_VayNo::~QL_VayNo(){
    for(int i=0; i<tableVN.size();i++){
        delete tableVN[i];
    }
    tableVN.clear();
}

void QL_VayNo::AddVN(QL_GiaoDich& QL_GD){
    VayNo *vn = new VayNo;
    string temp_ID = QL_GD.tableGD[QL_GD.tableGD.size() - 1]->GetID();
    temp_ID = QL_GD.next_ID(temp_ID, GiaoDich::max_ID_digit - 1);
    
    //interface
    gotoXY(7, 19);
    if(QL_GD.tableGD[QL_GD.tableGD.size()-1]->Getcategory()<=2) cout << "- NGUOI VAY       : ";
    else cout << "- NGUOI CHO VAY   :";
    string name;
    getline(cin, name);

    vn->SetIDGD_VN(temp_ID); 
    vn->SetWho(name); //set props
    tableVN.push_back(vn);
}

void QL_VayNo::AddVN(string ID, string Name){
    VayNo *temp_VN = new VayNo;
    temp_VN->SetAll(ID, Name);
    tableVN.push_back(temp_VN);
}


string category(int dm){
    if(dm==1) return "Cho vay";
    if(dm==2) return "Thu no";
    if(dm==3) return "Di vay";
    return "Tra no";
}
int QL_VayNo::ShowVN(QL_NganHang& QL_NH, QL_GiaoDich& QL_GD, QL_TietKiem& QL_TK){
    int currentY = getY();
    hideCursor();
    int sizeVN = tableVN.size();
    if(sizeVN <=0) {
        drawBox(10, 15, 70, 6); gotoXY(10, 20); color2(34); cout << " THONG BAO ";
        centerText(45, 17, "Ban hien khong co vay/no nao.");
        centerButton(13, 13, "DONG", 45, 19, 8, "RED");
        getch();
        return -1;
    }

    int key, index = sizeVN - 1;
    titleBar(3, 143, 2 + currentY, " DANH SACH VAY/NO ", "BLUE"); centerButton(1, 1, "ESC : THOAT", 129, 2 + currentY, 15, "RED");
    gotoXY(3,4 + currentY); color2(47);
    cout << setw(6) << right  << "STT" << " | ";
    cout << setw(15) << left  << "DANH MUC" << " | ";
    cout << setw(20) << right << "SO TIEN" << " | ";
    cout << setw(20) << left  << "VI" << " | ";
    cout << setw(20) << left  << "DOI TUONG" << " | ";
    cout << setw(25) << left  << "GHI CHU" << " | ";
    cout << setw(15) << right << "THOI GIAN" << " |";
    resetText();


    for (int i = sizeVN - 1; i >=0; i--){
        gotoXY(3, sizeVN - 1 - i + 5 + currentY);
        int GD_index = searchID(QL_GD.tableGD, tableVN[i]->GetIDGD_VN()); 

        cout << setw(6) << right << sizeVN - i << " | "; //STT
        cout << setw(15) << left << category(QL_GD.tableGD[GD_index]->Getcategory()) << " | ";
        cout << setw(20) << right << currencyShow(QL_GD.tableGD[GD_index]->Getamount());
        cout << " | " << setw(20) << left << "  " + QL_GD.tableGD[GD_index]->GetwalletF() << " | ";
        cout << setw(20) << left << tableVN[i]->GetWho() << " | ";
        cout << setw(25) << left << QL_GD.tableGD[GD_index]->Getnote() << " | ";
        cout << setw(15) << right << QL_GD.tableGD[GD_index]->GetDate().GetDateinString() << " | ";
    }

    color(14);
    for (;;){
        for (int i = sizeVN - 1; i >= 0; i--){
            gotoXY(1, sizeVN - 1 - i + 5 + currentY);
            if (index == i) cout << ">";
            else cout << " ";
        }
        key = getkey();
        if (key == 27){
            return -1;
        }
        if (key == 1072){
            index++;
            if (index > sizeVN - 1) index = 0;
        }
        if (key == 1080){
            index--;
            if (index < 0) index = sizeVN - 1;
        }
        if (key == 13){
            break;
        }
    }
    resetText();
    
    return index;
}

void QL_VayNo::ShowVN(int pos, QL_NganHang& QL_NH, QL_GiaoDich& QL_GD, QL_TietKiem& QL_TK){
    if (pos == -1) return;
    int GD_index = searchID(QL_GD.tableGD, tableVN[pos]->GetIDGD_VN());
    QL_GD.ShowGD(GD_index, QL_NH, *this, QL_TK);
}

void QL_VayNo::DeleteVN(int pos, QL_NganHang& QL_NH, QL_GiaoDich& QL_GD, QL_TietKiem& QL_TK){
    int GD_index = searchID(QL_GD.tableGD, tableVN[pos]->GetIDGD_VN());
    QL_GD.DeleteGD(GD_index, QL_NH, *this, QL_TK);
}

void QL_VayNo::UpdateVN(int t_pos, QL_NganHang& QL_NH, QL_GiaoDich& QL_GD, QL_TietKiem& QL_TK){
    int pos;
    if(t_pos == -1){
        pos = ShowVN(QL_NH, QL_GD, QL_TK);
        if (pos == -1) return;
        pos = searchID(QL_GD.tableGD, tableVN[pos]->GetIDGD_VN());
    } else pos = searchID(QL_GD.tableGD, tableVN[t_pos]->GetIDGD_VN());
    QL_GD.UpdateGD(pos, QL_NH, *this, QL_TK);
}
void QL_VayNo::Load(const string& userPath){
    string temp_IDGD_VN, temp_Who, line;
    VN_FILE = "DATA/" + userPath + "_" + VN_FILE;
    ifstream file;
    file.open(VN_FILE);
    while (!file.eof()){ 
        VayNo *temp_VN = new VayNo;
        getline(file, line);
        stringstream ss(line);
        getline(ss, temp_IDGD_VN, '|');
        if (temp_IDGD_VN == "F_END")
        {
            break;
        }
        getline(ss, temp_Who, '|');
        temp_VN->SetAll(temp_IDGD_VN, temp_Who);
        tableVN.push_back(temp_VN);
    }
    file.close();
}

void QL_VayNo::Save(){
    ofstream file;
    file.open(VN_FILE);
    int sizeVN = tableVN.size();
    for (int i = 0; i < sizeVN; i++){
        file << tableVN[i]->GetIDGD_VN() <<'|'<< tableVN[i]->GetWho() <<endl;
    }
    file << "F_END";
    file.close();
}


void QL_VayNo::tongQuanVN(QL_GiaoDich& QL_GD){
    // 1 : cho vay, 2 : thu no, 3 : di vay, 4 : tra no

    int currentY = getY(); //interfact function
    if (tableVN.size() <= 0){ //check empty
        gotoXY(4, ++currentY); cout << "Ban hien khong cho vay va di vay khoan tien nao." << endl;
        gotoXY(4, ++++currentY);
        return;
    }

    currency choVay = 0, diVay = 0;
    int sizeGD = QL_GD.tableGD.size();
    for (int i = 0; i < sizeGD; i++){
        if (QL_GD.tableGD[i]->Getgroup() == 3){
            int cate = QL_GD.tableGD[i]->Getcategory();
            currency money = QL_GD.tableGD[i]->Getamount();
            if (cate == 1) choVay += money;
            else if (cate == 2) choVay -= money;
            else if (cate == 3) diVay += money;
            else if (cate == 4) diVay -= money;
        }
    }

    gotoXY(4, ++currentY);
    color(240); cout << setw(34) << left << " SO VAY NO"; resetText();
    if (choVay <= 0){
        gotoXY(4, ++currentY); cout << "Khong co khoan cho vay nao dang hoat dong";
    } else {
        gotoXY(4, ++currentY); cout << "Tong cho vay: " << setw(18) << right << currencyShow(choVay);
    }

    if (diVay <= 0){
        gotoXY(4, ++currentY); cout << "Khong co khoan di vay nao dang hoat dong";
    } else {
        gotoXY(4, ++currentY); cout << "Tong di vay : " << setw(18) << right << currencyShow(diVay);
    }
}

void QL_VayNo::chiTietVN(QL_GiaoDich& QL_GD)
{
    int sizeVN = tableVN.size();
    if (sizeVN <= 0){
        drawBox(10, 15, 70, 6); gotoXY(10, 20); color2(34); cout << " THONG BAO ";
        centerText(45, 17, "Ban hien khong co vay/no nao.");
        centerButton(13, 13, "DONG", 45, 19, 8, "RED");
        getch();
        return;
    }
    currency tongChoVay = 0, tongNo = 0;
    map<string, currency> choVay;
    map<string, currency> diVay;
    titleBar(3, 143, 2, "CHI TIET VAY NO", "BLUE");
    for (int i = 0; i < sizeVN; i++){
        int GD_index = searchID(QL_GD.tableGD, tableVN[i]->GetIDGD_VN());
        int cate = QL_GD.tableGD[GD_index]->Getcategory();
        currency money = QL_GD.tableGD[GD_index]->Getamount();
        string name = tableVN[i]->GetWho();
        if (cate == 1)
            choVay[name] += money;
        else if (cate == 2)
            choVay[name] -= money;
        else if (cate == 3)
            diVay[name] += money;
        else if (cate == 4)
            diVay[name] -= money;
    }
    gotoXY(3, 4); cout << "TONG QUAN - CHO VAY : --------------------" << endl;
    int notEmptyCheck = 0;
    gotoXY(3, getY());
    for (auto it : choVay){
        if (it.second > 0){
            notEmptyCheck = 1;
            gotoXY(3, getY() + 1);
            cout << " * " << it.first << " vay "; color(14); cout << currencyShow(it.second) << endl; resetText();
            tongChoVay += it.second;
        }
    }
    if (notEmptyCheck == 0) cout << "Ban khong cho vay khoan nao" << endl;

    gotoXY(3, getY() + 2); cout << "TONG QUAN - DI VAY  : --------------------" << endl;
    notEmptyCheck = 0;
    for (auto it : diVay){
        if (it.second > 0){
            notEmptyCheck = 1;
            gotoXY(3, getY());
            cout << " * " << it.first << " cho vay "; color(14); cout << currencyShow(it.second) << endl; resetText();
            tongNo += it.second;
        }
    }
    if (notEmptyCheck == 0) {
        gotoXY(3, getY() + 2);
        cout << "Ban khong vay khoan nao" << endl;
    }
    gotoXY(3, getY() + 2);
    cout << "TONG SO : --------------------------------" << endl;
    gotoXY(3, getY());
    cout << "Tong cho vay : " << setw(25) << right << currencyShow(tongChoVay) << endl;
    gotoXY(3, getY()); 
    cout << "Tong no      : " << setw(25) << right << currencyShow(tongNo) << endl;
}


void QL_VayNo::updateLoansList(QL_GiaoDich& QL_GD){

    Vector<string> tempVectr; //temp vector to store unique loans

    tempVectr.clear(); activeLoans.clear(); string temp_Who; int count = 1;
    //get unique loans
    for (int i = 0; i < tableVN.size(); i++){
        count = 1;
        temp_Who = tableVN[i]->GetWho();
        //check unique
        for (int j = 0; j < tableVN.size(); j++){
            if (temp_Who == tableVN[j]->GetWho() && i != j){
                count++;
            }
        }
        if (count == 1) tempVectr.push_back(temp_Who);
    }

    long long choVay = 0; long long diVay = 0; int cat = 0; int index_GD = 0;
    for (int i = 0; i < tempVectr.size(); i++){
        choVay = 0; diVay = 0; temp_Who = tempVectr[i];
        for (int j = 0; j < tableVN.size(); j++){
            if (temp_Who == tableVN[j]->GetWho()){
                index_GD = searchID(QL_GD.tableGD, tableVN[j]->GetIDGD_VN());
                cat = QL_GD.tableGD[index_GD]->Getcategory();
                switch (cat){
                    case 1 :
                        choVay += QL_GD.tableGD[index_GD]->Getamount();
                        break;
                    case 2:
                        choVay -= QL_GD.tableGD[index_GD]->Getamount();
                        break;
                    case 3:
                        diVay += QL_GD.tableGD[index_GD]->Getamount();
                        break;
                    case 4:
                        diVay -= QL_GD.tableGD[index_GD]->Getamount();
                        break;
                }
            }
        }
    }
    if (choVay > diVay) activeLoans.push_back(temp_Who);
}

int QL_VayNo::getSizeVN() {
    return this->tableVN.size();
}

