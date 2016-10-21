//
// Created by Haoyu Gu on 2016-10-08.
//

#include "ClientUIController.h"
#include "../Model/Person/Client.h"
#include "../Utils/headers.h"
#include "../Utils/sharedLib.h"

using namespace std;

ClientUIController::ClientUIController() {
    client = NULL;
}

ClientUIController::~ClientUIController() {
    delete client;
}

void ClientUIController::deposit() {
    system("cls");
    cout<<"===[<]==============Deposit==================="<<endl<<endl<<endl;
    double fund = 0;
    while (1) {
        cout<<endl<<"Amount:";
        cin>>fund;
        if (fund>0) {
            break;
        }
        else {
            cout<<"Invalid amount!"<<endl;
        }
    }
    string err;
    while (1) {
        cout<<"To which account?"<<endl<<" Available: "<<(client->chequing->isOpen()?"Chequing":"")<<(client->saving->isOpen()?"  Saving":"")<<endl<<endl;
        cout<<"[1] Chequing"<<endl<<"[2] Saving"<<endl<<endl<<"[0] Back"<<endl;
        char c= getch();
        if (c=='1') {
            if (client->chequing->isOpen()) {
                if (client->chequing->deposit(client, fund, err)) {
                    cout<<"Success!"<<endl<<endl<<"Balance: "<<client->chequing->getBalance()<<endl;
                    getch();
                    break;
                }
                else {
                    cout<<"Failed to deposit funds to your chequing account because "<<err<<endl;
                }
            }
            else {
                cout<<"Cannot deposit funds to your chequing account since its invalid."<<endl;
            }
        }
        else if (c=='2') {
            if (client->saving->isOpen()) {
                if (client->saving->deposit(client, fund, err)) {
                    cout<<"Success!"<<endl<<endl<<"Balance: "<<client->saving->getBalance()<<endl;
                    getch();
                    break;
                }
                else {
                    cout<<"Failed to deposit funds to your saving account because "<<err<<endl;
                }
            }
            else {
                cout<<"Cannot deposit funds to your saving account since its invalid."<<endl;
            }
        }
        else if (c=='0') {
            break;
        }
    }
}

void ClientUIController::withdraw() {
    system("cls");
    cout<<"===[<]=============Withdraw==================="<<endl<<endl<<endl;
    double fund = 0;
    while (1) {
        cout<<endl<<"Amount:";
        cin>>fund;
        if (fund>0) {
            break;
        }
        else {
            cout<<"Invalid amount!"<<endl;
        }
    }
    string err;
    while (1) {
        cout<<"From which account?"<<endl<<" Available: "<<(client->chequing->isOpen()?"Chequing":"")<<(client->saving->isOpen()?"  Saving":"")<<endl<<endl;
        cout<<"[1] Chequing"<<endl<<"[2] Saving"<<endl<<endl<<"[0] Back"<<endl;
        char c= getch();
        if (c=='1') {
            if (client->chequing->isOpen()) {
                bool doWithdraw= false;
                if (client->chequing->shouldShowErrorMessgage(fund, err)) {
                    while (1) {
                        cout<<err<<endl;
                        cout<<"[1] Continue"<<endl<<endl<<"[0] Cancel"<<endl;
                        char ccLevy = getch();
                        if (ccLevy=='1') {
                            fund+=2;
                            doWithdraw = true;
                            break;
                        }
                        else if (ccLevy=='0'){
                            break;
                        }
                    }
                }
                else {
                    doWithdraw = true;
                }
                if (doWithdraw) {
                    if (client->chequing->withdraw(client, fund, err)) {
                        cout<<"Success!"<<endl<<endl<<"Balance: "<<client->chequing->getBalance()<<endl;
                        getch();
                        break;
                    }
                    else {
                        cout<<"Failed to withdraw funds from your chequing account because "<<err<<endl;
                    }
                }
            }
            else {
                cout<<"Cannot withdraw funds from your chequing account since its invalid."<<endl;
            }
        }
        else if (c=='2') {
            if (client->saving->isOpen()) {
                if (client->saving->withdraw(client, fund, err)) {
                    cout<<"Success!"<<endl<<endl<<"Balance: "<<client->saving->getBalance()<<endl;
                    getch();
                    break;
                }
                else {
                    cout<<"Failed to withdraw funds from your saving account because "<<err<<endl;
                }
            }
            else {
                cout<<"Cannot withdraw funds from your saving account since its invalid."<<endl;
            }
        }
        else if (c=='0') {
            break;
        }
    }
}

void ClientUIController::transfer() {
    system("cls");
    cout<<"===[<]=============Transfer==================="<<endl<<endl<<endl;
    double fund = 0;
    while (1) {
        cout<<endl<<"Amount:";
        cin>>fund;
        if (fund>0) {
            break;
        }
        else {
            cout<<"Invalid amount!"<<endl;
        }
    }
    string err;
    bool fromAccountFlag = 0;
    while (1) {
        cout<<"From which account?"<<endl<<" Available: "<<(client->chequing->isOpen()?"Chequing":"")<<(client->saving->isOpen()?"  Saving":"")<<endl<<endl;
        cout<<"[1] Chequing"<<endl<<"[2] Saving"<<endl<<endl<<"[0] Back"<<endl;
        char c= getch();
        if (c=='1') {
            if (client->chequing->isOpen()) {
                bool toWhomFlag = 0;
                while (1) {
                    cout<<"To whom?"<<endl<<endl;
                    cout<<"[1] Self"<<endl<<"[2] Another client"<<endl<<endl<<"[0] Back"<<endl;
                    char cc= getch();
                    if (cc=='1') {
                        while (1) {
                            cout<<"To which account?"<<endl<<" Available: "<<(client->chequing->isOpen()?"Chequing":"")<<(client->saving->isOpen()?"  Saving":"")<<endl<<endl;
                            cout<<"[1] Chequing"<<endl<<"[2] Saving"<<endl<<endl<<"[0] Back"<<endl;
                            char ccc= getch();
                            if (ccc=='1') {
                                cout<<"You cannot transfer funds to same account!"<<endl;
                            }
                            else if (ccc=='2') {
                                bool doWithdraw= false;
                                double fundExtra = 0;
                                if (client->chequing->shouldShowErrorMessgage(fund, err)) {
                                    while (1) {
                                        cout<<err<<endl;
                                        cout<<"[1] Continue"<<endl<<endl<<"[0] Cancel"<<endl;
                                        char ccLevy = getch();
                                        if (ccLevy=='1') {
                                            fundExtra = 2;
                                            doWithdraw = true;
                                            break;
                                        }
                                        else if (ccLevy=='0'){
                                            break;
                                        }
                                    }
                                }
                                else {
                                    doWithdraw = true;
                                }
                                if (doWithdraw) {
                                    if (client->chequing->transfer(client, client, client->saving, fund+fundExtra, fund, err)) {
                                        toWhomFlag = 1;
                                        fromAccountFlag = 1;
                                        cout<<"Success!"<<endl<<endl<<"Balance: "<<client->chequing->getBalance()<<endl;
                                        getch();
                                        break;
                                    }
                                    else {
                                        cout<<"Failed to transfer funds because "<<err<<endl<<endl;
                                    }
                                }
                            }
                            else if (ccc=='0') {
                                break;
                            }
                        }

                    }
                    else if (cc=='2') {
                        bool toWhichClientFlag = 0;
                        while (1) {
                            cout<<"To which client?"<<endl;
                            string destId = "";
                            cin>>destId;
                            if (destId==client->getUid()) {
                                cout<<"You cannot transfer funds to your self in this mode."<<endl<<"You can go back and choose \"self\""<<endl<<endl;
                                continue;
                            }
                            if (Person::isExist(destId)) {
                                if (Person::whichType(destId) == Person::PersonType::client) {
                                    Client *dct = Client::readFromFile(destId);
                                    while (1) {
                                        cout<<"To which account?"<<endl<<" Available: "<<(dct->chequing->isOpen()?"Chequing":"")<<(dct->saving->isOpen()?"  Saving":"")<<endl<<endl;
                                        cout<<"[1] Chequing"<<endl<<"[2] Saving"<<endl<<endl<<"[0] Back"<<endl;
                                        char ccc= getch();
                                        if (ccc=='1') {
                                            double fundExtra = 0;
                                            bool doWithdraw= false;
                                            if (client->chequing->shouldShowErrorMessgage(fund, err)) {
                                                while (1) {
                                                    cout<<err<<endl;
                                                    cout<<"[1] Continue"<<endl<<endl<<"[0] Cancel"<<endl;
                                                    char ccLevy = getch();
                                                    if (ccLevy=='1') {
                                                        fundExtra=2;
                                                        doWithdraw = true;
                                                        break;
                                                    }
                                                    else if (ccLevy=='0'){
                                                        break;
                                                    }
                                                }
                                            }
                                            else {
                                                doWithdraw = true;
                                            }
                                            if (doWithdraw) {
                                                if (client->chequing->transfer(client, dct, dct->chequing, fund+fundExtra, fund, err)) {
                                                    toWhomFlag = 1;
                                                    toWhichClientFlag = 1;
                                                    fromAccountFlag = 1;
                                                    cout << "Success!" << endl << endl << "Balance: "
                                                         << client->chequing->getBalance() << endl;
                                                    getch();
                                                    break;
                                                } else {
                                                    cout << "Failed to transfer funds because " << err << endl << endl;
                                                }
                                            }
                                        }
                                        else if (ccc=='2') {
                                            double fundExtra = 0;
                                            bool doWithdraw= false;
                                            if (client->chequing->shouldShowErrorMessgage(fund, err)) {
                                                while (1) {
                                                    cout<<err<<endl;
                                                    cout<<"[1] Continue"<<endl<<endl<<"[0] Cancel"<<endl;
                                                    char ccLevy = getch();
                                                    if (ccLevy=='1') {
                                                        fundExtra=2;
                                                        doWithdraw = true;
                                                        break;
                                                    }
                                                    else if (ccLevy=='0'){
                                                        break;
                                                    }
                                                }
                                            }
                                            else {
                                                doWithdraw = true;
                                            }
                                            if (doWithdraw) {
                                                if (client->chequing->transfer(client, dct, dct->saving, fund+fundExtra, fund, err)) {
                                                    toWhomFlag = 1;
                                                    toWhichClientFlag = 1;
                                                    fromAccountFlag = 1;
                                                    cout << "Success!" << endl << endl << "Balance: "
                                                         << client->chequing->getBalance() << endl;
                                                    getch();
                                                    break;
                                                } else {
                                                    cout << "Failed to transfer funds because " << err << endl << endl;
                                                }
                                            }
                                        }
                                        else if (ccc=='0') {
                                            toWhichClientFlag = 1;
                                            break;
                                        }
                                    }
                                    delete dct;
                                }
                                else
                                    cout<<"You cannot transfer funds to a "<<(Person::PersonType::manager?"manager":"weird guy")<<endl;
                            }
                            else {
                                cout<<"Client does not exist!"<<endl;
                            }
                            if (toWhichClientFlag)
                                break;
                        }
                    }
                    else if (cc=='0') {
                        break;
                    }
                    if (toWhomFlag)
                        break;
                }
            }
            else {
                cout<<"Cannot withdraw funds from your chequing account since its invalid."<<endl;
            }
        }
        else if (c=='2') {
            if (client->saving->isOpen()) {
                cout<<"To whom?"<<endl<<endl;
                cout<<"[1] Self"<<endl<<"[2] Another client"<<endl<<endl<<"[0] Back"<<endl;
                bool toWhomFlag = 0;
                while (1) {
                    char cc = getch();
                    if (cc == '1') {
                        while (1) {
                            cout << "To which account?" << endl << " Available: "
                                 << (client->chequing->isOpen() ? "Chequing" : "")
                                 << (client->saving->isOpen() ? "  Saving" : "") << endl << endl;
                            cout << "[1] Chequing" << endl << "[2] Saving" << endl << endl << "[0] Back" << endl;
                            char ccc = getch();
                            if (ccc == '1') {
                                double fundExtra = 0;
                                bool doWithdraw= false;
                                if (client->chequing->shouldShowErrorMessgage(fund, err)) {
                                    while (1) {
                                        cout<<err<<endl;
                                        cout<<"[1] Continue"<<endl<<endl<<"[0] Cancel"<<endl;
                                        char ccLevy = getch();
                                        if (ccLevy=='1') {
                                            fundExtra=2;
                                            doWithdraw = true;
                                            break;
                                        }
                                        else if (ccLevy=='0'){
                                            break;
                                        }
                                    }
                                }
                                else {
                                    doWithdraw = true;
                                }
                                if (doWithdraw) {
                                    if (client->saving->transfer(client, client, client->chequing, fund+fundExtra, fund, err)) {
                                        toWhomFlag = 1;
                                        fromAccountFlag = 1;
                                        cout << "Success!" << endl << endl << "Balance: " << client->saving->getBalance()
                                             << endl;
                                        getch();
                                        break;
                                    } else {
                                        cout << "Failed to transfer funds because " << err << endl << endl;
                                    }
                                }
                            } else if (ccc == '2') {
                                cout << "You cannot transfer funds to same account!" << endl;
                            } else if (ccc == '0') {
                                break;
                            }
                        }
                    } else if (cc == '2') {
                        bool toWhichClientFlag = 0;
                        while (1) {
                            cout << "To which client?" << endl;
                            string destId = "";
                            cin >> destId;
                            if (Person::isExist(destId)) {
                                if (Person::whichType(destId) == Person::PersonType::client) {
                                    Client *dct = Client::readFromFile(destId);
                                    while (1) {
                                        cout << "To which account?" << endl << " Available: "
                                             << (dct->chequing->isOpen() ? "Chequing" : "")
                                             << (dct->saving->isOpen() ? "  Saving" : "") << endl << endl;
                                        cout << "[1] Chequing" << endl << "[2] Saving" << endl << endl << "[0] Back"
                                             << endl;
                                        char ccc = getch();
                                        if (ccc == '1') {
                                            double fundExtra = 0;
                                            bool doWithdraw= false;
                                            if (client->chequing->shouldShowErrorMessgage(fund, err)) {
                                                while (1) {
                                                    cout<<err<<endl;
                                                    cout<<"[1] Continue"<<endl<<endl<<"[0] Cancel"<<endl;
                                                    char ccLevy = getch();
                                                    if (ccLevy=='1') {
                                                        fundExtra=2;
                                                        doWithdraw = true;
                                                        break;
                                                    }
                                                    else if (ccLevy=='0'){
                                                        break;
                                                    }
                                                }
                                            }
                                            else {
                                                doWithdraw = true;
                                            }
                                            if (doWithdraw) {
                                                if (client->saving->transfer(client, dct, dct->chequing, fund+fundExtra, fund, err)) {
                                                    toWhomFlag = 1;
                                                    toWhichClientFlag = 1;
                                                    fromAccountFlag = 1;
                                                    cout << "Success!" << endl << endl << "Balance: "
                                                         << client->saving->getBalance() << endl;
                                                    getch();
                                                    break;
                                                } else {
                                                    cout << "Failed to transfer funds because " << err << endl << endl;
                                                }
                                            }
                                        } else if (ccc == '2') {
                                            double fundExtra = 0;
                                            bool doWithdraw= false;
                                            if (client->chequing->shouldShowErrorMessgage(fund, err)) {
                                                while (1) {
                                                    cout<<err<<endl;
                                                    cout<<"[1] Continue"<<endl<<endl<<"[0] Cancel"<<endl;
                                                    char ccLevy = getch();
                                                    if (ccLevy=='1') {
                                                        fundExtra=2;
                                                        doWithdraw = true;
                                                        break;
                                                    }
                                                    else if (ccLevy=='0'){
                                                        break;
                                                    }
                                                }
                                            }
                                            else {
                                                doWithdraw = true;
                                            }
                                            if (doWithdraw) {
                                                if (client->saving->transfer(client, dct, dct->saving, fund+fundExtra, fund, err)) {
                                                    toWhomFlag = 1;
                                                    toWhichClientFlag = 1;
                                                    fromAccountFlag = 1;
                                                    cout << "Success!" << endl << endl << "Balance: "
                                                         << client->saving->getBalance() << endl;
                                                    getch();
                                                    break;
                                                } else {
                                                    cout << "Failed to transfer funds because " << err << endl << endl;
                                                }
                                            }
                                        } else if (ccc == '0') {
                                            toWhichClientFlag = 1;
                                            break;
                                        }
                                    }
                                    delete dct;
                                } else
                                    cout << "You cannot transfer funds to a "
                                         << (Person::PersonType::manager ? "manager" : "weird guy") << endl;
                            } else {
                                cout << "Client does not exist!" << endl;
                            }
                            if (toWhichClientFlag)
                                break;
                        }
                    } else if (cc == '0') {
                        break;
                    }
                    if (toWhomFlag)
                        break;
                }
            }
            else {
                cout<<"Cannot withdraw funds from your saving account since its invalid."<<endl;
            }
        }
        else if (c=='0') {
            break;
        }
        if (fromAccountFlag) {
            break;
        }
    }
}

void ClientUIController::viewTransactions() {
    system("cls");
    cout<<"===[<]=========View Transactions=============="<<endl<<endl<<endl;
    for (auto i: client->transactions) {
        cout<<i<<endl;
    }
    cout<<endl<<"Press any key to continue";
    getch();
}

void ClientUIController::viewBalance() {
    system("cls");
    cout<<"===[<]=========View Balance==================="<<endl<<endl<<endl;
    cout<<"  Total Balance:"<<client->getSummaryBalance()<<endl;
    cout<<"   Chequing:  States: "<<(client->chequing->isOpen()?"Valid":"Invalid")<<"  Balance: "<<client->chequing->getBalance()<<endl;
    cout<<"   Saving:    States: "<<(client->saving->isOpen()?"Valid":"Invalid")<<"  Balance: "<<client->saving->getBalance()<<endl;
    cout<<endl<<"Press any key to continue";
    getch();
}

void ClientUIController::changePassword() {
    system("cls");
    cout<<"===[<]===========Change Password=============="<<endl<<endl<<endl;
    string cpwd, pwd1, pwd2;
    int wrongCount = 0;
    bool finish = false;
    while (1) {
        cout<<"Input your current password:";
        cin>>cpwd;
        if (cpwd == client->getPassword()) {
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
                        client->setPassword(pwd1);
                        if (client->writeToFile()) {
                            cout<<"Success!"<<endl<<"Press any key to continue."<<endl;
                        }
                        else {
                            cout<<"Failed to change password because "<<err<<endl<<"Press any key to continue."<<endl;
                        }
                        finish = true;
                        getch();
                        break;
                    }
                    else {
                        cout<<"Password does not match!"<<endl;
                    }
                }
            }
        }
        else {
            cout<<"Incorrect password, try again."<<endl;
            wrongCount++;
            if (wrongCount==3) {
                cout<<"Too many wrong attempts."<<endl;
                getch();
                finish = true;
                break;
            }
        }
        if (finish)
            break;
    }

}

void ClientUIController::drawMainMenu() {
    system("cls");
    cout<<" ===[ ]==============Main Menu================="<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|         [1] Deposit                          |"<<endl;
    cout<<"|         [2] Withdraw                         |"<<endl;
    cout<<"|         [3] Transfer                         |"<<endl;
    cout<<"|         [4] View Transactions                |"<<endl;
    cout<<"|         [5] Change password                  |"<<endl;
    cout<<"|         [6] View Balance                     |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|         [9] Logoff                           |"<<endl;
    cout<<"|         [0] Quit                             |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<" =============================================="<<endl;
}

void ClientUIController::drawBlockedMenu() {
    system("cls");
    cout<<" ===[ ]==============Main Menu================="<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|    Due to our security policy,               |"<<endl;
    cout<<"|      your account was blocked.               |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|    Please contact your manager               |"<<endl;
    cout<<"|      for assistance.                         |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|         [9] Logoff                           |"<<endl;
    cout<<"|         [0] Quit                             |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<" =============================================="<<endl;
    while (1) {
        char c = getch();
        if (c=='9') {
            break;
        }
        else if (c=='0') {
            exit(0);
        }
    }
}

void ClientUIController::init(std::string uid) {
    if (!client)
        client = Client::readFromFile(uid);
    if (!client) {
        sharedLib::errorHalt();
    }
    system("color 1E");
    if (client->getStatus()==Person::PersonStatus::normal) {
        drawMainMenu();
        bool endSession = 0;
        while (1) {
            char c = getch();
            switch (c) {
                case '1': {
                    deposit();
                    drawMainMenu();
                    break;
                }
                case '2': {
                    withdraw();
                    drawMainMenu();
                    break;
                }
                case '3': {
                    transfer();
                    drawMainMenu();
                    break;
                }
                case '4': {
                    viewTransactions();
                    drawMainMenu();
                    break;
                }
                case '5': {
                    changePassword();
                    drawMainMenu();
                    break;
                }
                case '6': {
                    viewBalance();
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
    else {
        drawBlockedMenu();
    }
}