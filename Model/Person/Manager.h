//
// Created by Haoyu Gu on 2016-10-06.
//

#ifndef BANK_MANAGER_H
#define BANK_MANAGER_H

#include "Person.h"
#include "Client.h"

class Manager : protected Person {
public:
    Manager();
    ~Manager();

private:
    bool createClient(const char *, const char *);
    bool createChquingForClient(Client *);
    bool createSavingForClient(Client *);
    std::vector<Account>& listClientAccounts(Client *);
    bool deleteClientAccount(Client *, int);

};


#endif //BANK_MANAGER_H
