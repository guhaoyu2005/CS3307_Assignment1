#include "Utils/headers.h"
#include "Utils/sharedLib.h"

int main() {
    system("mkdir Data");
    std::cout << "Bank" << std::endl;
    Logger::sharedInstance().setTraceMode(true);
    Logger::sharedInstance().logwt("System initialized.");

    Chequing *a = new Chequing(100, 1);
    Saving *b = new Saving(100, 1);
    std::string aaa;
    a->transfer(b, 100, aaa);
    printf("a: %d   b: %d  \n", a->getBalance(), b->getBalance());
    b->deposit(124, aaa);
    printf("b: %d\n", b->getBalance());
    b->withdraw(1000, aaa);
    printf("b: %d\n%s\n", b->getBalance(), aaa.c_str());

    std::string id,pwd,err;
    id = "123456";
    pwd = "1234";
    Client *c1 = new Client(id, pwd);
    c1->createAccount(Account::AccountType::Chequing, err);
    c1->chequing->deposit(100, err);
    printf("c1: %d\n", c1->chequing->getBalance());
    c1->addTransaction("Deposit 100, Balance 100");
    c1->writeToFile();
    delete c1;
    printf("C1 deleted!\n");
    c1 = Client::readFromFile(id);
    printf("c1: %d\n", c1->chequing->getBalance());
    c1->chequing->deposit(2134, err);
    c1->addTransaction("Deposit 2134, Balance 2234");
    printf("c1: %d\n", c1->chequing->getBalance());
    c1->writeToFile();
    delete c1;
    c1 = Client::readFromFile(id);
    for (auto x: c1->transactions)
        printf("%s\n", x.c_str());

    return 0;
}