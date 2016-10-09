//
// Created by Haoyu Gu on 2016-10-08.
//

#include "MainUIController.h"
#include "../Utils/headers.h"
#include "LoginUIController.h"
#include "ManagerUIController.h"
#include "ClientUIController.h"

LoginUIController *loginUICtl;


MainUIController::MainUIController() {
    loginUICtl = new LoginUIController();
    user = NULL;
}

MainUIController::~MainUIController() {
    delete loginUICtl;
    delete user;
}

void MainUIController::init() {
    system("cls");

    printf("Welcome to CS3307 Bank System\n");
    user = loginUICtl->login();
    loadMainMenu();
    delete loginUICtl;
     /*
    std::string s = "123456";
    user = Person::readFromFile(s);
    loadMainMenu();
      */
}

void MainUIController::loadMainMenu() {
    switch (user->type) {
        case Person::PersonType::manager: {
            ManagerUIController *mUiCtl = new ManagerUIController();
            mUiCtl->init(user->uid);
            delete mUiCtl;
            break;
        }
        case Person::PersonType::client: {
            ClientUIController *cUiCtl = new ClientUIController();
            cUiCtl->init(user->uid);
            delete cUiCtl;
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