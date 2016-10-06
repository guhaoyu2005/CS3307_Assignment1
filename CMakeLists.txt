cmake_minimum_required(VERSION 3.6)
project(CS3307_Assignment1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Model/Account/Account.cpp
    Model/Account/Account.h
    Model/Account/Chequing.cpp
    Model/Account/Chequing.h
    Model/Account/Saving.cpp
    Model/Account/Saving.h
    Model/Person/Client.cpp
    Model/Person/Client.h
    Model/Person/Manager.cpp
    Model/Person/Manager.h
    Model/Person/Person.cpp
    Model/Person/Person.h
    Model/Person/Service.cpp
    Model/Person/Service.h
    Utils/constants.h
    Utils/headers.h
    Utils/Logger.cpp
    Utils/Logger.h
    Utils/sharedLib.h
    main.cpp)

add_executable(CS3307_Assignment1 ${SOURCE_FILES})