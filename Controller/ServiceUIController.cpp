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

void ServiceUIController::clearLogFile() {
    system("cls");
    cout<<"===[<]=============Clear Log File============"<<endl<<endl<<endl;
    cout<<"Do you want to clear log file?"<<endl<<" Caution: All historical log will be erased!"<<endl<<endl;
    cout<<"[1] Continue Anyway"<<endl<<endl<<"[0] Back"<<endl;
    while (1) {
        char cc = getch();
        if (cc=='1') {
            Logger::sharedInstance().resetLogFile();
            cout<<"Success!"<<endl<<"Press any key to continue."<<endl;
            getch();
            break;
        }
        else if (cc=='0') {
            break;
        }
    }
}

void ServiceUIController::drawMainMenu () {
    system("cls");
    cout<<" ===[ ]==============Main Menu================="<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|         [1] Turn "<<(Logger::sharedInstance().traceMode?"off Traceback log           |":"on Traceback log            |")<<endl;
    cout<<"|         [2] Clear Log File                   |"<<endl;
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

void ServiceUIController::drawAutoClearMenu(int size) {
    system("cls");
    cout<<" ===[!]==File System Performance Helper========"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|     Your system tracelog file was too large  |"<<endl;
    cout<<"|     Size: "<<size<<"Byte(s)"<<endl;
    cout<<"|     And it may cause inefficient file system |"<<endl;
    cout<<"|     operation.                               |"<<endl;
    cout<<"|     We do recommend you clear it for the best|"<<endl;
    cout<<"|     performance.                             |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|         [1] Clear and continue               |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|         [0] No, thanks                       |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<" =============================================="<<endl;
    while (1) {
        char cc = getch();
        if (cc=='1') {
            Logger::sharedInstance().resetLogFile();
            break;
        }
        else if (cc=='2') {
            break;
        }
    }
}

void ServiceUIController::init(std::string uid) {
    bool endSession = 0;
    if (!service)
        service = Service::readFromFile(uid);
    if (!service)
        sharedLib::errorHalt();
    system("color 1E");
    if (Logger::sharedInstance().getLogFileSize()>LOGGER_FILE_RECOMMEND_CLEAR_SIZE) {
        drawAutoClearMenu(Logger::sharedInstance().getLogFileSize());
    }
    drawMainMenu();
    while (1) {
        char c= getch();
        switch (c) {
            case '1': {
                service->setTracelog(!service->getTracelog());
                drawMainMenu();
                break;
            }
            case '2': {
                clearLogFile();
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