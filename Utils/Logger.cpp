//
// Created by Haoyu Gu on 2016-10-05.
//

#include "Logger.h"
#include <time.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "sharedLib.h"

Logger::Logger() {
    traceMode = false;
    std::ifstream in;
    in.open("./Data/config.ini");
    if (in) {
        in>>traceMode;
    }
    in.close();
    if (traceMode) {
        logwt("\n\n");
        log("===================================================================");
        log("                     New traceback log begins                      ");
        log("===================================================================");
    }
}

Logger::~Logger() {

}

void Logger::setTraceMode(bool mode) {
    traceMode = mode;
    std::ofstream out;
    out.open("./Data/config.ini");
    out<<mode<<std::endl;
    out.close();
}

void Logger::log(const char* ptString) {
    if (traceMode) {
        std::string s = ptString;
        printToFile(s+"\n");
    }
}

void Logger::logwt(const char* ptString) {
    if (traceMode) {
        char s[1000];
        time_t t = time(NULL);
        struct tm *p = localtime(&t);
        strftime(s, 1000, "%A, %b %d %Y %X", p);
        std::string ss = s;
        printToFile("[" + ss + "]:"+ptString+"\n");
    }
}

void Logger::logwft(const char* file, int line, const char* func, const char* ptString) {
    if (traceMode) {
        char s[1000];
        time_t t = time(NULL);
        struct tm *p = localtime(&t);
        strftime(s, 1000, "%A, %b %d %Y %X", p);
        std::string ss = s;
        printToFile("[" + ss + "]:"+ file + "\" (line " + sharedLib::strFromInt(line) +") function \""+ func +"\" accessed. "+ptString+"\n");
    }
}

void Logger::logwuft(const char* user, const char* file, int line, const char* func, const char* ptString) {
    if (traceMode) {
        char s[1000];
        time_t t = time(NULL);
        struct tm *p = localtime(&t);
        strftime(s, 1000, "%A, %b %d %Y %X", p);
        std::string ss = s;
        printToFile("[" + ss + "][ id: " + user + " ]:In file \""+ file + "\" (line " + sharedLib::strFromInt(line) +") function \""+ func +"\" accessed. "+ptString+"\n");
    }
}

void Logger::printToFile(std::string s) {
    std::ofstream out;
    out.open("tracelog.log", std::ios::app);
    out<<s;
    out.close();
}

std::string Logger::getTimeInLogFormat() {
    char s[1000];
    time_t t = time(NULL);
    struct tm *p = localtime(&t);
    strftime(s, 1000, "[%A, %b %d %Y %X]", p);
    return s;
}



