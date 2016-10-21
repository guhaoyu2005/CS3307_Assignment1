//
// Created by Haoyu Gu on 2016-10-06.
//

#include "Chequing.h"
#include "../../Utils/constants.h"

Chequing::Chequing(double cBalance, bool open) {
    balance = cBalance;
    states = open;
    accountType = Account::AccountType::Chequing;
}

Chequing::~Chequing() {

}

bool Chequing::shouldShowErrorMessgage(double amount, std::string& strMsg) {
    if (balance>=CHEQUING_THRESHOLD_AMOUNT && balance-amount<CHEQUING_THRESHOLD_AMOUNT) {
        strMsg = "The balance on your chequing account will drop below $1000, and a charge of $2.00 will be applied, continue?";
        return true;
    }
    return false;
}