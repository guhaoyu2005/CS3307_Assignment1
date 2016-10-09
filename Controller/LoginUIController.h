//
// Created by Haoyu Gu on 2016-10-08.
//

#ifndef CS3307_ASSIGNMENT1_LOGINUICONTROLLER_H
#define CS3307_ASSIGNMENT1_LOGINUICONTROLLER_H

#include "../Model/Person/Person.h"

class LoginUIController {
public:
    LoginUIController();
    ~LoginUIController();

public:
    Person* login();
};


#endif //CS3307_ASSIGNMENT1_LOGINUICONTROLLER_H
