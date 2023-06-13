#include "NganHang.h"

NganHang::NganHang(){}

NganHang::~NganHang(){}

NganHang::NganHang(string ID, currency cost){
    this->IDGD_NHG = ID;
    this->cost = cost;
}

NganHang::NganHang(const NganHang& G){
    this->IDGD_NHG = G.IDGD_NHG;
    this->cost = G.cost;
}

void NganHang::SetIDGD_NHG(string ID){
    this->IDGD_NHG = ID;
}

void NganHang::SetCost(currency cost){
    this->cost = cost;
}

void NganHang::SetAll(string ID, currency cost){
    this->IDGD_NHG = ID;
    this->cost = cost;
}

string NganHang::GetIDGD_NHG(){
    return this->IDGD_NHG;
}

currency NganHang::GetCost(){
    return this->cost;
}

