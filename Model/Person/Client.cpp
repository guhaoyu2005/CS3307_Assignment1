//
// Created by Haoyu Gu on 2016-10-06.
//

#include "Client.h"
#include "../../Utils/headers.h"

Client::Client(std::string id, std::string pwd) {
    uid = id;
    password = pwd;
    chequing = new Chequing(0, 0);
    saving = new Saving(0, 0);
}

Client::~Client() {
    transactions.clear();
    delete chequing;
    delete saving;
}

bool Client::createAccount(Account::AccountType t, std::string& errMsg) {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    std::string err;
    switch (t) {
        case Account::AccountType::Chequing: {
            bool res = chequing->open(err);
            if (res)
                return true;
            else {
                errMsg = err;
                return false;
            }
        }
        case Account::AccountType::Saving: {
            bool res = saving->open(err);
            if (res)
                return true;
            else {
                errMsg = err;
                return false;
            }
        }
    }
    errMsg = "Unknown error.";
    return false;
}

bool Client::deleteAccount(Account::AccountType t, std::string& errMsg) {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    std::string err;
    switch (t) {
        case Account::AccountType::Chequing: {
            bool res = chequing->close(err);
            if (res)
                return true;
            else {
                errMsg = err;
                return false;
            }
        }
        case Account::AccountType::Saving: {
            bool res = saving->close(err);
            if (res)
                return true;
            else {
                errMsg = err;
                return false;
            }
        }
    }
    errMsg = "Unknown error.";
    return false;
}

bool Client::writeToFile() {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    std::ofstream out;
    out.open("./Data/"+uid+".uif");
    out<<uid<<" "<<password<<" "<<PersonType::client<<std::endl;
    out<<Account::AccountType::Chequing<<" "<<chequing->isOpen()<<" "<<chequing->getBalance()<<std::endl;
    out<<Account::AccountType::Saving<<" "<<saving->isOpen()<<" "<<saving->getBalance()<<std::endl;
    for (int i=0;i<transactions.size();i++) {
        out<<transactions[i]<<std::endl;
    }
    out.close();
    return true;
}

void Client::addTransaction(std::string tr) {
    Logger::sharedInstance().logwuft(uid.c_str(),__FILE__, __LINE__, __FUNCTION__ ,"");
    if (tr!="")
        transactions.push_back(tr);
}

double Client::getSummaryBalance() {
    Logger::sharedInstance().logwuft(uid.c_str(),__FILE__, __LINE__, __FUNCTION__ ,"");
    return (chequing->isOpen()?chequing->getBalance():0)+(saving->isOpen()?saving->getBalance():0);
}

Client* Client::readFromFile(std::string id) {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    std::ifstream in;
    in.open("./Data/"+id+".uif");
    std::string userId;
    std::string pwd;
    int type;
    in>>userId>>pwd>>type;
    Client *instance = new Client(userId, pwd);
    for (int i=0;i<2;i++) {
        int typeA;
        bool state = 0;
        double bal = 0;
        in>>typeA>>state>>bal;
        std::string err;
        if (typeA == Account::AccountType::Chequing) {
            instance->chequing = new Chequing(state?bal:0, state);
        }
        else {
            instance->saving = new Saving(state?bal:0, state);
        }
    }
    std::string tr = "";
    std::getline(in, tr);
    while (!in.eof()) {
        tr = "";
        std::getline(in, tr);
        instance->addTransaction(tr);
    }
    in.close();
    return instance;
}