//
// Created by Haoyu Gu on 2016-10-06.
//

#ifndef BANK_SERVICE_H
#define BANK_SERVICE_H

#include "Person.h"

class Service : protected Person {
public:
    Service();
    ~Service();

public:
    void setTracelog(bool);
    bool getTracelog();

public:
    bool writeToFile();

public:
    static Service* readFromFile(std::string);
};


#endif //BANK_SERVICE_H
