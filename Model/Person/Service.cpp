//
// Created by Haoyu Gu on 2016-10-06.
//

#include "Service.h"
#include "../../Utils/headers.h"
#include "../../Utils/sharedLib.h"

Service::Service() {
}

Service::~Service() {
}

void Service::setTracelog(bool tl) {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    Logger::sharedInstance().setTraceMode(tl);
}

bool Service::getTracelog() {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
   return Logger::sharedInstance().traceMode;
}

bool Service::writeToFile() {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    std::ofstream out;
    out.open(("./Data/"+uid+".uif").c_str());
    out<<uid<<" "<<password<<" "<<PersonType::service<<std::endl;
    out.close();
    return true;
}

Service* Service::readFromFile(std::string id) {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    std::ifstream in;
    in.open("./Data/"+id+".uif");
    std::string userId;
    std::string pwd;
    int type;
    in>>userId>>pwd>>type;
    Service *instance = new Service();
    instance->uid = userId;
    instance->password = pwd;
    instance->type = (Person::PersonType)type;
    in.close();
    return instance;
}