#include "TietKiem.h"

TietKiem::TietKiem()
{
    this->IDGD_TK = "";
    this->TenKhoanTK = "";
    this->InterestRate = 0;
    this->Term = 0;
    this->Mode = 0;
}

TietKiem::~TietKiem()
{
}

TietKiem::TietKiem(string ID, string tenKhoanTK, float rate, int term, int mode)
{
    this->IDGD_TK = ID;
    this->TenKhoanTK = tenKhoanTK;
    this->InterestRate = rate;
    this->Term = term;
    this->Mode = mode;
}

TietKiem::TietKiem(const TietKiem &TK)
{
    this->IDGD_TK = TK.IDGD_TK;
    this->TenKhoanTK = TK.TenKhoanTK;
    this->InterestRate = TK.InterestRate;
    this->Term = TK.Term;
    this->Mode = TK.Mode;
}

void TietKiem::SetID(string in_ID)
{
    this->IDGD_TK = in_ID;
}
void TietKiem::SetTenKhoanTK(string TenKhoanTK){
    this->TenKhoanTK = TenKhoanTK;
}

void TietKiem::SetInterest(float in_rate)
{
    this->InterestRate = in_rate;
}

void TietKiem::SetTerm(int in_term)
{
    this->Term = in_term;
}

void TietKiem::SetMode(int in_mode)
{
    this->Mode = in_mode;
}

void TietKiem::SetAll(string in_ID, string TenKhoanTK, float in_rate, int in_term, int in_mode)
{
    this->IDGD_TK = in_ID;
    this->TenKhoanTK = TenKhoanTK;
    this->InterestRate = in_rate;
    this->Term = in_term;
    this->Mode = in_mode;
}

string TietKiem::GetIDGD_TK()
{
    return this->IDGD_TK;
}
string TietKiem::GetTenKhoanTK(){
    return this->TenKhoanTK;
}
float TietKiem::GetInterest()
{
    return this->InterestRate;
}
int TietKiem::GetTerm()
{
    return this->Term;
}
int TietKiem::GetMode()
{
    return this->Mode;
}
