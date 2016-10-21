//
// Created by Haoyu Gu on 2016-10-06.
//

#ifndef BANK_SAVING_H
#define BANK_SAVING_H

#include "Account.h"

class Saving : public Account {

public:
    Saving(double, bool);
    ~Saving();
};


#endif //BANK_SAVING_H
