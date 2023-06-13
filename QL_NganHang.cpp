#include "QL_NganHang.h"


QL_NganHang::QL_NganHang(){

}

QL_NganHang::~QL_NganHang(){
    for(int i=0; i<tableNH.size();i++){
        delete tableNH[i];
    }
    tableNH.clear();
}


void QL_NganHang::AddNH(QL_GiaoDich& QL_GD){
    NganHang *nh = new NganHang; string temp_ID = QL_GD.tableGD[QL_GD.tableGD.size()-1]->GetID();
    temp_ID = QL_GD.next_ID(temp_ID, GiaoDich::max_ID_digit - 1);
    nh->SetIDGD_NHG(temp_ID);
    cout << "- Phi giao dich : ";
    currency cost; cin >> cost;
    nh->SetCost(cost);
    tableNH.push_back(nh);
    //delete nh;
}

void QL_NganHang::AddNH(string ID, currency cost){
    NganHang *temp_NH = new NganHang;
    temp_NH->SetAll(ID, cost);
    tableNH.push_back(temp_NH);
    //delete temp_NH;
}

void QL_NganHang::DeleteNH(int pos, QL_GiaoDich& QL_GD, QL_VayNo& QL_VN, QL_TietKiem& QL_TK){
    int GD_index = searchID(QL_GD.tableGD, tableNH[pos]->GetIDGD_NHG());
    QL_GD.DeleteGD(GD_index, *this, QL_VN, QL_TK);
}
void QL_NganHang::Load(const string& userPath){
    NH_FILE = "DATA/" + userPath + "_" + NH_FILE;
    string temp_IDGD_NH, line, temp_string;
    int temp_Cost;

    ifstream file;
    file.open(NH_FILE);
    while (!file.eof()){ 
        NganHang *temp_NHG = new NganHang;
        getline(file, line);
        stringstream ss(line);
        getline(ss, temp_IDGD_NH, '|');
        if (temp_IDGD_NH == "F_END")
        {
            break;
        }
        getline(ss, temp_string, '|');
        temp_Cost = stoi(temp_string);
        temp_NHG->SetAll(temp_IDGD_NH, temp_Cost);
        tableNH.push_back(temp_NHG);
    }

    file.close();
}

void QL_NganHang::Save(){
    ofstream file;
    file.open(NH_FILE);
    int sizeNH = tableNH.size();
    for (int i = 0; i < sizeNH; i++){
        file << tableNH[i]->GetIDGD_NHG() <<'|'<< tableNH[i]->GetCost() <<endl;
    }
    file << "F_END";
    file.close();

}

