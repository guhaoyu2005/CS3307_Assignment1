//
// Created by Haoyu Gu on 2016-10-06.
//

#ifndef BANK_CLIENT_H
#define BANK_CLIENT_H

#include "Person.h"

class Client : protected Person {
public:
    Client(std::string, std::string);
    ~Client();

public:
    bool writeToFile();

public:
    static Client* readFromFile(std::string);

public:
    bool createAccount(Account::AccountType, std::string&);
    bool deleteAccount(Account::AccountType, std::string&);

    void addTransaction(std::string);

    int getSummaryBalance();

public:
    std::string getUid() { return uid; }

public:
    std::vector<std::string> transactions;
    Chequing *chequing;
    Saving *saving;
};


#endif //BANK_CLIENT_H
