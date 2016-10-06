#include "Utils/headers.h"
#include "Utils/sharedLib.h"

int main() {
    std::cout << "Bank" << std::endl;
    Logger::sharedInstance().setTraceMode(true);
    Logger::sharedInstance().logwt("System initialized.");

    return 0;
}