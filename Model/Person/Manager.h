//
// Created by Haoyu Gu on 2016-10-06.
//

#ifndef BANK_MANAGER_H
#define BANK_MANAGER_H

#include "Person.h"
#include "Client.h"

class Manager : protected Person {
public:
    Manager(std::string& , std::string&);
    ~Manager();
public:
    std::vector<std::string> listClients();
    bool createClient(std::string&, std::string&, std::string&);
    bool createChquingForClient(std::string&, std::string&);
    bool createSavingForClient(std::string&, std::string&);
    std::vector<std::vector<int>> listClientAccounts(std::string&, std::string&);
    bool deleteClientAccount(std::string&, int, std::string&);

public:
    bool writeToFile();

public:
    static Manager* readFromFile(std::string&);

private:
    std::vector<std::string> clients;
};


#endif //BANK_MANAGER_H
