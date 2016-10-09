//
// Created by Haoyu Gu on 2016-10-05.
//

#include "Logger.h"
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <typeinfo>

Logger::Logger() {
    traceMode = false;
}

Logger::~Logger() {

}

void Logger::setTraceMode(bool mode) {
    traceMode = mode;
}

void Logger::log(const char* ptString) {
    if (traceMode) {
        printf("%s\n", ptString);
    }
}

void Logger::logwt(const char* ptString) {
    if (traceMode) {
        char s[1000];
        time_t t = time(NULL);
        struct tm *p = localtime(&t);
        strftime(s, 1000, "%A, %b %d %Y %X", p);
        printf("[%s]:%s\n", s, ptString);
    }
}

void Logger::logwft(const void *func, const char* ptString) {
    if (traceMode) {

    }
}

std::string Logger::getTimeInLogFormat() {
    char s[1000];
    time_t t = time(NULL);
    struct tm *p = localtime(&t);
    strftime(s, 1000, "[%A, %b %d %Y %X]", p);
    return s;
}



