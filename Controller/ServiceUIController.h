//
// Created by Haoyu Gu on 2016-10-09.
//

#ifndef CS3307_ASSIGNMENT1_SERVICEUICONTROLLER_H
#define CS3307_ASSIGNMENT1_SERVICEUICONTROLLER_H

#include <string>
#include "../Model/Person/Service.h"

class ServiceUIController {

public:
    ServiceUIController();
    ~ServiceUIController();

public:
    void init(std::string);

private:
    void drawMainMenu();
    void clearLogFile();
    void drawAutoClearMenu(int);

private:
    Service *service;
};


#endif //CS3307_ASSIGNMENT1_SERVICEUICONTROLLER_H
