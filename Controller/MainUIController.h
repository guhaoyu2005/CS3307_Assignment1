//
// Created by Haoyu Gu on 2016-10-08.
//

#ifndef CS3307_ASSIGNMENT1_MAINUICONTROLLER_H
#define CS3307_ASSIGNMENT1_MAINUICONTROLLER_H

#include "../Model/Person/Person.h"

class MainUIController {

public:
    MainUIController();
    ~MainUIController();

public:
    void init();

private:
    void loadMainMenu();

private:
    Person *user;
};


#endif //CS3307_ASSIGNMENT1_MAINUICONTROLLER_H
