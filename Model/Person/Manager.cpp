//
// Created by Haoyu Gu on 2016-10-06.
//

#include "Manager.h"
#include "../../Utils/constants.h"
#include "../../Utils/headers.h"

Manager::Manager(std::string id, std::string pwd) {
    uid = id;
    password = pwd;
}

Manager::~Manager() {
    clients.clear();
}

std::vector<std::string> Manager::listClients() {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    return clients;
}

bool Manager::createClient(std::string uid, std::string pwd, std::string& errMsg) {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    std::ifstream in;
    in.open("./Data/"+uid+".uid");
    if (!in) {
        Client *newClient = new Client(uid, pwd);
        newClient->writeToFile();
        clients.push_back(uid);
        writeToFile();
        delete newClient;
        return true;
    }
    else {
        in.close();
        errMsg = "User ID already used.";
        return false;
    }
}

bool Manager::createChquingForClient(std::string id, std::string& errMsg) {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    std::ofstream in;
    in.open("./Data/"+uid+".user");
    if (in) {
        in.close();
        Client *client = Client::readFromFile(id);
        bool r = client->createAccount(Account::AccountType::Chequing, errMsg);
        delete client;
        return r;
    }
    else {
        errMsg = "User ID doesn't exist.";
        return false;
    }

}

bool Manager::createSavingForClient(std::string id, std::string& errMsg) {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    std::ofstream in;
    in.open("./Data/"+uid+".user");
    if (in) {
        in.close();
        Client *client = Client::readFromFile(id);
        bool r = client->createAccount(Account::AccountType::Saving, errMsg);
        delete client;
        return r;
    }
    else {
        errMsg = "User ID doesn't exist.";
        return false;
    }
}

std::vector<std::vector<int>> Manager::listClientAccounts(std::string id, std::string& errMsg) {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    std::ofstream in;
    in.open("./Data/"+uid+".user");
    if (in) {
        in.close();
        Client *client = Client::readFromFile(id);
        std::vector<std::vector<int>> r;
        if (client->chequing->isOpen())
            r.push_back({0, client->chequing->getBalance()});
        if (client->saving->isOpen())
            r.push_back({1, client->saving->getBalance()});
        delete client;
        return r;
    }
    else {
        errMsg = "User ID doesn't exist.";
        return {};
    }
}

bool Manager::deleteClientAccount(std::string id, int type, std::string& errMsg) {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    std::ofstream in;
    in.open("./Data/"+uid+".user");
    if (in) {
        in.close();
        Client *client = Client::readFromFile(id);
        bool r= 0;
        if (type == 0)
            r = client->chequing->close(errMsg);
        else
            r = client->saving->close(errMsg);
        delete client;
        return r;
    }
    else {
        errMsg = "User ID doesn't exist.";
        return false;
    }
}

bool Manager::writeToFile() {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    std::ofstream out;
    out.open(("./Data/"+uid+".uif").c_str());
    out<<uid<<" "<<password<<" "<<PersonType::manager<<std::endl;
    for (int i=0;i<clients.size();i++)
        out<<clients[i]<<std::endl;
    out.close();
    return true;
}

Manager* Manager::readFromFile(std::string id) {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    std::ifstream in;
    in.open(("./Data/"+id+".uif").c_str());
    std::string userId;
    std::string pwd;
    int type;
    int clientNum;
    in>>userId>>pwd>>type;
    if (id == userId && type == PersonType::manager) {
        Manager *instance = new Manager(id, pwd);
        std::string client;
        while (!in.eof()) {
            client = "";
            in>>client;
            if (client!="")
                instance->clients.push_back(client);
        }
        in.close();
        return instance;
    }
    else {
        in.close();
        return NULL;
    }
}
