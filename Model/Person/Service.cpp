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
    Logger::sharedInstance().logwuft(uid.c_str(),__FILE__, __LINE__, __FUNCTION__ ,"");
    Logger::sharedInstance().setTraceMode(tl);
}

bool Service::getTracelog() {
    Logger::sharedInstance().logwuft(uid.c_str(),__FILE__, __LINE__, __FUNCTION__ ,"");
   return Logger::sharedInstance().traceMode;
}

bool Service::writeToFile() {
    Logger::sharedInstance().logwuft(uid.c_str(),__FILE__, __LINE__, __FUNCTION__ ,"");
    std::ofstream out;
    out.open(("./Data/"+uid+".uif").c_str());
    out<<uid<<" "<<password<<" "<<PersonType::service<<" 0"<<std::endl;
    out.close();
    return true;
}

Service* Service::readFromFile(std::string id) {
    Logger::sharedInstance().logwuft(id.c_str(),__FILE__, __LINE__, __FUNCTION__ ,"");
    std::ifstream in;
    in.open("./Data/"+id+".uif");
    std::string userId;
    std::string pwd;
    int type;
    int cStatus;
    in>>userId>>pwd>>type>>cStatus;
    Service *instance = new Service();
    instance->uid = userId;
    instance->password = pwd;
    instance->type = (Person::PersonType)type;
    instance->status = PersonStatus::normal;
    in.close();
    return instance;
}