#pragma once
#ifndef VAYNO_H
#define VAYNO_H


#include "GiaoDich.h"
#include "DateTime.h"



class VayNo{
    public:
        VayNo();
        ~VayNo();
        VayNo(string, string);
        VayNo(const VayNo&);

        //các hàm set:
        void SetIDGD_VN(string);
        void SetWho(string);
        void SetAll(string, string);

        //các hàm get:
        string GetIDGD_VN();
        string GetWho();

        //các hàm khác:
        

    private:
        string IDGD_VN;
        string who; /*người thực hiện hành vi*/
};

#endif