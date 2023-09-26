#include "../include/No.h"

No::No(int idNo){
    this->idNo = idNo;
}


void No::setProxNo(No *no){
    this->proxNo = no;
}

No * No::getProxNo(){
    return this->proxNo;
}