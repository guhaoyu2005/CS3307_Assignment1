//
// Created by Haoyu Gu on 2016-10-06.
//

#include "Manager.h"
#include "../../Utils/constants.h"
#include "../../Utils/headers.h"

Manager::Manager(std::string& id, std::string& pwd, int clientNum) {
    uid = id;
    password = pwd;
    clientCount = clientNum;
}

Manager::~Manager() {

}

std::vector<std::string> Manager::listClients() {
    std::ifstream in;
    in.open(("/Data/"+uid+".user").c_str());
    std::vector<std::string> clients;
    std::string userId;
    std::string pwd;
    int type;
    int clientNum;
    in>>userId>>pwd>>type;
    in>>clientNum;
    std::string client;
    while (!in.eof()) {
        client = "";
        in>>client;
        clients.push_back(client);
    }
    in.close();
    return clients;
}

bool Manager::createClient(std::string& uid, std::string& pwd) {

}

bool Manager::createChquingForClient(Client *) {

}

bool Manager::createSavingForClient(Client *) {

}

std::vector<Account>& Manager::listClientAccounts(Client *) {

}

bool Manager::deleteClientAccount(Client *, int) {

}

bool Manager::writeToFile() {

}

Manager* Manager::readFromFile(std::string& id) {
    std::ifstream in;
    in.open(("/Data/"+id+".user").c_str());
    std::string userId;
    std::string pwd;
    int type;
    int clientNum;
    in>>userId>>pwd>>type;
    in>>clientNum;
    in.close();
    if (id == userId && type == Person::PersonType::manager) {
        Manager *instance = new Manager(id, pwd, clientNum);
        return instance;
    }
    else {
        return NULL;
    }
}
