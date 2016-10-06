//
// Created by Haoyu Gu on 2016-10-06.
//

#include "Account.h"

Account::Account() {
    balance = 0;
    accountType = Account::AccountType::Unknown;
}

Account::~Account() {

}

int Account::getBalance() {
    return balance;
}

Account::AccountType Account::getType() {
    return accountType;
}

bool Account::deposit(int amount, std::string &errMsg) {
    int verify = balance;
    balance+=amount;
    if (balance == verify+amount){
        return true;
    }
    else {
        balance = verify;
        errMsg = "Failed to deposit.";
        return false;
    }
}

bool Account::withdraw(int amount, std::string &errMsg) {
    if (amount<=balance) {
        int verify = balance;
        balance-=amount;
        if (balance == verify-amount && balance>=0)
            return true;
        else {
            errMsg = "Failed to withdraw.";
            balance = verify;
            return false;
        }
    }
    else {
        errMsg = "Failed to withdraw: insufficient funds.";
        return false;
    }
}

bool Account::transfer(Account* destAccount, int amount, std::string &errMsg) {
    if (destAccount) {
        if (balance>= amount) {
            int verifySelf = balance;
            int verifyDest = destAccount->getBalance();
            balance-=amount;
            std::string err;
            bool res = destAccount->deposit(amount, err);
            if (res) {
                if (verifyDest+amount == destAccount->getBalance() && verifySelf-amount == balance && balance>=0) {
                    return true;
                }
                else {
                    errMsg = "Failed to transfer.";
                    return false;
                }
            }
            else {
                errMsg = "Failed to transfer.";
                balance = verifySelf;
                return false;
            }
        }
        else {
            errMsg = "Failed to transfer: insufficient funds.";
            return false;
        }
    }
    else {
        errMsg = "Failed to transfer: invalid target account.";
        return false;
    }
}