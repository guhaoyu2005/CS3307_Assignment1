//
// Created by Haoyu Gu on 2016-10-08.
//

#include "ManagerUIController.h"
#include "../Model/Person/Client.h"
#include "../Model/Person/Manager.h"
#include "../Model/Person/Service.h"
#include "../Utils/headers.h"
#include "../Utils/sharedLib.h"

using namespace std;

ManagerUIController::ManagerUIController() {
    manager = NULL;
}

ManagerUIController::~ManagerUIController() {
    delete manager;
}

void ManagerUIController::showClients() {
    system("cls");
    cout<<"===[<]=============Show Client(s)============="<<endl<<endl<<endl;
    cout<<"  Please input client id(Type \"all\" to show all):";
    string sid = "";
    cin>>sid;
    if (sid=="all") {
        cout<<"Total: "<<manager->listClients().size()<<" Clients."<<endl;
        for (auto i: manager->listClients()) {
            cout<<endl;
            Client *tc = Client::readFromFile(i);
            cout<<"ID: "<<tc->getUid()<<"  Total Balance:"<<tc->getSummaryBalance()<<endl;
            cout<<"   Chequing:  States: "<<(tc->chequing->isOpen()?"Valid":"Invalid")<<"  Balance: "<<tc->chequing->getBalance()<<endl;
            cout<<"   Saving:    States: "<<(tc->saving->isOpen()?"Valid":"Invalid")<<"  Balance: "<<tc->saving->getBalance()<<endl;
            delete tc;
        }
    }
    else {
        if (Person::isExist(sid)) {
            Client *tc = Client::readFromFile(sid);
            cout<<endl<<"ID: "<<tc->getUid()<<"  Total Balance:"<<tc->getSummaryBalance()<<endl;
            cout<<"   Chequing:  States: "<<(tc->chequing->isOpen()?"Valid":"Invalid")<<"  Balance: "<<tc->chequing->getBalance()<<endl;
            cout<<"   Saving:    States: "<<(tc->saving->isOpen()?"Valid":"Invalid")<<"  Balance: "<<tc->saving->getBalance()<<endl;
            delete tc;
        }
        else {
            cout<<"ID: "<<sid<<" does not exist!"<<endl;
        }
    }
    cout<<endl<<"Press any key to continue.";
    getch();
}

void ManagerUIController::createClient() {
    system("cls");
    cout<<"===[<]=============Create Client============="<<endl<<endl<<endl;
    string cid, pwd1, pwd2;
    while (1) {
        cout<<"Client Id(Length>="<< MIN_USER_ID_LENGTH <<"): ";
        cin>>cid;
        if (cid.length()<MIN_USER_ID_LENGTH) {
            cout<<"Client ID is too short."<<"(Need "<< MIN_USER_ID_LENGTH <<", actual "<<cid.length()<<")"<<endl;
        }
        else {
            if (!Person::isExist(cid)) {
                while (1) {
                    cout<<"Password(Length>="<< MIN_USER_PWD_LENGTH <<"): ";
                    cin>>pwd1;
                    if (pwd1.length()<MIN_USER_PWD_LENGTH) {
                        cout<<"Password is too short."<<"(Need "<< MIN_USER_PWD_LENGTH <<", actual "<<pwd1.length()<<")"<<endl;
                    }
                    else {
                        cout<<"Confirm: ";
                        cin>>pwd2;
                        if (pwd1==pwd2) {
                            string err;
                            if (manager->createClient(cid, pwd1, err)) {
                                cout<<"Success!"<<endl<<"Press any key to continue."<<endl;
                            }
                            else {
                                cout<<"Failed to create client because "<<err<<endl<<"Press any key to continue."<<endl;
                            }
                            getch();
                            break;
                        }
                        else {
                            cout<<"Password does not match!"<<endl;
                        }
                    }
                }
                break;
            }
            else {
                cout<<"Client ID already used."<<endl;
            }
        }
    }
}

void ManagerUIController::openAccount() {
    system("cls");
    cout<<"===[<]======Open Account for Client=========="<<endl<<endl<<endl;
    cout<<"Total: "<<manager->listClients().size()<<" Clients."<<endl<<endl;
    for (auto i: manager->listClients()) {
        Client *tc = Client::readFromFile(i);
        cout<<"ID: "<<tc->getUid()<<"  Balance:"<<tc->getSummaryBalance()<<endl;
        delete tc;
    }
    while (1) {
        cout<<endl<<"  Please input client id:";
        string sid = "";
        cin>>sid;
        if (Person::isExist(sid)) {
            Client *tc = Client::readFromFile(sid);
            if (sid=="manager" || sid=="service") {
                cout<<"  This client id does not belong to client group."<<endl<<"Please retry. Press Q to back.";
                char c = getch();
                if (c=='q' || c=='Q')
                    break;
                continue;
            }
            while (1) {
                cout<<"Which account you wanna open?"<<endl<<
                    "Available:"<<(tc->chequing->isOpen()?"-":"Chequing")
                    <<(tc->saving->isOpen()?"-":"  Saving")<<endl;
                cout<<endl<<"[1] Chequing"<<endl<<"[2] Saving"<<endl<<endl<<"[0] Back"<<endl;
                char c = getch();
                string err;
                if (c=='1') {
                    if (tc->createAccount(Account::AccountType::Chequing, err)) {
                        tc->writeToFile();
                        cout<<"Success!"<<endl<<"Press any key to continue.";
                        getch();
                        break;
                    }
                    else {
                        cout<<"Failed to open Chequing account for "<<tc->getUid()<<" because "<<err<<endl;
                    }
                }
                else if (c=='2') {
                    if (tc->createAccount(Account::AccountType::Saving, err)) {
                        tc->writeToFile();
                        cout<<"Success!"<<endl<<"Press any key to continue.";
                        getch();
                        break;
                    }
                    else {
                        cout<<"Failed to open Saving account for "<<tc->getUid()<<" because "<<err<<endl;
                    }
                }
                else if (c=='0')
                    break;
            }
            delete tc;
            break;
        }
        else {
            cout<<"  This client id does not exist"<<endl<<"Please retry. Press Q to back.";
            char c = getch();
            if (c=='q' || c=='Q')
                break;
        }
    }
}

void ManagerUIController::closeAccount() {
    system("cls");
    cout<<"===[<]======Close Account for Client========="<<endl<<endl<<endl;
    cout<<"Total: "<<manager->listClients().size()<<" Clients."<<endl<<endl;
    for (auto i: manager->listClients()) {
        Client *tc = Client::readFromFile(i);
        cout<<"ID: "<<tc->getUid()<<"  Balance:"<<tc->getSummaryBalance()<<endl;
        delete tc;
    }
    while (1) {
        cout<<endl<<"  Please input client id:";
        string sid = "";
        cin>>sid;
        if (Person::isExist(sid)) {
            Client *tc = Client::readFromFile(sid);
            if (sid=="manager" || sid=="service") {
                cout<<"  This client id does not belong to client group."<<endl<<"Please retry. Press Q to back.";
                char c = getch();
                if (c=='q' || c=='Q')
                    break;
                continue;
            }
            while (1) {
                cout<<"Which account you wanna close?"<<endl<<
                    "Available:"<<(tc->chequing->isOpen()?"Chequing":"-")
                    <<(tc->saving->isOpen()?"  Saving":"  -")<<endl;
                cout<<endl<<"[1] Chequing"<<endl<<"[2] Saving"<<endl<<endl<<"[0] Back"<<endl;
                char c = getch();
                string err;
                if (c=='1') {
                    if (tc->deleteAccount(Account::AccountType::Chequing, err)) {
                        tc->writeToFile();
                        cout<<"Success!"<<endl<<"Press any key to continue.";
                        getch();
                        break;
                    }
                    else {
                        cout<<"Failed to close Chequing account for "<<tc->getUid()<<" because "<<err<<endl;
                    }
                }
                else if (c=='2') {
                    if (tc->deleteAccount(Account::AccountType::Saving, err)) {
                        tc->writeToFile();
                        cout<<"Success!"<<endl<<"Press any key to continue.";
                        getch();
                        break;
                    }
                    else {
                        cout<<"Failed to close Saving account for "<<tc->getUid()<<" because "<<err<<endl;
                    }
                }
                else if (c=='0')
                    break;
            }
            delete tc;
            break;
        }
        else {
            cout<<"  This client id does not exist"<<endl<<"Please retry. Press Q to back.";
            char c = getch();
            if (c=='q' || c=='Q')
                break;
        }
    }
}

void ManagerUIController::resetClientPassword() {
    system("cls");
    cout<<"===[<]==========Reset Client Password========"<<endl<<endl<<endl;
    cout<<"Total: "<<manager->listClients().size()<<" Clients."<<endl<<endl;
    for (auto i: manager->listClients()) {
        Client *tc = Client::readFromFile(i);
        cout<<"ID: "<<tc->getUid()<<"  Status:"<<(tc->getStatus()==Person::PersonStatus::normal?"Normal":"Blocked")<<endl;
        delete tc;
    }
    while (1) {
        cout << endl << "  Please input client id:";
        string sid = "";
        cin >> sid;
        if (sid=="manager" || sid=="service") {
            cout<<"  This client id does not belong to client group."<<endl<<"Please retry. Press Q to back.";
            char c = getch();
            if (c=='q' || c=='Q')
                break;
            continue;
        }
        if (Person::isExist(sid)) {
            Client *tc = Client::readFromFile(sid);
            std::string pwd1, pwd2;
            while (1) {
                cout<<"Password(Length>="<< MIN_USER_PWD_LENGTH <<"): ";
                cin>>pwd1;
                if (pwd1.length()<MIN_USER_PWD_LENGTH) {
                    cout<<"Password is too short."<<"(Need "<< MIN_USER_PWD_LENGTH <<", actual "<<pwd1.length()<<")"<<endl;
                }
                else {
                    cout<<"Confirm: ";
                    cin>>pwd2;
                    if (pwd1==pwd2) {
                        string err;
                        tc->setPassword(pwd1);
                        if (tc->writeToFile()) {
                            cout<<"Success!"<<endl<<"Press any key to continue."<<endl;
                        }
                        else {
                            cout<<"Failed to change password because "<<err<<endl<<"Press any key to continue."<<endl;
                        }
                        getch();
                        break;
                    }
                    else {
                        cout<<"Password does not match!"<<endl;
                    }
                }
            }
            delete tc;
            break;
        }
        else {
            cout<<"  This client id does not exist"<<endl<<"Please retry. Press Q to back.";
            char c = getch();
            if (c=='q' || c=='Q')
                break;
        }
    }
}

void ManagerUIController::getBankSummary() {
    system("cls");
    cout<<"===[<]==========Show Bank Summary============"<<endl<<endl<<endl;
    cout<<manager->getBankSummary()<<endl;
    cout<<endl<<"Press any key to continue."<<endl;
    getch();
}

void ManagerUIController::setClientStatus() {
    system("cls");
    cout<<"===[<]==========Set Client Status============"<<endl<<endl<<endl;
    cout<<"Total: "<<manager->listClients().size()<<" Clients."<<endl<<endl;
    for (auto i: manager->listClients()) {
        Client *tc = Client::readFromFile(i);
        cout<<"ID: "<<tc->getUid()<<"  Status:"<<(tc->getStatus()==Person::PersonStatus::normal?"Normal":"Blocked")<<endl;
        delete tc;
    }
    while (1) {
        cout << endl << "  Please input client id:";
        string sid = "";
        cin>>sid;
        if (Person::isExist(sid)) {
            Client *tc = Client::readFromFile(sid);
            if (sid=="manager" || sid=="service") {
                cout<<"  This client id does not belong to client group."<<endl<<"Please retry. Press Q to back.";
                char c = getch();
                if (c=='q' || c=='Q')
                    break;
                continue;
            }
            while (1) {
                cout <<"Which status you wanna set for this client?"<<endl
                     <<"[1] Normal"<<endl<<"[2] Block"<<endl<<endl<<"[0] Back"<<endl;
                char c = getch();
                string err;
                if (c=='1') {
                    tc->setStatus(Person::PersonStatus::normal);
                    tc->writeToFile();
                    cout<<"Success!"<<endl<<"Press any key to continue.";
                    getch();
                    break;
                }
                else if (c=='2') {
                    tc->setStatus(Person::PersonStatus::blocked);
                    tc->writeToFile();
                    cout<<"Success!"<<endl<<"Press any key to continue.";
                    getch();
                    break;
                }
                else if (c=='0')
                    break;
            }
            delete tc;
            break;
        }
        else {
            cout<<"  This client id does not exist"<<endl<<"Please retry. Press Q to back.";
            char c = getch();
            if (c=='q' || c=='Q')
                break;
        }
    }
}

void ManagerUIController::drawMainMenu () {
    system("cls");
    cout<<" ===[ ]==============Main Menu================="<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|         [1] Show Client(s)                   |"<<endl;
    cout<<"|         [2] Create Client                    |"<<endl;
    cout<<"|         [3] Open Account For Client          |"<<endl;
    cout<<"|         [4] Close Account For Client         |"<<endl;
    cout<<"|         [5] Set Client Status                |"<<endl;
    cout<<"|         [6] Show Bank Summary                |"<<endl;
    cout<<"|         [7] Reset Client Password            |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|         [9] Logoff                           |"<<endl;
    cout<<"|         [0] Quit                             |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<" =============================================="<<endl;
}

void ManagerUIController::init(std::string uid) {
    if (!manager)
        manager = Manager::readFromFile(uid);
    if (!manager) {
        sharedLib::errorHalt();
    }
    system("color 1E");
    drawMainMenu();
    bool endSession = 0;
    while (1) {
        char c = getch();
        switch (c) {
            case '1': {
                showClients();
                drawMainMenu();
                break;
            }
            case '2': {
                createClient();
                drawMainMenu();
                break;
            }
            case '3': {
                openAccount();
                drawMainMenu();
                break;
            }
            case '4': {
                closeAccount();
                drawMainMenu();
                break;
            }
            case '5': {
                setClientStatus();
                drawMainMenu();
                break;
            }
            case '6': {
                getBankSummary();
                drawMainMenu();
                break;
            }
            case '7': {
                resetClientPassword();
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