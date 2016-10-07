//
// Created by Haoyu Gu on 2016-10-06.
//

#include "Account.h"

Account::Account() {
    balance = 0;
    states = 0;
    accountType = Account::AccountType::Unknown;
}

Account::~Account() {

}

int Account::getBalance() {
    return balance;
}

bool Account::open(std::string& errMsg) {
    if (!states) {
        balance = 0;
        states = true;
        return true;
    }
    else {
        errMsg = "Account already exists.";
        return false;
    }
}

bool Account::close(std::string& errMsg) {
    if (states) {
        if (balance==0) {
            states = false;
            return true;
        }
        else {
            errMsg = "Account balance is not 0.";
            return false;
        }
    }
    else {
        errMsg = "Account doesn't exist.";
        return false;
    }
}

bool Account::isOpen() {
    return states;
}

Account::AccountType Account::getType() {
    return accountType;
}

bool Account::deposit(int amount, std::string &errMsg) {
    if (!states) {
        errMsg = "This account doesn't exist.";
        return false;
    }
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
    if (!states) {
        errMsg = "This account doesn't exist.";
        return false;
    }
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
    if (!states) {
        errMsg = "This account doesn't exist.";
        return false;
    }
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