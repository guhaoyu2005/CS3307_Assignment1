//
// Created by Haoyu Gu on 2016-10-06.
//

#include "Person.h"
#include "../../Utils/sharedLib.h"
#include "../../Utils/headers.h"
#include "../../Utils/constants.h"

Person::Person() {

}

Person::~Person() {

}

Person* Person::readFromFile(std::string& id) {
    std::ifstream in;
    in.open("./Data/"+id+".uif");
    std::string userId;
    std::string pwd;
    int type;
    in>>userId>>pwd>>type;
    Person *instance = new Person();
    instance->uid = userId;
    instance->password = pwd;
    instance->type = (Person::PersonType)type;
    in.close();
    return instance;
}

bool Person::isExist(std::string& id) {
    std::ifstream in;
    in.open("./Data/"+id+".uif");
    if (!in) {
        return false;
    }
    in.close();
    return true;
}

/*
Person create(std::string& uid, std::string& pwd, Person::personType type) {

}
 */