cmake_minimum_required(VERSION 2.8) 

PROJECT(ResourcePackageTest)

INCLUDE_DIRECTORIES(../include) 
INCLUDE_DIRECTORIES(../../platform/include/)
link_directories("/home/lwh/workspace/platform/libs")

ADD_EXECUTABLE(Package package.cpp)  
TARGET_LINK_LIBRARIES(Package ResourcePackage mlibc dl)

ADD_EXECUTABLE(upackage upackage.cpp)  
TARGET_LINK_LIBRARIES(upackage ResourcePackage mlibc dl)
