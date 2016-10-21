//
// Created by Haoyu Gu on 2016-10-05.
//

#ifndef BANK_SHAREDLIB_H
#define BANK_SHAREDLIB_H

#include "../Model/Person/Client.h"
#include "../Model/Person/Manager.h"
#include "../Model/Person/Service.h"
#include "headers.h"

class sharedLib {
public:
    static std::string strFromInt(double);
    static void errorHalt();
};



#endif //BANK_SHAREDLIB_H
