//
// Created by Haoyu Gu on 2016-10-06.
//

#ifndef BANK_PERSON_H
#define BANK_PERSON_H

#include "../../Utils/constants.h"
#include <vector>
#include <string>
#include "../Account/Account.h"
#include "../Account/Chequing.h"
#include "../Account/Saving.h"

class Person {

public:
    enum PersonType {manager = 0, client, service, unknown};

public:
    std::string uid;
    std::string password;
    PersonType type;

public:
    Person();
    ~Person();
};


#endif //BANK_PERSON_H
