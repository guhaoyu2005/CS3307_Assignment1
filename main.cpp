#include "Utils/headers.h"
#include "Utils/sharedLib.h"
#include "Controller/MainUIController.h"

bool genDefaultAccounts() {
    std::ifstream in;
    std::ofstream out;
    in.open("./Data/manager.uif");
    if (!in) {
        in.close();
        out.open("./Data/manager.uif");
        out<<"manager manager 0 0"<<std::endl;
        out.close();
    }
    else
        in.close();

    in.open("./Data/service.uif");
    if (!in) {
        in.close();
        out.open("./Data/service.uif");
        out<<"service service 2 0"<<std::endl;
        out.close();
    }
    else
        in.close();

    in.open("./Data/manager.uif");
    if (!in) {
        in.close();
        return false;
    }
    else
        in.close();

    in.open("./Data/service.uif");
    if (!in) {
        in.close();
        return false;
    }
    else
        in.close();

    return true;
}

int main() {
    system("mkdir Data");
    if (!genDefaultAccounts()) {
        sharedLib::errorHalt();
    }
    std::cout << "Bank" << std::endl;
    Logger::sharedInstance().setTraceMode(true);
    Logger::sharedInstance().logwt("System initialized.");
    while (1) {
        MainUIController *ui = new MainUIController();
        ui->init();
        delete ui;
        ui = NULL;
    }

/*
    std::string id,pwd,err;
    id = "123456";
    pwd = "1234";
    Client *c1 = new Client(id, pwd);
    c1->createAccount(Account::AccountType::Chequing, err);
    c1->chequing->deposit(c1, 100, err);
    printf("c1: %d\n", c1->chequing->getBalance());
    c1->writeToFile();
    delete c1;
    printf("C1 deleted!\n");
    c1 = Client::readFromFile(id);
    printf("c1: %d\n", c1->chequing->getBalance());
    c1->chequing->deposit(c1, 2134, err);
    printf("c1: %d\n", c1->chequing->getBalance());
    c1->writeToFile();
    delete c1;
    c1 = Client::readFromFile(id);
    for (auto x: c1->transactions)
        printf("%s\n", x.c_str());
*/
    return 0;
}