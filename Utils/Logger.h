//
// Created by Haoyu Gu on 2016-10-05.
//

#ifndef BANK_LOGGER_H
#define BANK_LOGGER_H

#include <string>

class Logger {
public:
    static Logger& sharedInstance() {
        static Logger instance;
        return instance;
    }

public:
    void setTraceMode(bool);
    bool traceMode;

public:
    //log string
    void log(const char*);
    //log with time
    void logwt(const char*);
    //log with function name and time
    void logwft(const char*, int, const char*, const char*);
    //log with username, function name and time
    void logwuft(const char*, const char*, int, const char*, const char*);

    std::string getTimeInLogFormat();
    int getLogFileSize();

public:
    void resetLogFile();

private:
    Logger();
    ~Logger();
    Logger(const Logger&);
    Logger& operator=(const Logger&);

private:
    void printToFile(std::string);
};


#endif //BANK_LOGGER_H
