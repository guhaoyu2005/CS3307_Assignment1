//
// Created by Haoyu Gu on 2016-10-07.
//

#include "sharedLib.h"
#include <sstream>
#include <conio.h>

std::string sharedLib::strFromInt(int n) {
    std::ostringstream ss;
    ss << n;
    return ss.str();
}

void sharedLib::errorHalt() {
    system("clear");
    printf("Critical error! Application halt!\n");
    getchar();
    exit(-1);
}