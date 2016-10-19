//
// Created by Haoyu Gu on 2016-10-08.
//

#ifndef CS3307_ASSIGNMENT1_CLIENTUICONTROLLER_H
#define CS3307_ASSIGNMENT1_CLIENTUICONTROLLER_H

#include <string>
#include "../Model/Person/Client.h"

class ClientUIController {

public:
    ClientUIController();
    ~ClientUIController();

public:
    void init(std::string);

private:
    void drawBlockedMenu();
    void drawMainMenu();
    void deposit();
    void withdraw();
    void transfer();
    void viewTransactions();

    void changePassword();

private:
    Client *client;
};


#endif //CS3307_ASSIGNMENT1_CLIENTUICONTROLLER_H
