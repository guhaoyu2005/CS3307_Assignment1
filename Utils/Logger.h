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
    void logwft(const void*, const char*);

    std::string getTimeInLogFormat();

private:
    Logger();
    ~Logger();
    Logger(const Logger&);
    Logger& operator=(const Logger&);
};


#endif //BANK_LOGGER_H
