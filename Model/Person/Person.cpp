//
// Created by Haoyu Gu on 2016-10-06.
//

#include "Person.h"
#include "../../Utils/sharedLib.h"
#include "../../Utils/headers.h"
#include "../../Utils/constants.h"

Person::Person() {
    Logger::sharedInstance().logwt("Person created.");
}

Person::~Person() {

}

Person Person::create(const char *, const char *, personType) {

}
