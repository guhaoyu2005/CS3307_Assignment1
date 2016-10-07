//
// Created by Haoyu Gu on 2016-10-06.
//

#include "Saving.h"

Saving::Saving(int sBalance, bool open) {
    balance = sBalance;
    states = open;
    accountType = Account::AccountType::Saving;
}

Saving::~Saving() {

}