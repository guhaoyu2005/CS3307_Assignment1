//
// Created by Haoyu Gu on 2016-10-06.
//

#ifndef BANK_PERSON_H
#define BANK_PERSON_H

#include "../../Utils/constants.h"
#include <vector>
#include "../Account/Account.h"
#include "../Account/Chequing.h"
#include "../Account/Saving.h"

class Person {
    enum personType {manager, client, service, unknown};

protected:
    char id[MAX_USER_ID_LENGTH];
    char password[MAX_USER_PWD_LENGTH];
    personType type;
    std::vector<Account> accounts;

public:
    Person create(const char *, const char *, personType);

public:
    Person();
    ~Person();
};


#endif //BANK_PERSON_H
