//
// Created by Haoyu Gu on 2016-10-06.
//

#ifndef BANK_CHEQUING_H
#define BANK_CHEQUING_H

#include "Account.h"

class Chequing : public Account {

public:
    Chequing(double, bool);
    ~Chequing();
public:
    bool shouldShowErrorMessgage(double, std::string&);
};


#endif //BANK_CHEQUING_H
