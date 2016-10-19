//
// Created by Haoyu Gu on 2016-10-08.
//

#include "LoginUIController.h"
#include "../Utils/headers.h"
#include "../Model/Person/Client.h"

LoginUIController::LoginUIController() {

}

LoginUIController::~LoginUIController() {

}

Person* LoginUIController::login() {
    system("Color 07");
    std::string uid;
    Person *p;
    while (1) {
        std::cout<<"Login:";
        std::cin>>uid;
        std::ifstream in;
        in.open("./Data/"+uid+".uif");
        if (in) {
            in.close();
            p = Person::readFromFile(uid);
            break;
        }
        else {
            std::cout<<"User does not exist. Please contact system administrator."<<std::endl;
        }
    }
    getchar();
    int passwordRetryCount = MAX_LOGIN_PASSWORD_RETRY;
    while (passwordRetryCount >= 0) {
        std::cout<<"Password:";
        std::string pwd;
        char c;
        for (int i=0;i<MAX_USER_PWD_LENGTH;i++) {
            c = getch();
            if (c==13) {  //enter
                break;
            }
            else {
                pwd = pwd+c;
                putch('*');
            }
        }
        if (p->password == pwd) {
            return p;
        }
        else {
            passwordRetryCount--;
            std::cout<<std::endl<<"Password incorrect."<<std::endl;
        }
    }
    if (p->type==Person::PersonType::client) {
        Client *pp = Client::readFromFile(uid);
        pp->setStatus(Person::PersonStatus::blocked);
        pp->writeToFile();
    }
    std::cout<<"Too many attempts."<<std::endl<<"Authorization failed."<<std::endl<<std::endl<<(p->type==Person::PersonType::client?"Due to security policy, your account will be blocked. Please contact your manager for assistance.":"")<<std::endl<<"Application halt."<<std::endl;
    getch();
    exit(-1);
    return NULL;
}