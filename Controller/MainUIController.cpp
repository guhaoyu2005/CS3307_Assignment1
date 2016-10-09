//
// Created by Haoyu Gu on 2016-10-08.
//

#include "MainUIController.h"
#include "../Utils/headers.h"
#include "LoginUIController.h"
#include "ManagerUIController.h"
#include "ClientUIController.h"
#include "ServiceUIController.h"

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
            ServiceUIController *sUiCtl = new ServiceUIController();
            sUiCtl->init(user->uid);
            delete sUiCtl;
            break;
        }
        default: {
            std::cout<<"Improper user role. Application halt."<<std::endl;
            getch();
            exit(-1);
        }
    }
}