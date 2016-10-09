//
// Created by Haoyu Gu on 2016-10-09.
//

#include "ServiceUIController.h"
#include "../Utils/headers.h"
#include "../Utils/sharedLib.h"

using namespace std;

ServiceUIController::ServiceUIController() {
    service = NULL;
}

ServiceUIController::~ServiceUIController() {
    delete service;
}

void ServiceUIController::drawMainMenu () {
    system("cls");
    cout<<" ===[ ]==============Main Menu================="<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|         [1] Turn "<<(Logger::sharedInstance().traceMode?"off Traceback log           |":"on Traceback log            |")<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|         [9] Logoff                           |"<<endl;
    cout<<"|         [0] Quit                             |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<" =============================================="<<endl;
}

void ServiceUIController::init(std::string uid) {
    bool endSession = 0;
    if (!service)
        service = Service::readFromFile(uid);
    if (!service)
        sharedLib::errorHalt();
    system("color 1E");
    drawMainMenu();
    while (1) {
        char c= getch();
        switch (c) {
            case '1': {
                service->setTracelog(!service->getTracelog());
                drawMainMenu();
                break;
            }
            case '9': {
                endSession = 1;
                break;
            }
            case '0': {
                exit(0);
            }
        }
        if (endSession)
            break;
    }
}