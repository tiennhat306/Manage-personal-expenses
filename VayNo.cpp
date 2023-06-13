#include "VayNo.h"

VayNo::VayNo(){}

VayNo::~VayNo(){}

VayNo::VayNo(string ID, string who){
    this->IDGD_VN = ID;
    this->who =  who;
}

VayNo::VayNo(const VayNo& G){
    this->IDGD_VN= G.IDGD_VN;
    this->who = G.who;
}

void VayNo::SetIDGD_VN(string ID){
    this->IDGD_VN = ID;
}


void VayNo::SetWho(string Who){
    this->who = Who;
}



void VayNo::SetAll(string ID, string Who){
    this->IDGD_VN = ID;
    this->who = Who;
}

string VayNo::GetIDGD_VN(){
    return this->IDGD_VN;
}


string VayNo::GetWho(){
    return this->who;
}
