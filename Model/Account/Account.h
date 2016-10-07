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
    int getBalance();
    AccountType getType();
    bool deposit(int, std::string&);
    bool withdraw(int, std::string&);
    bool transfer(Account*, int, std::string&);
    bool isOpen();
    bool open(std::string&);
    bool close(std::string&);

protected:
    int balance;
    AccountType accountType;
    bool states;
};


#endif //BANK_ACCOUNT_H
