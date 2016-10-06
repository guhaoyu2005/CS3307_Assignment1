#include "Utils/headers.h"
#include "Utils/sharedLib.h"

int main() {
    std::cout << "Bank" << std::endl;
    Logger::sharedInstance().setTraceMode(true);
    Logger::sharedInstance().logwt("System initialized.");

    Chequing *a = new Chequing(100);
    Saving *b = new Saving(100);
    std::string aaa;
    a->transfer(b, 100, aaa);
    printf("a: %d   b: %d  \n", a->getBalance(), b->getBalance());
    b->deposit(124, aaa);
    printf("b: %d\n", b->getBalance());
    b->withdraw(1000, aaa);
    printf("b: %d\n%s\n", b->getBalance(), aaa.c_str());

    return 0;
}