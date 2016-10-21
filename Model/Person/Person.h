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
    enum PersonStatus {normal = 0, blocked};

public:
    std::string uid;
    std::string password;
    PersonType type;
    PersonStatus status;


public:
    Person();
    ~Person();

public:
    static Person* readFromFile(std::string);
    static bool isExist(std::string);
    static PersonType whichType(std::string);

};


#endif //BANK_PERSON_H
