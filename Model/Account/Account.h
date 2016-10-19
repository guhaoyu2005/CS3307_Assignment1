//
// Created by Haoyu Gu on 2016-10-06.
//

#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>

class Account {

public:
    enum AccountType {Chequing, Saving, Unknown};

public:
    Account();
    ~Account();

public:
    double getBalance();
    AccountType getType();
    bool deposit(void*, double, std::string&);
    bool withdraw(void*, double, std::string&);
    bool transfer(void*, void*,Account*, double, double, std::string&);
    bool transferReceive(void*, void*, double, std::string&);
    bool isOpen();
    bool open(std::string&);
    bool close(std::string&);

protected:
    double balance;
    AccountType accountType;
    bool states;
};


#endif //BANK_ACCOUNT_H
