//
// Created by Haoyu Gu on 2016-10-06.
//

#include "Chequing.h"

Chequing::Chequing(int cBalance, bool open) {
    balance = cBalance;
    states = open;
    accountType = Account::AccountType::Chequing;
}

Chequing::~Chequing() {

}