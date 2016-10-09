//
// Created by Haoyu Gu on 2016-10-08.
//

#ifndef CS3307_ASSIGNMENT1_MANAGERUICONTROLLER_H
#define CS3307_ASSIGNMENT1_MANAGERUICONTROLLER_H

#include <string>

class ManagerUIController {
public:
    ManagerUIController();
    ~ManagerUIController();

public:
    void init(std::string);
private:
    void showClients();
    void createClient();
    void openAccount();
    void closeAccount();
};


#endif //CS3307_ASSIGNMENT1_MANAGERUICONTROLLER_H
