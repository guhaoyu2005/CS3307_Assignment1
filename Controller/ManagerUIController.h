//
// Created by Haoyu Gu on 2016-10-08.
//

#ifndef CS3307_ASSIGNMENT1_MANAGERUICONTROLLER_H
#define CS3307_ASSIGNMENT1_MANAGERUICONTROLLER_H

#include <string>
#include "../Model/Person/Manager.h"

class ManagerUIController {
public:
    ManagerUIController();
    ~ManagerUIController();

public:
    void init(std::string);
private:
    void drawMainMenu();
    void showClients();
    void createClient();
    void openAccount();
    void closeAccount();
    void getBankSummary();
    void setClientStatus();
    void resetClientPassword();

private:
    Manager *manager;
};


#endif //CS3307_ASSIGNMENT1_MANAGERUICONTROLLER_H
