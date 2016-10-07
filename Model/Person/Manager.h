//
// Created by Haoyu Gu on 2016-10-06.
//

#ifndef BANK_MANAGER_H
#define BANK_MANAGER_H

#include "Person.h"
#include "Client.h"

class Manager : protected Person {
public:
    Manager(std::string& , std::string&, int);
    ~Manager();
public:
    std::vector<std::string> listClients();
    bool createClient(std::string& , std::string&);
    bool createChquingForClient(Client *);
    bool createSavingForClient(Client *);
    std::vector<Account>& listClientAccounts(Client *);
    bool deleteClientAccount(Client *, int);

public:
    bool writeToFile();

public:
    static Manager* readFromFile(std::string&);

private:
    int clientCount;

};


#endif //BANK_MANAGER_H
