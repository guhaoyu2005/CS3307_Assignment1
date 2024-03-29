//
// Created by Haoyu Gu on 2016-10-06.
//

#include "Manager.h"
#include "../../Utils/constants.h"
#include "../../Utils/headers.h"
#include "../../Utils/sharedLib.h"

Manager::Manager(std::string id, std::string pwd) {
    uid = id;
    password = pwd;
    status = PersonStatus::normal;
}

Manager::~Manager() {
    clients.clear();
}

std::vector<std::string> Manager::listClients() {
    Logger::sharedInstance().logwuft(uid.c_str(), __FILE__, __LINE__, __FUNCTION__ ,"");
    return clients;
}

bool Manager::createClient(std::string uid, std::string pwd, std::string& errMsg) {
    Logger::sharedInstance().logwuft(uid.c_str(),__FILE__, __LINE__, __FUNCTION__ ,"");
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
    Logger::sharedInstance().logwuft(uid.c_str(),__FILE__, __LINE__, __FUNCTION__ ,"");
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
    Logger::sharedInstance().logwuft(uid.c_str(),__FILE__, __LINE__, __FUNCTION__ ,"");
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

std::vector<std::vector<double>> Manager::listClientAccounts(std::string id, std::string& errMsg) {
    Logger::sharedInstance().logwuft(uid.c_str(),__FILE__, __LINE__, __FUNCTION__ ,"");
    std::ofstream in;
    in.open("./Data/"+uid+".user");
    if (in) {
        in.close();
        Client *client = Client::readFromFile(id);
        std::vector<std::vector<double>> r;
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
    Logger::sharedInstance().logwuft(uid.c_str(),__FILE__, __LINE__, __FUNCTION__ ,"");
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

bool Manager::setClientStatus(std::string id, PersonStatus ss, std::string& errMsg) {
    Logger::sharedInstance().logwuft(uid.c_str(),__FILE__, __LINE__, __FUNCTION__ ,"");
    std::ofstream in;
    in.open("./Data/"+uid+".user");
    if (in) {
        in.close();
        Client *client = Client::readFromFile(id);
        client->setStatus(ss);
        delete client;
        return true;
    }
    else {
        errMsg = "User ID doesn't exist.";
        return false;
    }
}

std::string Manager::getBankSummary() {
    std::string r= "";
    double summaryChequing = 0;
    double summarySaving = 0;
    for (auto i: clients) {
        Client *tc = Client::readFromFile(i);
        summaryChequing+=tc->chequing->getBalance();
        summarySaving+=tc->saving->getBalance();
        delete tc;
    }
    r = "Total funds in bank: " + sharedLib::strFromInt(summaryChequing+summarySaving) +
        "\n Total funds in chequing: " + sharedLib::strFromInt(summaryChequing) +
        "\n   Total funds in saving: " + sharedLib::strFromInt(summarySaving) + "\n";
    return r;
}

bool Manager::writeToFile() {
    Logger::sharedInstance().logwuft(uid.c_str(),__FILE__, __LINE__, __FUNCTION__ ,"");
    std::ofstream out;
    out.open(("./Data/"+uid+".uif").c_str());
    out<<uid<<" "<<password<<" "<<PersonType::manager<<" 0"<<std::endl;
    for (int i=0;i<clients.size();i++)
        out<<clients[i]<<std::endl;
    out.close();
    return true;
}

Manager* Manager::readFromFile(std::string id) {
    Logger::sharedInstance().logwuft(id.c_str(),__FILE__, __LINE__, __FUNCTION__ ,"");
    std::ifstream in;
    in.open(("./Data/"+id+".uif").c_str());
    std::string userId;
    std::string pwd;
    int type;
    int cStatus;
    in>>userId>>pwd>>type>>cStatus;
    if (id == userId && type == PersonType::manager) {
        Manager *instance = new Manager(id, pwd);
        instance->status = PersonStatus::normal;
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
