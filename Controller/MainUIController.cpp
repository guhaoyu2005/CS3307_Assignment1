//
// Created by Haoyu Gu on 2016-10-08.
//

#include "MainUIController.h"
#include "../Utils/headers.h"
#include "LoginUIController.h"
#include "ManagerUIController.h"

LoginUIController *loginUICtl;
Person *user;

MainUIController::MainUIController() {
    loginUICtl = new LoginUIController();
}

MainUIController::~MainUIController() {
    delete loginUICtl;
}

void MainUIController::init() {
    system("cls");
    /*
    printf("Welcome to CS3307 Bank System\n");
    user = loginUICtl->login();
    delete loginUICtl;
     */
    std::string s = "manager";
    user = Person::readFromFile(s);
    loadMainMenu();
}

void MainUIController::loadMainMenu() {
    switch (user->type) {
        case Person::PersonType::manager: {
            ManagerUIController *mUiCtl = new ManagerUIController();
            mUiCtl->init(user->uid);
            break;
        }
        case Person::PersonType::client: {
            break;
        }
        case Person::PersonType::service: {
            break;
        }
        default: {
            std::cout<<"Improper user role. Application halt."<<std::endl;
            getch();
            exit(-1);
        }
    }
}